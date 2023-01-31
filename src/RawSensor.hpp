/*
 * RawSensor.h
 *
 *  Created on: 26 Jan 2023
 *      Author: walberts
 */

#ifndef RAWSENSOR_H_
#define RAWSENSOR_H_

#include "Block.hpp"

class RawSensor: public Block {
public:
	RawSensor(double p);
	RawSensor(const std::string& bn, double p);
	virtual ~RawSensor();
	double* getOutputS1X();
	double* getOutputS1Y();
	double* getOutputS2X();
	double* getOutputS2Y();
	void calculate();
private:
	double s1x;
	double s1y;
	double s2x;
	double s2y;
};

#endif /* RAWSENSOR_H_ */

