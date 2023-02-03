/*
 * MeasurementSystem.cpp
 *
 *  Created on: 26 Jan 2023
 *      Author: walberts
 */

#include "SG_MeaSystem.hpp"

SG_MeaSystem::SG_MeaSystem(double p) : ServoGroup(p), rawSensor(nullptr), measurementSystem(nullptr)
{
}

SG_MeaSystem::~SG_MeaSystem(){};

std::vector<Block *>*  SG_MeaSystem::getSequence()
{
    sequence.clear();
    sequence.push_back(getRawSensor());
    sequence.push_back(getMeasurementSystem());
    getMeasurementSystem()->setInputX1(getRawSensor()->getOutputS1X());
    getMeasurementSystem()->setInputX2(getRawSensor()->getOutputS2X());
    getMeasurementSystem()->setInputY1(getRawSensor()->getOutputS1Y());
    getMeasurementSystem()->setInputY2(getRawSensor()->getOutputS2Y());
    return &sequence;
}

RawSensor *SG_MeaSystem::getRawSensor()
{
    if (rawSensor == nullptr)
    {
        rawSensor = new RawSensor("rawSensor", getPeriod());
    }
    return rawSensor;
}

MeasurementSystem *SG_MeaSystem::getMeasurementSystem()
{
    if (measurementSystem == nullptr)
    {
        measurementSystem = new MeasurementSystem("mea", getPeriod());
    }
    return measurementSystem;
}
