/*
 * ErrorDifferene.cpp
 *
 *  Created on: 25 Jan 2023
 *      Author: walberts
 */

#include "ErrorDifference.hpp"

ErrorDifference::ErrorDifference(const std::string& bn, double p) : Block("ErrorDifference", bn, p),
											 safe_actual(0), actual(&safe_actual), desired(&safe_actual), error(0)
{
}
ErrorDifference::~ErrorDifference()
{
	// TODO Auto-generated destructor stub
}

void ErrorDifference::calculate()
{
	error = *actual - *desired;
}

void ErrorDifference::setInputActual(double *p)
{
	if (p != 0)
	{
		actual = p;
	}
}
void ErrorDifference::setInputDesired(double *p)
{
	if (p != 0)
	{
		desired = p;
	}
}
double *ErrorDifference::getOutputError()
{
	return &error;
}