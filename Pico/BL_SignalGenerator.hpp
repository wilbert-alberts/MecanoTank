#ifndef __SIGNAL_GENERATOR_HPP__
#define __SIGNAL_GENERATOR_HPP__

#include <vector>

#include "BL.hpp"
#include "T.hpp"

class SignalGeneratorBlock: public Block
{
public:
    SignalGeneratorBlock(const std::string& bn);
    SignalGeneratorBlock(const std::string& bn, double sig);
    virtual ~SignalGeneratorBlock() {}
    virtual double* getOutput(const Terminal &t = OUT_OUTPUT);

protected:
    virtual void calculate();

private:
    std::vector<double> signals;
    double signal;
    unsigned int counter;
};
#endif
