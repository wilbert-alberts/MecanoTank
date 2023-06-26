

#include "BL_SignalGenerator.hpp"
#include <math.h>

SignalGeneratorBlock::SignalGeneratorBlock(const std::string &bn, float sfr)
    : Block("SignalGenerator", bn), 
    sampleFrequency (sfr), speed (0.1), position (0.0), output (0.0)
{
}

SignalGeneratorBlock::SignalGeneratorBlock(const std::string &bn, float _speed, float sfr)
    : Block("SignalGenerator", bn), 
    sampleFrequency (sfr), speed (_speed), position (0.0), output (0.0)
{
}

float *SignalGeneratorBlock::getOutput()
{
    return &output;
}

void SignalGeneratorBlock::calculate(int64_t counter)
{
    float arg = counter/sampleFrequency/5;
    float a = sin (arg);
    float sp = speed * a;
    position += sp/sampleFrequency;
    output = position;

}