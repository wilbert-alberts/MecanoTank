/*
 * PID.cpp
 *
 * dd: 26 May 2023, benslag
 * Stolen from walberts dd: 26 Jan 2023
 *  
 */

#include "BL_PID.hpp"
#include "ServoConstants.hpp"

PIDBlock::PIDBlock(const std::string &bn, bool _avoidWindup, float _servoFrequency)
	: Block("PID", bn), 
	servoFrequency(_servoFrequency), 
	avoidWindup (_avoidWindup),
	safeInput(0.0), 
	setpointInput(&safeInput),
	actualInput  (&safeInput),
    S_set (0.0),
	prev_S_set (0.0),
	S_act (0.0),
	delta_S (0.0),
	prev_delta_S (0.0),
	sum_delta_S (0.0),
	V_set (0.0),
	V_delta (0.0),
	setpointSpeedTerm (0.0),
	diffSpeedTerm (0.0),
	diffPosTerm (0.0),
	diffSumTerm (0.0),
	output (0.0),

	kFv (KFV), FvLow (FV_LOW), FvHigh (FV_HIGH),
	kP  (KP),  PLow  (P_LOW),  PHigh  (P_HIGH),
	kI  (KI),  ILow  (I_LOW),  IHigh  (I_HIGH),
	kD  (KD),  DLow  (D_LOW),  DHigh  (D_HIGH),
	    OutLow (PID_LOW),     OutHigh (PID_HIGH)
    {
		traceOutputs [0] = &setpointSpeedTerm;
		traceOutputs [1] = &diffSpeedTerm;
		traceOutputs [2] = &diffPosTerm;
		traceOutputs [3] = &diffSumTerm;
		traceOutputs [4] = &output;
		traceOutputs [5] = &S_set;
		traceOutputs [6] = &S_act;
	}
PIDBlock::~PIDBlock() {}

void PIDBlock::calculate(int64_t counter)
{
	
	S_set             = *setpointInput;
	S_act             = *actualInput;
	delta_S           = S_set - S_act;
	V_set             = ddt (S_set, &prev_S_set);
	setpointSpeedTerm = kFv * V_set;
	V_delta           = ddt (delta_S, &prev_delta_S);
	diffSpeedTerm     = kD * V_delta;
	diffPosTerm       = kP * delta_S;
	float integr      = idt (delta_S, &sum_delta_S);
	diffSumTerm       = kI * integr;


	if (avoidWindup) {
		if ((delta_S >= 0 && prev_delta_S  < 0) ||
		    (delta_S  < 0 && prev_delta_S >= 0)    ) {
			// avoid integrator windup
			sum_delta_S = 0;
		}
	}

    float total = clip (setpointSpeedTerm, FvLow,  FvHigh) +
				  clip (diffSpeedTerm,     DLow,   DHigh) +
				  clip (diffPosTerm,       PLow,   PHigh) +
				  clip (diffSumTerm,       ILow,   IHigh);

	output      = clip (total,             OutLow, OutHigh);

	// stop crit for tracer
	tracerStopCrit =  (S_act < -1e5) || (S_act > 1e5);

	prevOutput = output;
}

float *PIDBlock::getOutput()
{
	return &output;
}

float *PIDBlock::getTraceOutput (unsigned int which) 
{
	if (which < PID_N_TRACE_OUTPUTS) return traceOutputs [which];
	return &safeInput;
}

void PIDBlock::setSetpointInput(float *p)
{
	setpointInput = p;
}
void PIDBlock::setActualInput(float *p)
{
	actualInput = p;
}
void PIDBlock::setKP(float p, float low, float high)
{
	kP = p; PLow = low; PHigh = high;
}
void PIDBlock::setKI(float p, float low, float high)
{
	kI = p; ILow = low; IHigh = high;
}
void PIDBlock::setKD(float p,  float low, float high)
{
	kD = p; DLow = low; DHigh = high;
}
void PIDBlock::setOutLimits (float low, float high)
{
	OutLow = low; OutHigh = high;
}
