#ifndef __SG_MOTORCONTROLLER_HPP__
#define __SG_MOTORCONTROLLER_HPP__

#include <memory>

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
        auto spgFL = std::make_shared<SignalGeneratorBlock>("FrontLeft_SPG", 6800);

        auto abFL = std::make_shared<ABDecoderBlock>("FrontLeft", PIN_IN_FRONT_RIGHT_A, PIN_IN_FRONT_RIGHT_B);

        auto abDiffFL = std::make_shared<DifferentiatorBlock>("FrontLeft AB", SERVO_FREQUENCY);
        abDiffFL->setInput(abFL->getOutput().result);

        auto abErrorFL = std::make_shared<ErrorDifferenceBlock>("FrontLeft_Error");
        abErrorFL->setInput(ErrorDifferenceBlock::IN_ACTUAL,  abDiffFL->getOutput().result);
        abErrorFL->setInput(ErrorDifferenceBlock::IN_DESIRED, spgFL->getOutput().result);

        auto pidFL = std::make_shared<PIDBlock>("FrontLeft_PID", SERVO_FREQUENCY);
        pidFL->setInput(abErrorFL->getOutput().result);
        pidFL->setKP(20.0);

        auto sumFL = std::make_shared<SumBlock>("FrontLeft_Sum", 2);
        sumFL->setInput("0", spgFL->getOutput().result);
        sumFL->setInput("1", pidFL->getOutput().result);
        sumFL->setFactor(0, 1.0/(2*6800.0));
        sumFL->setFactor(1, 1.0/(2*6800.0));

        MotorInterfaceBlock* miFL = new MotorInterfaceBlock("FrontLeft_MI", PIN_OUT_FRONT_RIGHT_PWM, PIN_OUT_FRONT_RIGHT_DIR);
        miFL->setInput(sumFL->getOutput().result);

        blocks.push_back(spgFL);
        blocks.push_back(abFL);
        blocks.push_back(abDiffFL);
        blocks.push_back(abErrorFL);
        blocks.push_back(pidFL);
        blocks.push_back(sumFL);
        // sequence.push_back(miFL);


    }
    virtual ~SG_MotorController(){};
private:
};


#endif