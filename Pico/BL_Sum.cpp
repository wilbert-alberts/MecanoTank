#include "BL_Sum.hpp"

#include <iostream>

#include "T_ID.hpp"

SumBlock::SumBlock(const std::string &bn, unsigned int _nrInputs)
    : LeafBlock("Sum", bn), offset(0.0), safeValue(0), nrInputs(_nrInputs)
    , out(0)
{
    for ( unsigned int idx=0; idx< nrInputs; idx++) {
        factors.push_back(1.0);
        in.push_back(&safeValue);

        const std::string id = std::to_string(idx);
        addInput(id, &in[idx]);
    }
    addDefaultOutput(&out);
}

SumBlock::~SumBlock(){};
void SumBlock::calculate()
{
    out = offset;
    for (unsigned int idx=0; idx< nrInputs; idx++) {
        out += *(in[idx]) * factors[idx];
    }
    // std::cout<<"SUM in1: " << *in1 << ", in2: " << *in2 << ", out: " << out << std::endl;
    // std::cout<<"SUM in1: " << *in1*s1 << ", in2: " << *in2 * s2 << ", out: " << out << std::endl;
}
//double *SumBlock::getOutput(const Terminal &t)
//{
//    return &out;
//}
void SumBlock::setOffset(double o)
{
    offset = o;
}
void SumBlock::setFactor(unsigned int idx, double o)
{
    if (idx>=0 && idx<nrInputs)
    factors[idx] = o;
}

//void SumBlock::setInput(const Terminal &t, double *src)
//{
//	const IDTerminal* idT = dynamic_cast<const IDTerminal*>(&t);
//
//	unsigned int idx = (unsigned int)(std::stoi(idT->getID()));
//    if (idx>=0 && idx<nrInputs)
//    in[idx] = src;
//}
