/*
 * ID.h
 *
 *  Created on: 26 mei 2023
 *      Author: wilbert
 */

#ifndef T_ID_H_
#define T_ID_H_

#include <string>

#include "T.hpp"

class IDTerminal: public Terminal {
public:
	IDTerminal(const std::string &n);
	virtual ~IDTerminal();

    const std::string& getID() const;

protected:
	virtual bool compareEqual(const Terminal *t) const;

private:
	const std::string id;
};

#endif /* T_ID_H_ */
