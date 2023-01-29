#ifndef __CONTROLLERSW_HPP__
#define __CONTROLLERSW_HPP__

#include <vector>
#include <freertos/timers.h>

#include "Controller.hpp"
#include "Block.hpp"

class ControllerSW: public Controller
{
public:
    ControllerSW(double period);
    ControllerSW(double period, std::vector<Block *>* sequence);
    virtual ~ControllerSW();

    virtual void start();
    virtual void stop();

private:
    void tick();
    static void tmrTickStatic(TimerHandle_t params);

    TimerHandle_t tmrHandle;
    TickType_t remainingTime;
};

#endif