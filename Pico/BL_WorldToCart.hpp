#ifndef WORLD_TO_CART_HPP_
#define WORLD_TO_CART_HPP_

#include "BL_Leaf.hpp"
#include "T.hpp"

class WorldToCartBlock : public LeafBlock
{
public:
    WorldToCartBlock(const std::string &bn);
    virtual ~WorldToCartBlock();
    virtual void calculate();

    static const IDTerminal IN_X;
    static const IDTerminal IN_Y;
    static const IDTerminal IN_RZ;

    static const IDTerminal OUT_X;
    static const IDTerminal OUT_Y;
    static const IDTerminal OUT_RZ;

private:
    double safeDbl;

    double xCart;
    double yCart;
    double rzCart;

    double *xWorld;
    double *yWorld;
    double *rzWorld;
};

#endif
