#include "NesBus.h"
#include "c6502.h"

NesBus::NesBus(const std::vector<uint8_t> &prg) : prg_rom(prg) {}

uint8_t NesBus::read(c6502 *cpu, Addr address, bool sync)
{
    (void)cpu;
    (void)sync;
    if (address < 0x2000) {
        return ram[address & 0x07FF];
    } else if(address >= 0x8000) {
        if(prg_rom.empty()) return 0;
        size_t offset = address - 0x8000;
        if(prg_rom.size() == 16384)
            offset %= 16384;
        if(offset < prg_rom.size())
            return prg_rom[offset];
    }
    return 0;
}

void NesBus::write(c6502 *cpu, Addr address, uint8_t data)
{
    (void)cpu;
    if(address < 0x2000) {
        ram[address & 0x07FF] = data;
    }
}
