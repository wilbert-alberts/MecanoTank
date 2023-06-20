
#include <iostream>
#include <cstring>

#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"

#include "task.h"
#include "semphr.h"

#include "pico/stdio.h"

#include "HSI.hpp"

#include "CLI.hpp"

#include "CLI_time.hpp"
#include "CLI_trace.hpp"

#define MAX_INPUT_LENGTH 255
#define MAX_OUTPUT_LENGTH 255

void registerTestCommand();

const char *const MecanumCLI::welcomeMessage = "Mecanumtank CLI started.\r\nType Help for more information.\r\n\0";

MecanumCLI *MecanumCLI::instance(nullptr);

MecanumCLI *MecanumCLI::getInstance()
{
    if (instance == nullptr)
        instance = new MecanumCLI();
    return instance;
}

MecanumCLI::MecanumCLI()
{
    initializeCommands();
    initIO();
}

MecanumCLI::~MecanumCLI()
{
    termIO();
}

void MecanumCLI::initializeCommands()
{
    timeCmd = TimeCommand::getInstance();
    addTraceableCmd = AddTraceeableCommand::getInstance();
}

void MecanumCLI::setServoGroup(ServoGroup *sg)
{
    servoGroup = sg;
    timeCmd->registerServoGroup(sg);
    addTraceableCmd->registerServoGroup(sg);
}

void MecanumCLI::startCLITask()
{
    TaskHandle_t consoleTaskHandle;
    auto r = xTaskCreate(consoleTaskStatic, "ConsoleTask", 8192, this, TASK_PRIO_CONSOLE, &consoleTaskHandle);
    if (r != pdPASS)
    {
        // std::cerr << "Unable to create console task";
        printf("Unable to create task: console task\n");
    }
}

void MecanumCLI::initIO()
{
    waitingOnCharsSem = xSemaphoreCreateBinary();
    // std::cerr << "initIO: waitingOnCharsSem: " << waitingOnCharsSem << std::endl;
    // std::cerr << "initIO: waitingOnCharsSem count: " << uxSemaphoreGetCount(waitingOnCharsSem) << std::endl;
    // std::cerr << "initIO: this: " << this << std::endl;
    // stdio_set_chars_available_callback(MecanumCLI::charsArrivedStaticFromISR, this);
    // std::cerr << "initIO: Registered callback." << std::endl;
}

void MecanumCLI::termIO()
{
    // stdio_set_chars_available_callback(NULL, this);
    vSemaphoreDelete(waitingOnCharsSem);
}

void MecanumCLI::charsArrivedStaticFromISR(void *p)
{
    MecanumCLI *cli = (MecanumCLI *)p;
    cli->charsArrivedFromISR();
}

// Implementation based on semaphore

void MecanumCLI::charsArrivedFromISR()
{
    BaseType_t contextSwitchRequested = pdFALSE;

    xSemaphoreGiveFromISR(waitingOnCharsSem, &contextSwitchRequested);
    // portYIELD_FROM_ISR(contextSwitchRequested);
}

void MecanumCLI::CLIReadChar(char *c)
{
    int r;
    // std::cerr << "CLIReadChar: " << std::endl;
    while ((r = getchar_timeout_us(0)) == PICO_ERROR_TIMEOUT)
    {
        // std::cerr << "CLIReadChar: no data" << std::endl;
        // std::cerr << "CLIReadChar: waitingOnCharsSem: " << waitingOnCharsSem << std::endl;
        // std::cerr << "charsArrivedFromISR: waitingOnCharsSem count: " << uxSemaphoreGetCount(waitingOnCharsSem) << std::endl;
        stdio_set_chars_available_callback(MecanumCLI::charsArrivedStaticFromISR, this);
        xSemaphoreTake(waitingOnCharsSem, portMAX_DELAY);
        stdio_set_chars_available_callback(nullptr, this);
        // std::cerr << "charsArrivedFromISR: waitingOnCharsSem count: " << uxSemaphoreGetCount(waitingOnCharsSem) << std::endl;
    }
    *c = (char)r;
    // std::cerr << "CLIReadChar: read" << *c << std::endl;
}

// Implementation based on task suspend/resume

// static TaskHandle_t myTask(nullptr);

// void MecanumCLI::charsArrivedFromISR()
// {
//     // std::cerr << "charsArrivedFromISR " << std::endl;
//     if (myTask != NULL)
//     {
//         // std::cerr << "charsArrivedFromISR: need to wake someone up: "<<myTask << std::endl;
//         xTaskResumeFromISR(myTask);
//         // std::cerr << "charsArrivedFromISR: woken up" << std::endl;
//     }
//     // std::cerr << "charsArrivedFromISR: " << std::endl;
// }

