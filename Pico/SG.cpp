
#include "SG.hpp"
#include "BL.hpp"

#include "BL_Trace.hpp"

ServoGroup::ServoGroup(const std::string &n, double p)
    : CompositeBlock(n, std::vector<CompositeBlock::BlockPtr>()), counter(0), period(p)
{
    traceBlock = std::make_shared<TraceBlock>();
    blocks.push_back(traceBlock);
}

ServoGroup::~ServoGroup()
{
}

const std::string &ServoGroup::getName()
{
    // Serial.println("ServoGroup::getPeriod()");
    return getBlockName();
}

std::vector<std::string> ServoGroup::getOutputNames()
{
    // Differs from the composite block by the fact that 
    // the name of the ServoGroup itsels does not need to be
    // prefixed.
	auto result = std::vector<std::string>();
	for(auto b: blocks) {
		auto blockOutputs = b->getOutputNames();
		for (auto n: blockOutputs) {
			result.push_back(n);
		}
	}
	return result;
}
double ServoGroup::getPeriod()
{
    // Serial.println("ServoGroup::getPeriod()");
    return period;
}

int64_t ServoGroup::getCounter()
{
    // Serial.println("ServoGroup::getPeriod()");
    return counter;
}

void ServoGroup::addBlock(Block::BlockPtr blockPtr)
{
    auto iter = blocks.end();
    iter--; // iter now points at the traceblock;
    blocks.insert(iter, blockPtr);
}

TraceBlock *ServoGroup::getTraceBlock()
{
    return traceBlock.get();
}

void ServoGroup::executeSequence()
{
    for (auto b : blocks)
    {
        b->calculate();
    }

    counter++;
}
