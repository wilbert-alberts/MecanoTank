#ifndef SERVOGROUP_HPP_
#define SERVOGROUP_HPP_

#include <vector>
#include <string>

#include "BL_Composite.hpp"

class ServoGroup: public CompositeBlock
{
public:
    ServoGroup(const std::string& name, double period);
    const std::string& getName();
    double getPeriod();
    std::vector<Block *> *getSequence();

    void executeSequence();
    int64_t getCounter();

protected:
    int64_t counter;
    double period;
};

#endif
