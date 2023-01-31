/*
 * GainOffsetSensor.cpp
 *
 *  Created on: 26 Jan 2023
 *      Author: walberts
 */

#include "GainOffsetSensor.hpp"

GainOffsetSensor::GainOffsetSensor(const std::string& bn, double p) : Block("GainOffset", bn, p),
											   gain(0), offset(0), input(&safeValue), output(0), safeValue(0){};

GainOffsetSensor::~GainOffsetSensor()
{
	// TODO Auto-generated destructor stub
}

void GainOffsetSensor::calculate()
{
	output = *input * gain + offset;
}
double *GainOffsetSensor::getOutput()
{
	return &output;
}
void GainOffsetSensor::setInput(double *d)
{
	input = d;
}
void GainOffsetSensor::setGain(double d)
{
	gain = d;
}
void GainOffsetSensor::setOffset(double d)
{
	offset = d;
}