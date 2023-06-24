#ifndef __CLI_HPP__
#define __CLI_HPP__

#include <vector>

#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"

#include "task.h"
#include "semphr.h"

class ServoGroup;
class AbstractCommand;

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
    std::vector<AbstractCommand*> commands;

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