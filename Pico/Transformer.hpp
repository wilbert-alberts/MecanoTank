//
// transformer.h -- position transformations for mecanum cart
//
// BSla, 20 jul 2023
//
#ifndef _TRANSFORMER_H
#define _TRANSFORMER_H

#include "XYAVect.hpp"
#include "Quad.hpp"


// World coordinates: XYAVect. Position of CART in x,y coordinates relative to ORIGIN. Rz is rotation of CART around its own origin, compared to ORIGIN

// Cart coordinates: XYAVect. Position of ORIGN in x, y coordinates relative to CART. Rz is the kept rotation of the WORLD relative to the CART,

// WheelPos: positions of the individual wheels, expressed in meters.

class Transformer
{
public:
    static double getRadius() { return radius; }
    static void setRadius(double rad) { radius = rad; }

    static void worldToCart(const XYAVect world, XYAVect &cart);
    static void cartToWorld(const XYAVect cart, XYAVect &world);
    static void cartToWheels(const XYAVect current, const XYAVect desired, Quad &wheels);
    static void wheelsToCart(const Quad wheels, XYAVect &cart);

    static double unwind(double value, double reference = 0.0);

private:
    static double radius;
};
#endif //_TRANSFORMER_H
