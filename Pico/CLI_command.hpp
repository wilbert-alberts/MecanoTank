#ifndef CLI_COMMAND_HPP
#define CLI_COMMAND_HPP

#include <string>

#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"

#include "SG.hpp"

class AbstractCommand
{
public:
    virtual ~AbstractCommand();
    void registerServoGroup(ServoGroup *sg);

protected:
    AbstractCommand(const char* cmdName,
                    const char* help,
                    const pdCOMMAND_LINE_CALLBACK func,
                    int8_t nrParams);

    std::string getStringParameter(uint idx, const char* cmdString);
    int  getIntParameter(uint idx, const char* cmdString);
    double getDoubleParameter(uint idx, const char* cmdString);

    CLI_Command_Definition_t cmdDefinition;
    ServoGroup *servoGroup;
};

#endif