// void MecanumCLI::CLIReadChar(char *c)
// {
//     int r;
//     // std::cerr << "CLIReadChar: " << std::endl;
//     while ((r = getchar_timeout_us(0)) == PICO_ERROR_TIMEOUT)
//     {
//         // std::cerr << "CLIReadChar: no data" << std::endl;
//         myTask = xTaskGetCurrentTaskHandle();
//         // std::cerr << "CLIReadChar: going to sleep: "<< myTask<< std::endl;
//         vTaskSuspend(myTask);
//         // std::cerr << "CLIReadChar: woken up: "<< myTask<< std::endl;
//         myTask = NULL;
//     }
//     *c = (char)r;
//     // std::cerr << "CLIReadChar: read" << *c << std::endl;
// }

void MecanumCLI::CLIWriteMsg(const char *msg, uint len)
{
    // puts(msg);
    printf("%s", msg);
}

void MecanumCLI::consoleTaskStatic(void *p)
{
    MecanumCLI *cli = (MecanumCLI *)p;
    cli->consoleTask();
}

void MecanumCLI::consoleTask()
{

    char cRxedChar = 0;
    char cInputIndex = 0;
    BaseType_t xMoreDataToFollow;
    /* The input and output buffers are declared static to keep them off the stack. */
    static char pcOutputString[MAX_OUTPUT_LENGTH];
    static char pcInputString[MAX_INPUT_LENGTH];

    // Suspend for a second to get serial connections up and running
    vTaskDelay(2000 / portTICK_PERIOD_MS);

    /* Send a welcome message to the user knows they are connected. */
    CLIWriteMsg(welcomeMessage, strlen(welcomeMessage));
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    for (;;)
    {
        /* This implementation reads a single character at a time.  Wait in the
        Blocked state until a character is received. */
        CLIReadChar(&cRxedChar);

        if ((cRxedChar == '\r') || (cRxedChar == '\n'))
        {
            /* A newline character was received, so the input command string is
            complete and can be processed.  Transmit a line separator, just to
            make the output easier to read. */
            CLIWriteMsg("\r\n", strlen("\r\n"));

            /* The command interpreter is called repeatedly until it returns
            pdFALSE.  See the "Implementing a command" documentation for an
            exaplanation of why this is. */
            do
            {
                /* Send the command string to the command interpreter.  Any
                output generated by the command interpreter will be placed in the
                pcOutputString buffer. */
                xMoreDataToFollow = FreeRTOS_CLIProcessCommand(
                    pcInputString,    /* The command string.*/
                    pcOutputString,   /* The output buffer. */
                    MAX_OUTPUT_LENGTH /* The size of the output buffer. */
                );

                /* Write the output generated by the command interpreter to the
                console. */
                CLIWriteMsg(pcOutputString, strlen(pcOutputString));

            } while (xMoreDataToFollow != pdFALSE);

            /* All the strings generated by the input command have been sent.
            Processing of the command is complete.  Clear the input string ready
            to receive the next command. */
            cInputIndex = 0;
            memset(pcInputString, 0x00, MAX_INPUT_LENGTH);
        }
        else
        {
            /* The if() clause performs the processing after a newline character
            is received.  This else clause performs the processing if any other
            character is received. */

            if (cRxedChar == '\r')
            {
                /* Ignore carriage returns. */
            }
            else if (cRxedChar == '\b')
            {
                /* Backspace was pressed.  Erase the last character in the input
                buffer - if there are any. */
                if (cInputIndex > 0)
                {
                    cInputIndex--;
                    pcInputString[cInputIndex] = 0x00;
                }

                // Implement remote echo
                putchar(cRxedChar);
            }
            else
            {
                /* A character was entered.  It was not a new line, backspace
                or carriage return, so it is accepted as part of the input and
                placed into the input buffer.  When a n is entered the complete
                string will be passed to the command interpreter. */

                if (cInputIndex < MAX_INPUT_LENGTH)
                {
                    pcInputString[cInputIndex] = cRxedChar;
                    cInputIndex++;
                    // Implement remote echo
                    putchar(cRxedChar);
                }
            }
        }
    }
}

BaseType_t testCommand(char *outputBuffer, size_t outputLen, const char *command)
{
    strncpy(outputBuffer, "Test command succeeded.\n", outputLen);
    return pdFALSE;
}

void registerTestCommand()
{
    static const CLI_Command_Definition_t greetTheWorldCmd{
        .pcCommand = "test",
        .pcHelpString = "test:\n Test whether CLI console is working.\n\n",
        .pxCommandInterpreter = testCommand,
        .cExpectedNumberOfParameters = 0};
    FreeRTOS_CLIRegisterCommand(&greetTheWorldCmd);
}
