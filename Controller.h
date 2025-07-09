#pragma once
#include <cstdint>

// Simple controller handling 8 buttons
class Controller {
public:
    // Button order: A B Select Start Up Down Left Right
    void setState(uint8_t state) { buttons = state; shift = state; }

    uint8_t read() {
        uint8_t ret = (shift & 0x80) ? 1 : 0;
        shift <<= 1;
        return ret | 0x40; // open bus high bits set
    }

    void write(uint8_t value) {
        if(value & 1)
            shift = buttons;
    }

private:
    uint8_t buttons = 0; // bitmask
    uint8_t shift = 0;
};
