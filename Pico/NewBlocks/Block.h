/*
 * Block.h
 *
 *  Created on: 26 mei 2023
 *      Author: wilbert
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include <string>

#include "IDTerminal.h"
#include "Terminal.h"

class Block {
public:
	Block(const std::string& typeName, const std::string& blockName);
	virtual ~Block() ;

    const std::string& getBlockName() const ;
    const std::string& getBlockTypeName()  const;

	virtual void calculate() = 0;
	virtual double* getOutput(const Terminal &t = OUT_OUTPUT) = 0;
	virtual void setInput(const Terminal &t = IN_INPUT, double *src = nullptr) = 0;

	static const IDTerminal IN_INPUT;
	static const IDTerminal OUT_OUTPUT ;

protected:
	std::string type;
	std::string id;
};


#endif /* BLOCK_H_ */
