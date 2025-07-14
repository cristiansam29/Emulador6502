#include "PPU.h"
#include <cstring>

PPU::PPU() {
    std::memset(framebuffer, 0, sizeof(framebuffer));
}

uint8_t PPU::cpuRead(uint16_t addr) {
    // Stub PPU registers
    return 0;
}

void PPU::cpuWrite(uint16_t addr, uint8_t data) {
    // Stub PPU registers
}

void PPU::step() {
    // Simple dummy rendering: clear framebuffer
}
