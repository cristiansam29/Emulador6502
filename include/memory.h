// CPU memory map implementation for Mapper 0
#pragma once

#include <cstdint>
#include <vector>
#include "cpu.h"
#include "ppu.h"

class Rom;

class Memory : public Bus {
public:
    Memory(PPU& ppu, Rom& rom);

    uint8_t read(c6502* cpu, Addr address, bool sync = false) override;
    void write(c6502* cpu, Addr address, uint8_t data) override;

private:
    PPU& ppu;
    Rom& rom;
    std::vector<uint8_t> ram;
};
