/*
 * BL_Integrator.h
 *
 *  Created on: 23 May 2023
 *      Author: walberts
 */

#ifndef __BL_INTEGRATOR_H__
#define __BL_INTEGRATOR_H__

#include <string>

#include "BL.hpp"

class IntegratorBlock: public Block
{
public:
	IntegratorBlock(const std::string &bn, float _servoFrequency) 
	: Block("Integrator", bn)
	, input(&safeInput)
	, clearIntegrator (&noCI)
	, integratorSum (0.0)
	, output(0.0)
	, servoFrequency(_servoFrequency)
	, safeInput(0.0)
	, noCI (false)

	{}
	virtual ~IntegratorBlock() {}
	virtual void calculate(int64_t) {
		if (*clearIntegrator) integratorSum = 0.0;
        integratorSum += *input;		
		output = integratorSum / servoFrequency;
		// std::cout << "ED: input: " << *input << ", output: " << output << std::endl;
	}
	void setInput(float* src) {
		if (src != nullptr)	input = src;
	}
	void setClearInt(bool *b) {
		if (b != nullptr) clearIntegrator = b;
	}
	float* getOutput() {
		return &output;
	}


private:
	float *input;
	bool  *clearIntegrator;
	float  integratorSum;
	float  output;
	float  servoFrequency;
	float  safeInput;
	bool   noCI;
};


#endif /* BL_Integrator_H_ */
