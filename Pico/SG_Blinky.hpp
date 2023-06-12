#ifndef __SG_BLINKY_HPP__
#define __SG_BLINKY_HPP__

#include <memory>
#include <string>
#include <iostream>

#include "SG.hpp"

#include "HSI.hpp"
#include "BL_Debug.hpp"
#include "BL_ABDecoder.hpp"
#include "BL_MotorInterface.hpp"
#include "BL_SignalGenerator.hpp"
#include "BL_Differentiator.hpp"
#include "BL_ErrorDifference.hpp"
#include "BL_PID.hpp"
#include "BL_Sum.hpp"
#include "BL_Leaf.hpp"
#include "BL_Analog.hpp"

class BlinkBlock : public Block
{
public:
    BlinkBlock(const std::string &bn, uint _pin)
        : Block("BlinkBlock", bn), pin(_pin)
    {
        gpio_set_dir(pin, GPIO_OUT);
        gpio_set_function(pin, GPIO_FUNC_SIO);
    }
    virtual ~BlinkBlock() {}
    virtual void calculate()
    {
        static uint state = 1;
        state = 1 - state;
        gpio_put(pin, state);
        std::cout << "State on cout: " << state << std::endl;
        std::cerr << "State on cerr: " << state << std::endl;
    }

protected:
    uint pin;
};


class SG_Blinky : public ServoGroup
{
public:
    SG_Blinky()
        : ServoGroup("SG_Blinky", SERVO_PERIOD)
    {
        blocks.push_back(std::make_shared<BlinkBlock>("Blinky", 5));
        blocks.push_back(std::make_shared<CPUTempBlock>("cpuTemp"));
    }

    virtual ~SG_Blinky(){};

private:
};

#endif