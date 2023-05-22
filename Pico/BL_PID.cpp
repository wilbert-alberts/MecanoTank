/*
 * PID.cpp
 *
 *  Created on: 26 Jan 2023
 *      Author: walberts
 */

#include "BL_PID.hpp"

PIDBlock::PIDBlock(const std::string &bn, double _servoFrequency)
	: Block("PID", bn), servoFrequency(_servoFrequency), saveInput(0), input(&saveInput), sumInput(0),
	  prevInput(0), kP(1), kI(0), kD(0){};
PIDBlock::~PIDBlock() {}

void PIDBlock::calculate()
{
	sumInput += *input;
	double p = kP * (*input);
	double i = kI * sumInput;
	double d = kD * (*input - prevInput) * servoFrequency;
	output = p + i + d;
}
double *PIDBlock::getOutput()
{
	return &output;
}
void PIDBlock::setInput(double *p)
{
	input = p;
}
void PIDBlock::setKP(double p)
{
	kP = p;
}
void PIDBlock::setKI(double p)
{
	kI = p;
}
void PIDBlock::setKD(double p)
{
	kD = p;
}
