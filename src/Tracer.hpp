#ifndef TRACER_HPP_
#define TRACER_HPP_

#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "Block.hpp"
#include "Traceable.hpp"

class ServoGroup;

class Tracer 
{
    typedef std::vector<double> Trace;
    typedef std::deque<Trace> TraceBuffer;

public:
    Tracer(ServoGroup *sg);
    virtual ~Tracer();
    void startTracing() const;
    void stopTracing() const;
    std::string getTraceNames() const;
    virtual void captureTrace(uint64_t sequenceCounter);
    void setBufferSize(int bs);
    Trace popTrace(TickType_t timeout);

private:
    boolean tracing;
    std::vector<Traceable> traceables;

    Trace bufferEntry;
    TraceBuffer traceBuffer;
    QueueHandle_t commandQueue;
    QueueHandle_t commandAckQueue;
    SemaphoreHandle_t bufferMux;
    SemaphoreHandle_t bufferSem;
};

#endif