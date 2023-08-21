#include "BL_CartToWheels.hpp"

#include <iostream>

#include "T_ID.hpp"
#include "Quad.hpp"
#include "Transformer.hpp"

const IDTerminal CartToWheelsBlock::IN_X("cartX");
const IDTerminal CartToWheelsBlock::IN_Y("cartY");
const IDTerminal CartToWheelsBlock::IN_RZ("cartRZ");

const IDTerminal CartToWheelsBlock::OUT_LB("wheel_LB");
const IDTerminal CartToWheelsBlock::OUT_LF("wheel_LF");
const IDTerminal CartToWheelsBlock::OUT_RF("wheel_RF");
const IDTerminal CartToWheelsBlock::OUT_RB("wheel_RB");

CartToWheelsBlock::CartToWheelsBlock(const std::string &bn) 
: LeafBlock("CartToWheels", bn)
, safeDbl(0.0)
, lbCart(0.0)
, lfCart(0.0)
, rfCart(0.0)
, rbCart(0.0)
, xCart(&safeDbl)
, yCart(&safeDbl)
, rzCart(&safeDbl)
, current(0.0, 0.0, 0.0)
{
}

CartToWheelsBlock::~CartToWheelsBlock()
{
}

void CartToWheelsBlock::calculate()
{
	XYAVect input(*xCart, *yCart, *rzCart);
	Quad output;

	Transformer::cartToWheels(current, input, output);
	output.get(lbCart, lfCart, rfCart, rbCart);
	current = input;
}