#ifndef SUM4_HPP_
#define SUM4_HPP_

#include "BL.hpp"

#define SUM4_N_INPUTS 4
class Sum4Block : public Block
{
public:
    
    Sum4Block(const std::string &bn):Block("Sum4", bn)
    ,safeValue (0.0)
    ,out (0.0)
    {
        for (int i = 0; i < SUM4_N_INPUTS; i++) inputs [i] = &safeValue;
    }
    virtual ~Sum4Block() {}
    virtual void calculate(int64_t) {
        out = 0.0;
        for (int i=0; i < SUM4_N_INPUTS; i++) out += *inputs [i];
    }

    float *getOutput() {return &out;}
    void setInput (unsigned int which, float *p) {
        if (which < SUM4_N_INPUTS) inputs [which] = p;}

private:
    float safeValue;

    float out;
    float *inputs [SUM4_N_INPUTS];
};

#endif
