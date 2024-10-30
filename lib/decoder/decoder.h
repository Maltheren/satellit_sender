#include<Arduino.h>


class decoder{
    uint16_t baud_rate;
    uint16_t T;
    const uint8_t pin = 2;
    uint16_t start_symbol = 0x2A2A;

public:
    decoder(uint16_t baud_rate);

    
};