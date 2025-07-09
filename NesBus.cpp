#include "NesBus.h"
#include "PPU.h"
#include <fstream>
#include <iostream>

NesBus::NesBus() {}
NesBus::~NesBus() {}

bool NesBus::loadROM(const std::string &path) {
    std::ifstream f(path, std::ios::binary);
    if (!f)
        return false;

    std::vector<uint8_t> header(16);
    f.read(reinterpret_cast<char*>(header.data()), 16);
    if (header[0] != 'N' || header[1] != 'E' || header[2] != 'S' || header[3] != 0x1A)
        return false;

    size_t prgSize = header[4] * 16384; // 16KB units
    size_t chrSize = header[5] * 8192;  // 8KB units

    prgROM.resize(prgSize);
    f.read(reinterpret_cast<char*>(prgROM.data()), prgSize);

    chrROM.resize(chrSize);
    if (chrSize)
        f.read(reinterpret_cast<char*>(chrROM.data()), chrSize);

    if (ppu)
        ppu->loadCHR(chrROM);

    return true;
}

uint8_t NesBus::read(c6502 *cpu, Addr addr, bool sync) {
    addr &= 0xFFFF;
    if (addr < 0x2000) {
        // internal RAM mirrored every 2KB
        return ram[addr & 0x07FF];
    } else if (addr < 0x4000) {
        // PPU registers mirrored every 8 bytes
        if (ppu)
            return ppu->readRegister(0x2000 + (addr & 7));
        return 0;
    } else if (addr < 0x4020) {
        // APU / IO. Only controller for now
        if (ctrl && addr == 0x4016)
            return ctrl->read();
        return 0;
    } else if (addr >= 0x8000) {
        // PRG ROM (NROM only, 16K or 32K)
        size_t index = addr - 0x8000;
        if (prgROM.size() == 16384 && addr >= 0xC000)
            index = addr - 0xC000; // mirror if 16K
        if (index < prgROM.size())
            return prgROM[index];
        return 0;
    }
    // other ranges: return open bus
    return 0;
}

void NesBus::write(c6502 *cpu, Addr addr, uint8_t data) {
    addr &= 0xFFFF;
    if (addr < 0x2000) {
        ram[addr & 0x07FF] = data;
    } else if (addr < 0x4000) {
        if (ppu)
            ppu->writeRegister(0x2000 + (addr & 7), data);
    } else if (addr < 0x4020) {
        if (ctrl && addr == 0x4016)
            ctrl->write(data);
    } else if (addr >= 0x6000 && addr < 0x8000) {
        sram[addr - 0x6000] = data;
    }
    // writes to ROM are ignored
}
