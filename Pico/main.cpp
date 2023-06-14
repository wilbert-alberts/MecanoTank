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

/*-----------------------------------------------------------*/

void mainTask(void *);

int main(void)
{
    // prvSetupHardware();
    stdio_init_all();

    std::cout << "Starting" << std::endl;

    // ServoGroup* sg = new SG_MotorController();
    // ServoGroup* sg = new SG_Blinky();
    SG_SPG *sg = new SG_SPG();

    ServoGroupExecutor *seq = new ServoGroupExecutor(sg);

    seq->start();

    TaskHandle_t mainTaskHandle;
    BaseType_t r = xTaskCreate(mainTask,
                               "MainTask",
                               1000,
                               sg,
                               1,
                               &mainTaskHandle);
    std::cout << "TaskCreated: " << r << std::endl;

    if (r != pdPASS)
        printf("xTaskCreate failed.");

    vTaskStartScheduler();

    for (;;)
        ;

    return 0;
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
