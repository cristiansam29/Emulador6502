#pragma once
#include <cstdint>

// Minimal stub for APU. Does not produce sound.
class APU {
public:
    uint8_t readRegister(uint16_t addr) { (void)addr; return 0; }
    void writeRegister(uint16_t addr, uint8_t data) { (void)addr; (void)data; }
};
