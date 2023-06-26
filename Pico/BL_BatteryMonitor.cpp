//
// BatteryMonitor.cpp
//
#include "hardware/gpio.h"
#include "adc.h" // DIRTY TRICK -- COPIED TO HERE
//#include "pico/stdlib.h"

#include "BL_BatteryMonitor.hpp"
#include "HSI.hpp"


int   BatteryMonitor::avgSamples = 0;
int   BatteryMonitor::nSamplesA  = 0;
int   BatteryMonitor::nSamplesB  = 0;
float BatteryMonitor::sumA       = 0.0;
float BatteryMonitor::sumB       = 0.0;
bool  BatteryMonitor::inited     = false;
float BatteryMonitor::batFactor  = 0.0;



BatteryMonitor::BatteryMonitor (const std::string& bn, float servoFreq)
: Block ("BatteryMonitor", bn)
{
    if (!inited) {
        inited = true;

        // setup ADC hardware

        adc_init ();
        adc_gpio_init    (PIN_IN_BAT_VOLT);
        adc_select_input (BAT_VOLT_ADC_INPUT);

        // setup class internals

        // perform a number of adcs to have a decent readout
        avgSamples = servoFreq * BAT_AVG_TIME;
        for (int i = 0; i < avgSamples/2; i++) {
            sumA += adc_read () * BATTERY_VOLT_PER_BIT;
        }
        nSamplesA = avgSamples / 2;

        sumB = 0.0; nSamplesB = 0;
        calculate (0);
    } 
}

BatteryMonitor::~BatteryMonitor () {}

void BatteryMonitor::calculate (int64_t counter)
{
    // household
    if (nSamplesA >= avgSamples) {
        nSamplesA = 0;
        sumA      = 0.0;
    }
    if (nSamplesB >= avgSamples) {
        nSamplesB = 0;
        sumB      = 0.0;
    }

    float v = adc_read () * BATTERY_VOLT_PER_BIT;
    sumA += v;
    sumB += v;
    nSamplesA++;
    nSamplesB++;

    if (batteryOK ()) {
    
        const float rc     = BATTERY_DROP_COMPENSATION;
        const float offset = 1.0-(rc*BATTERY_NOMINAL_VOLTS);  // for 11 volts in, out = 1.0
        batFactor = avgVolts () * rc + offset;
    }
    else batFactor = 0.0;


}

float BatteryMonitor::avgVolts ()
{
    float result;
    if (nSamplesB > nSamplesA) {
        result = sumB / nSamplesB;
    }
    else {
        result = sumA / nSamplesA;
    }
    return result;
}

bool BatteryMonitor::batteryOK ()
{
    bool r = false;
    if (avgVolts () > BATTERY_MIN_VOLTS) r = true;
    return r; 
}

float *BatteryMonitor::getBatFactor ()
{
    return &batFactor;
}
