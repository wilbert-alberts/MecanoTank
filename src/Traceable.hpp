/*
 * Traceable.h
 *
 *  Created on: 3 april 2023
 *      Author: walberts
 */

#ifndef TRACEABLE_HPP__
#define TRACEABLE_HPP__

#include <string>

class Traceable
{
public:
	Traceable(const std::string& n, const double* src);

	const std::string& getName() const;
	double getValue() const;
	
private:
	const std::string name;
	const double*     traceable;
};


#endif
