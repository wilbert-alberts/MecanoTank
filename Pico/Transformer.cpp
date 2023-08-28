//
// transformer.cpp -- position transformations for mecanum cart
//

#include "Transformer.hpp"

#define DEFAULT_RADIUS (0.225 / 2.0) // meter radius of wheels to center of cart

double Transformer::radius(DEFAULT_RADIUS);

void Transformer::worldToCart(const XYAVect world, XYAVect &cart)
{
    // first apply displacement, then angle

    Cartesian xy(0, 0);
    xy -= world.getXY(); // negative xy

    cart = xy;                  // Rz = 0; displacement done
    cart.setRz(-world.getRz()); // cart x, y = -world xy
    cart.rotate(cart.getRz());  // apply angle
}

void Transformer::cartToWorld(const XYAVect cart, XYAVect &world)
{
    // undo angle
    Cartesian c2 = cart.getXY();
    c2.rotate(-cart.getRz());
    Cartesian w(0, 0);
    w -= c2; // world xy = -cart xy
    world = w;
    world.setRz(-cart.getRz());
}

void Transformer::cartToWheels(const XYAVect current, const XYAVect desired, Quad &wheels)
{
    Cartesian c(desired.getXY());
    double x = c.getX();
    double y = c.getY();
    double rot = radius * unwind(desired.getRz(), current.getRz()); // rotation distance

    // viewed from above in cart coords, positive Rz is clockwise
    double lb, lf, rf, rb;
    lf = -x - y + rot;
    rf = x - y - rot;
    lb = x - y + rot;
    rb = -x - y - rot;

    wheels.set(lb, lf, rf, rb);
}

void Transformer::wheelsToCart(const Quad wheels, XYAVect &cart)
{
    double lb, lf, rf, rb;
    wheels.get(lb, lf, rf, rb);
    double rot = (lf + lb - rf - rb);
    cart.setRz(unwind(rot / radius, 0.0)); // rotation in cart coords

    lf -= rot;
    rf += rot;
    lb -= rot;
    rb += rot;
    double y = (lf + rf + lb + rb) / 4;
    double x = (rf + lb - lf - rb) / 4;
    cart.set(Cartesian(x, y));
}

double Transformer::unwind(double value, double reference)
{
    while (value - reference > M_PI)
        value -= TWOPI;
    while (value - reference < -M_PI)
        value += TWOPI;
    return value;
}
