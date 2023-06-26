#ifndef __MOTOR_INTERFACE_HPP__
#define __MOTOR_INTERFACE_HPP__

#define WRAP_LEVEL (1000)

#include <stdint.h>
#include <string>

#include "BL.hpp"


class MotorInterfaceBlock : public Block {
public:
    MotorInterfaceBlock(const std::string& bn, uint8_t pin, uint8_t dir) ;
    ~MotorInterfaceBlock() {}
    void setInput(float* src);
    void setBatteryFactor (float *bf);

protected:
    virtual void calculate(int64_t counter) ;

private:
    float safePWM;
    float* input;
    float* batFactor;
    
    uint sliceNum;
    uint channel;
    uint pwmPin;
    uint dirPin;

    float enforceLimits(float v);
};

#endif