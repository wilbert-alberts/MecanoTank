#include "BL_Sum.hpp"

#include <iostream>

SumBlock::SumBlock(const std::string &bn, double o, double s1_, double s2_, double s3_, double s4_)
    : Block("Sum", bn), offset(o), safeValue(0), s1(s1_), s2(s2_), s3(s3_), s4(s4_),
      out(0), in1(&safeValue), in2(&safeValue), in3(&safeValue), in4(&safeValue)
{
}
SumBlock::SumBlock(const std::string &bn, double o)
    : Block("Sum", bn), offset(o), safeValue(0),
      s1(0), s2(0), s3(0), s4(0), out(0),
      in1(&safeValue), in2(&safeValue), in3(&safeValue), in4(&safeValue)
{
}
SumBlock::~SumBlock(){};
void SumBlock::calculate()
{
    out = *in1 * s1 + *in2 * s2 + *in3 * s3 + *in4 * s4 + offset;
    // std::cout<<"SUM in1: " << *in1 << ", in2: " << *in2 << ", out: " << out << std::endl;
    // std::cout<<"SUM in1: " << *in1*s1 << ", in2: " << *in2 * s2 << ", out: " << out << std::endl;
}
double *SumBlock::getOutput()
{
    return &out;
}
void SumBlock::setOffset(double o)
{
    offset = o;
}
void SumBlock::setFactor1(double o)
{
    s1 = o;
}
void SumBlock::setFactor2(double o)
{
    s2 = o;
}
void SumBlock::setFactor3(double o)
{
    s3 = o;
}
void SumBlock::setFactor4(double o)
{
    s4 = o;
}

void SumBlock::setIn1(double *p)
{
    in1 = p;
}
void SumBlock::setIn2(double *p)
{
    in2 = p;
}
void SumBlock::setIn3(double *p)
{
    in3 = p;
}
void SumBlock::setIn4(double *p)
{
    in4 = p;
}