
//
// vector.cpp -- polar and cartesian notation of a vector
//

#include "XYAVect.hpp"

#include "Polar.hpp"

XYAVect::XYAVect() : xy(0, 0), Rz(0) {}

XYAVect XYAVect::operator+=(const XYAVect c)
{
    xy += c.getXY();
    Rz += c.getRz();
    return *this;
}
XYAVect XYAVect::operator-=(const XYAVect c)
{
    xy -= c.getXY();
    Rz -= c.getRz();
    return *this;
}

double XYAVect::getRz() const
{
    return Rz;
}

Cartesian XYAVect::getXY() const
{
    return xy;
}

XYAVect XYAVect::rotate(const double Rz)
{
    Polar p(xy);
    p.rotate(Rz);
    xy = Cartesian(p);
    return *this;
}
