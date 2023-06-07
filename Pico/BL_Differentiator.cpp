/*
 * Block.h
 *
 *  Created on: 25 Jan 2023
 *      Author: walberts
 */

#include "BL_Differentiator.hpp"

DifferentiatorBlock::DifferentiatorBlock(const std::string &bn, double _servoFrequency)
	: Block("Differentiator", bn)
	, input(&safeInput)
	, previousInput(safeInput)
	, output(0.0)
	, servoFrequency(_servoFrequency)
	, safeInput(0.0)
{
}

DifferentiatorBlock::~DifferentiatorBlock()
{};

void DifferentiatorBlock::calculate()
{
	output = (*input - previousInput) * servoFrequency;
	previousInput = *input;
	// std::cout << "ED: input: " << *input << ", output: " << output << std::endl;
}

void DifferentiatorBlock::setInput(const Terminal &t, double *src)
{
	if (src != nullptr)
		input = src;
}

double *DifferentiatorBlock::getOutput(const Terminal &t)
{
	return &output;
}
