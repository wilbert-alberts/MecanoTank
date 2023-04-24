/*
 * ErrorDifferene.h
 *
 *  Created on: 25 Jan 2023
 *      Author: walberts
 */

#ifndef _ERRORDIFFERENCE_H_
#define _ERRORDIFFERENCE_H_

#include "Block.hpp"

class ErrorDifference : public Block
{
public:
	ErrorDifference(const std::string& bn, double p);
	virtual ~ErrorDifference();
	virtual void calculate();
	void setInputActual(double *p);
	void setInputDesired(double *p);
	double *getOutputError();

private:
	double safe_actual;
	double *actual;
	double *desired;
	double error;
};

#endif /* ERRORDIFFERENCE_H_ */
