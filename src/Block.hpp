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

class Block
{
public:
	Block(double p);
	Block(const std::string &tn, const std::string &bn, double p);
	virtual ~Block();
	virtual void calculate() = 0;

	const std::string& getBlockName();
	const std::string& getTypeName();
	const std::vector<std::string> &getTraceNames();
	const std::vector<const double *> &getTraceables();

protected:
	void registerTraceable(const std::string &name, const double *ref);

	std::vector<std::string> traceNames;
	std::vector<const double *> traceables;

	std::string typeName;
	std::string blockName;
	double period;
};

#endif /* BLOCK_H_ */
