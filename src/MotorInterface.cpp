#include "MotorInterface.hpp"

MotorInterface::MotorInterface(const std::string &bn, double p,
                               uint8_t channel, uint8_t pp, uint8_t dp, bool *en)
    : Block("MotorInterface", bn, p), directionPin(dp), channel(channel),
      pwmIn(&safeValue), safeValue(0.0), enabled(en)
{
    // configure LED PWM functionalitites
    ledcSetup(channel, PWM_FREQ, PWM_RESOLUTION);

    // attach the channel to the GPIO to be controlled
    ledcAttachPin(pp, channel);
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
        ledcWrite(channel, 0);
    }
}