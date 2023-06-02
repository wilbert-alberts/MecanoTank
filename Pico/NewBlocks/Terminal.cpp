/*
 * Terminal.cpp
 *
 *  Created on: 26 mei 2023
 *      Author: wilbert
 */

#include "Terminal.h"

Terminal::Terminal() {
	// TODO Auto-generated constructor stub

}

Terminal::~Terminal() {
	// TODO Auto-generated destructor stub
}

bool Terminal::equals(const Terminal& t) const {
		if (this == &t)
			return true;
		else
			return compareEqual(&t);
	}

bool Terminal::compareEqual(const Terminal *t) const {
	return false;
}
