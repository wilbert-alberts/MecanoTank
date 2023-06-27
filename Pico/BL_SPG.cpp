

#include "BL_SPG.hpp"

#include "T_Factory.hpp"

const IDTerminal SPGBlock::OUT_POS_X("x");
const IDTerminal SPGBlock::OUT_POS_Y("y");
const IDTerminal SPGBlock::OUT_POS_RZ("rz");

const IDTerminal SPGBlock::OUT_VEL_X("v_x");
const IDTerminal SPGBlock::OUT_VEL_Y("v_y");
const IDTerminal SPGBlock::OUT_VEL_RZ("v_rz");

const IDTerminal SPGBlock::OUT_ACC_X("a_x");
const IDTerminal SPGBlock::OUT_ACC_Y("a_y");
const IDTerminal SPGBlock::OUT_ACC_RZ("a_rz");

SPGBlock::SPGBlock(const std::string &bn, double _servoFrequency)
    : LeafBlock("SPG", bn), state(State::IDLE), ruckig(1.0 / _servoFrequency)
{
    // addOutput(OUT_POS_X, &output.new_position.at(0));
    // addOutput(OUT_POS_Y, &output.new_position.at(1));
    // addOutput(OUT_POS_RZ, &output.new_position.at(2));

    // addOutput(OUT_VEL_X, &output.new_position.at(0));
    // addOutput(OUT_VEL_Y, &output.new_position.at(1));
    // addOutput(OUT_VEL_RZ, &output.new_position.at(2));

    // addOutput(OUT_ACC_X, &output.new_position.at(0));
    // addOutput(OUT_ACC_Y, &output.new_position.at(1));
    // addOutput(OUT_ACC_RZ, &output.new_position.at(2));
    addOutput(OUT_POS_X, &input.current_position.at(0));
    addOutput(OUT_POS_Y, &input.current_position.at(1));
    addOutput(OUT_POS_RZ, &input.current_position.at(2));

    addOutput(OUT_VEL_X, &input.current_velocity.at(0));
    addOutput(OUT_VEL_Y, &input.current_velocity.at(1));
    addOutput(OUT_VEL_RZ, &input.current_velocity.at(2));

    addOutput(OUT_ACC_X, &input.current_acceleration.at(0));
    addOutput(OUT_ACC_Y, &input.current_acceleration.at(1));
    addOutput(OUT_ACC_RZ, &input.current_acceleration.at(2));
}

SPGBlock::~SPGBlock()
{
}

SPGBlock::State SPGBlock::getState() {
    return state;
}

void SPGBlock::setPosition(const SPGBlock::Position &p)
{
    input.current_position = {p.x, p.y, p.rz};
}

SPGBlock::Position SPGBlock::getPosition()
{
    // double x = input.current_position.at(0);
    // double y = input.current_position.at(1);
    // double rz = input.current_position.at(2);

    Position result{
        input.current_position.at(0),
        input.current_position.at(1),
        input.current_position.at(2)

        // x, y, rz
    };

    // result.x = x;
    // result.y = y;
    // result.rz = rz;

    return result;
}

void SPGBlock::setMovementParameters(const SPGBlock::MovementParameters &pars)
{
    input.max_velocity = {
        pars.x.v,
        pars.y.v,
        pars.rz.v};
    input.max_acceleration = {
        pars.x.a,
        pars.y.a,
        pars.rz.a};
    input.max_jerk = {
        pars.x.j,
        pars.y.j,
        pars.rz.j};
}

SPGBlock::MovementParameters SPGBlock::getMovementParameters()
{
    MovementParameters result;

    result.x.v = input.max_velocity.at(0);
    result.y.v = input.max_velocity.at(1);
    result.rz.v = input.max_velocity.at(2);

    result.x.a = input.max_acceleration.at(0);
    result.y.a = input.max_acceleration.at(1);
    result.rz.a = input.max_acceleration.at(2);

    result.x.j = input.max_jerk.at(0);
    result.y.j = input.max_jerk.at(1);
    result.rz.j = input.max_jerk.at(2);
    return result;
}

void SPGBlock::startMove(const Position &target)
{
    switch (state)
    {
    case IDLE:
    {
        input.target_position = {target.x, target.y, target.rz};
        input.target_acceleration = {0.0, 0.0, 0.0};
        input.target_velocity = {0.0, 0.0, 0.0};

#if ((PICO_CXX_ENABLE_EXCEPTIONS == 1) || !defined(PICO_CXX_ENABLE_EXCEPTIONS))
        if (input.validate())
            state = MOVING;
        else
        {
            Warning("Illegal movement parameters, ignoring startMove()");
        }
#else
    state = MOVING;
#endif
        break;
    }
    case MOVING:
    {
        Warning("Unable to start move when move already in progress");
    }
    case ERROR:
    {
        Error("Unable to start move when SPG in ERROR state.");
    }
    }
}

void SPGBlock::calculate()
{

    if (state == State::MOVING)
    {

        auto r = ruckig.update(input, output);
        output.pass_to_input(input);
        std::cout << "Moving. x: " << output.new_position.at(0)
                  << ", y: " << output.new_position.at(0)
                  << ", rz: " << output.new_position.at(2) << std::endl;
        switch (r)
        {
        case ruckig::Result::Working:
            break;
        case ruckig::Result::Finished:
            state = State::IDLE;
            break;
        default:
            state = State::ERROR;
            break;
        }
    }
    else
    {
        switch (state)
        {
        case State::ERROR:
            std::cout << "Error!" << std::endl;
            break;
        case State::IDLE:
            // std::cout << "Idle." << std::endl;
            break;
        default:
            std::cout << "???" << std::endl;
            break;
        }
    }
}