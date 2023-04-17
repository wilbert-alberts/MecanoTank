#include "MotorInterface.hpp"

MotorInterface::MotorInterface(const std::string &bn, double p,
                               uint8_t channel, uint8_t pp, uint8_t dp, bool *en)
    : Block("MotorInterface", bn, p),
      directionPin(dp),
      channel(channel),
      pwmIn(&safeValue),
      safeValue(0.0), enabled(en)
{
    // Serial.println("MotorInterface::MotorInterface()");
    // Serial.print("pin: "); Serial.println(pp);
    // Serial.print("channel: "); Serial.println(channel);

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
        ledcWrite(channel, 0);
    }
}