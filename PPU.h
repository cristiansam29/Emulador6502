#pragma once
#include <array>
#include <cstdint>

class PPU {
    std::array<uint32_t, 256*240> framebuffer{};
    int scanline = 0;
    int cycle = 0;
    bool nmiFlag = false;
public:
    void reset();
    void clock();
    bool pollNMI();
    uint8_t readRegister(uint16_t addr);
    void writeRegister(uint16_t addr, uint8_t data);
    uint32_t* getFrameBuffer() { return framebuffer.data(); }
};
