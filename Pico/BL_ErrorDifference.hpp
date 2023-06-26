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
	virtual void calculate(int64_t counter);
	void setInputActual(float *p);
	void setInputDesired(float *p);
	float *getOutput () { return &difference;} 
	bool  *getCSOutput () {return &changedSign;}


private:
	float safeValue;
	float *actual;
	float *desired;
	float difference;
	float previousDifference;
	bool  changedSign;
};

#endif /* ERRORDIFFERENCE_H_ */
