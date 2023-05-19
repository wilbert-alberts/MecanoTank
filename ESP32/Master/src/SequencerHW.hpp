#ifndef __SEQUENCERHW_HPP__
#define __SEQUENCERHW_HPP__

#include <vector>
#include <freertos/semphr.h>
#include <driver/timer.h>

#include "Sequencer.hpp"
#include "Block.hpp"

class SequencerHW: public Sequencer
{
public:
    SequencerHW(ServoGroup* sg);
    SequencerHW(double period);
    SequencerHW(double period, std::vector<Block *>* sequence);
    virtual ~SequencerHW();

    virtual void start();
    virtual void stop();

private:
    static void initHWTimer(double period);
    static void initTask(SequencerHW* me);
    static void tickTask(void*);
    static timer_config_t* timerConfig;
    static TaskHandle_t tickTaskHandle;
    static SemaphoreHandle_t semaphore;
};

#endif