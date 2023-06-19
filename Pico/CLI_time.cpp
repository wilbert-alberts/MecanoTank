
#include "CLI_time.hpp"

#include <cstring>

TimeCommand *TimeCommand::instance(nullptr);

TimeCommand::~TimeCommand() {}

TimeCommand *TimeCommand::getInstance()
{
    if (instance == nullptr)
        instance = new TimeCommand();
    return instance;
}

void TimeCommand::registerServoGroup(ServoGroup *sg)
{
    getInstance()->registerServoGroup(sg);
}

void TimeCommand::registerSG(ServoGroup *sg)
{
    servoGroup = sg;
}

BaseType_t TimeCommand::command(char *outputBuffer, size_t outputLen, const char *command)
{
    TimeCommand *instance = TimeCommand::getInstance();
    if (instance->servoGroup != nullptr)
    {
        auto r = instance->servoGroup->getPeriod();
        snprintf(outputBuffer, outputLen, "Time: %d\n\n", r);
    }
    else
    {
        strncpy(outputBuffer, "Error: servoGroup not set.\n", outputLen);
    }
    return pdFALSE;
}

TimeCommand::TimeCommand()
{
    static const CLI_Command_Definition_t greetTheWorldCmd{
        .pcCommand = "time",
        .pcHelpString = "time:\n Print time of ServoGroup.\n\n",
        .pxCommandInterpreter = TimeCommand::command,
        .cExpectedNumberOfParameters = 0};
    FreeRTOS_CLIRegisterCommand(&greetTheWorldCmd);
}
