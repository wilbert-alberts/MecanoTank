#ifndef __SG_MOTORCONTROLLER_HPP__
#define __SG_MOTORCONTROLLER_HPP__

#define USE_PID_BLOCK

#include "SG.hpp"
#include "ServoConstants.hpp"
#include "HSI.hpp"
#include "BL_Debug.hpp"
#include "BL_ABDecoder.hpp"
#include "BL_BatteryMonitor.hpp"
#include "BL_MotorInterface.hpp"
#include "BL_MultClip.hpp"
#include "BL_SignalGenerator.hpp"
#include "BL_Integrator.hpp"
#include "BL_Differentiator.hpp"
#include "BL_ErrorDifference.hpp"
#include "BL_PID.hpp"
#include "BL_Sum4.hpp"
#include "BL_Tracer.hpp"

class SG_MotorController: public ServoGroup
{
public:
    SG_MotorController()
    : ServoGroup("SG_MotorController", SERVO_PERIOD)
    {
        SignalGeneratorBlock* spg = new SignalGeneratorBlock("The_SPG", SP_SPEED, SERVO_FREQUENCY);

        ABDecoderBlock* abFL = new ABDecoderBlock("FrontLeftPos",  PIN_IN_FRONT_LEFT_A,  PIN_IN_FRONT_LEFT_B,  METERS_PER_INCREMENT);
        ABDecoderBlock* abFR = new ABDecoderBlock("FrontRightPos", PIN_IN_FRONT_RIGHT_A, PIN_IN_FRONT_RIGHT_B, METERS_PER_INCREMENT);
        ABDecoderBlock* abBL = new ABDecoderBlock("BackLeftPos",   PIN_IN_BACK_LEFT_A,   PIN_IN_BACK_LEFT_B,   METERS_PER_INCREMENT);
        ABDecoderBlock* abBR = new ABDecoderBlock("BackRightPos",  PIN_IN_BACK_RIGHT_A,  PIN_IN_BACK_RIGHT_B,  METERS_PER_INCREMENT);

        TracerBlock* FLtracer = new TracerBlock ("FrontLeftTracer",  200, SERVO_FREQUENCY);
        TracerBlock* FRtracer = new TracerBlock ("FrontRightTracer", 200, SERVO_FREQUENCY);
        TracerBlock* BLtracer = new TracerBlock ("BackLeftTracer",   200, SERVO_FREQUENCY);
        TracerBlock* BRtracer = new TracerBlock ("BackRightTracer",  200, SERVO_FREQUENCY);
        bool now=true;
        FLtracer->setStartCondition (&now);
        FRtracer->setStartCondition (&now);
        BLtracer->setStartCondition (&now);
        BRtracer->setStartCondition (&now);


        PIDBlock *pidFL = new PIDBlock ("FrontLeft_PID",  true, SERVO_FREQUENCY);
        PIDBlock *pidFR = new PIDBlock ("FrontRight_PID", true, SERVO_FREQUENCY);
        PIDBlock *pidBL = new PIDBlock ("BackLeft_PID",   true, SERVO_FREQUENCY);
        PIDBlock *pidBR = new PIDBlock ("BackRight_PID",  true, SERVO_FREQUENCY);
        BRtracer -> setStopCondition (pidBR->getTracerStopCrit ());


        pidFL->setSetpointInput (spg->getOutput ());
        pidFL->setActualInput   (abFL ->getOutput());
        pidFR->setSetpointInput (spg->getOutput ());
        pidFR->setActualInput   (abFR ->getOutput());
        pidBL->setSetpointInput (spg->getOutput ());
        pidBL->setActualInput   (abBL ->getOutput());

        pidBR->setSetpointInput (spg->getOutput ());
        pidBR->setActualInput   (abBR ->getOutput());

        FLtracer->setInput (0, "Setpoint speed FFD", pidFL->getTraceOutput (0));
        FLtracer->setInput (1, "Damping",            pidFL->getTraceOutput (1));
        FLtracer->setInput (2, "Proportional",       pidFL->getTraceOutput (2));
        FLtracer->setInput (3, "Integral",           pidFL->getTraceOutput (3));
        FLtracer->setInput (4, "PID output",         pidFL->getOutput ());

        FRtracer->setInput (0, "Setpoint speed FFD", pidFR->getTraceOutput (0));
        FRtracer->setInput (1, "Damping",            pidFR->getTraceOutput (1));
        FRtracer->setInput (2, "Proportional",       pidFR->getTraceOutput (2));
        FRtracer->setInput (3, "Integral",           pidFR->getTraceOutput (3));
        FRtracer->setInput (4, "PID output",         pidFR->getOutput ());

        BLtracer->setInput (0, "Setpoint speed FFD", pidBL->getTraceOutput (0));
        BLtracer->setInput (1, "Damping",            pidBL->getTraceOutput (1));
        BLtracer->setInput (2, "Proportional",       pidBL->getTraceOutput (2));
        BLtracer->setInput (3, "Integral",           pidBL->getTraceOutput (3));
        BLtracer->setInput (4, "PID output",         pidBL->getOutput ());

        BRtracer->setInput (0, "Setpoint speed FFD", pidBR->getTraceOutput (0));
        BRtracer->setInput (1, "Damping",            pidBR->getTraceOutput (1));
        BRtracer->setInput (2, "Proportional",       pidBR->getTraceOutput (2));
        BRtracer->setInput (3, "Integral",           pidBR->getTraceOutput (3));
        BRtracer->setInput (4, "PID output",         pidBR->getOutput ());
        BRtracer->setInput (5, "Setpoint pos",       pidBR->getTraceOutput(5));
        BRtracer->setInput (6, "Actual pos",         pidBR->getTraceOutput(6));

        BatteryMonitor* batMon = new BatteryMonitor ("The only one", SERVO_FREQUENCY);

        MotorInterfaceBlock* miFL = new MotorInterfaceBlock("FrontLeft_MI",  PIN_OUT_FRONT_LEFT_PWM,  PIN_OUT_FRONT_LEFT_DIR);
        MotorInterfaceBlock* miFR = new MotorInterfaceBlock("FrontRight_MI", PIN_OUT_FRONT_RIGHT_PWM, PIN_OUT_FRONT_RIGHT_DIR);
        MotorInterfaceBlock* miBL = new MotorInterfaceBlock("BackLeftMI",    PIN_OUT_BACK_LEFT_PWM,   PIN_OUT_BACK_LEFT_DIR);
        MotorInterfaceBlock* miBR = new MotorInterfaceBlock("BackRight_MI",  PIN_OUT_BACK_RIGHT_PWM,  PIN_OUT_BACK_RIGHT_DIR);


        miFL->setInput(pidFL->getOutput ());
        miFL->setBatteryFactor (batMon-> getBatFactor ());
        miFR->setInput(pidFR->getOutput ());
        miFR->setBatteryFactor (batMon-> getBatFactor ());
        miBL->setInput(pidBL->getOutput ());
        miBL->setBatteryFactor (batMon-> getBatFactor ());
        miBR->setInput(pidBR->getOutput ());
        miBR->setBatteryFactor (batMon-> getBatFactor ());

        sequence.push_back(spg);
        sequence.push_back(abFL);
        sequence.push_back(abFR);
        sequence.push_back(abBL);
        sequence.push_back(abBR);


        sequence.push_back (pidFL);
        sequence.push_back (pidFR);
        sequence.push_back (pidBL);
        sequence.push_back (pidBR);

        sequence.push_back(batMon); // do only once for 4 wheels

        sequence.push_back(miFL);
        sequence.push_back(miFR);
        sequence.push_back(miBL);
        sequence.push_back(miBR);

        sequence.push_back(FLtracer);
        sequence.push_back(FRtracer);
        sequence.push_back(BLtracer);
        sequence.push_back(BRtracer);
    }
    virtual ~SG_MotorController(){};
private:
};


#endif