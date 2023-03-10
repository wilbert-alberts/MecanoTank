#ifndef SG_MOTORINTEGRATION_HPP_
#define SG_MOTORINTEGRATION_HPP_

#include <vector>

#include "ServoGroup.hpp"
#include "Block.hpp"
#include "Sum.hpp"
#include "MotorSystem.hpp"
#include "MotorInterface.hpp"
#include "RedButton.hpp"

class SG_MotorIntegration : public ServoGroup
{
public:
    SG_MotorIntegration(double p, uint8_t redbuttonPin);
    virtual ~SG_MotorIntegration();
    std::vector<Block *> *getSequence();
    Sum *getInjX();
    Sum *getInjY();
    Sum *getInjRz();

private:
    bool emergencyStop;
    uint8_t redButtonPin;

    std::vector<Block *> sequence;
    double period;

    Sum *injX;
    Sum *injY;
    Sum *injRz;

    MotorSystem *motorSysX;
    MotorSystem *getMotorSysX();

    MotorSystem *motorSysY;
    MotorSystem *getMotorSysY();

    MotorSystem *motorSysRz;
    MotorSystem *getMotorSysRz();

    Sum *sumFR;
    Sum *getSumFR();
    Sum *sumFL;
    Sum *getSumFL();
    Sum *sumBR;
    Sum *getSumBR();
    Sum *sumBL;
    Sum *getSumBL();

    RedButton* rbp;
    RedButton* getRedButton();

    MotorInterface *motoIfFL;
    MotorInterface *getMotorInterfaceFL();

    MotorInterface *motoIfFR;
    MotorInterface *getMotorInterfaceFR();

    MotorInterface *motoIfBL;
    MotorInterface *getMotorInterfaceBL();

    MotorInterface *motoIfBR;
    MotorInterface *getMotorInterfaceBR();
};

#endif