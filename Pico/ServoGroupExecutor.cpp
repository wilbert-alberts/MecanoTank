#include "ServoGroupExecutor.hpp"

#include "pico/stdlib.h"
#include "HSI.hpp"


ServoGroupExecutor::ServoGroupExecutor(ServoGroup *sg)
    : PeriodicTask(sg->getPeriod(), sg->getName()), servoGroup(sg)
{
    gpio_init(PIN_OUT_DEBUG);
    gpio_set_dir(PIN_OUT_DEBUG, GPIO_OUT);

}

void ServoGroupExecutor::tick()
{
    static uint l = 1;

    gpio_put(PIN_OUT_DEBUG, 1);
    servoGroup->executeSequence();
    
    gpio_put(PIN_OUT_DEBUG, 0);
    l = 1 - l;
}
