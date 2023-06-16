#ifndef __BL_TRACE_HPP__
#define __BL_TRACE_HPP__

#include <vector>
#include <string>
#include <iostream>

#include "FreeRTOS.h"
#include <semphr.h>

#include "BL.hpp"

class TraceBlockAbstract
{
public:
    TraceBlockAbstract(uint nrOfDoublesToBuffer);

    virtual ~TraceBlockAbstract();

    virtual void calculate();
    virtual void addTraceable(const std::string &name, double *src);
    virtual void dumpTrace();

protected:
    virtual void dumpLabels();
    virtual void dumpTrace(uint time, double *traceables, uint nrTraceables);
    virtual void Error(const std::string &msg);

private:
    double *buffer;
    uint bufferSize;
    uint time;
    uint idx;
    std::vector<double *> traceables;
    uint nrTraceables;
    uint nrTraces;
    std::vector<std::string> labels;
};

class TraceBlock : public TraceBlockAbstract, public Block
{
public:
    TraceBlock();
    virtual ~TraceBlock();

    virtual void calculate();
    virtual void dumpTrace();
    
    static const uint BUFFERSIZE_IN_KB = (10);
    static const uint BUFFERSIZE_IN_DOUBLES = (BUFFERSIZE_IN_KB * 1024) / sizeof(double);

private:
    SemaphoreHandle_t semDumping;
};

#endif
