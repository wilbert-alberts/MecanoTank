/*
 * CLIFreeRTOS.h
 *
 *  Created on: 22 Jun 2023
 *      Author: walberts
 */

#ifndef CLIFREERTOS_HPP_
#define CLIFREERTOS_HPP_

#include "CLI_command.hpp"

class HeapStatsCommand: public AbstractCommand {
public:
    static HeapStatsCommand *getInstance();
	virtual ~HeapStatsCommand();

protected:
	HeapStatsCommand();
    static BaseType_t command(char *outputBuffer, size_t outputLen, const char *command);

    static HeapStatsCommand *instance;
};

class TaskStatsCommand: public AbstractCommand {
public:
    static TaskStatsCommand *getInstance();
	virtual ~TaskStatsCommand();

protected:
	TaskStatsCommand();
    static BaseType_t command(char *outputBuffer, size_t outputLen, const char *command);

    static TaskStatsCommand *instance;
};

#endif /* CLIFREERTOS_HPP_ */
