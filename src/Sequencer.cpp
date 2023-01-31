// #include "FreeRTOS.h"
#include <Arduino.h>
#include <freertos/timers.h>

#include "ServoGroup.hpp"
#include "Tracer.hpp"

#include "Sequencer.hpp"

Sequencer::Sequencer(ServoGroup *sg) : running(false), period(sg->getPeriod()), sequence(sg->getSequence())
{
    Serial.print("Creating Controller with period: ");
    Serial.println(period);
    tracer = new Tracer("tracer", sg->getPeriod(), sg);
}

Sequencer::Sequencer(double p, std::vector<Block *> *s) : running(false), period(p), sequence(s)
{
    Serial.println("Creating controller with deprecated constructor");
    tracer = new Tracer("tracer", p, s);
}

Sequencer::Sequencer(double p) : running(false), period(p), sequence(new std::vector<Block *>())
{
    Serial.println("Creating controller with empty sequence.");
    tracer = new Tracer("tracer", p, sequence);
}

Sequencer::~Sequencer() {}

void Sequencer::executeSequence()
{
    std::for_each(sequence->begin(), sequence->end(), [](Block *block)
                  { block->calculate(); });
    tracer->calculate();
}

void Sequencer::hasStarted()
{
    running = true;
}

void Sequencer::hasStopped()
{
    running = false;
}

const Tracer* Sequencer::getTracer() {
    return tracer;
}