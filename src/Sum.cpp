#include "Sum.hpp"

Sum::Sum(double p, double o, double s1_, double s2_, double s3_, double s4_)
    : Block(p), offset(o), safeValue(0), s1(s1_), s2(s2_), s3(s3_), s4(s4_), out(0), in1(&safeValue), in2(&safeValue), in3(&safeValue), in4(&safeValue)
{
}
Sum::Sum(double p, double o) : Block(p), offset(o), safeValue(0), s1(0), s2(0), s3(0), s4(0), out(0), in1(&safeValue), in2(&safeValue), in3(&safeValue), in4(&safeValue)
{
}
Sum::~Sum(){};
void Sum::calculate()
{
    out = *in1 * s1 + *in2 * s2 + *in3 * s3 + *in4 * s4 + offset;
}
double *Sum::getOutput()
{
    return &out;
}
void Sum::setOffset(double o)
{
    offset = o;
}
void Sum::setFactor1(double o)
{
    s1 = o;
}
void Sum::setFactor2(double o)
{
    s2 = o;
}
void Sum::setFactor3(double o)
{
    s3 = o;
}
void Sum::setFactor4(double o)
{
    s4 = o;
}

void Sum::setIn1(double *p)
{
    in1 = p;
}
void Sum::setIn2(double *p)
{
    in2 = p;
}
void Sum::setIn3(double *p)
{
    in3 = p;
}
void Sum::setIn4(double *p)
{
    in4 = p;
}