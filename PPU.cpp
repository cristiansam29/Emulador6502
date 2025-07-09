#include "PPU.h"

void PPU::loadCHR(const std::vector<uint8_t> &chr) {
    chrROM = chr;
}

uint8_t PPU::readRegister(uint16_t addr) {
    addr &= 7;
    return registers[addr];
}

void PPU::writeRegister(uint16_t addr, uint8_t value) {
    addr &= 7;
    registers[addr] = value;
}
