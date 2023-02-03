/*
 * RawSensor.cpp
 *
 *  Created on: 26 Jan 2023
 *      Author: walberts
 */
#include <Arduino.h>
#include "RawSensor.hpp"

RawSensor::RawSensor(const std::string& bn, double p) : Block("RawSensor", bn, p), s1x(0), s1y(0), s2x(0), s2y(0){
	registerTraceable("s1x", &s1x);
	registerTraceable("s1y", &s1y);
	registerTraceable("s2x", &s2x);
	registerTraceable("s2y", &s2y);
};

RawSensor::~RawSensor(){};
double *RawSensor::getOutputS1X()
{
	return &s1x;
}
double *RawSensor::getOutputS1Y()
{
	return &s1y;
}
double *RawSensor::getOutputS2X()
{
	return &s2x;
}
double *RawSensor::getOutputS2Y()
{
	return &s2y;
}
void RawSensor::calculate()
{
	Serial.println("RawSensor::calculate()");
}
