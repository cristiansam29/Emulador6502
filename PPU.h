#pragma once
#include <array>
#include <vector>
#include <cstdint>

// Very small placeholder implementation of the NES PPU. It stores
// registers and character ROM data but does not fully emulate graphics.
class PPU {
public:
    void loadCHR(const std::vector<uint8_t> &chr);

    uint8_t readRegister(uint16_t addr);
    void writeRegister(uint16_t addr, uint8_t value);

private:
    std::array<uint8_t, 8> registers{};
    std::vector<uint8_t> chrROM;
};
