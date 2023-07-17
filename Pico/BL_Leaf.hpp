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

	virtual SuccessT<double*> getOutput(const Terminal &t);
	virtual SuccessT<double*> getOutput(const std::string &tid);
	virtual SuccessT<double*> getOutput();
	virtual std::vector<std::string> getOutputNames();

	virtual void setInput(const Terminal &t = Block::IN_INPUT, double *src = nullptr) ;
	virtual void setInput(const std::string& tid, double *src = nullptr) ;
	virtual void setInput(double *src = nullptr) ;

	virtual VoidSuccessT setParameter(const Terminal &t, double value);
	virtual SuccessT<double> getParameter(const Terminal &t);
	virtual std::vector<std::string> getParameterNames();

protected:

	void addParameter(const IDTerminal& t, double* src);
	void addDefaultOutput(double* src) ;
	void addOutput(const IDTerminal& t, double* src);
	void addDefaultInput(double** src);
	void addInput(const IDTerminal& t, double** src);
	

	std::map<const std::string, double*> parameters;
	std::map<const std::string, double*> outputTerminals;
	std::map<const std::string, double**> inputTerminals;


};

#endif /* BL_LEAF_H_ */
