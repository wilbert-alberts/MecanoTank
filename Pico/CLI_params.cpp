#include <vector>
#include <string>

#include "CLI_params.hpp"

SetParameterCommand *SetParameterCommand::instance(nullptr);

SetParameterCommand *SetParameterCommand::getInstance()
{
	if (instance == nullptr)
	{
		instance = new SetParameterCommand();
	}
	return instance;
}

SetParameterCommand::~SetParameterCommand()
{
}

SetParameterCommand::SetParameterCommand()
	: AbstractCommand("setParameter",
					  "addTraceable <param> <value>:\n Set param to value\n",
					  SetParameterCommand::command, 2)
{
}

BaseType_t SetParameterCommand::command(char *outputBuffer, size_t outputLen,
										const char *command)
{
	BaseType_t paramNameLen(0);
	const char *paramName = FreeRTOS_CLIGetParameter(command, 1,
													 &paramNameLen);
	std::string paramNameString(paramName, paramNameLen);

	BaseType_t valueLength(0);
	const char *value = FreeRTOS_CLIGetParameter(command, 2,
												 &valueLength);
	std::string valueString(value, valueLength);
	double valueDbl = std::stod(valueString);

	auto output = instance->servoGroup->setParameter(paramNameString, valueDbl);

	if (!output.success)
	{
		snprintf(outputBuffer, outputLen, "Error: unable to set parameter: %s\n ",
				 paramNameString.c_str());
		// std::cerr << "Error: unable to find output " << traceableNameString << std::endl;
	}
	else
	{
		snprintf(outputBuffer, outputLen, "\nOK.\n");
	}
	return pdFALSE;
}

/*--------------------------------------------------*/

GetParameterCommand *GetParameterCommand::instance(nullptr);

GetParameterCommand *GetParameterCommand::getInstance()
{
	if (instance == nullptr)
	{
		instance = new GetParameterCommand();
	}
	return instance;
}

GetParameterCommand::~GetParameterCommand()
{
}

GetParameterCommand::GetParameterCommand()
	: AbstractCommand("getParameter",
					  "getParameter <param>:\n Return the value of param.\n",
					  GetParameterCommand::command, 1)
{
}

BaseType_t GetParameterCommand::command(char *outputBuffer, size_t outputLen,
										const char *command)
{
	BaseType_t paramNameLen(0);
	const char *paramName = FreeRTOS_CLIGetParameter(command, 1,
													 &paramNameLen);
	std::string paramNameString(paramName, paramNameLen);

	auto output = instance->servoGroup->getParameter(paramNameString);

	if (!output.success)
	{
		snprintf(outputBuffer, outputLen, "Error: unable to get parameter: %s\n ",
				 paramNameString.c_str());
		// std::cerr << "Error: unable to find output " << traceableNameString << std::endl;
	}
	else
	{
		std::string valueString = std::to_string(output.result);
		snprintf(outputBuffer, outputLen, "%s %s\nOK.\n", paramNameString.c_str(), valueString.c_str());
	}
	return pdFALSE;
}

/*--------------------------------------------------*/

GetParametersCommand *GetParametersCommand::instance(nullptr);

GetParametersCommand *GetParametersCommand::getInstance()
{
	if (instance == nullptr)
	{
		instance = new GetParametersCommand();
	}
	return instance;
}

GetParametersCommand::~GetParametersCommand()
{
}

GetParametersCommand::GetParametersCommand()
	: AbstractCommand("getParameters",
					  "getParameters:\n Dump all parameter values.\n",
					  GetParametersCommand::command, 0)
{
}

BaseType_t GetParametersCommand::command(char *outputBuffer, size_t outputLen,
										 const char *command)
{
	snprintf(outputBuffer, outputLen,
			 "Error: not implemented yet\n");
	return pdFALSE;
}

/*--------------------------------------------------*/

GetParameterNamesCommand *GetParameterNamesCommand::instance(nullptr);

GetParameterNamesCommand *GetParameterNamesCommand::getInstance()
{
	if (instance == nullptr)
	{
		instance = new GetParameterNamesCommand();
	}
	return instance;
}

GetParameterNamesCommand::~GetParameterNamesCommand()
{
}

GetParameterNamesCommand::GetParameterNamesCommand()
	: AbstractCommand("getParameterNames", "getParameterNames:\n Dump all parameter names.\n",
					  GetParameterNamesCommand::command, 0)
{
}

BaseType_t GetParameterNamesCommand::command(char *outputBuffer, size_t outputLen,
											 const char *command)
{
	snprintf(outputBuffer, outputLen,
			 "Error: not implemented yet\n");
	return pdFALSE;
}
