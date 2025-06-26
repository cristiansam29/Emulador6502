#include "memory.h"
#include "rom.h"

Memory::Memory(PPU& ppu_, Rom& rom_) : ppu(ppu_), rom(rom_), ram(2 * 1024, 0) {}

uint8_t Memory::read(c6502* cpu, Addr addr, bool sync) {
    (void)cpu; (void)sync;
    if (addr < 0x2000) {
        return ram[addr & 0x07FF];
    } else if (addr < 0x4000) {
        // PPU registers mirror every 8
        return 0; // placeholder
    } else if (addr >= 0x8000) {
        return rom.prg[addr - 0x8000];
    }
    return 0;
}

void Memory::write(c6502* cpu, Addr addr, uint8_t data) {
    (void)cpu;
    if (addr < 0x2000) {
        ram[addr & 0x07FF] = data;
    } else if (addr < 0x4000) {
        // write to PPU register
    }
}
