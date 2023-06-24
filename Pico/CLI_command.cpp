
#include "CLI_command.hpp"

AbstractCommand::AbstractCommand(const char* cmdName,
                                 const char* help,
                                 const pdCOMMAND_LINE_CALLBACK func,
                                 int8_t nrParams)
:servoGroup(nullptr), cmdDefinition({
        .pcCommand = cmdName,
        .pcHelpString = help,
        .pxCommandInterpreter = func,
        .cExpectedNumberOfParameters = nrParams})
{
    FreeRTOS_CLIRegisterCommand(&cmdDefinition);
}

AbstractCommand::~AbstractCommand()
{
}

void AbstractCommand::registerServoGroup(ServoGroup *sg)
{
    servoGroup = sg;
}
