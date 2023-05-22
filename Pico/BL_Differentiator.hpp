/*
 * Block.h
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
	DifferentiatorBlock(const std::string &bn, double _servoFrequency) 
	: Block("Differentiator", bn)
	, input(&safeInput)
	, previousInput(safeInput)
	, output(0.0)
	, servoFrequency(_servoFrequency)
	, safeInput(0.0)
	{}
	virtual ~DifferentiatorBlock() {};
	virtual void calculate() {		
		output = (*input - previousInput)*servoFrequency;
		previousInput = *input;
		// std::cout << "ED: input: " << *input << ", output: " << output << std::endl;
	}
	void setInput(double* src) {
		if (src != nullptr)
		input = src;
	}
	double* getOutput() {
		return &output;
	}

private:
	double* input;
	double  previousInput;
	double  output;
	double  servoFrequency;
	double  safeInput;
};


#endif /* BLOCK_H_ */
