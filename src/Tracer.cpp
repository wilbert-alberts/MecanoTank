#include "freertos/FreeRTOS.h"
#include <Arduino.h>

#include <algorithm>

#include "Tracer.hpp"

#include "ServoGroup.hpp"

typedef enum
{
    START,
    STOP
} TracerCommandEnum;

Tracer::Tracer(ServoGroup *sg) : tracing(false)
{
    commandQueue = xQueueCreate(4, sizeof(TracerCommandEnum));
    commandAckQueue = xQueueCreate(4, sizeof(bool));
    bufferSem = xSemaphoreCreateCounting(1, 0);
    bufferMux = xSemaphoreCreateMutex();

    auto seq = sg->getSequence();
    std::for_each(seq->begin(), seq->end(), [this](Block *p)
                  {
        auto traceablesForBlock = p->getTraceables();
        std::for_each(traceablesForBlock.begin(), traceablesForBlock.end(), [this](const double* tr){
            traceables.push_back(tr);
        });
        auto traceNamesForBlock = p->getTraceNames();
        std::for_each(traceNamesForBlock.begin(), traceNamesForBlock.end(), [this, p](const std::string& n){
            traceNames.push_back(p->getBlockName()+ "::" + n);
        }); });
    bufferEntry.resize(1+traceables.size());
}

Tracer::~Tracer()
{
}
void Tracer::setBufferSize(int bs)
{
    if (!tracing)
    {
        xSemaphoreTake(bufferMux, portMAX_DELAY);
        traceBuffer.clear();
        vSemaphoreDelete(bufferSem);
        bufferSem = xSemaphoreCreateCounting(bs, 0);
        xSemaphoreGive(bufferMux);
    }
    else {
        Serial.println("Error: should not change trace buffer size during tracing.");
    }
}
void Tracer::startTracing() const
{
    bool ack;
    TracerCommandEnum cmd = TracerCommandEnum::START;
    auto sendResult = xQueueSend(commandQueue, &cmd, pdMS_TO_TICKS(1000));
    if (sendResult == pdTRUE)
    {
        auto ackResult = xQueueReceive(commandAckQueue, &ack, pdMS_TO_TICKS(1000));
        if (ackResult == pdTRUE)
        {
            if (!ack)
            {
                Serial.println("Unable to start tracing; ack result if false (expected true).");
            }
        }
        else
        {
            Serial.println("Unable to start tracing; ack result not received.");
        }
    }
    else
    {
        Serial.println("Unable to start tracing; unable to send command.");
    }
}
void Tracer::stopTracing() const
{
    bool ack;
    TracerCommandEnum cmd = TracerCommandEnum::STOP;
    auto sendResult = xQueueSend(commandQueue, &cmd, pdMS_TO_TICKS(1000));
    if (sendResult == pdTRUE)
    {
        auto ackResult = xQueueReceive(commandAckQueue, &ack, pdMS_TO_TICKS(1000));
        if (ackResult == pdTRUE)
        {
            if (!ack)
            {
                Serial.println("Unable to start tracing; ack result if false (expected true).");
            }
        }
        else
        {
            Serial.println("Unable to stop tracing; ack result not received.");
        }
    }
    else
    {
        Serial.println("Unable to stop tracing; unable to send command.");
    }
}

std::string Tracer::getTraceNames() const
{
    std::string result("");
    std::for_each(
        traceNames.begin(), traceNames.end(), [&result](const std::string &tr)
        { result += tr + ","; });
    if (result.at(result.length() - 1) == ',')
        result = result.substr(0, result.length() - 1);
    return result;
}

void Tracer::captureTrace(uint64_t traceCounter)
{
    // Note: this function is called from the Timer task.
    // It should never block and run as quick as possible.
    if (tracing)
    {
        xSemaphoreTake(bufferMux, pdMS_TO_TICKS(1000));
        traceBuffer.push_front(bufferEntry);
        traceBuffer.front().at(0) = (double)traceCounter;
        auto startOfValues = traceBuffer.front().begin();
        startOfValues++;
        std::transform(traceables.begin(), traceables.end(), startOfValues, [](const double *r)
                       { return *r; });
        auto sg = xSemaphoreGive(bufferSem);
        if (sg == pdFALSE)
        {
            // semGive failed, buffer full? Remove most recently added entry
            traceBuffer.pop_front();
            Serial.println("Trace buffer overflow");
        }
        xSemaphoreGive(bufferMux);
    }
    if (uxQueueMessagesWaiting(commandQueue) > 0)
    {
        TracerCommandEnum msg;
        auto r = xQueueReceive(commandQueue, &msg, 0);
        if (r == pdTRUE && msg == TracerCommandEnum::START)
        {
            tracing = true;
            bool ack = true;
            r = xQueueSend(commandAckQueue, &ack, 0);
            if (r != pdTRUE)
            {
                Serial.println("Unable to acknowledge trace start command.");
            }
        }
        if (r == pdTRUE && msg == TracerCommandEnum::STOP)
        {
            tracing = false;
            bool ack = true;
            r = xQueueSend(commandAckQueue, &ack, 0);
            if (r != pdTRUE)
            {
                Serial.println("Unable to acknowledge trace stop command.");
            }
        }
    }
}

std::vector<double> Tracer::popTrace(TickType_t to)
{
    std::vector<double> rv;
    auto r = xSemaphoreTake(bufferSem, to);
    if (r == pdTRUE)
    {
        xSemaphoreTake(bufferMux, portMAX_DELAY);
        rv = traceBuffer.back();
        traceBuffer.pop_back();
        xSemaphoreGive(bufferMux);
    }
    return rv;
}