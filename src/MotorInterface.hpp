#ifndef MOTORINTERFACE_HPP_
#define MOTORINTERFACE_HPP_

#include <Arduino.h>
#include "Block.hpp"

#define PWM_FREQ (5000)
#define PWM_RESOLUTION (10)
#define PWM_MAX (1 << PWM_RESOLUTION)


#define CHANNEL_FL (0)
#define CHANNEL_FR (0)
#define CHANNEL_BL (0)
#define CHANNEL_BR (0)

#define PIN_PWM_FL (0)
#define PIN_PWM_FR (0)
#define PIN_PWM_BL (0)
#define PIN_PWM_BR (0)

#define PIN_DIR_FL (0)
#define PIN_DIR_FR (0)
#define PIN_DIR_BL (0)
#define PIN_DIR_BR (0)

class MotorInterface : public Block
{
public:
    MotorInterface(const std::string &bn, double p,
                   uint8_t channel, uint8_t pwmPin,
                   uint8_t directionPin, bool *enabled);
    virtual ~MotorInterface();

    void setPWMIn(double* p);

    virtual void calculate();


private:
    uint8_t directionPin;
    uint8_t channel;
    double *pwmIn;
    double safeValue;
    bool *enabled;
};

#endif