/*
 * PID.h
 *
 *  Created on: 26 Jan 2023
 *      Author: walberts
 */

#ifndef PID_H_
#define PID_H_

#include <string>

#include "BL_Leaf.hpp"
#include "T.hpp"

class PIDBlock : public LeafBlock
{
public:
	PIDBlock(const std::string &bn, double servoFrequency, bool avoidWindup);
	virtual ~PIDBlock();
	virtual void calculate();

	static const IDTerminal IN_ACTUAL;
	static const IDTerminal IN_SETPOINT;


	void setKFV(double f, double low, double high);
	void setKP(double p, double low, double high);
	void setKI(double i, double low, double high);
	void setKD(double d, double low, double high);
	void setOutLimits(double low, double high);

private:
	double clip(double value, double low, double high);
	double ddt(double value, double *prev);
	double idt(double value, double *sum);

	double servoFrequency;
	bool   avoidWindup;
	double safeInput;

	double *setpointInput;
	double *actualInput;

	double S_set;
	double prev_S_set;
	double S_act;
	double delta_S;
	double prev_delta_S;
	double sum_delta_S;

	double V_set;
	double V_delta;

	double setpointSpeedTerm;
	double diffSpeedTerm;
	double diffPosTerm;
	double diffSumTerm;
	double output;
	double prevOutput;

	double kFv;
	double FvLow;
	double FvHigh;
	double kP;
	double PLow;
	double PHigh;
	double kI;
	double ILow;
	double IHigh;
	double kD;
	double DLow;
	double DHigh;
	double OutLow;
	double OutHigh;
};

#endif /* PID_H_ */
