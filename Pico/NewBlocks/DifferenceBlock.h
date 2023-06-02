/*
 * DifferenceBlock.h
 *
 *  Created on: 26 mei 2023
 *      Author: wilbert
 */

#ifndef DIFFERENCEBLOCK_H_
#define DIFFERENCEBLOCK_H_

#include <string>

#include "Block.h"
#include "IDTerminal.h"

class DifferenceBlock : public Block {
public:
	DifferenceBlock(const std::string& blockName);
	virtual ~DifferenceBlock();

	static const IDTerminal IN_ACTUAL;
	static const IDTerminal IN_DESIRED;

	virtual void setInput(const Terminal &t, double *src);
	virtual double* getOutput(const Terminal &t = OUT_OUTPUT);
	virtual void calculate();

private:
	double *actual;
	double *desired;
	double difference;
};


#endif /* DIFFERENCEBLOCK_H_ */
