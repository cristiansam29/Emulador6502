#include "NesBus.h"
#include <fstream>

NesBus::NesBus() : cpu(*this) {}

bool NesBus::loadROM(const std::string& path) {
    std::ifstream f(path, std::ios::binary);
    if (!f) return false;
    std::array<uint8_t,16> header{};
    f.read((char*)header.data(),16);
    if (header[0] != 'N' || header[1] != 'E' || header[2] != 'S') return false;
    uint8_t prgBanks = header[4];
    uint8_t chrBanks = header[5];
    uint8_t mapperID = (header[6] >> 4) | (header[7] & 0xF0);
    std::vector<uint8_t> prg(prgBanks*16384);
    std::vector<uint8_t> chr(chrBanks?chrBanks*8192:8192);
    f.read((char*)prg.data(), prg.size());
    f.read((char*)chr.data(), chr.size());
    auto it = MapperRegistry::registry().find(mapperID);
    if (it == MapperRegistry::registry().end()) return false;
    mapper.reset(it->second(prg, chr));
    cpu.setReset(true);
    ppu.reset();
    apu.reset();
    return true;
}

uint8_t NesBus::read(CPU6502*, Addr addr, bool) {
    if (addr < 0x2000) return ram[addr & 0x7FF];
    else if (addr < 0x4000) return ppu.readRegister(addr & 7);
    else if (addr == 0x4016) return pad1.read();
    else if (addr == 0x4017) return pad2.read();
    else if (addr >= 0x8000) return mapper ? mapper->readPRG(addr - 0x8000) : 0;
    return 0;
}

void NesBus::write(CPU6502*, Addr addr, uint8_t data) {
    if (addr < 0x2000) ram[addr & 0x7FF] = data;
    else if (addr < 0x4000) ppu.writeRegister(addr & 7, data);
    else if (addr == 0x4016) pad1.write(data);
    else if (addr == 0x4017) pad2.write(data);
    else if (addr >= 0x8000 && mapper) mapper->writePRG(addr - 0x8000, data);
}
