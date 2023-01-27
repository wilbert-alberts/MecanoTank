#ifndef __CONTROLLER_HPP__
#define __CONTROLLER_HPP__

#include <freertos/timers.h>
#include <vector>
#include "Block.hpp"

class Controller
{
public:
    Controller(double period, std::vector<Block *>* sequence);
    virtual ~Controller();

    void start();
    void stop();

private:
    void tick();
    static void tmrTickStatic(TimerHandle_t params);

    bool running = false;
    double period;
    TimerHandle_t tmrHandle;
    TickType_t remainingTime;
    std::vector<Block *>* sequence;
};

#endif