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
#if ((PICO_CXX_ENABLE_EXCEPTIONS==1) || !defined(PICO_CXX_ENABLE_EXCEPTIONS) )
	throw std::invalid_argument(msg);
#endif
}

void Warning(const std::string& msg)  {
	std::cerr <<"Warning: "<< msg << std::endl;
}
