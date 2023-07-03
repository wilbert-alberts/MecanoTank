#ifndef __MOTOR_INTERFACE_HPP__
#define __MOTOR_INTERFACE_HPP__

#define WRAP_LEVEL (1000)

#include <stdint.h>
#include <string>

#include "BL_Leaf.hpp"
#include "T.hpp"

class MotorInterfaceBlock : public LeafBlock {
public:
    MotorInterfaceBlock(const std::string& bn, uint8_t pin, uint8_t dir) ;
    ~MotorInterfaceBlock() {}

protected:
    virtual void calculate() ;

private:
    double safePWM;
    double* input;
    double  output;
    
    uint sliceNum;
    uint channel;
    uint pwmPin;
    uint dirPin;

    double enforceLimits(double v);
};

#endif
