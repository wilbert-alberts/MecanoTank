
#include "SG.hpp"
#include "BL.hpp"

ServoGroup::ServoGroup(const std::string& n, double p)
: CompositeBlock(n, std::vector<CompositeBlock::BlockPtr>())
, counter(0)
, period(p) 
{}

ServoGroup::~ServoGroup()
{}

const std::string& ServoGroup::getName()
{
    // Serial.println("ServoGroup::getPeriod()");
    return getBlockName();
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
    for (auto b: blocks) {
        b->calculate();
    }

    counter++;
}
