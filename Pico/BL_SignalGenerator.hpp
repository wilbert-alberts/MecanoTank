#ifndef __SIGNAL_GENERATOR_HPP__
#define __SIGNAL_GENERATOR_HPP__

#include <vector>

#include "BL.hpp"

class SignalGeneratorBlock: public Block
{
public:
    SignalGeneratorBlock(const std::string& bn, float sfr);
    SignalGeneratorBlock(const std::string& bn, float sig, float sfr);
    virtual ~SignalGeneratorBlock() {}
    float* getOutput();

protected:
    virtual void calculate(int64_t counter);

private:
    float sampleFrequency;
    float speed;
    float position;
    float output;
};
#endif