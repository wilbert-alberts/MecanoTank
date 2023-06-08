/*
 * Terminal.h
 *
 *  Created on: 26 mei 2023
 *      Author: wilbert
 */

#ifndef T_H_
#define T_H_

#include <memory>

#include "ErrorHandling.hpp"

class Terminal {
public:
	Terminal() ;
	virtual ~Terminal() ;

	virtual bool hasID() const;
	virtual const std::string& getID() const;

	virtual bool hasCompositeStructure() const;
	virtual const Terminal& getHead() const;
	virtual const Terminal& getTail() const;

	bool equals(const Terminal& t) const;

protected:
	// Precondition: t not null and different from this.
	virtual bool compareEqual(const Terminal *t) const;
};
#endif /* T_H_ */
