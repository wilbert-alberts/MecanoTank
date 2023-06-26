/*
 * Block.h
 *
 *  Created on: 25 Jan 2023
 *      Author: walberts
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include <string>
#include <vector>

class Block
{
public:
	Block(const std::string &tn, const std::string &bn);
	virtual ~Block();
	virtual void calculate(int64_t counter) = 0;

	const std::string& getBlockName();
	const std::string& getTypeName();

protected:
	std::string typeName;
	std::string blockName;
};


#endif /* BLOCK_H_ */
