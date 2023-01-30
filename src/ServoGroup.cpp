#include "ServoGroup.hpp"

ServoGroup::ServoGroup(double p) : period(p) {}
double ServoGroup::getPeriod()
{
    return period;
}
