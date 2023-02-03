#ifndef REDBUTTON_HPP_
#define REDBUTTON_HPP_

#include <Arduino.h>

#include "Block.hpp"

class RedButton : public Block
{
public:
    RedButton(const std::string &bn, double p, uint8_t pin, boolean *enabled);
    virtual ~RedButton();

    virtual void calculate();

private:
    bool enabled;
    uint8_t redButtonPin;
    bool *destination;
};

#endif