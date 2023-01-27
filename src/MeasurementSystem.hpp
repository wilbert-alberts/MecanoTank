/*
 * MeasurementSystem.h
 *
 *  Created on: 26 Jan 2023
 *      Author: walberts
 */

#ifndef MEASUREMENTSYSTEM_H_
#define MEASUREMENTSYSTEM_H_

#include <cmath>
#include "Block.hpp"

class MeasurementSystem : public Block
{
public:
	MeasurementSystem(double period);
	virtual ~MeasurementSystem();
	virtual void calculate();
	void setInputX1(double *p);
	void setInputX2(double *p);
	void setInputY1(double *p);
	void setInputY2(double *p);
	double *getOutputX();
	double *getOutputY();
	double *getOutputRz();

private:
	double *x1;
	double *y1;
	double *x2;
	double *y2;
	double x;
	double y;
	double rz;

	double armY;
	double safeValue;
};

#endif /* MEASUREMENTSYSTEM_H_ */
