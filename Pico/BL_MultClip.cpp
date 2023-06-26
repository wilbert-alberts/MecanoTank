/*
 * BL_MultClip.cpp
 *
 *  Created on: 22 May 2023
 *      Author: benslag
 */

#include "BL_MultClip.hpp"

MultClipBlock::MultClipBlock(const std::string &bn, 
    float _factor, float _lowLimit, float _highLimit)
	: Block("MultClip", bn), 
    factor(_factor), 
    lowLimit(_lowLimit), 
    highLimit (_highLimit), 
    safeInput (0), 
    input(&safeInput) {}
MultClipBlock::~MultClipBlock() {}

void MultClipBlock::calculate(int64_t counter)
{
	output = *input * factor;
    if (output > highLimit) output = highLimit;
    if (output < lowLimit)  output = lowLimit;
}
float *MultClipBlock::getOutput()
{
	return &output;
}
void MultClipBlock::setInput(float *p)
{
	input = p;
}
void MultClipBlock::setFactor(float f)
{
    factor = f;
}
void MultClipBlock::setLower(float f)
{
    lowLimit = f;
}
void MultClipBlock::setHigher(float f)
{
    highLimit = f;
}

