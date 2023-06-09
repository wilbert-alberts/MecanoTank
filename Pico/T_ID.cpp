/*
 * ID.cpp
 *
 *  Created on: 26 mei 2023
 *      Author: wilbert
 */

#include "T_ID.hpp"

IDTerminal::IDTerminal(const std::string &n) :
		id(n) {

}

IDTerminal::~IDTerminal() {
	// TODO Auto-generated destructor stub
}

bool IDTerminal::hasID() const {
	return true;
}

const std::string& IDTerminal::getID() const {
	return id;
}

bool IDTerminal::compareEqual(const Terminal *t) const {
	if (!t->hasID())
		return false;
	return t->getID() == id;
}

const std::string& IDTerminal::getFQN() const {
	return id;
}
