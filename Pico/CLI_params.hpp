#ifndef _CLI_PARAMS_HPP_
#define _CLI_PARAMS_HPP_

#include "CLI_command.hpp"

class SetParameterCommand : public AbstractCommand
{
public:
    static SetParameterCommand *getInstance();
    virtual ~SetParameterCommand();

protected:
    SetParameterCommand();
    static BaseType_t command(char *outputBuffer, size_t outputLen, const char *command);

    static SetParameterCommand *instance;
};

class GetParameterCommand : public AbstractCommand
{
public:
    static GetParameterCommand *getInstance();
    virtual ~GetParameterCommand();

protected:
    GetParameterCommand();
    static BaseType_t command(char *outputBuffer, size_t outputLen, const char *command);

    static GetParameterCommand *instance;
};

class GetParametersCommand : public AbstractCommand
{
public:
    static GetParametersCommand *getInstance();
    virtual ~GetParametersCommand();

protected:
    GetParametersCommand();
    static BaseType_t command(char *outputBuffer, size_t outputLen, const char *command);
    void getParamNamesAndValues(std::vector<std::pair<std::string, std::string>> *v);

    static GetParametersCommand *instance;
};

class GetParameterNamesCommand : public AbstractCommand
{
public:
    static GetParameterNamesCommand *getInstance();
    virtual ~GetParameterNamesCommand();

protected:
    GetParameterNamesCommand();
    static BaseType_t command(char *outputBuffer, size_t outputLen, const char *command);

    static GetParameterNamesCommand *instance;
};

#endif
