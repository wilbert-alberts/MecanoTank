/*
 * PID.cpp
 *
 *  Created on: 26 Jan 2023
 *      Author: walberts
 */

#include "BL_PID.hpp"
#include "ServoConstants.hpp"

#include "T_Factory.hpp"

const IDTerminal PIDBlock::IN_ACTUAL("actual");
const IDTerminal PIDBlock::IN_SETPOINT("setpoint");

#define CREATE_PARAMETER(P) \
		{ \
		const IDTerminal P## _ID( #P ); \
		addParameter(P ## _ID, &P); \
		}


#define CREATE_PIDPARAMETER(P) \
		CREATE_PARAMETER(k ## P) \
		CREATE_PARAMETER(P ## _High) \
		CREATE_PARAMETER(P ## _Low)


PIDBlock::PIDBlock(const std::string &bn, double _servoFrequency, bool _avoidWindup)
	: LeafBlock("PID", bn), servoFrequency(_servoFrequency),
	  avoidWindup(_avoidWindup),
	  safeInput(0.0),
	  setpointInput(&safeInput),
	  actualInput(&safeInput),
	  S_set(0.0),
	  prev_S_set(0.0),
	  S_act(0.0),
	  delta_S(0.0),
	  prev_delta_S(0.0),
	  sum_delta_S(0.0),
	  V_set(0.0),
	  V_delta(0.0),
	  setpointSpeedTerm(0.0),
	  diffSpeedTerm(0.0),
	  diffPosTerm(0.0),
	  diffSumTerm(0.0),
	  output(0.0),

	  kFv(KFV), Fv_Low(FV_LOW), Fv_High(FV_HIGH),
	  kP(KP), P_Low(P_LOW), P_High(P_HIGH),
	  kI(KI), I_Low(I_LOW), I_High(I_HIGH),
	  kD(KD), D_Low(D_LOW), D_High(D_HIGH),
	  OutLow(PID_LOW), OutHigh(PID_HIGH)

{
	addInput(IN_ACTUAL, &actualInput);
	addInput(IN_SETPOINT, &setpointInput);

	CREATE_PIDPARAMETER(P)
	CREATE_PIDPARAMETER(I)
	CREATE_PIDPARAMETER(D)
	CREATE_PIDPARAMETER(Fv)
	CREATE_PARAMETER(OutLow)
	CREATE_PARAMETER(OutHigh)

	addDefaultOutput(&output);
}

PIDBlock::~PIDBlock()
{
}

void PIDBlock::calculate()
{
	S_set = *setpointInput;
	S_act = *actualInput;
	delta_S = S_set - S_act;
	V_set = ddt(S_set, &prev_S_set);
	setpointSpeedTerm = kFv * V_set;
	V_delta = ddt(delta_S, &prev_delta_S);
	diffSpeedTerm = kD * V_delta;
	diffPosTerm = kP * delta_S;
	double integr = idt(delta_S, &sum_delta_S);
	diffSumTerm = kI * integr;

	if (avoidWindup)
	{
		if ((delta_S >= 0 && prev_delta_S < 0) ||
			(delta_S < 0 && prev_delta_S >= 0))
		{
			// avoid integrator windup
			sum_delta_S = 0;
		}
	}

	double total = clip(setpointSpeedTerm, Fv_Low, Fv_High) +
				   clip(diffSpeedTerm, D_Low, D_High) +
				   clip(diffPosTerm, P_Low, P_High) +
				   clip(diffSumTerm, I_Low, I_High);

	output = clip(total, OutLow, OutHigh);

	prevOutput = output;
}

double PIDBlock::clip(double value, double low, double high)
{
	if (value < low)
		value = low;
	if (value > high)
		value = high;
	return value;
}

double PIDBlock::ddt(double value, double *prev)
{
	double out = (value - *prev) * servoFrequency;
	*prev = value;
	return out;
}

double PIDBlock::idt(double value, double *sum)
{
	*sum += value;
	return (*sum / servoFrequency);
}

void PIDBlock::setKP(double p, double low, double high)
{
	kP = p;
	P_Low = low;
	P_High = high;
}
void PIDBlock::setKI(double p, double low, double high)
{
	kI = p;
	I_Low = low;
	I_High = high;
}
void PIDBlock::setKD(double p, double low, double high)
{
	kD = p;
	D_Low = low;
	D_High = high;
}
void PIDBlock::setOutLimits(double low, double high)
{
	OutLow = low;
	OutHigh = high;
}
