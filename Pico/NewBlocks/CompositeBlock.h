/*
 * CompositeBlock.h
 *
 *  Created on: 26 mei 2023
 *      Author: wilbert
 */

#ifndef COMPOSITEBLOCK_H_
#define COMPOSITEBLOCK_H_

#include <string>
#include <vector>

#include "Block.h"

class CompositeBlock: public Block {
public:
	CompositeBlock(const std::string &bn, std::vector<Block*> _blocks);

	virtual ~CompositeBlock();

	virtual void calculate();
	virtual double* getOutput(const Terminal &t);
	virtual void setInput(const Terminal &t, double *src);

protected:
	std::vector<Block*> blocks;
};

#endif /* COMPOSITEBLOCK_H_ */
