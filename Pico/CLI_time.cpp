
#include "CLI_time.hpp"

#include <cstring>

TimeCommand *TimeCommand::instance(nullptr);

TimeCommand::~TimeCommand() {}

TimeCommand *TimeCommand::getInstance()
{
    // std::cerr << "TimeCommand::getInstance" << std::endl;
    if (instance == nullptr)
        instance = new TimeCommand();
    return instance;
}

BaseType_t TimeCommand::command(char *outputBuffer, size_t outputLen, const char *command)
{
    // std::cerr << "TimeCommand::command: instance " << instance << std::endl;
    // std::cerr << "TimeCommand::command: servogroup " << instance->servoGroup << std::endl;
    if (instance->servoGroup != nullptr)
    {
        int64_t r = instance->servoGroup->getCounter();
        snprintf(outputBuffer, outputLen, "Time: %ju\nOK.\n", r);
    }
    else
    {
        strncpy(outputBuffer, "Error: servoGroup not set.\n", outputLen);
    }
    return pdFALSE;
}

TimeCommand::TimeCommand() : AbstractCommand(
    "time",
    "time:\n Print time of ServoGroup.\n",
    TimeCommand::command,
    0)
{
}
