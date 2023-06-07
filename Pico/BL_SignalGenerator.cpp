

#include "BL_SignalGenerator.hpp"

SignalGeneratorBlock::SignalGeneratorBlock(const std::string &bn)
    : LeafBlock("SignalGenerator", bn), signal(0.0), counter(0)
{
	addDefaultOutput(&signal);
    // signals.push_back(0.0);
    // signals.push_back(0.33);
    signals.push_back(0.5);
    // signals.push_back(1.0);
}

SignalGeneratorBlock::SignalGeneratorBlock(const std::string &bn, double s)
    : LeafBlock("SignalGenerator", bn), signal(s), counter(0)
{
	addDefaultOutput(&signal);
}

double *SignalGeneratorBlock::getOutput(const Terminal &t)
{
    return &signal;
}

void SignalGeneratorBlock::calculate()
{
    if (signals.size() > 0)
    {
        signal = signals[counter];
        counter = (counter + 1) % signals.size();
    }
}
