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

#include "Traceable.hpp"

class Block
{
public:
	Block(const std::string &tn, const std::string &bn, double p);
	virtual ~Block();
	virtual void calculate() = 0;

	const std::string& getBlockName();
	const std::string& getTypeName();

	const std::vector<Traceable> &getTraceables();

protected:
	void registerTraceable(const std::string &name, const double *ref);
	std::vector<Traceable> traceables;

	std::string typeName;
	std::string blockName;
	double period;
};


#endif /* BLOCK_H_ */
