#include "Cartridge.h"

#include <fstream>

bool Cartridge::load(const std::string &path) {
    std::ifstream f(path, std::ios::binary);
    if(!f)
        return false;

    uint8_t header[16];
    f.read((char*)header, 16);
    if(f.gcount()!=16)
        return false;

    if(header[0] != 'N' || header[1] != 'E' || header[2] != 'S' || header[3] != 0x1a)
        return false;

    uint8_t prg_chunks = header[4];
    uint8_t chr_chunks = header[5];
    mapper_id = (header[6] >> 4) | (header[7] & 0xF0);
    mirroring_vertical = header[6] & 0x01;

    prg_rom.resize(prg_chunks * 0x4000);
    f.read((char*)prg_rom.data(), prg_rom.size());

    if(chr_chunks == 0)
        chr_mem.resize(0x2000); // CHR RAM
    else {
        chr_mem.resize(chr_chunks * 0x2000);
        f.read((char*)chr_mem.data(), chr_mem.size());
    }

    return true;
}

uint8_t Cartridge::readPRG(uint16_t addr) const {
    if(prg_rom.empty()) return 0;

    if(prg_rom.size() == 0x4000) // 16KB
        addr &= 0x3FFF; // espejo
    else
        addr &= 0x7FFF;

    return prg_rom[addr];
}

void Cartridge::writePRG(uint16_t addr, uint8_t data) {
    // NROM es solo lectura, pero se permite para expansiones
    if(prg_rom.size() == 0x4000)
        addr &= 0x3FFF;
    else
        addr &= 0x7FFF;

    if(addr < prg_rom.size())
        prg_rom[addr] = data;
}

uint8_t Cartridge::readCHR(uint16_t addr) const {
    if(chr_mem.empty()) return 0;
    addr &= (chr_mem.size()-1);
    return chr_mem[addr];
}

void Cartridge::writeCHR(uint16_t addr, uint8_t data) {
    if(chr_mem.empty()) return;
    addr &= (chr_mem.size()-1);
    chr_mem[addr] = data;
}

