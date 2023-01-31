// #include "FreeRTOS.h"

#include <Arduino.h>

#include "Block.hpp"
#include "ServoGroup.hpp"

#include "SequencerHW.hpp"
#include "Debugpin.hpp"

timer_config_t *SequencerHW::timerConfig = nullptr;
SemaphoreHandle_t SequencerHW::semaphore;
TaskHandle_t SequencerHW::tickTaskHandle;

void IRAM_ATTR timer_group0_isr(void *para)
{
    uint32_t intr_status = TIMERG0.int_st_timers.val;
    if (intr_status & BIT(TIMER_0))
    {
        TIMERG0.int_clr_timers.t0 = 1;
        TIMERG0.hw_timer[TIMER_0].config.alarm_en = TIMER_ALARM_EN;
        SemaphoreHandle_t sem = (SemaphoreHandle_t)para;
        xSemaphoreGiveFromISR(sem, nullptr);
    }
}

SequencerHW::SequencerHW(ServoGroup* sg) : Sequencer(sg)
{
    initTask(this);
    initHWTimer(sg->getPeriod());
}
SequencerHW::SequencerHW(double period) : Sequencer(period)
{
    initTask(this);
    initHWTimer(period);
}

SequencerHW::~SequencerHW() {}

void SequencerHW::initHWTimer(double period)
{
    if (SequencerHW::timerConfig == nullptr)
    {
        SequencerHW::timerConfig = new timer_config_t;
        SequencerHW::timerConfig->alarm_en = TIMER_ALARM_EN;
        SequencerHW::timerConfig->counter_en = TIMER_PAUSE;
        SequencerHW::timerConfig->counter_dir = TIMER_COUNT_UP;
        SequencerHW::timerConfig->auto_reload = TIMER_AUTORELOAD_EN;
        /*
                clock is 80 Mhz = 80.000Khz = 80.000.000 hz
                Let clock tick at 1 Mhz, divider of 80.
                Means that 1 second 1.000.0000 ticks
                1000 clock tick is 1 ms
                1 clock tick is 1 us
        */
        SequencerHW::timerConfig->divider = 80;

        timer_init(TIMER_GROUP_0, TIMER_0, SequencerHW::timerConfig);
        timer_set_counter_value(TIMER_GROUP_0, TIMER_0, 0x00000000ULL);

        uint64_t timerScale = TIMER_BASE_CLK / SequencerHW::timerConfig->divider;
        uint64_t alarmValue = (uint64_t)(period * timerScale);

        /* Configure the alarm value and the interrupt on alarm. */
        timer_set_alarm_value(TIMER_GROUP_0, TIMER_0, alarmValue);
        timer_enable_intr(TIMER_GROUP_0, TIMER_0);
        timer_isr_register(TIMER_GROUP_0, TIMER_0, timer_group0_isr,
                           (void *)SequencerHW::semaphore, ESP_INTR_FLAG_IRAM, NULL);
    }
    else
    {
        Serial.println("Error: can have at most 1 instance of ControllerHW");
    }
}

void SequencerHW::initTask(SequencerHW *me)
{
    SequencerHW::semaphore = xSemaphoreCreateBinary();
    BaseType_t r = xTaskCreate(SequencerHW::tickTask,
                               "tickTask",
                               2048,
                               me,
                               1,
                               &tickTaskHandle);
    if (r != pdPASS)
    {
        Serial.println("Unable to initTickTask");
    }
    else
    {
        Serial.println("tickTask initialized.");
    }
}

void SequencerHW::tickTask(void *me)
{
    static int v = 0;
    SequencerHW *obj = (SequencerHW *)me;
    TickType_t timeout = (TickType_t)pdMS_TO_TICKS(1000 * 3 * obj->period);
    uint64_t computationTime;
    while (1)
    {
        if (xSemaphoreTake(SequencerHW::semaphore, timeout) == pdTRUE)
        {
            digitalWrite(DEBUGPIN, v);
            v = 1 - v;
            obj->executeSequence();
            timer_get_counter_value(TIMER_GROUP_0, TIMER_0, &computationTime);
            // Serial.print("Duration: "); Serial.println(computationTime);
        }
        else
        {
            Serial.println("tickTask semTake failed.");
        }
    }
}

void SequencerHW::start()
{
    timer_set_counter_value(TIMER_GROUP_0, TIMER_0, 0x00000000ULL);
    timer_start(TIMER_GROUP_0, TIMER_0);
    hasStarted();
}

void SequencerHW::stop()
{
    timer_pause(TIMER_GROUP_0, TIMER_0);
    hasStopped();
}
