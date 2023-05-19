#ifndef SG_DEBUG_HPP
#define SG_DEBUG_HPP

#include "ServoGroup.hpp"
#include "DebugBlock.hpp"

class SG_Debug: public ServoGroup
{
public:
    SG_Debug() ;
    virtual ~SG_Debug(){};
};

#endif