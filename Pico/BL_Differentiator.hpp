/*
 * BL_Differentiator.h
 *
 *  Created on: 25 Jan 2023
 *      Author: walberts
 */

#ifndef __DIFFERENTIATORBLOCK_H__
#define __DIFFERENTIATORBLOCK_H__

#include <string>

#include "BL.hpp"

class DifferentiatorBlock: public Block
{
public:
	DifferentiatorBlock(const std::string &bn, float _servoFrequency) 
	: Block("Differentiator", bn)
	, input(&safeInput)
	, previousInput(safeInput)
	, output(0.0)
	, servoFrequency(_servoFrequency)
	, safeInput(0.0)
	{}
	virtual ~DifferentiatorBlock() {};

	virtual void calculate(int64_t) {		
		output = (*input - previousInput)*servoFrequency;
		previousInput = *input;
	}

	void setInput(float* src) {
		if (src != nullptr)
		input = src;
	}
	float* getOutput() {
		return &output;
	}

private:
	float* input;
	float  previousInput;
	float  output;
	float  servoFrequency;
	float  safeInput;
};


#endif /* BLOCK_H_ */
