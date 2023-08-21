
//
// vector.h -- polar and cartesian notation of a vector
//

#ifndef _POLAR_HPP
#define _POLAR_HPP

#include <math.h>

#define TWOPI (M_PI * 2)
#define HALFPI (M_PI / 2)
#define KWARTPI (M_PI / 2)

#define DEG_PER_RAD (180.0 / M_PI)
#define TO_DEG(rad) (rad * DEG_PER_RAD)
#define TO_RAD(deg) (deg / DEG_PER_RAD)

class Cartesian;

// a polar vector
class Polar
{

public:
  Polar() : r(0), a(0) {}
  Polar(const double rr, const double aa) : r(rr), a(aa) { normalize(); }
  Polar(const Polar &p);
  Polar(const Cartesian &a);
  ~Polar() {}

  double getR() const { return r; }
  double getA() const { return a; }
  void getRA(double &R, double &A) const
  {
    R = r;
    A = a;
  }

  Polar operator=(const Polar p)
  {
    r = p.getR();
    a = p.getA();
    return *this;
  }
  Polar operator=(const Cartesian c);
  Polar operator*=(const Polar p)
  {
    r *= p.getR();
    a += p.getA();
    normalize();
    return *this;
  }
  Polar operator*=(const double d)
  {
    r *= d;
    return *this;
  }
  Polar operator/=(const Polar p)
  {
    r /= p.getR();
    a -= p.getA();
    normalize();
    return *this;
  }
  Polar operator/=(const double d)
  {
    r /= d;
    return *this;
  }
  Polar minus(const Polar p) const
  {
    Polar t(p);
    t.a += M_PI;
    t.normalize();
    return t;
  }
  Polar rotate(const double Rz)
  {
    a += Rz;
    return *this;
  }

  void normalize()
  {
    while (a > M_PI)
      a -= TWOPI;
    while (a < -M_PI)
      a += TWOPI;
  }

private:
  double r;
  double a;
};

Polar operator*(Polar a, Polar b);
Polar operator/(Polar a, Polar b);
Polar operator+(Polar a, Polar b);
Polar operator-(Polar a, Polar b);

#endif // _POLAR_HPP
