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



Tracer::Tracer(const std::string &bn, double period, ServoGroup *sg) : Block("Tracer", bn, period)
{
    commandQueue = xQueueCreate(4, sizeof(TracerCommandEnum));
    commandAckQueue = xQueueCreate(4, sizeof(bool));
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
    values.resize(traceables.size());
}

Tracer::Tracer(const std::string &bn, double period, std::vector<Block *> *s): Block("Tracer", bn, period)
{
    commandQueue = xQueueCreate(4, sizeof(TracerCommandEnum));
    commandAckQueue = xQueueCreate(4, sizeof(bool));
    // auto seq = sg->getSequence();
    std::for_each(s->begin(), s->end(), [this](Block *p)
                  {
        auto traceablesForBlock = p->getTraceables();
        std::for_each(traceablesForBlock.begin(), traceablesForBlock.end(), [this](const double* tr){
            traceables.push_back(tr);
        });
        auto traceNamesForBlock = p->getTraceNames();
        std::for_each(traceNamesForBlock.begin(), traceNamesForBlock.end(), [this, p](const std::string& n){
            traceNames.push_back(p->getBlockName()+ "::" + n);
        }); });
}

Tracer::~Tracer() {

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

void Tracer::calculate()
{
    // Note: this function is called from the Timer task.
    // It should never block and run as quick as possible.
    static bool tracing = false;
    if (tracing)
    {
        std::transform(traceables.begin(), traceables.end(), values.begin(), [](const double* r){
            return *r;
        });   
        sendTrace(values);
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

void Tracer::sendTrace(const std::vector<double>& vs) {
    std::for_each(vs.begin(), vs.end(), [](double v){
        Serial.println(v);
    });
} 