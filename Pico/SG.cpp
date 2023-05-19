
#include "SG.hpp"
#include "BL.hpp"

ServoGroup::ServoGroup(const std::string& n, double p)
: name(n)
, period(p) 
, counter(0)
{}

const std::string& ServoGroup::getName()
{
    // Serial.println("ServoGroup::getPeriod()");
    return name;
}

double ServoGroup::getPeriod()
{
    // Serial.println("ServoGroup::getPeriod()");
    return period;
}

int64_t ServoGroup::getCounter()
{
    // Serial.println("ServoGroup::getPeriod()");
    return counter;
}

void ServoGroup::executeSequence()
{
    for (auto b: sequence) {
        b->calculate();
    }

    counter++;
}
