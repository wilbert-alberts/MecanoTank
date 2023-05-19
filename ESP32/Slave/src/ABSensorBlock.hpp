#ifndef __ABSENSORBLOCK_HPP__
#define __ABSENSORBLOCK_HPP__

/* Scheduler include files. */
#include "FreeRTOS.h"

/* Library includes. */
#include <stdio.h>

#include <list>
#include <algorithm>

class ABSensorBlock 
{
public:
    ABSensorBlock(uint8_t pa, uint8_t pb);
    virtual ~ABSensorBlock();

    int64_t getPosition();
    void resetPosition();

private:
    static std::list<ABSensorBlock *> abSensors;
    // static void irq_any(uint gpio, uint32_t events);
    static void irq_any();
    void pinChanged();

    uint8_t pinA;
    uint8_t pinB;

    uint8_t currentA;
    uint8_t currentB;

    int64_t position;
};

#endif
