// #include "FreeRTOS.h"
#include <Arduino.h>
#include <freertos/timers.h>

#include "Sequencer.hpp"

Sequencer::Sequencer(ServoGroup* sg): running(false), period(sg->getPeriod()), sequence(sg->getSequence()){

}

Sequencer::Sequencer(double p, std::vector<Block *> *s) : running(false), period(p), sequence(s)
{
    Serial.print("Period: ");
    Serial.println(period);
}

Sequencer::Sequencer(double p) : running(false), period(p), sequence(new std::vector<Block *>())
{
    Serial.println("Creating controller with empty sequence.");
}

Sequencer::~Sequencer() {}

void Sequencer::executeSequence()
{
    std::for_each(sequence->begin(), sequence->end(), [](Block *block)
                  { block->calculate(); });
}

void Sequencer::hasStarted()
{
    running = true;
}

void Sequencer::hasStopped()
{
    running = false;
}