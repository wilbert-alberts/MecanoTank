/*
 * CheapCompositeTerminal.h
 *
 *  Created on: 6 Jun 2023
 *      Author: walberts
 */

#ifndef T_COMPOSITE_H_
#define T_COMPOSITE_H_

#include <memory>

#include "T_ID.hpp"

class CompositeTerminal: public Terminal {
public:
	CompositeTerminal(std::unique_ptr<const IDTerminal> head, std::unique_ptr<const Terminal> tail);
	virtual ~CompositeTerminal();

	virtual const std::string getFQN() const;

	virtual bool hasCompositeStructure() const;
	virtual const Terminal& getHead() const;
	virtual const Terminal& getTail() const;

protected:
	virtual bool compareEqual(const Terminal *t) const;

private:
	std::unique_ptr<const IDTerminal> head;
	std::unique_ptr<const Terminal> tail;
};



#endif /* T_COMPOSITE_H_ */
