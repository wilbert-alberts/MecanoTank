// #include "FreeRTOS.h"
#include <Arduino.h>
#include <freertos/timers.h>

#include "SequencerSW.hpp"
#include "Debugpin.hpp"

SequencerSW::SequencerSW(ServoGroup *sg) : Sequencer(sg)
{
}

SequencerSW::SequencerSW(double p, std::vector<Block *> *s) : Sequencer(p, s)
{
}

SequencerSW::SequencerSW(double p) : Sequencer(p)
{
}

SequencerSW::~SequencerSW() {}

void SequencerSW::tmrTickStatic(TimerHandle_t timerHandle)
{
    SequencerSW *obj = static_cast<SequencerSW *>(pvTimerGetTimerID(timerHandle));
    obj->tick();
}

void SequencerSW::tick()
{
    static int v = 0;
    digitalWrite(DEBUGPIN, v);
    v = 1 - v;

    executeSequence();

    TickType_t now = xTaskGetTickCount();
    TickType_t expiresAt = xTimerGetExpiryTime(tmrHandle);
    uint32_t remainingTime = expiresAt - now;
    Serial.print("Remaining Time: ");
    Serial.println(remainingTime);
}

void SequencerSW::start()
{
    int periodInMs = (int)(period * 1000.0);
    Serial.print("Starting controller with period in ms: ");
    Serial.println(periodInMs);
    tmrHandle = xTimerCreate("TmrController",
                             pdMS_TO_TICKS(periodInMs),
                             true,
                             this,
                             SequencerSW::tmrTickStatic);
    xTimerStart(tmrHandle, pdMS_TO_TICKS(3 * periodInMs));
    hasStarted();
}

void SequencerSW::stop()
{
    xTimerStop(tmrHandle, pdMS_TO_TICKS(1000));
    hasStopped();
}