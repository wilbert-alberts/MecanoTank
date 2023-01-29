// #include "FreeRTOS.h"
#include <Arduino.h>
#include <freertos/timers.h>

#include "Controller.hpp"

Controller::Controller(double p, std::vector<Block *> *s) : running(false), period(p), sequence(s)
{
    Serial.print("Period: ");
    Serial.println(period);
}

Controller::Controller(double p) : running(false), period(p), sequence(new std::vector<Block *>())
{
    Serial.println("Creating controller with empty sequence.");
}

Controller::~Controller() {}

void Controller::executeSequence()
{
    std::for_each(sequence->begin(), sequence->end(), [](Block *block)
                  { block->calculate(); });
}

void Controller::hasStarted()
{
    running = true;
}

void Controller::hasStopped()
{
    running = false;
}