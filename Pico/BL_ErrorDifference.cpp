/*
 * ErrorDifferene.cpp
 *
 *  Created on: 25 Jan 2023
 *      Author: walberts
 */

#include "BL_ErrorDifference.hpp"

ErrorDifferenceBlock::ErrorDifferenceBlock(const std::string& bn) 
: Block("ErrorDifferenceBlock", bn),
   safeValue(0.0), 
   actual(&safeValue), 
   desired(&safeValue), 
   difference (0.0),
   previousDifference (0.0),
   changedSign (false)
{
}

ErrorDifferenceBlock::~ErrorDifferenceBlock()
{
	// TODO Auto-generated destructor stub
}

void ErrorDifferenceBlock::calculate(int64_t counter)
{
	difference = *desired - *actual;
	if ((difference >= 0 && previousDifference <  0) ||
	    (difference >  0 && previousDifference <= 0)   ) {
		changedSign = true;
	}
	previousDifference = difference;
}

void ErrorDifferenceBlock::setInputActual(float *p)
{
	if (p != nullptr)
	{
		actual = p;
	}
}
void ErrorDifferenceBlock::setInputDesired(float *p)
{
	if (p != nullptr)
	{
		desired = p;
	}
}
