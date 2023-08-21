#include "BL_WorldToCart.hpp"

#include <iostream>

#include "T_ID.hpp"
#include "Transformer.hpp"

const IDTerminal WorldToCartBlock::IN_X("worldX");
const IDTerminal WorldToCartBlock::IN_Y("worldY");
const IDTerminal WorldToCartBlock::IN_RZ("worldRZ");

const IDTerminal WorldToCartBlock::OUT_X("cartX");
const IDTerminal WorldToCartBlock::OUT_Y("cartY");
const IDTerminal WorldToCartBlock::OUT_RZ("cartRZ");

WorldToCartBlock::WorldToCartBlock(const std::string &bn) 
: LeafBlock("WorldToCart", bn)
, safeDbl(0.0)
, xCart(0.0)
, yCart(0.0)
, rzCart(0.0)
, xWorld(&safeDbl)
, yWorld(&safeDbl)
, rzWorld(&safeDbl)
{
}

WorldToCartBlock::~WorldToCartBlock()
{
}

void WorldToCartBlock::calculate()
{
	XYAVect input(*xWorld, *yWorld, *rzWorld);
	XYAVect output;

	Transformer::worldToCart(input, output);
	Cartesian c = output.getXY();
	xCart = c.getX();
	yCart = c.getY();
	rzCart = output.getRz();
}