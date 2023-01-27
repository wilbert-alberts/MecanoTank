/*
 * GainOffsetSensor.h
 *
 *  Created on: 26 Jan 2023
 *      Author: walberts
 */

#ifndef GAINOFFSETSENSOR_H_
#define GAINOFFSETSENSOR_H_

#include "Block.hpp"

class GainOffsetSensor : public Block
{
public:
	GainOffsetSensor(double p);
	virtual ~GainOffsetSensor();
	virtual void calculate();
	double *getOutput();
	void setInput(double *d);
	void setGain(double d);
	void setOffset(double d);

private:
	double gain;
	double offset;
	double *input;
	double output;
	double safeValue;
};

#endif /* GAINOFFSETSENSOR_H_ */
