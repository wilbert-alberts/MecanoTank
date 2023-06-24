#include <string>

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

std::string AbstractCommand::getStringParameter(uint idx, const char* commandStr) {
    BaseType_t len;
    const char* c = FreeRTOS_CLIGetParameter(commandStr, idx, &len);
    return std::string(c, len);
}

int AbstractCommand::getIntParameter(uint idx, const char* commandStr) {
    BaseType_t len;
    const char* c = FreeRTOS_CLIGetParameter(commandStr, idx, &len);
    return atoi(std::string(c, len).c_str());
}

double AbstractCommand::getDoubleParameter(uint idx, const char* commandStr) {
    BaseType_t len;
    const char* c = FreeRTOS_CLIGetParameter(commandStr, idx, &len);
    return atof(std::string(c, len).c_str());
}

void AbstractCommand::registerServoGroup(ServoGroup *sg)
{
    servoGroup = sg;
}
