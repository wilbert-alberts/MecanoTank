#include "SG_SingleMotorInterface.hpp"

#include <iostream>

static double normalizeDC(double dc)
{
    if (dc < -1.0)
        dc = -1.0;
    if (dc > 1.0)
        dc = 1.0;
    return dc;
}

void SG_QuadMotorInterface::conditionallyConstructMI(
    MotorInterface **mi,
    const std::string &n,
    uint8_t channel,
    uint8_t pwm,
    uint8_t dir,
    double *dc)
{
    if (*mi == nullptr)
    {
        *mi = new MotorInterface(n,
                                 getPeriod(),
                                 channel,
                                 pwm,
                                 dir,
                                 &enabled);
        (*mi)->setPWMIn(dc);
    }
}

SG_QuadMotorInterface::SG_QuadMotorInterface(double p)
    : ServoGroup(p),
      enabled(false),
      miFL(nullptr),
      miFR(nullptr),
      miBL(nullptr),
      miBR(nullptr)
{
}

SG_QuadMotorInterface::~SG_QuadMotorInterface() {}

void SG_QuadMotorInterface::enable()
{
    enabled = true;
}

void SG_QuadMotorInterface::disable()
{
    enabled = false;
}

void SG_QuadMotorInterface::setFL(double dc)
{
    std::cout << "setPWM(FL, " << dc << ")" << std::endl;
    dcFL = normalizeDC(dc);
}

void SG_QuadMotorInterface::setFR(double dc)
{
    std::cout << "setPWM(FR, " << dc << ")" << std::endl;
    dcFR = normalizeDC(dc);
}

void SG_QuadMotorInterface::setBL(double dc)
{
    std::cout << "setPWM(BL, " << dc << ")" << std::endl;
    dcBL = normalizeDC(dc);
}

void SG_QuadMotorInterface::setBR(double dc)
{
    std::cout << "setPWM(BR, " << dc << ")" << std::endl;
    dcBR = normalizeDC(dc);
}

std::vector<Block *> *SG_QuadMotorInterface::getSequence()
{
    sequence.clear();
    sequence.push_back(getMotorInterfaceFL());
    sequence.push_back(getMotorInterfaceFR());
    sequence.push_back(getMotorInterfaceBL());
    sequence.push_back(getMotorInterfaceBR());
    return &sequence;
}

MotorInterface *SG_QuadMotorInterface::getMotorInterfaceFL()
{
    conditionallyConstructMI(&miFL, "MI_FL", CHANNEL_FL, PIN_PWM_FL, PIN_DIR_FL, &dcFL);
    return miFL;
}

MotorInterface *SG_QuadMotorInterface::getMotorInterfaceFR()
{
    conditionallyConstructMI(&miFR, "MI_FR", CHANNEL_FR, PIN_PWM_FR, PIN_DIR_FR, &dcFR);
    return miFR;
}

MotorInterface *SG_QuadMotorInterface::getMotorInterfaceBL()
{
    conditionallyConstructMI(&miBL, "MI_BL", CHANNEL_BL, PIN_PWM_BL, PIN_DIR_BL, &dcBL);
    return miBL;
}

MotorInterface *SG_QuadMotorInterface::getMotorInterfaceBR()
{
    conditionallyConstructMI(&miBR, "MI_BR", CHANNEL_BR, PIN_PWM_BR, PIN_DIR_BR, &dcBR);
    return miBR;
}
