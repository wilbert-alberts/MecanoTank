/* Scheduler include files. */
#include <Arduino.h>

/* Library includes. */
#include <stdio.h>

#include "ABSensorBlock.hpp"

#include <list>
#include <algorithm>

std::list<ABSensorBlock *> ABSensorBlock::abSensors;

ABSensorBlock::ABSensorBlock(uint8_t pa, uint8_t pb) : pinA(pa), pinB(pb), currentA(0), currentB(0), position(0)
{
    pinMode(pa, INPUT);
    pinMode(pb, INPUT);

    currentA = digitalRead(pinA);
    currentB = digitalRead(pinB);
    position = 0;
    attachInterrupt(digitalPinToInterrupt(pa), ABSensorBlock::irq_any, CHANGE);
    attachInterrupt(digitalPinToInterrupt(pb), ABSensorBlock::irq_any, CHANGE);
    ABSensorBlock::abSensors.push_back(this);
}

ABSensorBlock::~ABSensorBlock()
{
    ABSensorBlock::abSensors.remove(this);
}

void ABSensorBlock::resetPosition()
{
    position = 0;
}

int64_t ABSensorBlock::getPosition() {
    return position;
}

void ABSensorBlock::pinChanged()
{
    uint8_t newA = digitalRead(pinA);
    uint8_t newB = digitalRead(pinB);

    // Capture state
    uint8_t state = (currentA << 3) | (newA << 2) | (currentB << 1) | (newB);

    /*
          aold       anew    bold    bnew
    0       0         0       0       0           0
    1       0         0       0       1           -1
    2       0         0       1       0           +1
    3       0         0       1       1           0
    4       0         1       0       0           +1
    5       0         1       0       1           err
    6       0         1       1       0           err
    7       0         1       1       1           -1
    8       1         0       0       0           -1
    9       1         0       0       1           err
    10      1         0       1       0           err
    11      1         0       1       1           +1
    12      1         1       0       0           0
    13      1         1       0       1           +1
    14      1         1       1       0           -1
    15      1         1       1       1           0

    */
    // Process new state
    switch (state)
    {
    case 0:
    case 3:
    case 12:
    case 15:
        // No change
        break;
    case 1:
    case 7:
    case 8:
    case 14:
        position--;
        break;
    case 2:
    case 4:
    case 11:
    case 13:
        position++;
    case 5:
    case 6:
    case 9:
    case 10:
        // Error transition
        break;
    }

    // Update AB values
    currentA = newA;
    currentB = newB;
}

// void ABSensorBlock::irq_any(uint gpio, uint32_t events)
void ABSensorBlock::irq_any()
{
    std::for_each(ABSensorBlock::abSensors.begin(), ABSensorBlock::abSensors.end(), [=](ABSensorBlock *s)
                  { s->pinChanged(); });
}
