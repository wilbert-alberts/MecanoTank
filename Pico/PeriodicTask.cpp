#include "FreeRTOS.h"
#include "timers.h"

#include <iostream>

#include "PeriodicTask.hpp"

void PeriodicTask::staticTaskFunction(void *params)
{
    PeriodicTask *seq = static_cast<PeriodicTask *>(params);
    seq->taskFunction();
}

void PeriodicTask::taskFunction()
{

    TickType_t xLastWakeTime;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();
    running = true;
    while (!stopped)
    {

        // Perform action here.
        tick();
        // Wait for the next cycle.
        xTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000 * servoPeriod));
    }
    running=false;

    // Wait until being killed
    while(1);
}

void PeriodicTask::tick()
{
    // std::cout << "tick" << std::endl;
}

PeriodicTask::PeriodicTask(double sp, const std::string& tn)
    : taskName(tn)
    , servoPeriod(sp)
    , running(false)
    , stopped(false)
    , tickTask(nullptr)
{
}

void PeriodicTask::startExecutorTask()
{
    BaseType_t r = xTaskCreate(PeriodicTask::staticTaskFunction,
                "Sequencer",
                10240,
                this,
                1,
                &tickTask);
    if (r != pdPASS) 
        printf("xTaskCreate failed.");
}

void PeriodicTask::stop() {
    stopped = true;
    while (running);
    vTaskDelete(tickTask);
    stopped = false;
}
