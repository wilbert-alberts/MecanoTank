#ifndef TRACER_HPP_
#define TRACER_HPP_

#include <algorithm>
#include <string>
#include <vector>
#include "freertos/queue.h"
#include "Block.hpp"

class ServoGroup;

class Tracer : public Block
{
public:
    Tracer(const std::string &bn, double period, ServoGroup *sg);
    Tracer(const std::string &bn, double period, std::vector<Block *> *s);
    virtual ~Tracer();
    void startTracing() const;
    void stopTracing() const;
    std::string getTraceNames() const;
    virtual void calculate();

private:
    std::vector<const double *> traceables;
    std::vector<std::string> traceNames;
    std::vector<double> values;
    QueueHandle_t commandQueue;
    QueueHandle_t commandAckQueue;

    virtual void sendTrace(const std::vector<double>& values);
};

#endif