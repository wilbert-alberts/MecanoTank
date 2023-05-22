/*
 * ErrorDifferene.cpp
 *
 *  Created on: 25 Jan 2023
 *      Author: walberts
 */

#include "BL_ErrorDifference.hpp"

ErrorDifferenceBlock::ErrorDifferenceBlock(const std::string& bn) 
: Block("ErrorDifferenceBlock", bn)
, safe_actual(0), actual(&safe_actual), desired(&safe_actual), error(0)
{
}
ErrorDifferenceBlock::~ErrorDifferenceBlock()
{
	// TODO Auto-generated destructor stub
}

void ErrorDifferenceBlock::calculate()
{
	error = *desired - *actual;
}

void ErrorDifferenceBlock::setInputActual(double *p)
{
	if (p != nullptr)
	{
		actual = p;
	}
}
void ErrorDifferenceBlock::setInputDesired(double *p)
{
	if (p != nullptr)
	{
		desired = p;
	}
}
double *ErrorDifferenceBlock::getOutput()
{
	return &error;
}