#ifndef SG_DEBUG_HPP
#define SG_DEBUG_HPP

#include "SG.hpp"

class SG_Debug: public ServoGroup
{
public:
    SG_Debug() ;
    virtual ~SG_Debug(){};
private:
    double dc;
};

#endif