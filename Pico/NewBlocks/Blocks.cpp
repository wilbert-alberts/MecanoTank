//============================================================================
// Name        : Blocks.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

#include "DifferenceBlock.h"
#include "CompositeBlock.h"
#include "CompositeTerminal.h"

int main() {
	double actualInput = 42;
	double desiredInput = 41;

	double* result;

	auto block = new DifferenceBlock("MyDiff");

	block->setInput(DifferenceBlock::IN_ACTUAL, &actualInput);
	block->setInput(DifferenceBlock::IN_DESIRED, &desiredInput);

	result = block->getOutput(DifferenceBlock::OUT_OUTPUT);

	block->calculate();

	cout << "Result: " << *result << endl;



	double actualInputComp = 41;
	double desiredInputComp = 42;

	vector<Block*> compositeBlocks;
	compositeBlocks.push_back(block);

	auto compBlock = new CompositeBlock("MyComposite", compositeBlocks);
	auto head = IDTerminal("MyDiff");
	auto tail = DifferenceBlock::IN_ACTUAL;
	auto comp = CompositeTerminal(head, tail);

	compBlock->setInput(CompositeTerminal(IDTerminal("MyDiff"), DifferenceBlock::IN_ACTUAL), &actualInputComp );
	compBlock->setInput(CompositeTerminal("MyDiff", DifferenceBlock::IN_DESIRED), &desiredInputComp );
	result = compBlock->getOutput(CompositeTerminal(IDTerminal("MyDiff"), DifferenceBlock::OUT_OUTPUT) );

	compBlock->calculate();

	cout << "Result: " << *result << endl;



	return 0;
}
