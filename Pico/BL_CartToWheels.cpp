#include "BL_CartToWheels.hpp"

#include <iostream>

#include "T_ID.hpp"
#include "Quad.hpp"
#include "Transformer.hpp"

const IDTerminal CartToWheelsBlock::IN_X("cartX");
const IDTerminal CartToWheelsBlock::IN_Y("cartY");
const IDTerminal CartToWheelsBlock::IN_RZ("cartRZ");

const IDTerminal CartToWheelsBlock::OUT_BL("wheelBL");
const IDTerminal CartToWheelsBlock::OUT_FL("wheelFL");
const IDTerminal CartToWheelsBlock::OUT_FR("wheelFR");
const IDTerminal CartToWheelsBlock::OUT_BR("wheelBR");

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
	addInput(IN_X, &xCart);
	addInput(IN_Y, &yCart);
	addInput(IN_RZ, &rzCart);

	addOutput(OUT_BL, &lbCart);
	addOutput(OUT_FL, &lfCart);
	addOutput(OUT_FR, &rfCart);
	addOutput(OUT_BR, &rbCart);
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