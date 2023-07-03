/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "main.h"

/* Library includes. */
#include <stdio.h>
#include "pico/stdlib.h"
#if (mainRUN_ON_CORE == 1)
#include "pico/multicore.h"
#endif

#include "PeriodicTask.hpp"
#include "SG_Debug.hpp"
#include "SG_MotorController.hpp"
#include "SG_Blinky.hpp"
#include "SG_SPG.hpp"
#include "ServoGroupExecutor.hpp"

#include "CLI.hpp"

/*-----------------------------------------------------------*/

void createMainTask();
void mainTask(void *);

void createSerialTask();

int main(void)
{
    // prvSetupHardware();
    stdio_init_all();
    stdio_set_translate_crlf(&stdio_uart, true);


    // // Create ServoGroup
    ServoGroup *sg = new SG_MotorController();

    // // Create Executor and start execution task.
    ServoGroupExecutor *seq = new ServoGroupExecutor(sg);
    seq->startExecutorTask();

    // Create CLI and start command line interpreter task.
    MecanumCLI *cli = MecanumCLI::getInstance();
    cli->startCLITask();

    // Tell CLI which ServoGroup to act upon.
    cli->setServoGroup(sg);

    vTaskStartScheduler();

    for (;;)
        ;

    return 0;
}

void createMainTask()
{
    // ServoGroup* sg = new SG_MotorController();
    // ServoGroup* sg = new SG_Blinky();

    //  createConsoleTask();

    // SG_SPG *sg = new SG_SPG();

    // ServoGroupExecutor *seq = new ServoGroupExecutor(sg);

    // seq->start();

    // TaskHandle_t mainTaskHandle;
    // BaseType_t r = xTaskCreate(mainTask,
    //                            "MainTask",
    //                            1000,
    //                            sg,
    //                            1,
    //                            &mainTaskHandle);
    // std::cout << "TaskCreated: " << r << std::endl;

    // if (r != pdPASS)
    //     printf("xTaskCreate failed.");
}

void mainTask(void *pvParameters)
{
    std::cout << ">mainTask()" << std::endl;

    SG_SPG *sg = (SG_SPG *)pvParameters;

    for (int i = 5; i >= 0; i--)
    {
        std::cout << "Prepare to move in " << i << " seconds." << std::endl;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    std::cout << "Moving" << std::endl;
    sg->move(10.0, 5.0, 1.0);
    sg->dumpTrace();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    std::cout << "Moving finished" << std::endl;

    for (;;)
    {
        /* Task code goes here. */
    }
}

/*-----------------------------------------------------------*/

extern "C" void
vApplicationMallocFailedHook(void)
{
    /* Called if a call to pvPortMalloc() fails because there is insufficient
    free memory available in the FreeRTOS heap.  pvPortMalloc() is called
    internally by FreeRTOS API functions that create tasks, queues, software
    timers, and semaphores.  The size of the FreeRTOS heap is set by the
    configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */

    /* Force an assert. */
    configASSERT((volatile void *)NULL);
}
/*-----------------------------------------------------------*/

extern "C" void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    (void)pcTaskName;
    (void)pxTask;

    /* Run time stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected. */

    /* Force an assert. */
    configASSERT((volatile void *)NULL);
}
/*-----------------------------------------------------------*/

TaskStatus_t traceArray[10];

extern "C" void vApplicationTickHook(void)
{
    volatile size_t xFreeHeapSpace;

    /* This is just a trivial example of an idle hook.  It is called on each
    cycle of the idle task.  It must *NOT* attempt to block.  In this case the
    idle task just queries the amount of FreeRTOS heap that remains.  See the
    memory management section on the http://www.FreeRTOS.org web site for memory
    management options.  If there is a lot of heap memory free then the
    configTOTAL_HEAP_SIZE value in FreeRTOSConfig.h can be reduced to free up
    RAM. */
    xFreeHeapSpace = xPortGetFreeHeapSize();

    static int counter(0);
    static int period(configTICK_RATE_HZ);

    counter++;
    if (counter == period)
    {
        // std::cout << "mem: " << xFreeHeapSpace << std::endl;
        // printf("Free mem: %d\n", xFreeHeapSpace);
        counter = 0;

        int nrTraces = uxTaskGetSystemState(traceArray, 10, NULL);

        for (int i = 0; i < nrTraces; i++)
        {
            const char *taskName = traceArray[i].pcTaskName;
            auto taskHandle = traceArray[i].xHandle;
            UBaseType_t remainingStack = uxTaskGetStackHighWaterMark(taskHandle);
            // std::cout << taskName << ": " << remainingStack << std::endl;
            // printf("Free stack: %s: %d\n", taskName, remainingStack);
        }
    }

    /* Remove compiler warning about xFreeHeapSpace being set but never used. */
    (void)xFreeHeapSpace;
}
