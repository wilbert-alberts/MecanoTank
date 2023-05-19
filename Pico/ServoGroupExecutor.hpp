#ifndef __SERVOGROUP_EXECUTOR_HPP__
#define __SERVOGROUP_EXECUTOR_HPP__

#include "PeriodicTask.hpp"

#include "ServoGroup.hpp"

class ServoGroupExecutor: public PeriodicTask
{
public:
    ServoGroupExecutor(ServoGroup* sg);
    virtual ~ServoGroupExecutor() {}; 

protected:
    virtual void tick();

private:
    ServoGroup* servoGroup;

};


#endif
