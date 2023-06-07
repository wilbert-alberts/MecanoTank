/*
 * PID.cpp
 *
 *  Created on: 26 Jan 2023
 *      Author: walberts
 */

#include "BL_PID.hpp"

PIDBlock::PIDBlock(const std::string &bn, double _servoFrequency) :
		LeafBlock("PID", bn), servoFrequency(_servoFrequency), output(0.0), saveInput(
				0), input(&saveInput), sumInput(0), prevInput(0), kP(1), kI(0), kD(
				0) {
	addDefaultInput(&input);
	addDefaultOutput(&output);
}

PIDBlock::~PIDBlock() {
}

void PIDBlock::calculate() {
	sumInput += *input;
	double p = kP * (*input);
	double i = kI * sumInput;
	double d = kD * (*input - prevInput) * servoFrequency;
	output = p + i + d;
}
//double* PIDBlock::getOutput(const Terminal &t) {
//	return &output;
//}
//void PIDBlock::setInput(const Terminal &t, double *p) {
//	input = p;
//}
void PIDBlock::setKP(double p) {
	kP = p;
}
void PIDBlock::setKI(double p) {
	kI = p;
}
void PIDBlock::setKD(double p) {
	kD = p;
}
