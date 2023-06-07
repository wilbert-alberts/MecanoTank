/*
 * Block.h
 *
 *  Created on: 7 Jun 2023
 *      Author: walberts
 */

#include <string>
#include <iostream>
#include <stdexcept>

void Error(const std::string& msg)
{
	std::cerr <<"Error: "<< msg << std::endl;
	throw std::invalid_argument(msg);
}

void Warn(const std::string& msg)  {
	std::cerr <<"Warning: "<< msg << std::endl;
}
