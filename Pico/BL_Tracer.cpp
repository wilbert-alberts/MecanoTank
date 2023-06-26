/*
 * BL_Tracer.cpp
 *
 *  Created on: 24-May-2023
 *      Author: benslag
 */
#include <stdio.h>
#include "BL_Tracer.hpp"

TracerBlock::TracerBlock(const std::string &bn, int _nSamples, float sfr)
    : Block("TracerBlock", bn),
    sampleFrequency (sfr),
    nSamples  (_nSamples)
{
    for (int i = 0; i < TRACER_N_INPUTS; i++){
        inputs   [i] = &safeInput;
        sigNames [i] = "None";
    }


    samples = new float [TRACER_N_INPUTS * nSamples];
}

TracerBlock::~TracerBlock()
{
    delete [] samples;
}

void TracerBlock::calculate (int64_t count) 
{
    if (state == IDLE) {
        if (*startCondition) state = TRACING;
    }
    if (state == TRACING) {
        if (*stopCondition){
            state = STOP_SEEN;
            stopCount = 0;
        }
    }
    if (state == STOP_SEEN) {
        if (stopCount++ >= samplesPostStop) state = DONE;
    }

    if (state == TRACING || state == STOP_SEEN) {
       int ix = fillIndex * TRACER_N_INPUTS;
       for (int i = 0; i < TRACER_N_INPUTS; i++) {
           samples [ix++] = *inputs [i];
       }
       fillIndex = (fillIndex+1) % nSamples;
       if (fillIndex == emptyIndex) {
          emptyIndex = (emptyIndex+1) % nSamples;
          bufferFull = true;
       }
    }

    if (state == DONE) {
        report ();
        state = REPORTED;
    }
}



void TracerBlock::setInput (int which, const char *name, float *p) 
{
    if (which < TRACER_N_INPUTS) {
        inputs   [which] = p;
        sigNames [which] = name;
    }
}

void TracerBlock::clear ()
{
    state      = IDLE;
    fillIndex  = emptyIndex = 0;
    bufferFull = false;
    nSamples   = 0;
    stopCount  = 0;
    state      = IDLE;
    fillIndex  = emptyIndex = 0;
} 

void TracerBlock::report () 
{
    int nsa = (fillIndex-emptyIndex+nSamples) % nSamples;
    printf ("Tracer block %s, %d samples; buffer %d bytes, sample frequency = %g [Hz]; ", 
            getBlockName ().c_str (), nsa, 
            sizeof(float) * TRACER_N_INPUTS * nSamples, 
            sampleFrequency);
    printf ("state = %s (%d)\n\n", //IDLE, TRACING, STOP_SEEN, DONE, REPORTED};
               state==IDLE? "Idle": 
               state==TRACING? "Tracing":
               state==STOP_SEEN? "Stop seen":
               state==DONE? "Done":
               state==REPORTED? "Reported": "Unknown!",
               (int) state
            );
    printf ("Index, ");
    
    for (int i = 0; i < TRACER_N_INPUTS; i++) {
        printf ("%s, ", sigNames [i]);
    }
    printf ("\n");

    for (int i = 0; i < nsa; i++) {
        int ix = ((emptyIndex + i + nSamples) % nSamples) * TRACER_N_INPUTS;
        printf ("%d, ", i);
        for (int j = 0; j < TRACER_N_INPUTS; j++) {
            printf ("%f, ", samples [ix++]);
        }
        printf ("\n");
    }
}