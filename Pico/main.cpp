/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "main.h"

/* Library includes. */
#include <stdio.h>
#include "pico/stdlib.h"
#if ( mainRUN_ON_CORE == 1 )
#include "pico/multicore.h"
#endif

#include "PeriodicTask.hpp"
#include "SG_Debug.hpp"
#include "SG_MotorController.hpp"
#include "ServoGroupExecutor.hpp"

/*-----------------------------------------------------------*/

int main( void )
{
 
    stdio_init_all();

    ServoGroup* sg = new SG_MotorController();
    ServoGroupExecutor* seq = new ServoGroupExecutor(sg);

    seq->start();

	vTaskStartScheduler();

	for( ;; );

    return 0;
}

/*-----------------------------------------------------------*/

extern "C" void vApplicationMallocFailedHook( void )
{
    /* Called if a call to pvPortMalloc() fails because there is insufficient
    free memory available in the FreeRTOS heap.  pvPortMalloc() is called
    internally by FreeRTOS API functions that create tasks, queues, software
    timers, and semaphores.  The size of the FreeRTOS heap is set by the
    configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */

    /* Force an assert. */
    configASSERT( ( volatile void * ) NULL );
}
/*-----------------------------------------------------------*/

extern "C" void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
    ( void ) pcTaskName;
    ( void ) pxTask;

    /* Run time stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected. */

    /* Force an assert. */
    configASSERT( ( volatile void * ) NULL );
}
/*-----------------------------------------------------------*/
