/*
 * Terminal.cpp
 *
 *  Created on: 26 mei 2023
 *      Author: wilbert
 */

#include "T.hpp"

Terminal::Terminal() {
	// TODO Auto-generated constructor stub

}

Terminal::~Terminal() {
	// TODO Auto-generated destructor stub
}

bool Terminal::hasID() const {
	return false;
}

const std::string& Terminal::getID() const {
	::Error("Trying to getID() from element that hasn't an ID.");
	return "<null>";
}

bool Terminal::hasCompositeStructure() const {
	return false;
}

const Terminal& Terminal::getHead() const {
	::Error("Trying to getHead() from element that hasn't a Head.");
	return Terminal();
}

const Terminal& Terminal::getTail() const {
	::Error("Trying to getTail() from element that hasn't a Tail.");
	return Terminal();
}

bool Terminal::equals(const Terminal &t) const {
	if (this == &t)
		return true;
	if (&t == nullptr)
		return false;

	return compareEqual(&t);
}

bool Terminal::compareEqual(const Terminal *t) const {
	return false;
}
