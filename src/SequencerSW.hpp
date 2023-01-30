#ifndef __SEQUENCERSW_HPP__
#define __SEQUENCERSW_HPP__

#include <vector>
#include <freertos/timers.h>

#include "Sequencer.hpp"
#include "Block.hpp"

class SequencerSW: public Sequencer
{
public:
    SequencerSW(ServoGroup* sg);
    SequencerSW(double period);
    SequencerSW(double period, std::vector<Block *>* sequence);
    virtual ~SequencerSW();

    virtual void start();
    virtual void stop();

private:
    void tick();
    static void tmrTickStatic(TimerHandle_t params);

    TimerHandle_t tmrHandle;
    TickType_t remainingTime;
};

#endif