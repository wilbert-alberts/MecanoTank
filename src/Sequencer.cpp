// #include "FreeRTOS.h"
#include <Arduino.h>
#include <freertos/timers.h>

#include "ServoGroup.hpp"
#include "Tracer.hpp"

#include "Sequencer.hpp"

Sequencer::Sequencer(ServoGroup *sg) : sequenceCounter(0), running(false), period(sg->getPeriod()), sequence(sg->getSequence())
{
    Serial.print("Creating Controller with period: ");
    Serial.println(period);
    tracer = new Tracer(sg);
}

Sequencer::Sequencer(double p) : sequenceCounter(0), running(false), period(p), sequence(new std::vector<Block*>())
{
    Serial.println("Creating controller with deprecated constructor");
    tracer = nullptr;
}

Sequencer::~Sequencer() {}

void Sequencer::executeSequence()
{
    std::for_each(sequence->begin(), sequence->end(), [](Block *block)
                  { block->calculate(); });
    if (tracer != nullptr)
        tracer->captureTrace(sequenceCounter);
    sequenceCounter++;
}

void Sequencer::hasStarted()
{
    running = true;
}

void Sequencer::hasStopped()
{
    running = false;
}

Tracer *Sequencer::getTracer()
{
    return tracer;
}