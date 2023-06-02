/*
 * ID.h
 *
 *  Created on: 26 mei 2023
 *      Author: wilbert
 */

#ifndef IDTERMINAL_H_
#define IDTERMINAL_H_

#include <string>

#include "Terminal.h"

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

#endif /* IDTERMINAL_H_ */
