
//
// vector.h -- polar and cartesian notation of a vector
//

#ifndef _CARTESIAN_HPP
#define _CARTESIAN_HPP

#include <math.h>

#define TWOPI (M_PI * 2)
#define HALFPI (M_PI / 2)
#define KWARTPI (M_PI / 2)

#define DEG_PER_RAD (180.0 / M_PI)
#define TO_DEG(rad) (rad * DEG_PER_RAD)
#define TO_RAD(deg) (deg / DEG_PER_RAD)

class Polar;

class Cartesian
{
public:
  Cartesian() : x(0), y(0) {}
  Cartesian(const double xx, const double yy) : x(xx), y(yy) {}
  Cartesian(const Cartesian &c);
  Cartesian(const Polar &p);
  ~Cartesian() {}

  double getX() const { return x; }
  double getY() const { return y; }
  void getXY(double &X, double &Y) const
  {
    X = x;
    Y = y;
  }

  Cartesian operator=(const Polar p);
  Cartesian operator+=(const Cartesian c)
  {
    x += c.getX();
    y += c.getY();
    return *this;
  }
  Cartesian operator-=(const Cartesian c)
  {
    x -= c.getX();
    y -= c.getY();
    return *this;
  }
  Cartesian minus(const Cartesian c) const
  {
    Cartesian t(0, 0);
    t -= c;
    return t;
  }
  Cartesian rotate(const double Rz); // {Polar p (*this); p.rotate(Rz); *this = Cartesian (p); return *this;}

private:
  double x;
  double y;
};

Cartesian operator+(Cartesian a, Cartesian b);
Cartesian operator-(Cartesian a, Cartesian b);
Cartesian operator*(Cartesian a, Cartesian b);
Cartesian operator/(Cartesian a, Cartesian b);

#endif // _CARTESIAN_HPP
