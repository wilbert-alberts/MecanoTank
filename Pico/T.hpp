/*
 * Terminal.h
 *
 *  Created on: 26 mei 2023
 *      Author: wilbert
 */

#ifndef T_H_
#define T_H_

class Terminal {
public:
	Terminal() ;
	virtual ~Terminal() ;

	bool equals(const Terminal& t) const;
protected:
	virtual bool compareEqual(const Terminal *t) const;
};
#endif /* T_H_ */
