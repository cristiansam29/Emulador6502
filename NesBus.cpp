#include "NesBus.h"
#include "CPU6502.h"
#include "PPU.h"
#include "APU.h"
#include "Mapper.h"
#include "Controller.h"

#include <fstream>
#include <vector>
#include <cstring>

NesBus::NesBus()
    : ppu(new PPU()), apu(new APU()), mapper(nullptr), controller1(new Controller()) {}

NesBus::~NesBus() {
    delete ppu;
    delete apu;
    delete mapper;
    delete controller1;
}

bool NesBus::loadROM(const char *filename) {
    std::ifstream f(filename, std::ios::binary);
    if(!f)
        return false;

    std::vector<uint8_t> data((std::istreambuf_iterator<char>(f)), {});
    if(data.size() < 16)
        return false;

    const uint8_t *header = data.data();
    size_t prgSize = header[4]*16384;
    size_t chrSize = header[5]*8192;
    uint8_t mapperId = (header[6]>>4) | (header[7]&0xF0);

    size_t offset = 16;
    if(header[6] & 0x04)
        offset += 512; // trainer

    std::vector<uint8_t> prg(data.begin()+offset, data.begin()+offset+prgSize);
    offset += prgSize;
    std::vector<uint8_t> chr;
    if(chrSize) {
        chr.assign(data.begin()+offset, data.begin()+offset+chrSize);
    }

    delete mapper;
    mapper = MapperFactory::create(mapperId, prg, chr);
    if(!mapper)
        return false;

    reset();
    return true;
}

uint8_t NesBus::read(CPU6502 *cpu, Addr addr, bool sync) {
    if(addr < 0x2000) {
        return ram[addr & 0x7FF];
    } else if(addr < 0x4000) {
        return ppu->cpuRead(addr);
    } else if(addr >= 0x8000) {
        return mapper->readPrg(addr);
    }
    return 0;
}

void NesBus::write(CPU6502 *cpu, Addr addr, uint8_t data) {
    if(addr < 0x2000) {
        ram[addr & 0x7FF] = data;
    } else if(addr < 0x4000) {
        ppu->cpuWrite(addr, data);
    } else if(addr >= 0x8000) {
        mapper->writePrg(addr, data);
    }
}

void NesBus::clock() {
    ppu->step();
    apu->step();
}

void NesBus::reset() {
    std::memset(ram, 0, sizeof(ram));
}
