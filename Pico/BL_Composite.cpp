/*
 * CompositeBlock.cpp
 *
 *  Created on: 26 mei 2023
 *      Author: wilbert
 */

#include <algorithm>

#include "T_Composite.hpp"
#include "T_ID.hpp"
#include "T_Factory.hpp"

#include "BL_Composite.hpp"

const std::string CompositeBlock::separator(".");

CompositeBlock::CompositeBlock(const std::string &bn) :
		Block("CompositeBlock", bn), blocks(std::vector<BlockPtr>()) {
}

CompositeBlock::CompositeBlock(const std::string &bn,
		std::vector<BlockPtr> _blocks) :
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
	if (!t.hasCompositeStructure()) {
		Error(
				"CompositeBlock::getOutput(): Expected an CompositeTerminal but got something else");
	}
	const Terminal& head = t.getHead();
	if (!head.hasID()) {
		Error("CompositeBlock::getOutput(): Expected the head of the composite input terminal to have an ID but id doesn't");
	}
	const std::string& headIDName = head.getID();
	auto block = findBlockByNameOrError(headIDName,
			"CompositeBlock::getOutput(): Unable to find an block named "
					+ headIDName);

	return block->getOutput(t.getTail());

}

double* CompositeBlock::getOutput(const CompositeTerminal &ct) {
	const Terminal& head = ct.getHead();

	const std::string& headIDName = head.getID();
	BlockPtr block = findBlockByNameOrError(headIDName,
			"CompositeBlock::getOutput(): Unable to find an block named "
					+ headIDName);
	return block->getOutput(ct.getTail());
}

double* CompositeBlock::getOutput(const std::string &tid) {
	auto t = TerminalFactory::createFromString(tid);
	return getOutput(*t);
}

void CompositeBlock::setInput(const Terminal &t, double *src) {
	if (!t.hasCompositeStructure()) {
		Error(
				"CompositeBlock::setInput(): Expected an CompositeTerminal but got something else");
	}
	const Terminal& head = t.getHead();

	const std::string& headIDName = head.getID();
	BlockPtr block = findBlockByNameOrError(headIDName,
			"CompositeBlock::setInput(): Unable to find an block named "
					+ headIDName);
	block->setInput(t.getTail(), src);
}

void CompositeBlock::setInput(const CompositeTerminal &ct, double *src) {
	const Terminal& head = ct.getHead();

	const std::string headIDName = head.getID();
	BlockPtr block = findBlockByNameOrError(headIDName,
			"CompositeBlock::setInput(): Unable to find an block named "
					+ headIDName);
	block->setInput(ct.getTail(), src);
}

void CompositeBlock::setInput(const std::string &tid, double *src) {
	auto t = TerminalFactory::createFromString(tid);
	setInput(*t, src);
}

bool CompositeBlock::hasSubBlocks() const {
	return true;
}
CompositeBlock::BlockPtr CompositeBlock::getSubBlockByName(const std::string &fqn) {
	size_t separatorIdx = fqn.find(separator);
	if (separatorIdx == std::string::npos) {
		auto block =
				findBlockByNameOrError(fqn,
						"CompositeBlock::getBlockByName(): Unable to find an block named "
								+ fqn);
		return block;
	} else {
		auto head = fqn.substr(0, separatorIdx);
		auto tail = fqn.substr(separatorIdx + 1, std::string::npos);

		BlockPtr foundBlock =
				findBlockByNameOrError(head,
						"CompositeBlock::getBlockByName(): Unable to find an block named "
								+ head);

		if (!foundBlock->hasSubBlocks()) {
			Error(
					"CompositeBlock::getBlockByName(): Unable to descend. "
							+ head + " is not a CompositeBlock");
		}
		return foundBlock->getSubBlockByName(tail);
	}
	return nullptr;
}

CompositeBlock::BlockPtr CompositeBlock::findBlockByNameOrError(const std::string &fqn,
		const std::string &errorMsg) {
	auto iter = std::find_if(blocks.begin(), blocks.end(), [&](auto b) {
		return b->getBlockName() == fqn;
	});
	if (iter != blocks.end()) {
		return *iter;
	} else {
		Error(errorMsg);
	}
	return nullptr;

}
