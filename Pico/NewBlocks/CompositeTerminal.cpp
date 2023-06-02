/*
 * CompositeTerminal.cpp
 *
 *  Created on: 26 mei 2023
 *      Author: wilbert
 */

#include <string>
#include <vector>
#include <cstring>
#include <deque>

#include "CompositeTerminal.h"
#include "IDTerminal.h"

CompositeTerminal::CompositeTerminal(const Terminal &_head,
		const Terminal &_tail) :
		head(_head), tail(_tail) {
}

CompositeTerminal::CompositeTerminal(const std::string &_head,	const Terminal &_tail) :
		head(IDTerminal(_head)), tail(_tail) {
}

CompositeTerminal::CompositeTerminal(const std::string &_head,	const std::string &_tail) :
		head(IDTerminal(_head)), tail(IDTerminal(_tail)) {
}

CompositeTerminal::CompositeTerminal(const std::string& fqn) {
	char* str = new char[fqn.size() + 1];
	char* tok = strtok(str, ".");
	std::deque<IDTerminal> ids;

	while (tok != nullptr) {
		ids.push_front(IDTerminal(tok));
		tok = strtok(nullptr, ".");
	}
	delete[] str;

	if (ids.size() >1) {
		Terminal& i = ids.[0];
		ids.pop_front();
		while (ids.size() > 0) {
			Terminal& c = new CompositeTerminal(ids[0], i);
		}
	}
}



CompositeTerminal::~CompositeTerminal() {
}

const Terminal& CompositeTerminal::getHead() const {
	return head;
}

const Terminal& CompositeTerminal::getTail() const {
	return tail;
}

bool CompositeTerminal::compareEqual(const Terminal* t) const {
	const CompositeTerminal *other(dynamic_cast<const CompositeTerminal*>(t));
	return ((other != nullptr) && head.equals(other->head) && tail.equals(other->tail));
}
