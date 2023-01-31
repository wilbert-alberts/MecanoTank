#include "MotorSystem.hpp"

MotorSystem::MotorSystem(const std::string &bn, double p, double fl, double fr, double bl, double br)
    : Block("MotorSystem", bn, p), safeValue(0), frontLeft(fl), frontRight(fr), backLeft(bl), backRight(br), in(&safeValue),
      outputFrontLeft(0), outputFrontRight(0), outputBackLeft(0), outputBackRight(0)
{
}

MotorSystem::~MotorSystem(){};

void MotorSystem::calculate()
{
    outputFrontLeft = *in * frontLeft;
    outputFrontRight = *in * frontRight;
    outputBackLeft = *in * backLeft;
    outputBackRight = *in * backRight;
}

void MotorSystem::setInput(double *r)
{
    in = r;
}

double *MotorSystem::getOutputFrontLeft()
{
    return &outputFrontLeft;
}

double *MotorSystem::getOutputFrontRight()
{
    return &outputFrontRight;
}

double *MotorSystem::getOutputBackLeft()
{
    return &outputBackLeft;
}

double *MotorSystem::getOutputBackRight()
{
    return &outputBackRight;
}