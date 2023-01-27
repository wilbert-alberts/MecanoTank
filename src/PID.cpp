/*
 * PID.cpp
 *
 *  Created on: 26 Jan 2023
 *      Author: walberts
 */

#include "PID.hpp"

PID::PID(double period) : Block(period), output(0), saveInput(0), input(&saveInput), sumInput(
																						 0),
						  prevInput(0), kP(1), kI(0), kD(0){};
PID::~PID() {}

void PID::calculate()
{
	sumInput += *input;
	double p = kP * (*input);
	double i = kI * sumInput;
	double d = kD * (*input - prevInput) / period;
	output = p + i + d;
}
double *PID::getOutput()
{
	return &output;
}
void PID::setInput(double *p)
{
	input = p;
}
void PID::setKP(double p)
{
	kP = p;
}
void PID::setKI(double p)
{
	kI = p;
}
void PID::setKD(double p)
{
	kD = p;
}
