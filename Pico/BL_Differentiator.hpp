/*
 * Block.h
 *
 *  Created on: 25 Jan 2023
 *      Author: walberts
 */

#ifndef __DIFFERENTIATORBLOCK_H__
#define __DIFFERENTIATORBLOCK_H__

#include <string>

#include "BL_Leaf.hpp"

class DifferentiatorBlock: public LeafBlock
{
public:
	DifferentiatorBlock(const std::string &bn, double _servoFrequency);
	virtual ~DifferentiatorBlock();
	virtual void calculate();

private:
	double* input;
	double  previousInput;
	double  output;
	double  servoFrequency;
	double  safeInput;
};


#endif /* BLOCK_H_ */
