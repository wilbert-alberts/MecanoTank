/*
 * CompositeBlock.cpp
 *
 *  Created on: 26 mei 2023
 *      Author: wilbert
 */

#include <algorithm>

#include "BL_Composite.hpp"

#include "T_Composite.hpp"
#include "T_ID.hpp"

const std::string CompositeBlock::separator(".");

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
	const auto head = ct->getHead();

	const std::string headIDName = head.getID();
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

double* CompositeBlock::getOutput(const CompositeTerminal &ct) {
	const auto head = ct.getHead();

	const std::string headIDName = head.getID();
	auto iter = std::find_if(blocks.begin(), blocks.end(), [&](auto b) {
		return b->getBlockName() == headIDName;
	});
	if (iter != blocks.end()) {
		auto block = *iter;
		return block->getOutput(ct.getTail());
	}
	// Todo: deal with block not found?
	return nullptr;
}

void CompositeBlock::setInput(const Terminal &t, double *src) {
	const CompositeTerminal *ct = dynamic_cast<const CompositeTerminal*>(&t);
	const auto head = ct->getHead();

	const std::string headIDName = head.getID();
	auto iter = std::find_if(blocks.begin(), blocks.end(), [&](auto b) {
		return b->getBlockName() == headIDName;
	});
	if (iter != blocks.end()) {
		auto block = *iter;
		block->setInput(ct->getTail(), src);
	}
	// Todo: deal with block not found?
}

void CompositeBlock::setInput(const CompositeTerminal &ct, double *src) {
	const auto head = ct.getHead();

	const std::string headIDName = head.getID();
	auto iter = std::find_if(blocks.begin(), blocks.end(), [&](auto b) {
		return b->getBlockName() == headIDName;
	});
	if (iter != blocks.end()) {
		auto block = *iter;
		block->setInput(ct.getTail(), src);
	}
	// Todo: deal with block not found?
}

Block* CompositeBlock::getBlockByName(const std::string& fqn) {
	size_t separatorIdx = fqn.find(separator);
	if (separatorIdx == std::string::npos) {
		auto iter = std::find_if(blocks.begin(), blocks.end(), [&](Block* b) {
			return b->getBlockName() == fqn;
		});
		if (iter != blocks.end()) {
			return *iter;
		}
		else {
			return nullptr;
		}
	}
	else {
		auto head = fqn.substr(0,  separatorIdx);
		auto tail = fqn.substr(separatorIdx+1, std::string::npos);

		auto iter = std::find_if(blocks.begin(), blocks.end(), [&](const Block* b) {
			return b->getBlockName() == head;
		});
		if (iter != blocks.end()) {
			auto foundCompositeBlock = dynamic_cast<CompositeBlock*>(*iter);

			if (foundCompositeBlock != nullptr) {
				return foundCompositeBlock->getBlockByName(tail);
			}
			else {
				return nullptr;
			}

		}
		else {
			return nullptr;
		}
	}

}
