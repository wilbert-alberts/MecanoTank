#ifndef SG_SINGLE_MOTOR_INTERFACE_HPP_
#define SG_SINGLE_MOTOR_INTERFACE_HPP_

#include <vector>

#include "ServoGroup.hpp"
#include "MotorInterface.hpp"

class SG_QuadMotorInterface : public ServoGroup
{
public:
    SG_QuadMotorInterface(double p);
    virtual ~SG_QuadMotorInterface();
    std::vector<Block *> *getSequence();

    void setFL(double dc);
    void setFR(double dc);
    void setBL(double dc);
    void setBR(double dc);
    void enable();
    void disable();

private:
    std::vector<Block *> sequence;

    boolean enabled;
    double dcFL;
    double dcFR;
    double dcBL;
    double dcBR;

    void conditionallyConstructMI(MotorInterface **mi,
                const std::string &n,
                uint8_t channel,
                uint8_t pwm,
                uint8_t dir,
                double *dc);

    MotorInterface *miFL;
    MotorInterface *getMotorInterfaceFL();

    MotorInterface *miFR;
    MotorInterface *getMotorInterfaceFR();

    MotorInterface *miBL;
    MotorInterface *getMotorInterfaceBL();

    MotorInterface *miBR;
    MotorInterface *getMotorInterfaceBR();
};

#endif