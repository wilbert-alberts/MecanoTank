#include "ServoGroupExecutor.hpp"

ServoGroupExecutor::ServoGroupExecutor(ServoGroup *sg)
    : PeriodicTask(sg->getPeriod(), sg->getName()), servoGroup(sg)
{
}

void ServoGroupExecutor::tick()
{
    servoGroup->executeSequence();
}
