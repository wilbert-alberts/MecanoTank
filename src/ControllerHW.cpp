// #include "FreeRTOS.h"

#include <Arduino.h>
#include "ControllerHW.hpp"
#include "Debugpin.hpp"

timer_config_t *ControllerHW::timerConfig = nullptr;
SemaphoreHandle_t ControllerHW::semaphore;
TaskHandle_t ControllerHW::tickTaskHandle;

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

ControllerHW::ControllerHW(double period) : Controller(period)
{
    initTask(this);
    initHWTimer(period);
}

ControllerHW::ControllerHW(double period, std::vector<Block *> *sequence) : Controller(period, sequence)
{
    initTask(this);
    initHWTimer(period);
}

ControllerHW::~ControllerHW() {}

void ControllerHW::initHWTimer(double period)
{
    if (ControllerHW::timerConfig == nullptr)
    {
        ControllerHW::timerConfig = new timer_config_t;
        ControllerHW::timerConfig->alarm_en = TIMER_ALARM_EN;
        ControllerHW::timerConfig->counter_en = TIMER_PAUSE;
        ControllerHW::timerConfig->counter_dir = TIMER_COUNT_UP;
        ControllerHW::timerConfig->auto_reload = TIMER_AUTORELOAD_EN;
        /*
                clock is 80 Mhz = 80.000Khz = 80.000.000 hz
                Let clock tick at 1 Mhz, divider of 80.
                Means that 1 second 1.000.0000 ticks
                1000 clock tick is 1 ms
                1 clock tick is 1 us
        */
        ControllerHW::timerConfig->divider = 80;

        timer_init(TIMER_GROUP_0, TIMER_0, ControllerHW::timerConfig);
        timer_set_counter_value(TIMER_GROUP_0, TIMER_0, 0x00000000ULL);

        uint64_t timerScale = TIMER_BASE_CLK / ControllerHW::timerConfig->divider;
        uint64_t alarmValue = (uint64_t)(period * timerScale);

        /* Configure the alarm value and the interrupt on alarm. */
        timer_set_alarm_value(TIMER_GROUP_0, TIMER_0, alarmValue);
        timer_enable_intr(TIMER_GROUP_0, TIMER_0);
        timer_isr_register(TIMER_GROUP_0, TIMER_0, timer_group0_isr,
                           (void *)ControllerHW::semaphore, ESP_INTR_FLAG_IRAM, NULL);
    }
    else
    {
        Serial.println("Error: can have at most 1 instance of ControllerHW");
    }
}

void ControllerHW::initTask(ControllerHW *me)
{
    ControllerHW::semaphore = xSemaphoreCreateBinary();
    BaseType_t r = xTaskCreate(ControllerHW::tickTask,
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

void ControllerHW::tickTask(void *me)
{
    static int v = 0;
    ControllerHW *obj = (ControllerHW *)me;
    TickType_t timeout = (TickType_t)pdMS_TO_TICKS(1000 * 3 * obj->period);
    uint64_t computationTime;
    while (1)
    {
        if (xSemaphoreTake(ControllerHW::semaphore, timeout) == pdTRUE)
        {
            digitalWrite(DEBUGPIN, v);
            v = 1 - v;
            obj->executeSequence();
            timer_get_counter_value(TIMER_GROUP_0, TIMER_0, &computationTime);
            Serial.print("Duration: "); Serial.println(computationTime);
        }
        else
        {
            Serial.println("tickTask semTake failed.");
        }
    }
}

void ControllerHW::start()
{
    timer_set_counter_value(TIMER_GROUP_0, TIMER_0, 0x00000000ULL);
    timer_start(TIMER_GROUP_0, TIMER_0);
    hasStarted();
}

void ControllerHW::stop()
{
    timer_pause(TIMER_GROUP_0, TIMER_0);
    hasStopped();
}
