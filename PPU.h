#pragma once
#include <cstdint>

class PPU {
public:
    PPU();
    uint8_t cpuRead(uint16_t addr);
    void cpuWrite(uint16_t addr, uint8_t data);
    void step();

    const uint32_t* frameBuffer() const { return framebuffer; }

private:
    uint32_t framebuffer[256*240];
};
