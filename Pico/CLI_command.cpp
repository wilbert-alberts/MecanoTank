
#include "CLI_command.hpp"

AbstractCommand::AbstractCommand(const std::string &cmdName,
                                 const std::string &help,
                                 const pdCOMMAND_LINE_CALLBACK func,
                                 int8_t nrParams)
{
    static const CLI_Command_Definition_t cmd{
        .pcCommand = cmdName.c_str(),
        .pcHelpString = help.c_str(),
        .pxCommandInterpreter = func,
        .cExpectedNumberOfParameters = nrParams};
    FreeRTOS_CLIRegisterCommand(&cmd);
}

AbstractCommand::~AbstractCommand()
{
}

void AbstractCommand::registerServoGroup(ServoGroup *sg)
{
    servoGroup = sg;
}
