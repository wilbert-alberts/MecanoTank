#ifndef __SG_MOTORCONTROLLER_HPP__
#define __SG_MOTORCONTROLLER_HPP__

#include <memory>

#include "SG.hpp"

#include "HSI.hpp"

#include "BL_SPG.hpp"
#include "BL_Composite.hpp"
#include "BL_ABDecoder.hpp"
#include "BL_PID.hpp"
#include "BL_MotorInterface.hpp"

// #include "BL_Debug.hpp"
// #include "BL_SignalGenerator.hpp"
// #include "BL_Differentiator.hpp"
// #include "BL_ErrorDifference.hpp"
// #include "BL_Sum.hpp"

class DecoderBlockGroup : public CompositeBlock
{
public:
    DecoderBlockGroup(const std::string &bn) : CompositeBlock(bn)
    {
        std::shared_ptr<ABDecoderBlock> backLeft = std::make_shared<ABDecoderBlock>("BL",
                                                                                    PIN_IN_BACK_LEFT_A,
                                                                                    PIN_IN_BACK_LEFT_B,
                                                                                    METERS_PER_INCREMENT);
        addBlock(backLeft);
        std::shared_ptr<ABDecoderBlock> frontLeft = std::make_shared<ABDecoderBlock>("FL",
                                                                                     PIN_IN_FRONT_LEFT_A,
                                                                                     PIN_IN_FRONT_LEFT_B,
                                                                                     METERS_PER_INCREMENT);
        addBlock(frontLeft);
        std::shared_ptr<ABDecoderBlock> frontRight = std::make_shared<ABDecoderBlock>("FR",
                                                                                      PIN_IN_FRONT_RIGHT_A,
                                                                                      PIN_IN_FRONT_RIGHT_B,
                                                                                      METERS_PER_INCREMENT);
        addBlock(frontRight);
        std::shared_ptr<ABDecoderBlock> backRight = std::make_shared<ABDecoderBlock>("BR",
                                                                                     PIN_IN_BACK_RIGHT_A,
                                                                                     PIN_IN_BACK_RIGHT_B,
                                                                                     METERS_PER_INCREMENT);
        addBlock(backRight);
    }
    virtual ~DecoderBlockGroup() {}
};

class PIDBlockGroup : public CompositeBlock
{
public:
    PIDBlockGroup(const std::string &bn, double servoFreq, bool avoidWindup) : CompositeBlock(bn)
    {
        std::shared_ptr<PIDBlock> backLeft = std::make_shared<PIDBlock>("BL", servoFreq, avoidWindup);
        addBlock(backLeft);
        std::shared_ptr<PIDBlock> frontLeft = std::make_shared<PIDBlock>("FL", servoFreq, avoidWindup);
        addBlock(frontLeft);
        std::shared_ptr<PIDBlock> frontRight = std::make_shared<PIDBlock>("FR", servoFreq, avoidWindup);
        addBlock(frontRight);
        std::shared_ptr<PIDBlock> backRight = std::make_shared<PIDBlock>("BR", servoFreq, avoidWindup);
        addBlock(backRight);
    }
    virtual ~PIDBlockGroup() {}
};

class MotorBlockGroup : public CompositeBlock
{
public:
    MotorBlockGroup(const std::string &bn) : CompositeBlock(bn)
    {
        std::shared_ptr<MotorInterfaceBlock> backLeft = std::make_shared<MotorInterfaceBlock>("BL", PIN_OUT_BACK_LEFT_PWM, PIN_OUT_BACK_LEFT_DIR);
        addBlock(backLeft);
        std::shared_ptr<MotorInterfaceBlock> frontLeft = std::make_shared<MotorInterfaceBlock>("FL", PIN_OUT_FRONT_LEFT_PWM, PIN_OUT_FRONT_LEFT_DIR);
        addBlock(frontLeft);
        std::shared_ptr<MotorInterfaceBlock> frontRight = std::make_shared<MotorInterfaceBlock>("FR", PIN_OUT_FRONT_RIGHT_PWM, PIN_OUT_FRONT_RIGHT_DIR);
        addBlock(frontRight);
        std::shared_ptr<MotorInterfaceBlock> backRight = std::make_shared<MotorInterfaceBlock>("BR", PIN_OUT_BACK_RIGHT_PWM, PIN_OUT_BACK_RIGHT_DIR);
        addBlock(backRight);
    }
    virtual ~MotorBlockGroup() {}
};
class SG_MotorController : public ServoGroup
{
public:
    SG_MotorController()
        : ServoGroup("SG_MotorController", SERVO_PERIOD)
    {
        addAndSetupSPG();

        addAndSetupABDecoders();

        addAndSetupPIDs();

        setInput("pids.BL.setpoint", getOutput("SPG.x").result);
        setInput("pids.FL.setpoint", getOutput("SPG.y").result);
        setInput("pids.FR.setpoint", getOutput("SPG.rz").result);
        setInput("pids.BR.setpoint", getOutput("SPG.x").result);

        setInput("pids.BL.actual", getOutput("decoders.BL.output").result);
        setInput("pids.FL.actual", getOutput("decoders.FL.output").result);
        setInput("pids.FR.actual", getOutput("decoders.FR.output").result);
        setInput("pids.BR.actual", getOutput("decoders.BR.output").result);

        addAndSetupMotors();

        setInput("motors.BL.input", getOutput("pids.BL.output").result);
        setInput("motors.FL.input", getOutput("pids.FL.output").result);
        setInput("motors.FR.input", getOutput("pids.FR.output").result);
        setInput("motors.BR.input", getOutput("pids.BR.output").result);

    }
    virtual ~SG_MotorController(){};

private:
    std::shared_ptr<SPGBlock> spgBlock;
    std::shared_ptr<DecoderBlockGroup> abDecoders;

    void addAndSetupSPG()
    {
        spgBlock = std::make_shared<SPGBlock>("SPG", SERVO_FREQUENCY);
        addBlock(spgBlock);

        SPGBlock::MovementParameters mp;
        mp.x.j = 10.0;
        mp.x.a = 0.05;
        mp.x.v = 1;

        mp.y = mp.x;
        mp.rz = mp.x;

        spgBlock->setMovementParameters(mp);

        SPGBlock::Position pos{0.0, 0.0, 0.0};
        spgBlock->setPosition(pos);
    }

    void addAndSetupABDecoders()
    {
        auto abDecoderBlockGroup = std::make_shared<DecoderBlockGroup>("decoders");
        addBlock(abDecoderBlockGroup);
    }

    void addAndSetupPIDs()
    {
        auto pidBlockGroup = std::make_shared<PIDBlockGroup>("pids", SERVO_FREQUENCY, true);
        addBlock(pidBlockGroup);
    }

    void addAndSetupMotors()
    {
        // auto batteryBlock = std::make_shared<AnalogInBlock>("battery", BAT_VOLT_ADC_INPUT);

        auto motorBlockGroup = std::make_shared<MotorBlockGroup>("motors");
        addBlock(motorBlockGroup);
    }
};

#endif