#ifndef SUM_HPP_
#define SUM_HPP_

#include "BL.hpp"

class SumBlock : public Block
{
public:
    SumBlock(const std::string &bn, float o, float s1_, float s2_, float s3_, float s4_);
    SumBlock(const std::string &bn, float o);
    virtual ~SumBlock();
    virtual void calculate(int64_t);

    float *getOutput();
    void setOffset(float o);
    void setFactor1(float o);
    void setFactor2(float o);
    void setFactor3(float o);
    void setFactor4(float o);
    void setIn1(float *p);
    void setIn2(float *p);
    void setIn3(float *p);
    void setIn4(float *p);

private:
    float offset;
    float safeValue;
    float s1;
    float s2;
    float s3;
    float s4;

    float out;
    float *in1;
    float *in2;
    float *in3;
    float *in4;
};

#endif
