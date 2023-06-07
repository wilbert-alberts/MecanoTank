/*
 * Block.h
 *
 *  Created on: 25 Jan 2023
 *      Author: walberts
 */

#include "BL_Differentiator.hpp"

DifferentiatorBlock::DifferentiatorBlock(const std::string &bn, double _servoFrequency)
	: LeafBlock("Differentiator", bn)
	, input(&safeInput)
	, previousInput(safeInput)
	, output(0.0)
	, servoFrequency(_servoFrequency)
	, safeInput(0.0)
{
	addDefaultInput(&input);
	addDefaultOutput(&output);
}

DifferentiatorBlock::~DifferentiatorBlock()
{};

void DifferentiatorBlock::calculate()
{
	output = (*input - previousInput) * servoFrequency;
	previousInput = *input;
	// std::cout << "ED: input: " << *input << ", output: " << output << std::endl;
}
