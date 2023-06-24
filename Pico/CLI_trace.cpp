#include "CLI_trace.hpp"

AddTraceeableCommand *AddTraceeableCommand::instance(nullptr);

AddTraceeableCommand *AddTraceeableCommand::getInstance()
{
	if (instance == nullptr)
	{
		instance = new AddTraceeableCommand();
	}
	return instance;
}

AddTraceeableCommand::~AddTraceeableCommand()
{
}

AddTraceeableCommand::AddTraceeableCommand() : AbstractCommand("addTraceable",
															   "addTraceable <output>:\n Start tracing output.\n\n",
															   AddTraceeableCommand::command, 1)
{
}

BaseType_t AddTraceeableCommand::command(char *outputBuffer, size_t outputLen,
										 const char *command)
{
	BaseType_t traceableNameLength(0);
	const char *traceableName = FreeRTOS_CLIGetParameter(command, 1,
														 &traceableNameLength);
	std::string traceableNameString(traceableName, traceableNameLength);

	auto output = instance->servoGroup->getOutput(traceableNameString);

	if (!output.success)
	{
		snprintf(outputBuffer, outputLen, "Error: unable to find output: %s\n ",
				 traceableNameString.c_str());
		// std::cerr << "Error: unable to find output " << traceableNameString << std::endl;
	}
	else
	{
		auto traceBlock = instance->servoGroup->getTraceBlock();
		traceBlock->addTraceable(traceableNameString, output.result);
		snprintf(outputBuffer, outputLen, "\nOK.\n");
	}
	return pdFALSE;
}

/*--------------------------------------------------*/

ClearTraceablesCommand *ClearTraceablesCommand::instance(nullptr);

ClearTraceablesCommand *ClearTraceablesCommand::getInstance()
{
	if (instance == nullptr)
	{
		instance = new ClearTraceablesCommand();
	}
	return instance;
}

ClearTraceablesCommand::~ClearTraceablesCommand()
{
}

ClearTraceablesCommand::ClearTraceablesCommand() : AbstractCommand("clearTraceables",
																   "clearTraceables:\n Remove all tracebles.\n\n",
																   ClearTraceablesCommand::command, 0)
{
}

BaseType_t ClearTraceablesCommand::command(char *outputBuffer, size_t outputLen,
										   const char *command)
{
	auto traceBlock = instance->servoGroup->getTraceBlock();
	traceBlock->clearTraceables();
	snprintf(outputBuffer, outputLen, "\nOK.\n");
	return pdFALSE;
}

/*--------------------------------------------------*/

ClearTraceableCommand *ClearTraceableCommand::instance(nullptr);

ClearTraceableCommand *ClearTraceableCommand::getInstance()
{
	if (instance == nullptr)
	{
		instance = new ClearTraceableCommand();
	}
	return instance;
}

ClearTraceableCommand::~ClearTraceableCommand()
{
}

ClearTraceableCommand::ClearTraceableCommand() : AbstractCommand("clearTraceable",
																 "clearTraceable <output>:\n Remove output from tracebles.\n\n",
																 ClearTraceableCommand::command, 1)
{
}

BaseType_t ClearTraceableCommand::command(char *outputBuffer, size_t outputLen,
										  const char *command)
{
	BaseType_t traceableNameLength(0);
	const char *traceableName = FreeRTOS_CLIGetParameter(command, 1,
														 &traceableNameLength);
	std::string traceableNameString(traceableName, traceableNameLength);

	auto traceBlock = instance->servoGroup->getTraceBlock();
	auto r = traceBlock->clearTraceable(traceableNameString);
	if (r.success)
	{
		snprintf(outputBuffer, outputLen, "\nOK.\n");
	}
	else
	{
		snprintf(outputBuffer, outputLen,
				 "Error: couldn't find traceable to erase: %s\n",
				 traceableNameString.c_str());
	}
	return pdFALSE;
}

/*--------------------------------------------------*/

DumpTraceCommand *DumpTraceCommand::instance(nullptr);

DumpTraceCommand *DumpTraceCommand::getInstance()
{
	if (instance == nullptr)
	{
		instance = new DumpTraceCommand();
	}
	return instance;
}

DumpTraceCommand::~DumpTraceCommand()
{
}

DumpTraceCommand::DumpTraceCommand() : AbstractCommand("dumpTrace", "dumpTrace:\n Dump all traceables.\n\n",
													   DumpTraceCommand::command, 0)
{
}

BaseType_t DumpTraceCommand::command(char *outputBuffer, size_t outputLen,
									 const char *command)
{
	// Not reentrant!
	static bool dumping = false;
	static uint time = 0;
	static uint endTime = 0;
	static TraceBlock *traceBlock = nullptr;
	std::string line = "";
	if (!dumping)
	{
		dumping = true;
		traceBlock = instance->servoGroup->getTraceBlock();

		traceBlock->startDump();
		endTime = traceBlock->getEndTime();
		time = traceBlock->getStartTime();
		line = traceBlock->getHeader() + "\n";
	}
	line += traceBlock->getTraceOfTime(time) + "\n";
	time++;
	if (time == endTime)
	{
		line += "OK.\n";
		traceBlock->endDump();
		dumping = false;
		time = 0;
		endTime = 0;
		traceBlock = nullptr;
	}
	snprintf(outputBuffer, outputLen, line.c_str());
	return dumping;
}
