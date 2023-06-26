#include <string>

#include <iostream>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

#include "BL_MotorInterface.hpp"

#define WRAP_LEVEL (1000)

MotorInterfaceBlock::MotorInterfaceBlock(const std::string &bn, uint8_t pin, uint8_t dir)
    : Block("MotorInterfaceBlock", bn), 
    safePWM(0.0), 
    input(&safePWM), 
    batFactor (&safePWM), 
    sliceNum(0), 
    channel(0), 
    pwmPin(pin), 
    dirPin(dir)
{
    gpio_set_dir(dirPin, GPIO_OUT);
    gpio_set_function(dirPin, GPIO_FUNC_SIO);

    gpio_set_dir(pwmPin, GPIO_OUT);
    gpio_set_function(pwmPin, GPIO_FUNC_SIO);

    sliceNum = pwm_gpio_to_slice_num(pwmPin);
    channel = pwm_gpio_to_channel(pwmPin);
    pwm_set_wrap(sliceNum, WRAP_LEVEL);

    //std::cout << "pwmPin: " << pwmPin << ", slice: " << sliceNum << ", channel: " << channel << std::endl;
}

void MotorInterfaceBlock::setInput(float *src)
{
    input = src;
}
void MotorInterfaceBlock::setBatteryFactor (float *bf)
{
    batFactor = bf;
}

void MotorInterfaceBlock::calculate(int64_t counter)
{
    float pwm = enforceLimits(*input * *batFactor);

    uint8_t dirValue = 1;
    if (pwm < 0)
        dirValue = 0;
    gpio_put(dirPin, dirValue);

    pwm = std::abs(pwm);

    // std::cout << "pwmPin: " << pwmPin << ", slice: " << sliceNum << ", channel: " << channel << std::endl;
    // std::cout << "input: " << *input << ", pwm: " << pwm << std::endl;

    uint pwmInt = (uint)(pwm * WRAP_LEVEL);
    // std::cout << "input: " << *input << ", pwm: " << pwm << ", pwmInt: " << pwmInt << std::endl;
    
    if ((pwmInt > 0) && (pwmInt < WRAP_LEVEL))
    {
        gpio_set_function(pwmPin, GPIO_FUNC_PWM);
        pwm_set_chan_level(sliceNum, channel, pwmInt);
        pwm_set_enabled(sliceNum, true);
        // std::cout << "pwm set to " << pwmInt << std::endl;
    }
    if (pwmInt == 0)
    {
        pwm_set_enabled(sliceNum, false);
        gpio_set_function(pwmPin, GPIO_FUNC_SIO);
        gpio_put(pwmPin, 0);
        // std::cout << "pwm set to zero" << std::endl;
    }
    if (pwmInt == WRAP_LEVEL)
    {
        pwm_set_enabled(sliceNum, false);
        gpio_set_function(pwmPin, GPIO_FUNC_SIO);
        gpio_put(pwmPin, 1);
        // std::cout << "pwm set to max" << std::endl;
    }
}

float MotorInterfaceBlock::enforceLimits(float v)
{
    if (v > 1.0)
        return 1.0;
    if (v < -1.0)
        return -1.0;
    return v;
}
