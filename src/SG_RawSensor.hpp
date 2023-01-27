/*
 * SG_RawSensor.hpp
 *
 *  Created on: 27 Jan 2023
 *      Author: Wilbert Alberts
 */

#ifndef SG_RawSensor_HPP_
#define SG_RawSensor_HPP_

#include <vector>

#include "Block.hpp"
#include "RawSensor.hpp"
#include "MeasurementSystem.hpp"
#include "PID.hpp"

class SG_RawSensor
{
public:
    SG_RawSensor(double p);
    virtual ~SG_RawSensor();
    std::vector<Block*>* getSequence() ;
private:
    std::vector<Block *> sequence;
    double period;

    RawSensor* rawSensor;
    RawSensor* getRawSensor();
};

#endif /* SG_RawSensor_HPP_ */
