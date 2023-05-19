/*
 * Block.h
 *
 *  Created on: 25 Jan 2023
 *      Author: walberts
 */

#ifndef __DEBUGBLOCK_H_
#define __DEBUGBLOCK_H_

#include <string>
#include <iostream>

#include "Block.hpp"

class DebugBlock: public Block
{
public:
	DebugBlock(const std::string &bn) : Block("DebugBlock", bn) {}
	virtual ~DebugBlock() {};
	virtual void calculate() {
		std::cout << "calculate: " << getBlockName() << std::endl;
	}
};


#endif /* BLOCK_H_ */
