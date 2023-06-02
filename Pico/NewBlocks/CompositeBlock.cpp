/*
 * CompositeBlock.cpp
 *
 *  Created on: 26 mei 2023
 *      Author: wilbert
 */

#include <algorithm>

#include "CompositeBlock.h"

#include "CompositeTerminal.h"
#include "IDTerminal.h"

CompositeBlock::CompositeBlock(const std::string &bn,
		std::vector<Block*> _blocks) :
		Block("CompositeBlock", bn), blocks(_blocks) {
}

CompositeBlock::~CompositeBlock() {
}


void CompositeBlock::calculate() {
	for (auto b : blocks) {
		b->calculate();
	}
}

double* CompositeBlock::getOutput(const Terminal &t) {
	const CompositeTerminal *ct = dynamic_cast<const CompositeTerminal*>(&t);
	const auto head = &ct->getHead();

	const IDTerminal *headID = dynamic_cast<const IDTerminal*>(head);
	const std::string headIDName = headID->getID();
	auto iter = std::find_if(blocks.begin(), blocks.end(), [&](auto b) {
		return b->getBlockName() == headIDName;
	});
	if (iter != blocks.end()) {
		auto block = *iter;
		return block->getOutput(ct->getTail());
	}
	// Todo: deal with block not found?
	return nullptr;
}

void CompositeBlock::setInput(const Terminal &t, double *src) {
	const CompositeTerminal *ct = dynamic_cast<const CompositeTerminal*>(&t);
	const auto head = &ct->getHead();

	const IDTerminal *headID = dynamic_cast<const IDTerminal*>(head);
	const std::string headIDName = headID->getID();
	auto iter = std::find_if(blocks.begin(), blocks.end(), [&](auto b) {
		return b->getBlockName() == headIDName;
	});
	if (iter != blocks.end()) {
		auto block = *iter;
		block->setInput(ct->getTail(), src);
	}
	// Todo: deal with block not found?
}
