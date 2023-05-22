#ifndef SUM_HPP_
#define SUM_HPP_

#include "BL.hpp"

class SumBlock : public Block
{
public:
    SumBlock(const std::string &bn, double o, double s1_, double s2_, double s3_, double s4_);
    SumBlock(const std::string &bn, double o);
    virtual ~SumBlock();
    virtual void calculate();

    double *getOutput();
    void setOffset(double o);
    void setFactor1(double o);
    void setFactor2(double o);
    void setFactor3(double o);
    void setFactor4(double o);
    void setIn1(double *p);
    void setIn2(double *p);
    void setIn3(double *p);
    void setIn4(double *p);

private:
    double offset;
    double safeValue;
    double s1;
    double s2;
    double s3;
    double s4;

    double out;
    double *in1;
    double *in2;
    double *in3;
    double *in4;
};

#endif
