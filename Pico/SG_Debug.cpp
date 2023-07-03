#include <memory>

#include "SG_Debug.hpp"


#include "HSI.hpp"

#include "BL_Debug.hpp"
#include "BL_ABDecoder.hpp"
#include "BL_MotorInterface.hpp"
#include "BL_SignalGenerator.hpp"

SG_Debug::SG_Debug()
    : ServoGroup("DebugSG", 1.0)
    , dc(0.33)
{

    auto sgFL = std::make_shared<SignalGeneratorBlock>("Generator FL");
    auto abFL = std::make_shared<ABDecoderBlock>("FrontLeft", PIN_IN_FRONT_LEFT_B, PIN_IN_FRONT_LEFT_A,METERS_PER_INCREMENT);
    auto miFL = std::make_shared<MotorInterfaceBlock>("FrontLeft", PIN_OUT_FRONT_LEFT_PWM, PIN_OUT_FRONT_LEFT_DIR);

    blocks.push_back(sgFL);
    blocks.push_back(abFL);
    blocks.push_back(miFL);
    miFL->setInput(sgFL->getOutput().result);

    auto sgFR = std::make_shared<SignalGeneratorBlock>("Generator FR");
    auto abFR = std::make_shared<ABDecoderBlock>("FrontRight", PIN_IN_FRONT_RIGHT_A, PIN_IN_FRONT_RIGHT_B,METERS_PER_INCREMENT);
    auto miFR = std::make_shared<MotorInterfaceBlock>("FrontRight", PIN_OUT_FRONT_RIGHT_PWM, PIN_OUT_FRONT_RIGHT_DIR);

    blocks.push_back(sgFR);
    blocks.push_back(abFR);
    blocks.push_back(miFR);
    miFR->setInput(sgFR->getOutput().result);

    auto sgBL = std::make_shared<SignalGeneratorBlock>("Generator BL");
    auto abBL = std::make_shared<ABDecoderBlock>("BackLeft", PIN_IN_BACK_LEFT_A, PIN_IN_BACK_LEFT_B,METERS_PER_INCREMENT);
    auto miBL = std::make_shared<MotorInterfaceBlock>("FrontLeft", PIN_OUT_BACK_LEFT_PWM, PIN_OUT_BACK_LEFT_DIR);

    blocks.push_back(sgBL);
    blocks.push_back(abBL);
    blocks.push_back(miBL);
    miBL->setInput(sgBL->getOutput().result);

    auto sgBR = std::make_shared<SignalGeneratorBlock>("Generator BR");
    auto abBR = std::make_shared<ABDecoderBlock>("BackRight", PIN_IN_BACK_RIGHT_A, PIN_IN_BACK_RIGHT_B,METERS_PER_INCREMENT);
    auto miBR = std::make_shared<MotorInterfaceBlock>("BackRight", PIN_OUT_BACK_RIGHT_PWM, PIN_OUT_BACK_RIGHT_DIR);

    blocks.push_back(sgBR);
    blocks.push_back(abBR);
    blocks.push_back(miBR);
    miBR->setInput(sgBR->getOutput().result);
}
