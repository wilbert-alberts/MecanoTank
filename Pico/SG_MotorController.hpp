#ifndef __SG_MOTORCONTROLLER_HPP__
#define __SG_MOTORCONTROLLER_HPP__


#include "SG.hpp"

#include "HSI.hpp"
#include "BL_Debug.hpp"
#include "BL_ABDecoder.hpp"
#include "BL_MotorInterface.hpp"
#include "BL_SignalGenerator.hpp"
#include "BL_Differentiator.hpp"
#include "BL_ErrorDifference.hpp"
#include "BL_PID.hpp"
#include "BL_Sum.hpp"

class SG_MotorController: public ServoGroup
{
public:
    SG_MotorController()
    : ServoGroup("SG_MotorController", SERVO_PERIOD)
    {
        SignalGeneratorBlock* spgFL = new SignalGeneratorBlock("FrontLeft_SPG", 6800);

        ABDecoderBlock* abFL = new ABDecoderBlock("FrontLeft", PIN_IN_FRONT_RIGHT_A, PIN_IN_FRONT_RIGHT_B);

        DifferentiatorBlock* abDiffFL = new DifferentiatorBlock("FrontLeft AB", SERVO_FREQUENCY);
        abDiffFL->setInput(abFL->getOutput());

        ErrorDifferenceBlock* abErrorFL = new ErrorDifferenceBlock("FrontLeft_Error");
        abErrorFL->setInputActual(abDiffFL->getOutput());
        abErrorFL->setInputDesired(spgFL->getOutput());

        PIDBlock* pidFL = new PIDBlock("FrontLeft_PID", SERVO_FREQUENCY);
        pidFL->setInput(abErrorFL->getOutput());
        pidFL->setKP(20.0);

        SumBlock* sumFL = new SumBlock("FrontLeft_Sum", 0,1,1,0,0);
        sumFL->setIn1(spgFL->getOutput());
        sumFL->setIn2(pidFL->getOutput());
        sumFL->setFactor1(1.0/(2*6800.0));
        sumFL->setFactor2(1.0/(2*6800.0));

        MotorInterfaceBlock* miFL = new MotorInterfaceBlock("FrontLeft_MI", PIN_OUT_FRONT_RIGHT_PWM, PIN_OUT_FRONT_RIGHT_DIR);
        miFL->setInput(sumFL->getOutput());

        sequence.push_back(spgFL);
        sequence.push_back(abFL);
        sequence.push_back(abDiffFL);
        sequence.push_back(abErrorFL);
        sequence.push_back(pidFL);
        sequence.push_back(sumFL);
        // sequence.push_back(miFL);


    }
    virtual ~SG_MotorController(){};
private:
};


#endif