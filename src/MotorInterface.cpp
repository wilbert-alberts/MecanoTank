#include <iostream>

#include "MotorInterface.hpp"

MotorInterface::MotorInterface(const std::string &bn, double p,
                               uint8_t channel, uint8_t pp, uint8_t dp, bool *en)
    : Block("MotorInterface", bn, p),
      directionPin(dp),
      channel(channel),
      pwmIn(&safeValue),
      safeValue(0.0), enabled(en)
{
    std::cout << "MotorInterface::MotorInterface(" << bn << ")" << std::endl;
    std::cout << "pwm: " << (int)pp << std::endl;
    std::cout << "dir: " << (int)dp << std::endl;
    std::cout << "channel: " << (int)channel << std::endl;

    // Set direction pin to output
    pinMode(dp, OUTPUT);

    // attach the channel to the GPIO to be controlled
    pinMode(pp, OUTPUT);
    ledcAttachPin(pp, channel);

    // configure LED PWM functionalitites
    ledcSetup(channel, PWM_FREQ, PWM_RESOLUTION);

    // Serial.println("MotorInterface::MotorInterface() exit");
}

MotorInterface::~MotorInterface()
{
}
void MotorInterface::setPWMIn(double *p)
{
    pwmIn = p;
}

void MotorInterface::calculate()
{
    if (*enabled)
    {
        uint16_t pwmValue = abs(*pwmIn) * PWM_MAX;
        if (*pwmIn < 0)
        {
            digitalWrite(directionPin, false);
        }
        else
        {
            digitalWrite(directionPin, true);
        }
        ledcWrite(channel, pwmValue);
    }
    else
    {
        digitalWrite(directionPin, false);
        ledcWrite(channel, 0);
    }
}