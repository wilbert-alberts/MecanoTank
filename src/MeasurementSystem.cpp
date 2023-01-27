/*
 * MeasurementSystem.cpp
 *
 *  Created on: 26 Jan 2023
 *      Author: walberts
 */

#include "MeasurementSystem.hpp"

MeasurementSystem::MeasurementSystem(double period) : Block(period), x1(&safeValue), y1(&safeValue), x2(&safeValue), y2(
																														 &safeValue),
													  x(0), y(0), rz(0), armY(1), safeValue(0)
{
}

MeasurementSystem::~MeasurementSystem()
{
}
void MeasurementSystem::calculate()
{
	rz = atan((-(*x2) + (*x1)) / armY);
	x = ((*x1) + (*x2)) / 2.0;
	y = ((*y1) + (*y2)) / 2.0;
}
void MeasurementSystem::setInputX1(double *p)
{
	x1 = p;
}
void MeasurementSystem::setInputX2(double *p)
{
	x2 = p;
}
void MeasurementSystem::setInputY1(double *p)
{
	y1 = p;
}
void MeasurementSystem::setInputY2(double *p)
{
	y2 = p;
}
double *MeasurementSystem::getOutputX()
{
	return &x;
}
double *MeasurementSystem::getOutputY()
{
	return &y;
}
double *MeasurementSystem::getOutputRz()
{
	return &rz;
}