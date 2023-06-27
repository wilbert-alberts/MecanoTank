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

	CompositeBlock(const std::string &bn);
	CompositeBlock(const std::string &bn, std::vector<BlockPtr> _blocks);

	virtual ~CompositeBlock();

	virtual void calculate();

	virtual SuccessT<double*> getOutput(const Terminal &t);
	virtual void setInput(const Terminal &t, double *src);

	virtual SuccessT<double*> getOutput(const CompositeTerminal &t);
	virtual void setInput(const CompositeTerminal &t, double *src);

	virtual SuccessT<double*> getOutput(const std::string &t);
	virtual void setInput(const std::string &t, double *src);

	virtual SuccessT<double*> getOutput();
	virtual void setInput(double *src);

	static const std::string separator;
	
	virtual std::vector<std::string> getOutputNames();

    virtual bool hasSubBlocks() const;
    virtual SuccessT<BlockPtr>  getSubBlockByName(const std::string& blockname);

protected:
	std::vector<BlockPtr> blocks;

	SuccessT<BlockPtr>  findBlockByNameOrError(const std::string &fqn,
			const std::string &errorMsg);
};

#endif /* COMPOSITEBLOCK_H_ */
