#ifndef _CLI_TRACE_HPP_
#define _CLI_TRACE_HPP_

#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"

#include "SG.hpp"

class AddTraceeableCommand
{
public:
    static AddTraceeableCommand *getInstance();

    virtual ~AddTraceeableCommand();
    void registerServoGroup(ServoGroup *sg);

protected:
    AddTraceeableCommand();
    static BaseType_t command(char *outputBuffer, size_t outputLen, const char *command);

    static AddTraceeableCommand *instance;
    ServoGroup *servoGroup;
};

#endif