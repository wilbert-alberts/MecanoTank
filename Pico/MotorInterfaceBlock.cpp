#include <string>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

#include "MotorInterfaceBlock.hpp"

#define WRAP_LEVEL (1000)

MotorInterfaceBlock::MotorInterfaceBlock(const std::string &bn, uint8_t pin, uint8_t dir)
    : Block("MotdorInterfaceBlock", bn)
    , safePWM(0.0), input(&safePWM), sliceNum(0), channel(0), pwmPin(pin), dirPin(dir)
{
    gpio_set_function(pwmPin, GPIO_FUNC_PWM);
    sliceNum = pwm_gpio_to_slice_num(pwmPin);
    channel = pwm_gpio_to_channel(pwmPin);
    pwm_set_wrap(sliceNum, WRAP_LEVEL);
}

void MotorInterfaceBlock::setInput(double *src)
{
    input = src;
}

void MotorInterfaceBlock::calculate()
{
    double pwm = enforceLimits(*input);

    uint8_t dirValue = 1;
    if (pwm < 0)
        dirValue = 0;

    pwm = abs(pwm);

    uint pwmInt = (uint)(pwm * WRAP_LEVEL);
    pwm_set_chan_level(sliceNum, channel, pwmInt);
    gpio_put(dirPin, dirValue);
}

double MotorInterfaceBlock::enforceLimits(double v)
{
    if (v > 1.0)
        return 1.0;
    if (v < -1.0)
        return -1.0;
    return v;
}
