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
#include "BL_WorldToCart.hpp"
#include "BL_CartToWheels.hpp"

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

        addAndSetupTransformers();

        addAndSetupABDecoders();

        addAndSetupPIDs();

        setInput("worldToCart.worldX", getOutput("SPG.x").result);
        setInput("worldToCart.worldY", getOutput("SPG.y").result);
        setInput("worldToCart.worldRZ", getOutput("SPG.rz").result);

        setInput("cartToWheels.cartX", getOutput("worldToCart.cartX").result);
        setInput("cartToWheels.cartY", getOutput("worldToCart.cartY").result);
        setInput("cartToWheels.cartRZ", getOutput("worldToCart.cartRZ").result);

        setInput("pids.BL.setpoint", getOutput("cartToWheels.wheelBL").result);
        setInput("pids.FL.setpoint", getOutput("cartToWheels.wheelFL").result);
        setInput("pids.FR.setpoint", getOutput("cartToWheels.wheelFR").result);
        setInput("pids.BR.setpoint", getOutput("cartToWheels.wheelBR").result);

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

        spgBlock->setParameter(SPGBlock::X_MAXV, 0.5);
        spgBlock->setParameter(SPGBlock::X_MAXA, 0.25);
        spgBlock->setParameter(SPGBlock::X_MAXJ, 1);

        spgBlock->setParameter(SPGBlock::Y_MAXV, 0.5);
        spgBlock->setParameter(SPGBlock::Y_MAXA, 0.25);
        spgBlock->setParameter(SPGBlock::Y_MAXJ, 1);

        spgBlock->setParameter(SPGBlock::RZ_MAXV, 0.5);
        spgBlock->setParameter(SPGBlock::RZ_MAXA, 0.25);
        spgBlock->setParameter(SPGBlock::RZ_MAXJ, 1);


        SPGBlock::Position pos{0.0, 0.0, 0.0};
        spgBlock->setPosition(pos);
    }

    void addAndSetupTransformers() {
        auto worldToCartBlock = std::make_shared<WorldToCartBlock>("worldToCart");
        addBlock(worldToCartBlock);

        auto cartToWheelsBlock = std::make_shared<CartToWheelsBlock>("cartToWheels");
        addBlock(cartToWheelsBlock);
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