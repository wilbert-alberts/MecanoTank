#ifndef __ABDECODER_BLOCK_HPP
#define __ABDECODER_BLOCK_HPP

// #include "FreeRTOS.h"

#include <vector>

#include "BL.hpp"
#include "ABDecoder.hpp"




class ABDecoderBlock: public Block
{
public:
    ABDecoderBlock(const std::string& bn, uint8_t a, uint8_t b);
    virtual ~ABDecoderBlock();
	virtual void calculate();

    double* getOutput();

private:
    uint8_t pinA;
    uint8_t pinB;
    uint64_t position;
    double   positionDbl;
    ABDecoder decoder;

    static void pinChangedStatic(uint gpio, uint32_t mask);
    static std::vector<ABDecoderBlock*> decoders;

    void pinChanged();
};

#endif