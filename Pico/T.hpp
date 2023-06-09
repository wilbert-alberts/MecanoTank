/*
 * Terminal.h
 *
 *  Created on: 26 mei 2023
 *      Author: wilbert
 */

#ifndef T_H_
#define T_H_

#include <string>
#include <memory>
#include <iostream>

#include "ErrorHandling.hpp"

class Terminal {
public:
	Terminal() ;
	virtual ~Terminal() ;

	virtual bool hasID() const;
	virtual const std::string& getID() const;

	static const std::string separator;
	virtual const std::string& getFQN() const;

	virtual bool hasCompositeStructure() const;
	virtual const Terminal& getHead() const;
	virtual const Terminal& getTail() const;

	bool equals(const Terminal& t) const;

protected:
	// Precondition: t not null and different from this.
	virtual bool compareEqual(const Terminal *t) const;
};

std::ostream& operator<<(std::ostream &strm, const Terminal &a);

#endif /* T_H_ */
