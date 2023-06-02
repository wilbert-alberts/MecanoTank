/*
 * Terminal.h
 *
 *  Created on: 26 mei 2023
 *      Author: wilbert
 */

#ifndef TERMINAL_H_
#define TERMINAL_H_

class Terminal {
public:
	Terminal() ;
	virtual ~Terminal() ;

	bool equals(const Terminal& t) const;
protected:
	virtual bool compareEqual(const Terminal *t) const;
};
#endif /* TERMINAL_H_ */
