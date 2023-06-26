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

#define PID_N_TRACE_OUTPUTS 6

class PIDBlock : public Block
{
public:
	PIDBlock(const std::string &bn, bool avoidWindup, float servoFrequency);
	virtual ~PIDBlock();
	void calculate(int64_t);
	float *getOutput();
	float *getTraceOutput (unsigned int which);
	bool *getTracerStopCrit () {return &tracerStopCrit;}
	void setSetpointInput(float *p);
	void setActualInput(float *p);
	void setKFV(float f, float low, float high);
	void setKP (float p, float low, float high);
	void setKI (float i, float low, float high);
	void setKD (float d, float low, float high);
	void setOutLimits   (float low, float high);

private:

    float clip (float value, float low, float high) {
		if (value < low)  value = low;
		if (value > high) value = high;
		return value;
	}

	float ddt (float value, float *prev) {
		float out = (value - *prev) * servoFrequency;
		*prev = value;
		return out; 
	}

	float idt (float value, float *sum) {
		*sum += value;
		return (*sum / servoFrequency);
	}


	float servoFrequency;
	bool  avoidWindup;
	float *traceOutputs[PID_N_TRACE_OUTPUTS];
	float safeInput;
	float *setpointInput;
	float *actualInput;

	float S_set;
	float prev_S_set;
	float S_act;
	float delta_S;
	float prev_delta_S;
	float sum_delta_S;

	float V_set;
	float V_delta;

	float setpointSpeedTerm;
	float diffSpeedTerm;
	float diffPosTerm;
	float diffSumTerm;
	float output;
	float prevOutput;
	bool  tracerStopCrit;


	float kFv;
	float FvLow;
	float FvHigh;
	float kP;
	float PLow;
	float PHigh;
	float kI;
	float ILow;
	float IHigh;
	float kD;
	float DLow;
	float DHigh;
	float OutLow;
	float OutHigh;
};

#endif /* PID_H_ */
