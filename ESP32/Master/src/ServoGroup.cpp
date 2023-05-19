#include  <Arduino.h>

#include "ServoGroup.hpp"

ServoGroup::ServoGroup(double p) : period(p) 
{}

double ServoGroup::getPeriod()
{
    // Serial.println("ServoGroup::getPeriod()");
    return period;
}
