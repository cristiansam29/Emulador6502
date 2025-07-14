#pragma once
#include <cstdint>

class Controller {
public:
    Controller() : state(0) {}
    void setButton(uint8_t mask, bool pressed) {
        if(pressed) state |= mask; else state &= ~mask;
    }
    uint8_t read() { return state; }
private:
    uint8_t state;
};

enum Button {
    BUTTON_A    = 0x01,
    BUTTON_B    = 0x02,
    BUTTON_SELECT = 0x04,
    BUTTON_START  = 0x08,
    BUTTON_UP     = 0x10,
    BUTTON_DOWN   = 0x20,
    BUTTON_LEFT   = 0x40,
    BUTTON_RIGHT  = 0x80
};
