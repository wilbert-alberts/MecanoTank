/*
 * Block.cpp
 *
 *  Created on: 26 mei 2023
 *      Author: wilbert
 */

#include "Block.h"

Block::Block(const std::string &typeName, const std::string &blockName) :
		type(typeName), id(blockName) {
}
Block::~Block() {
}
;

const std::string& Block::getBlockName() const {
	return id;
}
;
const std::string& Block::getBlockTypeName() const {
	return type;
}

const IDTerminal Block::IN_INPUT = IDTerminal("input");
const IDTerminal Block::OUT_OUTPUT = IDTerminal("output");
