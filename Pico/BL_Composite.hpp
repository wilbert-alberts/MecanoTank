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

#include "BL.hpp"
#include "T.hpp"
#include "T_Composite.hpp"

class CompositeBlock: public Block {
public:
	CompositeBlock(const std::string &bn, std::vector<Block*> _blocks);

	virtual ~CompositeBlock();

	virtual void calculate();

	virtual double* getOutput(const Terminal &t);
	virtual void setInput(const Terminal &t, double *src);

	virtual double* getOutput(const CompositeTerminal &t);
	virtual void setInput(const CompositeTerminal &t, double *src);

	static const std::string separator;
	Block* getBlockByName(const std::string& fqn);

protected:
	std::vector<Block*> blocks;
};

#endif /* COMPOSITEBLOCK_H_ */
