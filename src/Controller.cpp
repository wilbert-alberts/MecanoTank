// #include "FreeRTOS.h"
#include <Arduino.h>
#include <freertos/timers.h>

#include "Controller.hpp"

Controller::Controller(double p, std::vector<Block *> *s): period(p), sequence(s) {

}

Controller::~Controller() {}

void Controller::tmrTickStatic(TimerHandle_t params)
{
    Controller *obj = static_cast<Controller *>(params);
    obj->tick();
}

void Controller::tick()
{
    // std::for_each(sequence->begin(), sequence->end(), [](Block *block)
    //               { block->calculate(); });

    remainingTime = xTimerGetExpiryTime(tmrHandle) - xTaskGetTickCount();
    Serial.print("Remaining Time: ");
    Serial.println(remainingTime);
}

void Controller::start()
{
    running = true;
    int periodInMs = (int)(period*1000.0);
    tmrHandle = xTimerCreate("TmrController",
                             pdMS_TO_TICKS(periodInMs),
                             true,
                             this,
                             Controller::tmrTickStatic);
    xTimerStart(tmrHandle, pdMS_TO_TICKS(3*periodInMs));
}

void Controller::stop()
{
    xTimerStop(tmrHandle, pdMS_TO_TICKS(1000));
    running = false;
}