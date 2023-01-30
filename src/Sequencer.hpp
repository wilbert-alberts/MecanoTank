#ifndef __SEQUENCER_HPP__
#define __SEQUENCER_HPP__

#include <freertos/timers.h>
#include <vector>

#include "Block.hpp"
#include "ServoGroup.hpp"

class Sequencer
{
public:
    Sequencer(ServoGroup* sg);
    Sequencer(double period);
    Sequencer(double period, std::vector<Block *>* sequence);
    virtual ~Sequencer();

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