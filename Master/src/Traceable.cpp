/*
 * Traceable.cpp
 *
 *  Created on: 3 april 2023
 *      Author: walberts
 */

#include "Traceable.hpp"

Traceable::Traceable(const std::string& n, const double* src): name(n), traceable(src) {
}

const std::string& Traceable::getName() const {
	return name;
}

double Traceable::getValue() const {
	return *traceable;
}
	
