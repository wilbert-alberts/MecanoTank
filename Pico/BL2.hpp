/*
 * Bl.hpp
 *
 *  Created on: 24 May 2023
 *      Author: walberts
 */

#ifndef BL_HPP_
#define BL_HPP_

#include <string>
#include <vector>
#include <algorithm>

class Terminal {
public:
	Terminal() {
	}
	;
	virtual ~Terminal() {
	}
	;

	bool equals(const Terminal& t) const {
		if (this == &t)
			return true;
		else
			return compareEqual(&t);
	}
protected:
	virtual bool compareEqual(const Terminal *t) const {
		return false;
	}
};

class ID: public Terminal {
public:
	ID(const std::string &n) :
			id(n) {
	}
	;
	virtual ~ID() {
	}
	;

    const std::string& getID() const { return id; }

protected:
	virtual bool compareEqual(const Terminal *t) {
		const ID *other(dynamic_cast<const ID*>(t));
		return (other != nullptr) && (other->id == id);
	}

private:
	const std::string id;
};

class CompositeTerminal: public Terminal {
public:
	CompositeTerminal(const CompositeTerminal& _head, const CompositeTerminal& _tail)
	: head(_head)
	, tail(_tail)
	{}
	virtual ~CompositeTerminal() {}
    const Terminal& getHead() const {
        return head;
    }

    const Terminal& getTail() const {
        return tail;
    }

protected:
	Terminal head;
	Terminal tail;

	virtual bool compareEqual(const Terminal* t) {
		const CompositeTerminal *other(dynamic_cast<const CompositeTerminal*>(t));
		return ((other != nullptr) && head.equals(other->head) && tail.equals(other->tail));
	}
};

class Block {
public:
	Block(const std::string& typeName, const std::string& blockName)
	: type(typeName), id(blockName)
	{}
	virtual ~Block() {};

    const std::string& getBlockName() const { return id;};
    const std::string& getBlockTypeName()  const { return type;}

	static const ID IN_INPUT;
	static const ID OUT_OUTPUT ;

	virtual void calculate() = 0;
	virtual double* getOutput(const Terminal &t = OUT_OUTPUT) = 0;
	virtual void setInput(const Terminal &t = IN_INPUT, double *src = nullptr) = 0;

protected:
	std::string type;
	std::string id;
};

const ID Block::IN_INPUT  = ID("input");
const ID Block::OUT_OUTPUT = ID("output");

class Difference: public Block {
public:
	Difference(const std::string& blockName) :
		Block("Difference", blockName),
		actual(nullptr), desired(nullptr), difference(0) {
	}
	;
	virtual ~Difference() {
	}
	;

	static const ID IN_ACTUAL;
	static const ID IN_DESIRED;

	virtual void setInput(const Terminal &t, double *src) {
		if (src != nullptr) {
			if (IN_ACTUAL.equals(t)) {
				actual = src;
			}
			if (IN_DESIRED.equals(t)) {
				desired = src;
			}
		}
	}

	virtual double* getOutput(const Terminal &t = OUT_OUTPUT) {
		if (OUT_OUTPUT.equals(t))
			return &difference;
		else
			return nullptr;
	}

	virtual void calculate() {
		difference = *desired - *actual;
	}

private:
	double *actual;
	double *desired;
	double difference;
};

const ID Difference::IN_ACTUAL = ID("actual");
const ID Difference::IN_DESIRED = ID("desired");

class CompositeBlock : public Block{
public:
	CompositeBlock(const std::string& bn, std::vector<Block*> _blocks)
    : Block("CompositeBlock", bn)
    , blocks(_blocks)
    {
    }

    virtual ~CompositeBlock() {};

    virtual void calculate() {
        for (auto b: blocks) {
            b->calculate();
        }
    }

    virtual double* getOutput(const Terminal &t) {
        const CompositeTerminal* ct = dynamic_cast<const CompositeTerminal*>(&t);
        const auto head = ct->getHead();
        const auto tail = ct->getTail();

        const ID* headID = dynamic_cast<const ID*>(&head);
        const std::string headIDName = headID->getID();
        auto iter = std::find_if(blocks.begin(), blocks.end(), [](auto b){
            b->getBlockName() == headIDName;
        });

    }
protected:
    std::vector<Block*> blocks;
};

#endif /* BL_HPP_ */
