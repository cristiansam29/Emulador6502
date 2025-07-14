#pragma once

#include <cstdint>

using Addr = uint16_t;

class CPU6502;
class PPU;
class APU;
class IMapper;
class Controller;

// NES address bus connecting CPU, PPU and cartridges
class NesBus {
public:
    NesBus();
    ~NesBus();

    bool loadROM(const char *filename);

    uint8_t read(CPU6502 *cpu, Addr addr, bool sync = false);
    void write(CPU6502 *cpu, Addr addr, uint8_t data);

    void clock();

    PPU* getPPU() const { return ppu; }

private:
    uint8_t ram[0x0800]; // 2KB internal RAM

    PPU *ppu;
    APU *apu;
    IMapper *mapper;
    Controller *controller1;

    void reset();
};
