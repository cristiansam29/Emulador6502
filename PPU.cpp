#include "PPU.h"
#include "Cartridge.h"

#include <cstring>

PPU::PPU() {
    tbl_name.resize(2048);
    tbl_palette.resize(32);
    framebuffer.resize(256*240, 0xFF000000); // negro opaco
}

void PPU::connect(Cartridge* c) {
    cart = c;
}

uint8_t PPU::cpuRead(uint16_t addr) {
    // En esta implementaci\u00f3n simple solo devolvemos 0
    return 0;
}

void PPU::cpuWrite(uint16_t addr, uint8_t data) {
    // A\u00fan no implementado
}

void PPU::clock(int cycles) {
    // Para simplificar, cada cuadro tiene 341*262 ciclos de PPU
    for(int i=0;i<cycles;i++) {
        cycle++;
        if(cycle >= 341) {
            cycle = 0;
            scanline++;
            if(scanline >= 262) {
                scanline = 0;
                frame_complete = true;
            }
        }
    }
}

