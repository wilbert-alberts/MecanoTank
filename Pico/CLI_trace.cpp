#include "CLI_trace.hpp"

AddTraceeableCommand *AddTraceeableCommand::instance(nullptr);

AddTraceeableCommand *AddTraceeableCommand::getInstance()
{
    if (instance == nullptr)
    {
        instance = new AddTraceeableCommand();
    }
    return instance;
}

AddTraceeableCommand::~AddTraceeableCommand()
{
}

void AddTraceeableCommand::registerServoGroup(ServoGroup *sg)
{
    servoGroup = sg;
}

AddTraceeableCommand::AddTraceeableCommand() : servoGroup(nullptr)
{
    static const CLI_Command_Definition_t cmd{
        .pcCommand = "addTraceable",
        .pcHelpString = "addTraceable <output>:\n Start tracing output.\n\n",
        .pxCommandInterpreter = AddTraceeableCommand::command,
        .cExpectedNumberOfParameters = 1};
    FreeRTOS_CLIRegisterCommand(&cmd);
}

BaseType_t AddTraceeableCommand::command(char *outputBuffer, size_t outputLen, const char *command)
{
    BaseType_t traceableNameLength(0);
    const char *traceableName = FreeRTOS_CLIGetParameter(command, 1, &traceableNameLength);
    std::string traceableNameString(traceableName, traceableNameLength);

    double *output = instance->servoGroup->getOutput(traceableNameString);

    if (output == nullptr)
    {
        std::cerr << "Error: unable to find output " << traceableNameString << std::endl;
    }
    else
    {
    }
    return pdFALSE;
}
