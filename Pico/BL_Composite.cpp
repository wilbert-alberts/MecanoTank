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

CompositeBlock::CompositeBlock(const std::string &bn) : Block("CompositeBlock", bn), blocks(std::vector<BlockPtr>())
{
}

CompositeBlock::CompositeBlock(const std::string &bn,
							   std::vector<BlockPtr> _blocks) : Block("CompositeBlock", bn), blocks(_blocks)
{
}

CompositeBlock::~CompositeBlock()
{
}

void CompositeBlock::addBlock(Block::BlockPtr blockPtr)
{
    blocks.push_back(blockPtr);
}
void CompositeBlock::calculate()
{
	for (auto b : blocks)
	{
		b->calculate();
	}
}

SuccessT<double *> CompositeBlock::getOutput(const Terminal &t)
{
	if (!t.hasCompositeStructure())
		return SuccessT<double *>(nullptr, false,
								  "CompositeBlock::getOutput(): Expected an CompositeTerminal but got something else");

	const Terminal &head = t.getHead();
	if (!head.hasID())
		return SuccessT<double *>(nullptr, false,
								  "CompositeBlock::getOutput(): Expected the head of the composite input terminal to have an ID but id doesn't");

	const std::string &headIDName = head.getID();
	auto block = findBlockByNameOrError(headIDName,
										"CompositeBlock::getOutput(): Unable to find an block named " + headIDName);
	if (block.success)
	{
		return block.result->getOutput(t.getTail());
	}
	else
	{
		return SuccessT<double *>(nullptr, false, block.errorMsg);
	}
}

SuccessT<double *> CompositeBlock::getOutput(const CompositeTerminal &ct)
{
	const Terminal &head = ct.getHead();

	const std::string &headIDName = head.getID();
	auto block = findBlockByNameOrError(headIDName,
										"CompositeBlock::getOutput(): Unable to find an block named " + headIDName);
	if (block.success)
	{
		return block.result->getOutput(ct.getTail());
	}
	else
	{
		return nullptr;
	}
}

SuccessT<double *> CompositeBlock::getOutput(const std::string &tid)
{
	auto t = TerminalFactory::createFromString(tid);
	return getOutput(*t);
}

SuccessT<double *> CompositeBlock::getOutput()
{
	return getOutput(Block::OUT_OUTPUT);
}

std::vector<std::string> CompositeBlock::getOutputNames()
{
	auto result = std::vector<std::string>();
	for(auto b: blocks) {
		auto blockOutputs = b->getOutputNames();
		for (auto n: blockOutputs) {
			result.push_back(blockName + separator + n);
		}
	}
	return result;
}

void CompositeBlock::setInput(const Terminal &t, double *src)
{
	if (!t.hasCompositeStructure())
	{
		Error(
			"CompositeBlock::setInput(): Expected an CompositeTerminal but got something else");
	}
	const Terminal &head = t.getHead();

	const std::string &headIDName = head.getID();
	auto block = findBlockByNameOrError(headIDName,
										"CompositeBlock::setInput(): Unable to find an block named " + headIDName);
	if (block.success)
		block.result->setInput(t.getTail(), src);
}

void CompositeBlock::setInput(const CompositeTerminal &ct, double *src)
{
	const Terminal &head = ct.getHead();

	const std::string headIDName = head.getID();
	auto block = findBlockByNameOrError(headIDName,
										"CompositeBlock::setInput(): Unable to find an block named " + headIDName);
	if (block.success)
		block.result->setInput(ct.getTail(), src);
}

void CompositeBlock::setInput(const std::string &tid, double *src)
{
	auto t = TerminalFactory::createFromString(tid);
	setInput(*t, src);
}

void CompositeBlock::setInput(double *src)
{
	setInput(Block::IN_INPUT, src);
}

bool CompositeBlock::hasSubBlocks() const
{
	return true;
}

SuccessT<Block::BlockPtr> CompositeBlock::getSubBlockByName(const std::string &fqn)
{
	size_t separatorIdx = fqn.find(separator);
	if (separatorIdx == std::string::npos)
	{
		auto block =
			findBlockByNameOrError(fqn,
								   "CompositeBlock::getBlockByName(): Unable to find an block named " + fqn);
		return block;
	}
	else
	{
		auto head = fqn.substr(0, separatorIdx);
		auto tail = fqn.substr(separatorIdx + 1, std::string::npos);

		SuccessT<Block::BlockPtr> foundBlock =
			findBlockByNameOrError(head,
								   "CompositeBlock::getBlockByName(): Unable to find an block named " + head);

		if (foundBlock.success && !(foundBlock.result)->hasSubBlocks())
		{
			Error(
				"CompositeBlock::getBlockByName(): Unable to descend. " + head + " is not a CompositeBlock");
		}
		auto r = foundBlock.result->getSubBlockByName(tail);

		return r;
	}
	return SuccessT<Block::BlockPtr>(nullptr, false, "Unreacheable code");
}

SuccessT<Block::BlockPtr> CompositeBlock::findBlockByNameOrError(const std::string &fqn,
																 const std::string &errorMsg)
{
	auto iter = std::find_if(blocks.begin(), blocks.end(), [&](auto b)
							 { return b->getBlockName() == fqn; });
	if (iter != blocks.end())
	{
		return SuccessT<Block::BlockPtr>(*iter);
	}
	return SuccessT<Block::BlockPtr>(nullptr, false, errorMsg);
}
