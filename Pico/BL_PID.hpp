/*
 * PID.h
 *
 *  Created on: 26 Jan 2023
 *      Author: walberts
 */

#ifndef PID_H_
#define PID_H_

#include <string>

#include "BL.hpp"

class PIDBlock : public Block
{
public:
	PIDBlock(const std::string &bn, double servoFrequency);
	virtual ~PIDBlock();
	virtual void calculate();
	double *getOutput();
	void setInput(double *p);
	void setKP(double p);
	void setKI(double p);
	void setKD(double p);

private:
	double servoFrequency;
	double output;
	double saveInput;
	double *input;
	double sumInput;
	double prevInput;
	double kP;
	double kI;
	double kD;
};

#endif /* PID_H_ */
