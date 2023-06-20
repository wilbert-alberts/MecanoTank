#ifndef __CLI_HPP__
#define __CLI_HPP__

#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"

#include "task.h"
#include "semphr.h"

#include "SG.hpp"

class TimeCommand;
class AddTraceeableCommand;

class MecanumCLI
{
public:
    static MecanumCLI *getInstance();
    virtual ~MecanumCLI();
    void startCLITask();
    void setServoGroup(ServoGroup *sg);

protected:
    MecanumCLI();
    void initializeCommands();
    ServoGroup *servoGroup;

    TimeCommand *timeCmd;
    AddTraceeableCommand *addTraceableCmd;

private:
    static MecanumCLI *instance;
    SemaphoreHandle_t waitingOnCharsSem;
    TaskHandle_t consoleTaskHandle;
    static const char *const welcomeMessage;

    void initIO();
    void termIO();

    void charsArrivedFromISR();
    static void charsArrivedStaticFromISR(void *p);

    void CLIReadChar(char *c);
    void CLIWriteMsg(const char *msg, uint len);

    static void consoleTaskStatic(void *p);
    void consoleTask();
};
#endif