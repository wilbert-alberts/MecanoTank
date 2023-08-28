#ifndef CART_TO_WHEELS_HPP_
#define CART_TO_WHEELS_HPP_

#include "BL_Leaf.hpp"
#include "T.hpp"

#include "XYAVect.hpp"

class CartToWheelsBlock : public LeafBlock
{
public:
    CartToWheelsBlock(const std::string &bn);
    virtual ~CartToWheelsBlock();
    virtual void calculate();

    static const IDTerminal IN_X;
    static const IDTerminal IN_Y;
    static const IDTerminal IN_RZ;

    static const IDTerminal OUT_BL;
    static const IDTerminal OUT_FL;
    static const IDTerminal OUT_FR;
    static const IDTerminal OUT_BR;

private:
    double safeDbl;

    double lbCart;
    double lfCart;
    double rfCart;
    double rbCart;

    double *xCart;
    double *yCart;
    double *rzCart;

    XYAVect current;
};

#endif
