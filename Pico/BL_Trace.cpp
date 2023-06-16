
#include <vector>
#include <string>
#include <iostream>

#include "BL_Trace.hpp"

TraceBlockAbstract::TraceBlockAbstract(uint nrOfDoublesToBuffer)
    : buffer(new double[nrOfDoublesToBuffer]),
      bufferSize(nrOfDoublesToBuffer),
      time(0),
      idx(0),
      nrTraceables(0),
      nrTraces(0)
{
}

TraceBlockAbstract::~TraceBlockAbstract()
{
    delete[] buffer;
}

void TraceBlockAbstract::calculate()
{
    // Todo: skip calculate when dump is in progress
    // Retrieve and store all traceables
    for (uint i = 0; i < traceables.size(); i++)
    {
        buffer[idx++] = *(traceables[i]);
    }
    // See whether we need to start back at idx 0
    if (idx + nrTraceables > bufferSize)
    {
        idx = 0;
    }
    // Increase time.
    time++;
}

void TraceBlockAbstract::addTraceable(const std::string &name, double *src)
{
    // Adding traceables only possible at time zero.
    if (time == 0)
    {
        traceables.push_back(src);
        labels.push_back(name);
        nrTraceables++;
        nrTraces = bufferSize / nrTraceables;
    }
    else
    {
        Error("Adding traceables not possible anymore, sequence has already started.");
    }
}

void TraceBlockAbstract::dumpTrace()
{
    uint dumpIdx(0);
    uint dumpTime(0);
    dumpLabels();
    if (time * nrTraceables > bufferSize)
    { // We've overrun the buffer
        // Start at idx and dump until idx-1 (mod bufferSize)
        dumpIdx = idx;
        dumpTime = time - nrTraces;
        // First dump from idx to bufferSize
        while (dumpIdx < (nrTraces * nrTraceables))
        {
            dumpTrace(dumpTime, buffer + dumpIdx, nrTraceables);
            dumpIdx += nrTraceables;
            dumpTime++;
        }
    } // Start at 0 and dump until idx-1
    dumpIdx = 0;
    while (dumpIdx < idx)
    {
        dumpTrace(dumpTime, buffer + dumpIdx, nrTraceables);
        dumpIdx += nrTraceables;
        dumpTime++;
    }
}

void TraceBlockAbstract::dumpLabels()
{
    std::cout << "time";
    for (uint i = 0; i < traceables.size(); i++)
    {
        std::cout << ", " << labels[i];
    }
    std::cout << std::endl;
}

void TraceBlockAbstract::dumpTrace(uint time, double *traceables, uint nrTraceables)
{
    std::cout << time;
    for (uint i = 0; i < nrTraceables; i++)
    {
        std::cout << ", " << traceables[i];
    }
    std::cout << std::endl;
}

void TraceBlockAbstract::Error(const std::string &msg)
{
    std::cerr << "Error: " << msg << std::endl;
}

/************************ TraceBlock *******************************8*/
TraceBlock::TraceBlock()
    : TraceBlockAbstract(BUFFERSIZE_IN_DOUBLES),
      Block("TraceBlock", "tracer")
{
    std::cout << "Traceblock: allocating memory for: " << BUFFERSIZE_IN_DOUBLES << " doubles"<< std::endl;
    semDumping = xSemaphoreCreateBinary();
    xSemaphoreGive(semDumping);
}
TraceBlock::~TraceBlock()
{
}

void TraceBlock::calculate()
{
    auto r = xSemaphoreTake(semDumping, 0);

    if (r == pdTRUE)
    {
        TraceBlockAbstract::calculate();
        xSemaphoreGive(semDumping);
    }
}

void TraceBlock::dumpTrace()
{
    const TickType_t takeDumping = 5000 / portTICK_PERIOD_MS;

    auto r = xSemaphoreTake(semDumping, takeDumping);
    if (r == pdTRUE)
    {
        TraceBlockAbstract::dumpTrace();
        xSemaphoreGive(semDumping);
    }
    else {
        std::cerr <<"Unable to dumpTrace, taking semaphore failed." << std::endl;
    }
}
