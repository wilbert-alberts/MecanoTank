/*
 * Block.cpp
 *
 *  Created on: 25 Jan 2023
 *      Author: walberts
 */

#include "BL.hpp"
#include "T_ID.hpp"

//Block::Block(const std::string &tn, const std::string &bn)
//	: typeName(tn), blockName(bn)
//{
//}
//
//Block::~Block()
//{
//	// TODO Auto-generated destructor stub
//}
//
//const std::string &Block::getBlockName()
//{
//	return blockName;
//}
//
//const std::string &Block::getTypeName()
//{
//	return typeName;
//}
//
//double* Block::getOutput()
//{
//    return nullptr;
//}
//
//double* Block::getOutput(unsigned int id)
//{
//    return nullptr;
//}
//
//void Block::setInput(double* src)
//{
//}
//
//void Block::setInput(unsigned int id, double* src)
//{
//}

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

const IDTerminal Block::IN_INPUT("input");
const IDTerminal Block::OUT_OUTPUT("output");
