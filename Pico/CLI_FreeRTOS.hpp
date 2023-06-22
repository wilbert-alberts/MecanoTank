/*
 * CLIFreeRTOS.h
 *
 *  Created on: 22 Jun 2023
 *      Author: walberts
 */

#ifndef CLIFREERTOS_HPP_
#define CLIFREERTOS_HPP_

#include "CLI_command.hpp"

class CLI_heapStatsCommand: public AbstractCommand {
public:
    static CLI_heapStatsCommand *getInstance();
	virtual ~CLI_heapStatsCommand();

protected:
	CLI_heapStatsCommand();
    static BaseType_t command(char *outputBuffer, size_t outputLen, const char *command);

    static CLI_heapStatsCommand *instance;
};

class CLI_taskStatsCommand: public AbstractCommand {
public:
    static CLI_taskStatsCommand *getInstance();
	virtual ~CLI_taskStatsCommand();

protected:
	CLI_heapStatsCommand();
    static CLI_taskStatsCommand command(char *outputBuffer, size_t outputLen, const char *command);

    static CLI_taskStatsCommand *instance;
};

#endif /* CLIFREERTOS_HPP_ */
