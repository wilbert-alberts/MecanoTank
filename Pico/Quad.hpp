//
// transformer.h -- position transformations for mecanum cart
//
// BSla, 20 jul 2023
//
#ifndef _QUAD_HPP
#define _QUAD_HPP

class Quad
{
public:
    Quad() : LB(0), LF(0), RF(0), RB(0) {}
    Quad(double lb, double lf, double rf, double rb) : LB(lb), LF(lf), RF(rf), RB(rb) {}
    Quad get(double &lb, double &lf, double &rf, double &rb) const
    {
        lb = LB;
        lf = LF;
        rf = RF;
        rb = RB;
        return *this;
    }
    Quad set(double lb, double lf, double rf, double rb)
    {
        Quad t(lb, lf, rf, rb);
        *this = t;
        return *this;
    }

private:
    double LB;
    double LF;
    double RF;
    double RB;
};

#endif // _QUAD_HPP