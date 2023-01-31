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
    virtual ~Sequencer();

    virtual void start() = 0;
    virtual void stop() = 0;

    Tracer* getTracer();
    
protected:
    void hasStarted();
    void hasStopped();
    void executeSequence();
    uint64_t sequenceCounter;
    bool running;
    double period;
    std::vector<Block *>* sequence;
    Tracer* tracer;
};

#endif