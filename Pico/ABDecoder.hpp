#ifndef __ABDECODER_HPP__
#define __ABDECODER_HPP__

#include "stdint.h"

class ABDecoder
{
public:
    ABDecoder(uint8_t initialA, uint8_t initialB)
    : currentA(initialA)
    , currentB(initialB)
    , position(0)
    {}

    virtual ~ABDecoder() 
    {}
    
    void stateChanged(uint8_t newA, uint8_t newB)
    {

        // Capture state
        uint8_t state = (currentA << 3) | (newA << 2) | (currentB << 1) | (newB);

        /*
              aold       anew    bold    bnew
        0       0         0       0       0           0
        1       0         0       0       1           -1
        2       0         0       1       0           +1
        3       0         0       1       1           0
        4       0         1       0       0           +1
        5       0         1       0       1           err
        6       0         1       1       0           err
        7       0         1       1       1           -1
        8       1         0       0       0           -1
        9       1         0       0       1           err
        10      1         0       1       0           err
        11      1         0       1       1           +1
        12      1         1       0       0           0
        13      1         1       0       1           +1
        14      1         1       1       0           -1
        15      1         1       1       1           0

        */
        // Process new state
        switch (state)
        {
        case 0:
        case 3:
        case 12:
        case 15:
            // No change
            break;
        case 1:
        case 7:
        case 8:
        case 14:
            position--;
            break;
        case 2:
        case 4:
        case 11:
        case 13:
            position++;
        case 5:
        case 6:
        case 9:
        case 10:
            // Error transition
            break;
        }

        // Update AB values
        currentA = newA;
        currentB = newB;
    }

    int64_t getPosition()
    {
        return position;
    }

private:
    uint8_t currentA;
    uint8_t currentB;

    int64_t position;
};

#endif