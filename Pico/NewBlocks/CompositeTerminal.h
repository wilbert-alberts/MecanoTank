/*
 * CompositeTerminal.h
 *
 *  Created on: 26 mei 2023
 *      Author: wilbert
 */

#ifndef COMPOSITETERMINAL_H_
#define COMPOSITETERMINAL_H_

#include <vector>

#include "Terminal.h"



class CompositeTerminal: public Terminal {
public:
	CompositeTerminal(const Terminal& _head, const Terminal& _tail);
	CompositeTerminal(const std::string& _head, const Terminal& _tail);
	CompositeTerminal(const std::string& _head, const std::string& _tail);
	CompositeTerminal(const std::string& _fqn);
	CompositeTerminal(std::vector<const Terminal&> ts);


	virtual ~CompositeTerminal();
    const Terminal& getHead() const ;

    const Terminal& getTail() const;

protected:
	const Terminal& head;
	const Terminal& tail;

	virtual bool compareEqual(const Terminal* t) const;
};

#endif /* COMPOSITETERMINAL_H_ */
