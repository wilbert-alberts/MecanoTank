/*
 * ID.cpp
 *
 *  Created on: 26 mei 2023
 *      Author: wilbert
 */

#include "T_ID.hpp"

IDTerminal::IDTerminal(const std::string &n):
id(n) {

}

IDTerminal::~IDTerminal() {
	// TODO Auto-generated destructor stub
}

const std::string& IDTerminal::getID() const { return id; }

bool IDTerminal::compareEqual(const Terminal *t) const{
	const IDTerminal *other(dynamic_cast<const IDTerminal*>(t));
	return (other != nullptr) && (other->id == id);
}
