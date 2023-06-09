#include "BL_Sum.hpp"

#include <iostream>

#include "T_ID.hpp"

SumBlock::SumBlock(const std::string &bn, unsigned int _nrInputs)
    : LeafBlock("Sum", bn), offset(0.0), safeValue(0), nrInputs(_nrInputs)
    ,out(0)
{
	for ( unsigned int idx=0; idx< nrInputs; idx++) {
		factors.push_back(1.0);
		inputs.push_back(&safeValue);
	}
	for ( unsigned int idx=0; idx< nrInputs; idx++) {
		const std::string id = std::to_string(idx);
		addInput(id, &inputs[idx]);
	}
	addDefaultOutput(&out);
}

SumBlock::~SumBlock(){
};

void SumBlock::calculate()
{
    out = offset;
    for (unsigned int idx=0; idx< nrInputs; idx++) {
    	std::cout << "Taking input " << idx << " from " <<inputs[idx] << " which contains: " << *inputs[idx] << std::endl ;
        out += *(inputs[idx]) * factors[idx];
    }
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
