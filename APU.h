#pragma once
#include <cstdint>
class APU {
public:
    void reset() {}
    void clock() {}
    uint8_t readRegister(uint16_t) { return 0; }
    void writeRegister(uint16_t, uint8_t) {}
};
