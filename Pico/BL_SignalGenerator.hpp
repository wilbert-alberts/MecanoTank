#ifndef __SIGNAL_GENERATOR_HPP__
#define __SIGNAL_GENERATOR_HPP__

#include <vector>

#include "BL_Leaf.hpp"
#include "T.hpp"

class SignalGeneratorBlock: public LeafBlock
{
public:
    SignalGeneratorBlock(const std::string& bn);
    SignalGeneratorBlock(const std::string& bn, double sig);
    virtual ~SignalGeneratorBlock() {}

protected:
    virtual void calculate();

private:
    std::vector<double> signals;
    double signal;
    unsigned int counter;
};
#endif
