#ifndef _CLI_TEST_HPP_
#define _CLI_TEST_HPP_

#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"

#include "SG.hpp"

class TimeCommand
{
public:
    static TimeCommand *getInstance();
    static void registerServoGroup(ServoGroup *sg);

    virtual ~TimeCommand();
    void registerSG(ServoGroup *sg);

protected:
    TimeCommand();
    static BaseType_t command(char *outputBuffer, size_t outputLen, const char *command);

    static TimeCommand *instance;
    ServoGroup *servoGroup;
};

#endif