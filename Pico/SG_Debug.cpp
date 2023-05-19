#include "SG_Debug.hpp"


#include "HSI.hpp"

#include "DebugBlock.hpp"
#include "ABDecoderBlock.hpp"
#include "MotorInterfaceBlock.hpp"


SG_Debug::SG_Debug()
    : ServoGroup("DebugSG", 1.0)
{
    Block *b1 = new DebugBlock("block 1");
    Block *b2 = new DebugBlock("block 2");
    Block *b3 = new ABDecoderBlock("FrontLeft", PIN_IN_FRONT_LEFT_A, PIN_IN_FRONT_LEFT_B);
    Block *b4 = new MotorInterfaceBlock("FrontLeft", PIN_OUT_FRONT_LEFT_PWM, PIN_OUT_FRONT_LEFT_DIR);

    sequence.push_back(b1);
    sequence.push_back(b2);
    sequence.push_back(b3);
}
