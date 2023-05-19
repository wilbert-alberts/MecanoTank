/*
 * Block.cpp
 *
 *  Created on: 25 Jan 2023
 *      Author: walberts
 */

#include "BL.hpp"

Block::Block(const std::string &tn, const std::string &bn)
	: typeName(tn), blockName(bn)
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

