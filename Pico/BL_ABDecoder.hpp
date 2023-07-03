#ifndef __ABDECODER_BLOCK_HPP
#define __ABDECODER_BLOCK_HPP

// #include "FreeRTOS.h"

#include <vector>

#include "BL_Leaf.hpp"
#include "T.hpp"
#include "ABDecoder.hpp"

class ABDecoderBlock : public LeafBlock
{
public:
    ABDecoderBlock(const std::string &bn, uint8_t a, uint8_t b, double metersPerInc);
    virtual ~ABDecoderBlock();
    virtual void calculate();

private:
    uint8_t pinA;
    uint8_t pinB;
    int64_t position;
    double meterPerIncrement;
    double positionDbl;
    ABDecoder decoder;

    static void pinChangedStatic(uint gpio, uint32_t mask);
    static std::vector<ABDecoderBlock *> decoders;

    void pinChanged();
};

#endif
