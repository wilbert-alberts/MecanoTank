/*
 * ErrorDifferene.cpp
 *
 *  Created on: 25 Jan 2023
 *      Author: walberts
 */

#include "BL_ErrorDifference.hpp"

#include "T_ID.hpp"

const IDTerminal ErrorDifferenceBlock::IN_ACTUAL("actual");
const IDTerminal ErrorDifferenceBlock::IN_DESIRED("desired");

ErrorDifferenceBlock::ErrorDifferenceBlock(const std::string &bn) :
		Block("ErrorDifferenceBlock", bn), safe_actual(0), actual(&safe_actual), desired(
				&safe_actual), error(0) {
}
ErrorDifferenceBlock::~ErrorDifferenceBlock() {
	// TODO Auto-generated destructor stub
}

void ErrorDifferenceBlock::calculate() {
	error = *desired - *actual;
}

void ErrorDifferenceBlock::setInput(const Terminal &t, double *p) {
	if (p != nullptr) {
		if (IN_ACTUAL.equals(t)) {
			actual = p;
		}
		if (IN_DESIRED.equals(t)) {
			desired = p;
		}
	}
}

double* ErrorDifferenceBlock::getOutput(const Terminal &t) {
	return &error;
}
