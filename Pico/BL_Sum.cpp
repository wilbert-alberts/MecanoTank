#include "BL_Sum.hpp"

#include <iostream>

SumBlock::SumBlock(const std::string &bn, unsigned int _nrInputs)
    : Block("Sum", bn), offset(0.0), safeValue(0), nrInputs(_nrInputs)
    , out(0)
{
    for (int idx=0; idx< nrInputs; idx++) {
        factors.push_back(1.0);
        in.push_back(&safeValue);
    }
}

SumBlock::~SumBlock(){};
void SumBlock::calculate()
{
    out = offset;
    for (int idx=0; idx< nrInputs; idx++) {
        out += *(in[idx]) * factors[idx];
    }
    // std::cout<<"SUM in1: " << *in1 << ", in2: " << *in2 << ", out: " << out << std::endl;
    // std::cout<<"SUM in1: " << *in1*s1 << ", in2: " << *in2 * s2 << ", out: " << out << std::endl;
}
double *SumBlock::getOutput()
{
    return &out;
}
void SumBlock::setOffset(double o)
{
    offset = o;
}
void SumBlock::setFactor(unsigned int idx, double o)
{
    if (idx>=0 && idx<nrInputs)
    factors[idx] = o;
}

void SumBlock::setInput(unsigned int idx, double *p)
{
    if (idx>=0 && idx<nrInputs)
    in[idx] = p;
}
