/*
 * MeasurementSystem.cpp
 *
 *  Created on: 26 Jan 2023
 *      Author: walberts
 */

#include "SG_RawSensor.hpp"

SG_RawSensor::SG_RawSensor(double p) : period(p), rawSensor(nullptr)
{
}

SG_RawSensor::~SG_RawSensor(){};

std::vector<Block *>* SG_RawSensor::getSequence()
{
    sequence.clear();
    sequence.push_back(getRawSensor());
    return &sequence;
}

RawSensor *SG_RawSensor::getRawSensor()
{
    if (rawSensor == nullptr)
    {
        rawSensor = new RawSensor(period);
    }
    return rawSensor;
}
