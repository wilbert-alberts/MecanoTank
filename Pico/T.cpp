/*
 * Terminal.cpp
 *
 *  Created on: 26 mei 2023
 *      Author: wilbert
 */

#include "T.hpp"

const std::string Terminal::separator(".");

static const Terminal nullTerminal;
static const std::string nullString("<null>");

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
	return nullString;
}

const std::string& Terminal::getFQN() const {
	::Error("Trying to getFQN() from element that doesn't support it.");
	return nullString;
}

bool Terminal::hasCompositeStructure() const {
	return false;
}

const Terminal& Terminal::getHead() const {
	::Error("Trying to getHead() from element that hasn't a Head.");
	return nullTerminal;
}

const Terminal& Terminal::getTail() const {
	::Error("Trying to getTail() from element that hasn't a Tail.");
	return nullTerminal;
}

bool Terminal::equals(const Terminal &t) const {
	if (this == &t)
		return true;
//	if (&t == nullptr)
//		return false;

	return compareEqual(&t);
}

bool Terminal::compareEqual(const Terminal *t) const {
	return false;
}

std::ostream& operator<<(std::ostream &strm, const Terminal &a) {
	strm << a.getFQN();
	return strm;
}
