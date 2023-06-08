/*
 * BL_Leaf.h
 *
 *  Created on: 7 Jun 2023
 *      Author: walberts
 */

#ifndef BL_LEAF_H_
#define BL_LEAF_H_

#include <algorithm>
#include <map>
#include <string>

#include "BL.hpp"
#include "T.hpp"
#include "T_ID.hpp"

class LeafBlock: public Block {
public:
	LeafBlock(const std::string &_typeName, const std::string &_blockName) ;
	virtual ~LeafBlock();

	virtual double* getOutput(const Terminal &t = Block::OUT_OUTPUT);
	virtual double* getOutput(const std::string &tid);
	virtual void setInput(const Terminal &t = Block::IN_INPUT, double *src = nullptr) ;
	virtual void setInput(const std::string& tid, double *src = nullptr) ;


protected:

	void addDefaultOutput(double* src) ;
	void addOutput(const IDTerminal& t, double* src);
	void addDefaultInput(double** src);
	void addInput(const IDTerminal& t, double** src);

	std::map<const std::string, double*> outputTerminals;
	std::map<const std::string, double**> inputTerminals;


};

#endif /* BL_LEAF_H_ */
