/*
 * BL_Tracer.hpp
 *
 *  Created on: 24-May-2023
 *      Author: benslag
 */
#ifndef _TRACER_H_
#define _TRACER_H_

#include <string>

#include "BL.hpp"

#define TRACER_N_INPUTS (7)



class TracerBlock : public Block
{
public:
    enum State {IDLE, TRACING, STOP_SEEN, DONE, REPORTED};
	TracerBlock(const std::string &bn, int _nSamples, float sfr);
	virtual ~TracerBlock();
	virtual void calculate(int64_t counter);
	void report ();
    void clear ();
	void setInput (int which, const char *sigName, float *p);
    State getState () {return state;}
    void setStartCondition (bool *stac) {startCondition = stac;}
    void setStopCondition  (bool *stoc, unsigned int _samplesPostStop = 100) {
        stopCondition   = stoc; 
        samplesPostStop = _samplesPostStop;
        stopCount = 0;
    }

private:
    float safeInput = 0.0;
    bool  never = false;
    bool  now = true;
    bool  bufferFull = false;
    float sampleFrequency;
    int   nSamples;
    bool  *startCondition = &now;
    bool  *stopCondition = &never;
    unsigned int samplesPostStop = 100;
    int   stopCount = 0;
    State state = IDLE;
    int   fillIndex = 0;
    int   emptyIndex = 0;
    const char *sigNames [TRACER_N_INPUTS];
    float *inputs   [TRACER_N_INPUTS];
    float *samples;
};

#endif /* _TRACER_H_ */