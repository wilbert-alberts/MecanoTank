#ifndef MOTORSYSTEM_H_
#define MOTORSYSTEM_H_

#include "Block.hpp"

class MotorSystem: public Block
{
public: 
    MotorSystem(double p, double fl, double fr, double bl, double br);
    virtual ~MotorSystem();

    virtual void calculate();

    void setInput(double* r);
    double* getOutputFrontLeft();
    double* getOutputFrontRight();
    double* getOutputBackLeft();
    double* getOutputBackRight();

private:
    double safeValue;
    double frontLeft;
    double frontRight;
    double backLeft;
    double backRight;
    double* in;
    double outputFrontLeft;
    double outputFrontRight;
    double outputBackLeft;
    double outputBackRight;
};
#endif

