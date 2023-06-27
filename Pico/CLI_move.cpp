#include <cstring>

#include "BL_Composite.hpp"
#include "SG.hpp"
#include "BL_SPG.hpp"

#include "CLI_move.hpp"


GetPositionCommand *GetPositionCommand::instance(nullptr);

GetPositionCommand::~GetPositionCommand() {}

GetPositionCommand *GetPositionCommand::getInstance()
{
    // std::cerr << "TimeCommand::getInstance" << std::endl;
    if (instance == nullptr)
        instance = new GetPositionCommand();
    return instance;
}

BaseType_t GetPositionCommand::command(char *outputBuffer, size_t outputLen, const char *command)
{
    std::string result;

    auto spgBlockSuccess = instance->servoGroup->getSubBlockByName("SPG");
    if (spgBlockSuccess.success) {
        SPGBlock* spgBlock = (SPGBlock*)(spgBlockSuccess.result.get());
        SPGBlock::Position target;

        target = spgBlock->getPosition();

        result += "Position: (x: " + std::to_string(target.x) + ", y: " + std::to_string(target.y) + ", rz: " + std::to_string(target.rz) + ")\nOK.\n";
    }
    else {
        result = "Unable to find block named: SPG; therefore unable to move.";
    }
    snprintf(outputBuffer, outputLen, result.c_str());
    return pdFALSE;
}

GetPositionCommand::GetPositionCommand() : AbstractCommand(
    "getPosition",
    "getPosition:\n Print current position (x, y, rz).\n",
    GetPositionCommand::command,
    0)
{
}


StartMoveCommand *StartMoveCommand::instance(nullptr);

StartMoveCommand::~StartMoveCommand() {}

StartMoveCommand *StartMoveCommand::getInstance()
{
    // std::cerr << "TimeCommand::getInstance" << std::endl;
    if (instance == nullptr)
        instance = new StartMoveCommand();
    return instance;
}

BaseType_t StartMoveCommand::command(char *outputBuffer, size_t outputLen, const char *command)
{
     std::string result;

    auto spgBlockSuccess = instance->servoGroup->getSubBlockByName("SPG");
    if (spgBlockSuccess.success) {
        SPGBlock* spgBlock = (SPGBlock*)(spgBlockSuccess.result.get());
        SPGBlock::Position target;
        target.x = instance->getDoubleParameter(1, command);
        target.y = instance->getDoubleParameter(2, command);
        target.rz = instance->getDoubleParameter(3, command);
        spgBlock->startMove(target);

        auto state = spgBlock->getState();
        if (state == SPGBlock::State::MOVING) {
            result += "Move started.\nOK.\n";
        }
        else {
            result += "Start move failed.\nERROR.\n";
        }
    }
    else {
        result = "Unable to find block named: SPG; therefore unable to move.";
    }
    snprintf(outputBuffer, outputLen, result.c_str());
    return pdFALSE;
}

StartMoveCommand::StartMoveCommand() : AbstractCommand(
    "startMove",
    "startMove <x> <y> <rz>:\n Move to x, y, rz.\n",
    StartMoveCommand::command,
    3)
{
}
