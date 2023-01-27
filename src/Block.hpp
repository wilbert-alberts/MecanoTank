/*
 * Block.h
 *
 *  Created on: 25 Jan 2023
 *      Author: walberts
 */

#ifndef BLOCK_H_
#define BLOCK_H_

class Block {
public:
	Block(double p);
	virtual ~Block();
	virtual void calculate() = 0;
protected:
	double period;
};

#endif /* BLOCK_H_ */
