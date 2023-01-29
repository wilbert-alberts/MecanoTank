#ifndef __CONTROLLER_HPP__
#define __CONTROLLER_HPP__

#include <freertos/timers.h>
#include <vector>
#include "Block.hpp"

class Controller
{
public:
    Controller(double period);
    Controller(double period, std::vector<Block *>* sequence);
    virtual ~Controller();

    virtual void start() = 0;
    virtual void stop() = 0;

protected:
    void hasStarted();
    void hasStopped();
    void executeSequence();
    bool running;
    double period;
    std::vector<Block *>* sequence;
};

#endif