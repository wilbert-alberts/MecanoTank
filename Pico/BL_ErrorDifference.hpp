/*
 * ErrorDifferene.h
 *
 *  Created on: 25 Jan 2023
 *      Author: walberts
 */

#ifndef _ERRORDIFFERENCE_H_
#define _ERRORDIFFERENCE_H_

#include "BL_Leaf.hpp"
#include "T_ID.hpp"

class ErrorDifferenceBlock : public LeafBlock
{
public:
	ErrorDifferenceBlock(const std::string& bn);
	virtual ~ErrorDifferenceBlock();

	virtual void calculate();

//	virtual void setInput(const Terminal &t, double *src);
//	virtual double *getOutput(const Terminal &t = OUT_OUTPUT);

	static const IDTerminal IN_ACTUAL;
	static const IDTerminal IN_DESIRED;

private:
	double safe_actual;
	double *actual;
	double *desired;
	double error;
};

#endif /* ERRORDIFFERENCE_H_ */
