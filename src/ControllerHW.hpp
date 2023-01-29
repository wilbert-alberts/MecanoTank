#ifndef __CONTROLLERHW_HPP__
#define __CONTROLLERHW_HPP__

#include <vector>
#include <freertos/semphr.h>
#include <driver/timer.h>

#include "Controller.hpp"
#include "Block.hpp"

class ControllerHW: public Controller
{
public:
    ControllerHW(double period);
    ControllerHW(double period, std::vector<Block *>* sequence);
    virtual ~ControllerHW();

    virtual void start();
    virtual void stop();

private:
    static void initHWTimer(double period);
    static void initTask(ControllerHW* me);
    static void tickTask(void*);
    static timer_config_t* timerConfig;
    static TaskHandle_t tickTaskHandle;
    static SemaphoreHandle_t semaphore;
};

#endif