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

const IDTerminal KP_ID("kP");
const IDTerminal KPH_ID("kP-high");
const IDTerminal KPL_ID("kP-low");

const IDTerminal KI_ID("kI");
const IDTerminal KIH_ID("kI-high");
const IDTerminal KIL_ID("kI-low");

const IDTerminal KD_ID("kD");
const IDTerminal KDH_ID("kD-high");
const IDTerminal KDL_ID("kD-low");


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

	  kFv(KFV), FvLow(FV_LOW), FvHigh(FV_HIGH),
	  kP(KP), PLow(P_LOW), PHigh(P_HIGH),
	  kI(KI), ILow(I_LOW), IHigh(I_HIGH),
	  kD(KD), DLow(D_LOW), DHigh(D_HIGH),
	  OutLow(PID_LOW), OutHigh(PID_HIGH)

{
	addInput(IN_ACTUAL, &actualInput);
	addInput(IN_SETPOINT, &setpointInput);

	addParameter(KP_ID, &kP);
	addParameter(KPH_ID, &PHigh);
	addParameter(KPL_ID, &PLow);

	addParameter(KI_ID, &kI);
	addParameter(KIH_ID, &IHigh);
	addParameter(KIL_ID, &ILow);

	addParameter(KD_ID, &kD);
	addParameter(KDH_ID, &DHigh);
	addParameter(KDL_ID, &DLow);

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

	double total = clip(setpointSpeedTerm, FvLow, FvHigh) +
				   clip(diffSpeedTerm, DLow, DHigh) +
				   clip(diffPosTerm, PLow, PHigh) +
				   clip(diffSumTerm, ILow, IHigh);

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
	PLow = low;
	PHigh = high;
}
void PIDBlock::setKI(double p, double low, double high)
{
	kI = p;
	ILow = low;
	IHigh = high;
}
void PIDBlock::setKD(double p, double low, double high)
{
	kD = p;
	DLow = low;
	DHigh = high;
}
void PIDBlock::setOutLimits(double low, double high)
{
	OutLow = low;
	OutHigh = high;
}
