#include "Mapper.h"
#include <cstring>

Mapper0::Mapper0(const std::vector<uint8_t>&prg,const std::vector<uint8_t>&chr)
    : prgRom(prg), chrRom(chr) {}

uint8_t Mapper0::readPrg(uint16_t addr) {
    addr &= (prgRom.size()>16384)?0x7FFF:0x3FFF;
    return prgRom[addr];
}

void Mapper0::writePrg(uint16_t addr, uint8_t data) {
    // NROM is read-only
}

uint8_t Mapper0::readChr(uint16_t addr) {
    if(chrRom.empty()) return 0;
    return chrRom[addr & 0x1FFF];
}

void Mapper0::writeChr(uint16_t addr, uint8_t data) {
    if(chrRom.empty()) return; // CHR RAM not handled
}

IMapper* MapperFactory::create(uint8_t id, const std::vector<uint8_t>&prg, const std::vector<uint8_t>&chr) {
    switch(id) {
        case 0: return new Mapper0(prg, chr);
        default: return nullptr;
    }
}
