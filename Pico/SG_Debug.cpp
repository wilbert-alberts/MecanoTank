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
    Block *b1 = new DebugBlock("block 1");
    SignalGeneratorBlock *sg = new SignalGeneratorBlock("Generator FL");
    Block *b3 = new ABDecoderBlock("FrontLeft", PIN_IN_FRONT_LEFT_A, PIN_IN_FRONT_LEFT_B);
    MotorInterfaceBlock *mi = new MotorInterfaceBlock("FrontLeft", PIN_OUT_FRONT_LEFT_PWM, PIN_OUT_FRONT_LEFT_DIR);

    sequence.push_back(b1);
    sequence.push_back(sg);
    sequence.push_back(b3);
    sequence.push_back(mi);

    mi->setInput(sg->getOutput());
}
