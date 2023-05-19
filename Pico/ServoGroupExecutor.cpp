#include "ServoGroupExecutor.hpp"

#include "pico/stdlib.h"

#define LED_PIN 4

ServoGroupExecutor::ServoGroupExecutor(ServoGroup *sg)
    : PeriodicTask(sg->getPeriod(), sg->getName()), servoGroup(sg)
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

}

void ServoGroupExecutor::tick()
{
    static uint l = 1;

    servoGroup->executeSequence();
    gpio_put(LED_PIN, l);
    l = 1 - l;
}
