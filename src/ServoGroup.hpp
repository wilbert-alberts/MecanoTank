#ifndef SERVOGROUP_HPP_
#define SERVOGROUP_HPP_

#include <vector>
#include "Block.hpp"

class ServoGroup
{
public:
    ServoGroup(double p);
    double getPeriod();
    virtual std::vector<Block *> *getSequence() = 0;

private:
    double period;
};

#endif
