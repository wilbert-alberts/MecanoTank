#ifndef _CLI_TEST_HPP_
#define _CLI_TEST_HPP_

#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"

#include "CLI_command.hpp"

class TimeCommand: public AbstractCommand
{
public:
    static TimeCommand *getInstance();

    virtual ~TimeCommand();


protected:
    TimeCommand();
    static BaseType_t command(char *outputBuffer, size_t outputLen, const char *command);

    static TimeCommand *instance;

};

#endif