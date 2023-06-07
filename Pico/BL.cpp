/*
 * Block.cpp
 *
 *  Created on: 25 Jan 2023
 *      Author: walberts
 */

#include "T_ID.hpp"
#include "ErrorHandling.hpp"

#include "BL.hpp"

Block::Block(const std::string &_typeName, const std::string &_blockName) :
		typeName(_typeName), blockName(_blockName) {
}
Block::~Block() {
}
;

const std::string& Block::getBlockName() const {
	return blockName;
}
;
const std::string& Block::getBlockTypeName() const {
	return typeName;
}

double* Block::getOutput(const Terminal &t)
{
	Error("Block::getOutput not supported; block has no outputs");
	return nullptr;
}

void Block::setInput(const Terminal &t, double *src )
{
	Error("Block::setInput not supported; block has no input");
}


void Block::Error(const std::string& msg) {
	::Error(typeName + "::" + blockName+ ": " + msg);
}

const IDTerminal Block::IN_INPUT("input");
const IDTerminal Block::OUT_OUTPUT("output");
