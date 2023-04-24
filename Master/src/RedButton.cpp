#include <Arduino.h>

#include "RedButton.hpp"

RedButton::RedButton(const std::string &bn, double p, uint8_t pin, boolean *enabled)
    : Block("RedButton", bn, p), enabled(true), redButtonPin(pin), destination(enabled)
{
}

RedButton::~RedButton()
{
}

void RedButton::calculate()
{
    // On first press of red button, set destination to false
    boolean r = digitalRead(redButtonPin);
    if (r && enabled)
    {
        enabled = false;
        *destination = false;
    }
}
