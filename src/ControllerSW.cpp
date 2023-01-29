// #include "FreeRTOS.h"
#include <Arduino.h>
#include <freertos/timers.h>

#include "ControllerSW.hpp"

ControllerSW::ControllerSW(double p, std::vector<Block *> *s) : Controller(p,s){}


ControllerSW::ControllerSW(double p) : Controller(p)
{
}

ControllerSW::~ControllerSW() {}

void ControllerSW::tmrTickStatic(TimerHandle_t timerHandle)
{
    ControllerSW *obj = static_cast<ControllerSW*>(pvTimerGetTimerID(timerHandle));
    obj->tick();
}

void ControllerSW::tick()
{
    static int v = 0;
    digitalWrite(25, v);
    v = 1 - v;

    executeSequence();

    TickType_t now = xTaskGetTickCount();
    TickType_t expiresAt = xTimerGetExpiryTime(tmrHandle);
    uint32_t remainingTime = expiresAt - now;
    Serial.print("Remaining Time: ");
    Serial.println(remainingTime);
}

void ControllerSW::start()
{
    int periodInMs = (int)(period * 1000.0);
    Serial.print("Starting controller with period in ms: ");
    Serial.println(periodInMs);
    tmrHandle = xTimerCreate("TmrController",
                             pdMS_TO_TICKS(periodInMs),
                             true,
                             this,
                             ControllerSW::tmrTickStatic);
    xTimerStart(tmrHandle, pdMS_TO_TICKS(3 * periodInMs));
    hasStarted();
}

void ControllerSW::stop()
{
    xTimerStop(tmrHandle, pdMS_TO_TICKS(1000));
    hasStopped();
}