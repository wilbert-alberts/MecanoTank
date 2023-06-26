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

    SignalGeneratorBlock *sgFL = new SignalGeneratorBlock("Generator FL", SERVO_FREQUENCY);
    Block *abFL = new ABDecoderBlock("FrontLeft", PIN_IN_FRONT_LEFT_B, PIN_IN_FRONT_LEFT_A, METERS_PER_INCREMENT);
    MotorInterfaceBlock *miFL = new MotorInterfaceBlock("FrontLeft", PIN_OUT_FRONT_LEFT_PWM, PIN_OUT_FRONT_LEFT_DIR);

    sequence.push_back(sgFL);
    sequence.push_back(abFL);
    sequence.push_back(miFL);
    miFL->setInput(sgFL->getOutput());

    SignalGeneratorBlock *sgFR = new SignalGeneratorBlock("Generator FR", SERVO_FREQUENCY);
    Block *abFR = new ABDecoderBlock("FrontRight", PIN_IN_FRONT_RIGHT_A, PIN_IN_FRONT_RIGHT_B, METERS_PER_INCREMENT);
    MotorInterfaceBlock *miFR = new MotorInterfaceBlock("FrontRight", PIN_OUT_FRONT_RIGHT_PWM, PIN_OUT_FRONT_RIGHT_DIR);

    sequence.push_back(sgFR);
    sequence.push_back(abFR);
    sequence.push_back(miFR);
    miFR->setInput(sgFR->getOutput());

    SignalGeneratorBlock *sgBL = new SignalGeneratorBlock("Generator BL", SERVO_FREQUENCY);
    Block *abBL = new ABDecoderBlock("BackLeft", PIN_IN_BACK_LEFT_A, PIN_IN_BACK_LEFT_B, METERS_PER_INCREMENT);
    MotorInterfaceBlock *miBL = new MotorInterfaceBlock("FrontLeft", PIN_OUT_BACK_LEFT_PWM, PIN_OUT_BACK_LEFT_DIR);

    sequence.push_back(sgBL);
    sequence.push_back(abBL);
    sequence.push_back(miBL);
    miBL->setInput(sgBL->getOutput());

    SignalGeneratorBlock *sgBR = new SignalGeneratorBlock("Generator BR", SERVO_FREQUENCY);
    Block *abBR = new ABDecoderBlock("BackRight", PIN_IN_BACK_RIGHT_A, PIN_IN_BACK_RIGHT_B, METERS_PER_INCREMENT);
    MotorInterfaceBlock *miBR = new MotorInterfaceBlock("BackRight", PIN_OUT_BACK_RIGHT_PWM, PIN_OUT_BACK_RIGHT_DIR);

    sequence.push_back(sgBR);
    sequence.push_back(abBR);
    sequence.push_back(miBR);
    miBR->setInput(sgBR->getOutput());
}
