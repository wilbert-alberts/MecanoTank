#ifndef SERVOGROUP_HPP_
#define SERVOGROUP_HPP_

#include <vector>
#include <string>

#include "BL_Composite.hpp"
#include "BL_Trace.hpp"

class ServoGroup: public CompositeBlock
{
public:
    ServoGroup(const std::string& name, double period);
    virtual ~ServoGroup();
    const std::string& getName();
    double getPeriod();

    std::vector<Block *> *getSequence();

    void addBlock(Block::BlockPtr blockPtr);
    TraceBlock* getTraceBlock();

    void executeSequence();
    int64_t getCounter();

	virtual std::vector<std::string> getOutputNames();

protected:
    std::shared_ptr<TraceBlock> traceBlock;
    int64_t counter;
    double period;
};

#endif
