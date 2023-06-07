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
	DifferentiatorBlock(const std::string &bn, double _servoFrequency);
	virtual ~DifferentiatorBlock();
	virtual void calculate();
	virtual double* getOutput(const Terminal &t = OUT_OUTPUT) = 0;
	virtual void setInput(const Terminal &t = IN_INPUT, double *src = nullptr) = 0;

private:
	double* input;
	double  previousInput;
	double  output;
	double  servoFrequency;
	double  safeInput;
};


#endif /* BLOCK_H_ */
