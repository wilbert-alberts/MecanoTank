/*
 * CLIFreeRTOS.cpp
 *
 *  Created on: 22 Jun 2023
 *      Author: walberts
 */

#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"

#include "CLI_FreeRTOS.hpp"

HeapStatsCommand *HeapStatsCommand::instance(nullptr);

HeapStatsCommand* HeapStatsCommand::getInstance() {
	if (instance == nullptr) {
		instance = new HeapStatsCommand();
	}
	return instance;
}

HeapStatsCommand::~HeapStatsCommand() {
}

HeapStatsCommand::HeapStatsCommand() :
		AbstractCommand("heapStats", "heapStats:\n Dump heap statistics.\n",
				HeapStatsCommand::command, 0) {
}

BaseType_t HeapStatsCommand::command(char *outputBuffer, size_t outputLen,
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

TaskStatsCommand *TaskStatsCommand::instance(nullptr);

TaskStatsCommand* TaskStatsCommand::getInstance() {
	if (instance == nullptr) {
		instance = new TaskStatsCommand();
	}
	return instance;
}

TaskStatsCommand::~TaskStatsCommand() {
}

TaskStatsCommand::TaskStatsCommand() :
		AbstractCommand("taskStats", "taskStats:\n Dump task statistics.\n",
				TaskStatsCommand::command, 0) {
}

BaseType_t TaskStatsCommand::command(char *outputBuffer, size_t outputLen,
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
