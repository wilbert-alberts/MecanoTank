#include "FreeRTOS.h"

#include <iostream>

#include "hardware/gpio.h"
#include "algorithm"

#include "BL_ABDecoder.hpp"

std::vector<ABDecoderBlock *> ABDecoderBlock::decoders;

void ABDecoderBlock::pinChangedStatic(uint gpio, uint32_t mask)
{
    for (auto d : decoders)
    {
        d->pinChanged();
    }
}

ABDecoderBlock::ABDecoderBlock(const std::string &bn, uint8_t a, uint8_t b)
    : LeafBlock("ABDecoder", bn)
    , pinA(a)
    , pinB(b)
    , position(0)
    , positionDbl(0.0)
    , decoder(gpio_get(a), gpio_get(b))
{
    gpio_set_irq_enabled_with_callback(pinA, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, ABDecoderBlock::pinChangedStatic);
    gpio_set_irq_enabled_with_callback(pinB, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, ABDecoderBlock::pinChangedStatic);
    decoders.push_back(this);
    addDefaultOutput(&positionDbl);
}

ABDecoderBlock::~ABDecoderBlock() {
    gpio_set_irq_enabled(pinA, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, false);
    gpio_set_irq_enabled(pinB, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, false);
    std::remove(decoders.begin(), decoders.end(), this);
}

void ABDecoderBlock::pinChanged()
{
    uint8_t newA = gpio_get(pinA);
    uint8_t newB = gpio_get(pinB);
    decoder.stateChanged(newA, newB);
}

void ABDecoderBlock::calculate()
{
    position = decoder.getPosition();
    positionDbl = static_cast<double>(position);
    std::cout << "ABDecoder " << blockName << ": " << position << std::endl;
}
