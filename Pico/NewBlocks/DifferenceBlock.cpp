/*
 * DifferenceBlock.cpp
 *
 *  Created on: 26 mei 2023
 *      Author: wilbert
 */

#include "DifferenceBlock.h"

DifferenceBlock::DifferenceBlock(const std::string &blockName) :
		Block("Difference", blockName), actual(nullptr), desired(nullptr), difference(
				0) {
}

 DifferenceBlock::~DifferenceBlock() {
}


 void DifferenceBlock::setInput(const Terminal &t, double *src) {
	if (src != nullptr) {
		if (IN_ACTUAL.equals(t)) {
			actual = src;
		}
		if (IN_DESIRED.equals(t)) {
			desired = src;
		}
	}
}

 double* DifferenceBlock::getOutput(const Terminal &t) {
	if (Block::OUT_OUTPUT.equals(t))
		return &difference;
	else
		return nullptr;
}

 void DifferenceBlock::calculate() {
	difference = *desired - *actual;
}

const IDTerminal DifferenceBlock::IN_ACTUAL = IDTerminal("actual");
const IDTerminal DifferenceBlock::IN_DESIRED = IDTerminal("desired");

