/*
 * SG_MeaSystem.hpp
 *
 *  Created on: 27 Jan 2023
 *      Author: Wilbert Alberts
 */

#ifndef SG_MeaSystem_HPP_
#define SG_MeaSystem_HPP_

#include <vector>

#include "Block.hpp"
#include "RawSensor.hpp"
#include "MeasurementSystem.hpp"
#include "PID.hpp"

class SG_MeaSystem
{
public:
    SG_MeaSystem(double p);
    virtual ~SG_MeaSystem();
    std::vector<Block*>* getSequence() ;
private:
    std::vector<Block *> sequence;
    double period;

    RawSensor* rawSensor;
    RawSensor* getRawSensor();
    MeasurementSystem* measurementSystem;
    MeasurementSystem* getMeasurementSystem();
};

#endif /* SG_MeaSystem_HPP_ */
