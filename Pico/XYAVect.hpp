
//
// vector.h -- polar and cartesian notation of a vector
//

#ifndef _XYAVECT_HPP
#define _XYAVECT_HPP

#include <math.h>

#define TWOPI (M_PI * 2)
#define HALFPI (M_PI / 2)
#define KWARTPI (M_PI / 2)

#define DEG_PER_RAD (180.0 / M_PI)
#define TO_DEG(rad) (rad * DEG_PER_RAD)
#define TO_RAD(deg) (deg / DEG_PER_RAD)

#include "Cartesian.hpp"

class Polar;

class XYAVect
{
public:
  XYAVect(); //: xy (0,0), Rz (0) {}
  XYAVect(Cartesian &c) : xy(c), Rz(0) {}
  XYAVect(Cartesian &c, double rz) : xy(c), Rz(rz) {}
  XYAVect(double x, double y, double rz) : xy(x, y), Rz(rz) {}
  ~XYAVect() {}

  XYAVect operator=(const Cartesian &c)
  {
    xy = c;
    Rz = 0;
    return *this;
  }
  XYAVect operator+=(const Cartesian &c)
  {
    xy += c;
    return *this;
  }
  XYAVect operator-=(const Cartesian &c)
  {
    xy -= c;
    return *this;
  }
  XYAVect operator+=(const XYAVect c); //  {xy += c.getXY(); Rz += c.getRz(); return *this;}
  XYAVect operator-=(const XYAVect c); //   {xy -= c.getXY(); Rz -= c.getRz(); return *this;}

  double getRz() const;    //  {return Rz;}
  Cartesian getXY() const; // {return xy;}
  void set(const Cartesian &c) { xy = c; }
  void set(const Cartesian &c, double r)
  {
    set(c);
    Rz = r;
  }
  void setRz(double rz) { Rz = rz; }
  XYAVect rotate(const double Rz); // {Polar p(xy); p.rotate (Rz); xy = Cartesian (p); return *this; }

private:
  Cartesian xy;
  double Rz;
};

#endif // _XYAVECT_HPP
