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
	std::string typeName;
	std::string blockName;
};


//class Block
//{
//public:
//	Block(const std::string &tn, const std::string &bn);
//	virtual ~Block();
//	virtual void calculate() = 0;
//
//	const std::string& getBlockName();
//	const std::string& getTypeName();
//
//	virtual double* getOutput(unsigned int id);
//	virtual double* getOutput();
//	virtual void    setInput(unsigned int id, double* src);
//	virtual void    setInput(double* src);
//
//protected:
//	std::string typeName;
//	std::string blockName;
//};
//

#endif /* BLOCK_H_ */
