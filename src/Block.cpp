/*
 * Block.cpp
 *
 *  Created on: 25 Jan 2023
 *      Author: walberts
 */

#include "Block.hpp"

Block::Block(const std::string &tn, const std::string &bn, double p)
	: typeName(tn), blockName(bn), period(p)
{
}

Block::~Block()
{
	// TODO Auto-generated destructor stub
}

const std::string &Block::getBlockName()
{
	return blockName;
}

const std::string &Block::getTypeName()
{
	return typeName;
}

const std::vector<std::string> &Block::getTraceNames()
{
	return traceNames;
}

const std::vector<const double *> &Block::getTraceables()
{
	return traceables;
}

void Block::registerTraceable(const std::string &name, const double *ref)
{
	traceNames.push_back(name);
	traceables.push_back(ref);
}
