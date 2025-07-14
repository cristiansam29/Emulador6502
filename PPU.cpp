#include "PPU.h"

void PPU::reset() {
    scanline = cycle = 0;
    nmiFlag = false;
    framebuffer.fill(0xff000000);
}

void PPU::clock() {
    cycle++;
    if (cycle >= 341) {
        cycle = 0;
        scanline++;
        if (scanline >= 262) {
            scanline = 0;
            nmiFlag = true; // signal VBlank
        }
    }
}

bool PPU::pollNMI() {
    if (nmiFlag) {
        nmiFlag = false;
        return true;
    }
    return false;
}

uint8_t PPU::readRegister(uint16_t) { return 0; }
void PPU::writeRegister(uint16_t, uint8_t) {}
