#ifndef SERVOGROUP_HPP_
#define SERVOGROUP_HPP_

#include <vector>
#include <string>

#include "Block.hpp"

class ServoGroup
{
public:
    ServoGroup(const std::string& name, double period);
    const std::string& getName();
    double getPeriod();
    std::vector<Block *> *getSequence();
    void executeSequence();
    int64_t getCounter();

protected:
    const std::string& name;
    std::vector<Block *>    sequence;
    int64_t counter;
    double period;
};

#endif
