/*
 * Block.cpp
 *
 *  Created on: 25 Jan 2023
 *      Author: walberts
 */

#include "T_ID.hpp"
#include "ErrorHandling.hpp"

#include "BL.hpp"

Block::Block(const std::string &_typeName, const std::string &_blockName) : typeName(_typeName), blockName(_blockName)
{
}
Block::~Block(){};

const std::string &Block::getBlockName() const
{
	return blockName;
};
const std::string &Block::getBlockTypeName() const
{
	return typeName;
}

bool Block::hasSubBlocks() const
{
	return false;
}

SuccessT<Block::BlockPtr> Block::getSubBlockByName(const std::string &blockname)
{
	return SuccessT<Block::BlockPtr>(nullptr, false, "Block::getSubBlockByName has not subBlocks.");
}

SuccessT<double *> Block::getOutput(const Terminal &t)
{
	return SuccessT<double *>(nullptr, false, "Block::getOutput not supported; block has no outputs");
}

SuccessT<double *> Block::getOutput()
{
	return SuccessT<double *>(nullptr, false, "Block::getOutput not supported; block has no outputs");
}

std::vector<std::string> Block::getOutputNames()
{
	return std::vector<std::string>();
}

void Block::setInput(const Terminal &t, double *src)
{
	Error("Block::setInput not supported; block has no input");
}

void Block::setInput(double *src)
{
	Error("Block::setInput not supported; block has no input");
}

void Block::Error(const std::string &msg)
{
	::Error(typeName + "::" + blockName + ": " + msg);
}

void Block::Warning(const std::string &msg)
{
	::Warning(typeName + "::" + blockName + ": " + msg);
}

const IDTerminal Block::IN_INPUT("input");
const IDTerminal Block::OUT_OUTPUT("output");

