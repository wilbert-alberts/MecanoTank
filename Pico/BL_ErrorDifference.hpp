/*
 * ErrorDifferene.h
 *
 *  Created on: 25 Jan 2023
 *      Author: walberts
 */

#ifndef _ERRORDIFFERENCE_H_
#define _ERRORDIFFERENCE_H_

#include "BL.hpp"

class ErrorDifferenceBlock : public Block
{
public:
	ErrorDifferenceBlock(const std::string& bn);
	virtual ~ErrorDifferenceBlock();
	virtual void calculate();
	void setInputActual(double *p);
	void setInputDesired(double *p);
	double *getOutput();

private:
	double safe_actual;
	double *actual;
	double *desired;
	double error;
};

#endif /* ERRORDIFFERENCE_H_ */
