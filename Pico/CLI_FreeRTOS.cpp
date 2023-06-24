/*
 * CLIFreeRTOS.cpp
 *
 *  Created on: 22 Jun 2023
 *      Author: walberts
 */

#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"

#include "CLI_FreeRTOS.hpp"

CLI_heapStatsCommand *CLI_heapStatsCommand::instance(nullptr);

CLI_heapStatsCommand* CLI_heapStatsCommand::getInstance() {
	if (instance == nullptr) {
		instance = new CLI_heapStatsCommand();
	}
	return instance;
}

CLI_heapStatsCommand::~CLI_heapStatsCommand() {
}

CLI_heapStatsCommand::CLI_heapStatsCommand() :
		AbstractCommand("heapStats", "heapStats:\n Dump heap statistics.\n\n",
				CLI_heapStatsCommand::command, 0) {
}

BaseType_t CLI_heapStatsCommand::command(char *outputBuffer, size_t outputLen,
		const char *command) {

	HeapStats_t stats;

	auto curFreeHeapSize = xPortGetFreeHeapSize();
	auto minFreeHeapSize = xPortGetMinimumEverFreeHeapSize();

	snprintf(outputBuffer, outputLen,

	"Heapstats:\n"
			"	available:          %d bytes\n"
			"	min ever available: %d bytes\nOK\n",
			curFreeHeapSize,
			minFreeHeapSize);

	return pdFALSE;
}

CLI_taskStatsCommand *CLI_taskStatsCommand::instance(nullptr);

CLI_taskStatsCommand* CLI_taskStatsCommand::getInstance() {
	if (instance == nullptr) {
		instance = new CLI_taskStatsCommand();
	}
	return instance;
}

CLI_taskStatsCommand::~CLI_taskStatsCommand() {
}

CLI_taskStatsCommand::CLI_taskStatsCommand() :
		AbstractCommand("taskStats", "taskStats:\n Dump task statistics.\n\n",
				CLI_taskStatsCommand::command, 0) {
}

BaseType_t CLI_taskStatsCommand::command(char *outputBuffer, size_t outputLen,
		const char *command) {

	/* Take a snapshot of the number of tasks in case it changes while this
	 function is executing. */
	UBaseType_t uxArraySize(uxTaskGetNumberOfTasks());
	unsigned long ulTotalRunTime;
	static const char *nullTaskName = "<null>";
	static const char * stateToString[] = {
			"Ready", "Running", "Blocked", "Suspended", "Deleted"
	};

	/* Allocate a TaskStatus_t structure for each task.  An array could be
	 allocated statically at compile time. */
	TaskStatus_t *taskStatusArray= (TaskStatus_t*)
			pvPortMalloc(uxArraySize * sizeof(TaskStatus_t));

	if (taskStatusArray != NULL) {
		std::string result("");
		/* Generate raw status information about each task. */
		uxArraySize = uxTaskGetSystemState(taskStatusArray, uxArraySize,
				&ulTotalRunTime);

		for (int i = 0; i < uxArraySize; i++) {
			eTaskState state(taskStatusArray[i].eCurrentState);
			configSTACK_DEPTH_TYPE waterMark(
					taskStatusArray[i].usStackHighWaterMark);
			const char *taskName(nullTaskName);
			if (taskStatusArray[i].pcTaskName != nullptr) {
				taskName = taskStatusArray[i].pcTaskName;
			}
			result+= "task: ";
			result.append(taskName);
			result+=", stack: ";
			result+=std::to_string(waterMark);
			result+= ", state: ";
			result.append(stateToString[state]);
			result+="\n";
		}

		snprintf(outputBuffer, outputLen, "Taskstats:\n%sOK.\n", result.c_str());
		vPortFree (taskStatusArray);
	}

	return pdFALSE;
}
