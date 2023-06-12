#ifndef __BL_ANALOG_HPP__
#define __BL_ANALOG_HPP__

#include <string>
// #include <stdint>

#include "hardware/adc.h"

#include "BL_Leaf.hpp"

class AnalogBaseBlock : public LeafBlock
{
public:
    AnalogBaseBlock(const std::string &bt, const std::string &bn, uint _adc);
    virtual ~AnalogBaseBlock();
    virtual void calculate();

protected:
    static bool adcInitialized;
    bool valid;
    uint adc;
    uint16_t adcOutput;
};

class AnalogInBlock : public AnalogBaseBlock
{
public:
    AnalogInBlock(const std::string &bn, uint _adc);
    virtual ~AnalogInBlock();
    virtual void calculate();

protected:
    double output;
};

class CPUTempBlock : public AnalogBaseBlock
{
public:
    CPUTempBlock(const std::string &bn);
    virtual ~CPUTempBlock();
    virtual void calculate();

protected:
    static const uint CPU_TEMP_CHANNEL;
    double output;
};

#endif