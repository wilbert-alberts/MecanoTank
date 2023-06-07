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
	typedef std::shared_ptr<Block> BlockPtr;

	CompositeBlock(const std::string &bn);
	CompositeBlock(const std::string &bn, std::vector<BlockPtr> _blocks);

	virtual ~CompositeBlock();

	virtual void calculate();

	virtual double* getOutput(const Terminal &t);
	virtual void setInput(const Terminal &t, double *src);

	virtual double* getOutput(const CompositeTerminal &t);
	virtual void setInput(const CompositeTerminal &t, double *src);

	static const std::string separator;
	BlockPtr getBlockByFQN(const std::string &fqn);

protected:
	std::vector<BlockPtr> blocks;

	BlockPtr findBlockByNameOrError(const std::string &fqn,
			const std::string &errorMsg);
};

#endif /* COMPOSITEBLOCK_H_ */
