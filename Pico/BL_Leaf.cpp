/*
 * BL_Leaf.cpp
 *
 *  Created on: 7 Jun 2023
 *      Author: walberts
 */

#include "BL_Leaf.hpp"
#include "T_Factory.hpp"

LeafBlock::LeafBlock(const std::string &_typeName, const std::string &_blockName):
Block(_typeName, _blockName)
{
}

LeafBlock::~LeafBlock() {
}

double* LeafBlock::getOutput(const Terminal &t) {
	if (!t.hasID()) {
		Error("LeafBlock::getOutput, expected an IDTerminal but got something else.");
	}
	const std::string& id = t.getID();
	auto entry = std::find_if(outputTerminals.begin(), outputTerminals.end(),
			[&](auto e) {
		return e.first == id;
	});
	if (entry != outputTerminals.end()) {
		return entry->second;
	}
	else {
		Error("LeafBlock::getOutput, block does not have an output named: " + id);
	}
	return nullptr;
}

double* LeafBlock::getOutput(const std::string &tid) {
	auto t = TerminalFactory::createFromString(tid);
	return getOutput(*t);
}

void LeafBlock::setInput(const Terminal &t, double *src) {
	if (src == nullptr) {
		Error("LeafBlock::setInput: src should not be null");
	}

	if (!t.hasID()) {
		Error("LeafBlock::setInput, expected an IDTerminal but got something else.");
	}
	const std::string& id = t.getID();

	auto entry = std::find_if(inputTerminals.begin(), inputTerminals.end(),[&](auto e) {
		return e.first == id;
	});
	if (entry != inputTerminals.end()) {
		*(entry->second) = src;
	}
	else {
		Error("LeafBlock::getOutput, block does not have an output named: " + id);
	}
}

void LeafBlock::setInput(const std::string &tid, double *src) {
	auto t = TerminalFactory::createFromString(tid);
	setInput(*t,src);
}

void LeafBlock::addDefaultOutput(double* src) {
	addOutput(Block::OUT_OUTPUT, src);
}

void LeafBlock::addOutput(const IDTerminal& t, double* src) {
	const std::string id = t.getID();
	outputTerminals[id] = src;
}

void LeafBlock::addDefaultInput(double** src) {
	addInput(Block::IN_INPUT, src);
}

void LeafBlock::addInput(const IDTerminal& t, double** src) {
	const std::string id = t.getID();
	inputTerminals[id] = src;
}
