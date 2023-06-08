/*
 * CheapCompositeTerminal.cpp
 *
 *  Created on: 6 Jun 2023
 *      Author: walberts
 */

#include "T_Composite.hpp"

CompositeTerminal::CompositeTerminal(std::unique_ptr<const IDTerminal> _head,
		std::unique_ptr<const Terminal> _tail) :
		head(std::move(_head)),
		tail(std::move(_tail)) {
}

CompositeTerminal::~CompositeTerminal() {
}

bool CompositeTerminal::hasCompositeStructure() const {
	return true;
}

const Terminal& CompositeTerminal::getHead() const{
	return *head;
}

const Terminal& CompositeTerminal::getTail() const{
	return *tail;
}


bool CompositeTerminal::compareEqual(const Terminal *t) const
{
	if (!t->hasCompositeStructure())
		return false;

	return (t->getHead().equals(*head)) && (t->getTail().equals(*tail));
}
