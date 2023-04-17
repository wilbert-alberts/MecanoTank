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

const std::vector<Traceable> & Block::getTraceables()
{
	return traceables;
}

void Block::registerTraceable(const std::string &name, const double *ref)
{
	Traceable tr(name, ref);
	traceables.push_back(tr);
}
