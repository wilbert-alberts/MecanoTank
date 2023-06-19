#ifndef __PERIODICTASK_HPP__
#define __PERIODICTASK_HPP__

#include "FreeRTOS.h"
#include "task.h"

#include <string>

class PeriodicTask
{
public:
    PeriodicTask(double servoPeriod, const std::string& taskName);
    virtual ~PeriodicTask() {};
    void startExecutorTask();
    void stop();

protected:
    virtual void tick();

private:
    static void staticTaskFunction(void *params);
    void taskFunction();

    const std::string& taskName;
    double servoPeriod;
    bool running;
    bool stopped;

    TaskHandle_t tickTask;
};

#endif