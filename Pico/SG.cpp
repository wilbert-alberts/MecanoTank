
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
    iter--; // iter now points add the traceblock;
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
