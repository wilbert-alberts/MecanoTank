#ifndef __SPG_BLOCK_HPP_
#define __SPG_BLOCK_HPP_

#include "BL_Leaf.hpp"
#include "ruckig/include/ruckig/ruckig.hpp"

class SPGBlock : public LeafBlock
{
public:
    typedef enum
    {
        ERROR,
        IDLE,
        MOVING
    } State;

    typedef struct
    {
        double x;
        double y;
        double rz;
    } DOF3;

    typedef DOF3 Position;
    typedef DOF3 Velocity;
    typedef DOF3 Acceleration;

    typedef struct
    {
        double v;
        double a;
        double j;
    } VAJ;

    typedef struct
    {
        VAJ x;
        VAJ y;
        VAJ rz;
    } MovementParameters;

    SPGBlock(const std::string &bn, double _servoFrequency);
    virtual ~SPGBlock();
    virtual void calculate();

    State getState();

    void setPosition(const Position &p);
    Position getPosition();

    void setMovementParameters(const MovementParameters &pars);
    MovementParameters getMovementParameters();

    void startMove(const Position &target);

    static const IDTerminal OUT_POS_X;
    static const IDTerminal OUT_POS_Y;
    static const IDTerminal OUT_POS_RZ;

    static const IDTerminal OUT_VEL_X;
    static const IDTerminal OUT_VEL_Y;
    static const IDTerminal OUT_VEL_RZ;

    static const IDTerminal OUT_ACC_X;
    static const IDTerminal OUT_ACC_Y;
    static const IDTerminal OUT_ACC_RZ;

private:
    State state;
    ruckig::Ruckig<3> ruckig;
    ruckig::InputParameter<3> input;
    ruckig::OutputParameter<3> output;
};

#endif