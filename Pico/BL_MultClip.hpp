/*
 * BL_MultClip.hpp
 *
 *  Created on: 23-May-2023
 *      Author: benslag
 */

#ifndef MULTCLIP_H_
#define MULTCLIP_H_

#include <string>

#include "BL.hpp"

class MultClipBlock : public Block
{
public:
	MultClipBlock(const std::string &bn, float _factor, float _lowLimit, float _highLimit);
	virtual ~MultClipBlock();
	virtual void calculate(int64_t);
	float *getOutput();
	void setInput(float *p);
	void setFactor(float f);
	void setLower(float l);
	void setHigher(float h);

private:

	float factor;
    float lowLimit;
    float highLimit;
	float output;
    float safeInput;
	float *input;
};

#endif /* MULTCLIP_H_ */
