
//
// vector.cpp -- polar and cartesian notation of a vector
//

#include "Polar.hpp"

#include "Cartesian.hpp"

Polar::Polar(const Polar &p)
    : r(p.getR()),
      a(p.getA())
{
    normalize();
}

Polar::Polar(const Cartesian &c)
{
    double X;
    double Y;
    c.getXY(X, Y);
    r = sqrt(X * X + Y * Y);
    a = atan2(Y, X);
}

Polar Polar::operator=(const Cartesian c)
{
    Polar tmp(c);
    tmp.getRA(r, a);
    return *this;
}

Polar operator*(Polar a, Polar b)
{
    Polar tmp(a);
    tmp *= b;
    return tmp;
}

Polar operator/(Polar a, Polar b)
{
    Polar tmp(a);
    tmp /= b;
    return tmp;
}

Polar operator+(Polar a, Polar b)
{
    return Polar(Cartesian(a) + Cartesian(b));
}

Polar operator-(Polar a, Polar b)
{
    return Polar(Cartesian(a) - Cartesian(b));
}
