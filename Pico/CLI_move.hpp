#ifndef _CLI_MOVE_HPP_
#define _CLI_MOVE_HPP_

#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"

#include "CLI_command.hpp"

class StartMoveCommand: public AbstractCommand
{
public:
    static StartMoveCommand *getInstance();

    virtual ~StartMoveCommand();


protected:
    StartMoveCommand();
    static BaseType_t command(char *outputBuffer, size_t outputLen, const char *command);

    static StartMoveCommand *instance;

};

class GetPositionCommand: public AbstractCommand
{
public:
    static GetPositionCommand *getInstance();

    virtual ~GetPositionCommand();


protected:
    GetPositionCommand();
    static BaseType_t command(char *outputBuffer, size_t outputLen, const char *command);

    static GetPositionCommand *instance;

};

#endif