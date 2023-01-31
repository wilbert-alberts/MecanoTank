#ifndef TRACER_HPP_
#define TRACER_HPP_

#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "Block.hpp"

class ServoGroup;

class Tracer 
{
public:
    Tracer(ServoGroup *sg);
    virtual ~Tracer();
    void startTracing() const;
    void stopTracing() const;
    std::string getTraceNames() const;
    virtual void captureTrace(uint64_t sequenceCounter);
    void setBufferSize(int bs);
    std::vector<double> popTrace(TickType_t timeout);

private:
    boolean tracing;
    std::vector<const double *> traceables;
    std::vector<std::string> traceNames;
    std::vector<double> bufferEntry;
    std::deque<std::vector<double>> traceBuffer;
    QueueHandle_t commandQueue;
    QueueHandle_t commandAckQueue;
    SemaphoreHandle_t bufferMux;
    SemaphoreHandle_t bufferSem;
};

#endif