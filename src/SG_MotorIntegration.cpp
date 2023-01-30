
#include "SG_MotorIntegration.hpp"

SG_MotorIntegration::SG_MotorIntegration(double p) : ServoGroup(p), injX(nullptr), injY(nullptr), injRz(nullptr),
                                                     motorSysX(nullptr), motorSysY(nullptr), motorSysRz(nullptr),
                                                     sumFR(nullptr), sumFL(nullptr), sumBR(nullptr), sumBL(nullptr) {}

SG_MotorIntegration::~SG_MotorIntegration(){};

std::vector<Block *> *SG_MotorIntegration::getSequence()
{
    sequence.clear();

    sequence.push_back(getInjX());
    sequence.push_back(getInjY());
    sequence.push_back(getInjRz());

    sequence.push_back(getMotorSysX());
    sequence.push_back(getMotorSysY());
    sequence.push_back(getMotorSysRz());

    sequence.push_back(getSumFL());
    sequence.push_back(getSumFR());
    sequence.push_back(getSumBL());
    sequence.push_back(getSumBR());

    getMotorSysX()->setInput(getInjX()->getOutput());
    getMotorSysY()->setInput(getInjY()->getOutput());
    getMotorSysRz()->setInput(getInjRz()->getOutput());

    getSumFL()->setIn1(getMotorSysX()->getOutputFrontLeft());
    getSumFL()->setIn2(getMotorSysY()->getOutputFrontLeft());
    getSumFL()->setIn3(getMotorSysRz()->getOutputFrontLeft());

    getSumFR()->setIn1(getMotorSysX()->getOutputFrontRight());
    getSumFR()->setIn2(getMotorSysY()->getOutputFrontRight());
    getSumFR()->setIn3(getMotorSysRz()->getOutputFrontRight());

    getSumBL()->setIn1(getMotorSysX()->getOutputBackLeft());
    getSumBL()->setIn2(getMotorSysY()->getOutputBackLeft());
    getSumBL()->setIn3(getMotorSysRz()->getOutputBackLeft());

    getSumBR()->setIn1(getMotorSysX()->getOutputBackRight());
    getSumBR()->setIn2(getMotorSysY()->getOutputBackRight());
    getSumBR()->setIn3(getMotorSysRz()->getOutputBackRight());

    return &sequence;
};

Sum *SG_MotorIntegration::getInjX()
{
    if (injX == nullptr)
    {
        injX = new Sum(period, 0, 0, 0, 0, 0);
    }
    return injX;
}
Sum *SG_MotorIntegration::getInjY()
{
    if (injY == nullptr)
    {
        injY = new Sum(period, 0, 0, 0, 0, 0);
    }
    return injY;
}
Sum *SG_MotorIntegration::getInjRz()
{
    if (injRz == nullptr)
    {
        injRz = new Sum(period, 0, 0, 0, 0, 0);
    }
    return injRz;
}

MotorSystem *SG_MotorIntegration::getMotorSysX()
{
    if (motorSysX == nullptr)
    {
        motorSysX = new MotorSystem(period, 1.0, -1.0, -1.0, 1.0);
    }
    return motorSysX;
}

MotorSystem *SG_MotorIntegration::getMotorSysY()
{
    if (motorSysY == nullptr)
    {
        motorSysY = new MotorSystem(period, 1.0, 1.0, 1.0, 1.0);
    }
    return motorSysY;
}

MotorSystem *SG_MotorIntegration::getMotorSysRz()
{
    if (motorSysRz == nullptr)
    {
        motorSysRz = new MotorSystem(period, 1.0, 1.0, -1.0, -1.0);
    }
    return motorSysRz;
}

Sum *SG_MotorIntegration::getSumFR()
{
    if (sumFR == nullptr)
    {
        sumFR = new Sum(period, 0, 1.0, 1.0, 1.0, 0.0);
    }
    return sumFR;
}
Sum *SG_MotorIntegration::getSumFL()
{
    if (sumFL == nullptr)
    {
        sumFL = new Sum(period, 0, 1.0, 1.0, 1.0, 0.0);
    }
    return sumFL;
}
Sum *SG_MotorIntegration::getSumBR()
{
    if (sumBR == nullptr)
    {
        sumBR = new Sum(period, 0, 1.0, 1.0, 1.0, 0.0);
    }
    return sumBR;
}
Sum *SG_MotorIntegration::getSumBL()
{
    if (sumBL == nullptr)
    {
        sumBL = new Sum(period, 0, 1.0, 1.0, 1.0, 0.0);
    }
    return sumFL;
}

