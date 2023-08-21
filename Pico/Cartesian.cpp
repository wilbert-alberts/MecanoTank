
//
// vector.cpp -- polar and cartesian notation of a vector
//

#include "Cartesian.hpp"

#include "Polar.hpp"

Cartesian::Cartesian(const Cartesian &c)
{
    c.getXY(x, y);
}

Cartesian::Cartesian(const Polar &p)
{
    double R, A;
    p.getRA(R, A);
    x = R * cos(A);
    y = R * sin(A);
}

Cartesian Cartesian::rotate(const double Rz)
{
    Polar p(*this);
    p.rotate(Rz);
    *this = Cartesian(p);
    return *this;
}

Cartesian operator+(Cartesian a, Cartesian b)
{
    Cartesian tmp(a);
    tmp += b;
    return tmp;
}

Cartesian operator-(Cartesian a, Cartesian b)
{
    Cartesian tmp(a);
    tmp -= b;
    return tmp;
}

Cartesian operator*(Cartesian p, Cartesian q)
{
    return Cartesian(Polar(p) * Polar(q));
}

Cartesian operator/(Cartesian c, Cartesian d)
{
    return Cartesian(Polar(c) / Polar(d));
}
