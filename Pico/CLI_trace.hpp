#ifndef _CLI_TRACE_HPP_
#define _CLI_TRACE_HPP_

#include "CLI_command.hpp"

class AddTraceeableCommand : public AbstractCommand
{
public:
    static AddTraceeableCommand *getInstance();
    virtual ~AddTraceeableCommand();

protected:
    AddTraceeableCommand();
    static BaseType_t command(char *outputBuffer, size_t outputLen, const char *command);

    static AddTraceeableCommand *instance;
};

class ClearTraceablesCommand: public AbstractCommand
{
public:
    static ClearTraceablesCommand *getInstance();
    virtual ~ClearTraceablesCommand();

protected:
    ClearTraceablesCommand();
    static BaseType_t command(char *outputBuffer, size_t outputLen, const char *command);

    static ClearTraceablesCommand *instance;
};

class ClearTraceableCommand: public AbstractCommand
{
public:
    static ClearTraceableCommand *getInstance();
    virtual ~ClearTraceableCommand();

protected:
    ClearTraceableCommand();
    static BaseType_t command(char *outputBuffer, size_t outputLen, const char *command);

    static ClearTraceableCommand *instance;
};

class DumpTraceCommand: public AbstractCommand
{
public:
    static DumpTraceCommand *getInstance();
    virtual ~DumpTraceCommand();

protected:
    DumpTraceCommand();
    static BaseType_t command(char *outputBuffer, size_t outputLen, const char *command);

    static DumpTraceCommand *instance;
};

class GetTraceablesCommand: public AbstractCommand
{
public:
    static GetTraceablesCommand *getInstance();
    virtual ~GetTraceablesCommand();

protected:
    GetTraceablesCommand();
    static BaseType_t command(char *outputBuffer, size_t outputLen, const char *command);

    static GetTraceablesCommand *instance;
};
#endif
