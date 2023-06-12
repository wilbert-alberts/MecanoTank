/*
 * Block.h
 *
 *  Created on: 25 Jan 2023
 *      Author: walberts
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include <string>
#include <vector>

#include "T.hpp"
#include "T_ID.hpp"

class Block {
public:
	typedef std::shared_ptr<Block> BlockPtr;

	Block(const std::string& typeName, const std::string& blockName);
	virtual ~Block() ;

    const std::string& getBlockName() const ;
    const std::string& getBlockTypeName()  const;

    virtual bool hasSubBlocks() const;
    virtual BlockPtr getSubBlockByName(const std::string& blockname);

	virtual void calculate() = 0;

	virtual double* getOutput(const Terminal &t);
	virtual void    setInput(const Terminal &t, double *src);

	virtual double* getOutput();
	virtual void    setInput(double *src);

	static const IDTerminal IN_INPUT;
	static const IDTerminal OUT_OUTPUT ;

protected:
	void Error(const std::string& message);

	std::string typeName;
	std::string blockName;
};


#endif /* BLOCK_H_ */
