#ifndef __SG_SPG_HPP__
#define __SG_SPG_HPP__

#include <memory>
#include <string>
#include <iostream>

#include "SG.hpp"

#include "BL_SPG.hpp"
#include "BL_Trace.hpp"

class SG_SPG : public ServoGroup
{
public:
    SG_SPG()
        : ServoGroup("SG_SPG", SERVO_PERIOD)
    {

        spgBlock = std::make_shared<SPGBlock>("SPG", SERVO_FREQUENCY);
        addBlock(spgBlock);

        // traceBlock = std::make_shared<TraceBlock>();
        // blocks.push_back(traceBlock);

        // traceBlock->addTraceable("Pos_x", spgBlock->getOutput(SPGBlock::OUT_POS_X));

        SPGBlock::MovementParameters mp;
        mp.x.j = 10.0;
        mp.x.a = 3.0;
        mp.x.v = 10.0;

        mp.y = mp.x;
        mp.rz = mp.x;

        spgBlock->setMovementParameters(mp);

        SPGBlock::Position pos { 0.0, 0.0, 0.0 };
        spgBlock->setPosition(pos);

    }

    virtual ~SG_SPG(){};

    void move(double x, double y, double rz) {
        SPGBlock::Position target;
        target.x = x;
        target.y = y;
        target.rz= rz;
        spgBlock->startMove(target);

        while(spgBlock->getState() == SPGBlock::State::MOVING);
    }

    void dumpTrace() {
        traceBlock->dumpTraceToStdout();
    }

private:
    std::shared_ptr<SPGBlock> spgBlock;
    std::shared_ptr<TraceBlock> traceBlock;
};

#endif