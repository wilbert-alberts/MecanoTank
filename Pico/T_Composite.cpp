/*
 * CheapCompositeTerminal.cpp
 *
 *  Created on: 6 Jun 2023
 *      Author: walberts
 */

#include "T_Composite.hpp"

CompositeTerminal::CompositeTerminal() :
		head(nullptr), tail(nullptr) {
	// TODO Auto-generated constructor stub

}

CompositeTerminal::~CompositeTerminal() {
	// TODO Auto-generated destructor stub
}

CompositeTerminal::CompositeTerminal(std::unique_ptr<const IDTerminal> _head,
		std::unique_ptr<const Terminal> _tail) :
		head(std::move(_head)),
		tail(std::move(_tail)) {
}

const IDTerminal& CompositeTerminal::getHead() const{
	return *head;
}

const Terminal& CompositeTerminal::getTail() const{
	return *tail;
}


bool CompositeTerminal::compareEqual(const Terminal *t) const
{
	const CompositeTerminal* other = dynamic_cast<const CompositeTerminal*>(t);
	if (other == nullptr) {
		return false;
	}
	else {
		return head->equals(other->getHead()) && tail->equals(other->getTail());
	}
	return false;
}
