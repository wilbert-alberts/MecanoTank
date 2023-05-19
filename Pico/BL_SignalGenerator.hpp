#ifndef __SIGNAL_GENERATOR_HPP__
#define __SIGNAL_GENERATOR_HPP__

#include <vector>

#include "BL.hpp"

class SignalGeneratorBlock: public Block
{
public:
    SignalGeneratorBlock(const std::string& bn);
    virtual ~SignalGeneratorBlock() {}
    double* getOutput();

protected:
    virtual void calculate();

private:
    std::vector<double> signals;
    double signal;
    uint counter;
};
#endif