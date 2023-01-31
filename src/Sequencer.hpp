#ifndef __SEQUENCER_HPP__
#define __SEQUENCER_HPP__

#include <freertos/timers.h>
#include <vector>

class Tracer;
class ServoGroup;
class Block;

class Sequencer
{
public:
    Sequencer(ServoGroup* sg);
    Sequencer(double period);
    Sequencer(double period, std::vector<Block *>* sequence);
    virtual ~Sequencer();

    virtual void start() = 0;
    virtual void stop() = 0;

    const Tracer* getTracer();
    
protected:
    
    void hasStarted();
    void hasStopped();
    void executeSequence();
    bool running;
    double period;
    std::vector<Block *>* sequence;
    Tracer* tracer;
};

#endif