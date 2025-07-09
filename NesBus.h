#pragma once

#include "Bus.h"
#include "c6502.h"
#include <array>
#include "Controller.h"
#include <vector>
#include <string>

// Forward declarations for NES components
class PPU;
class APU;
class Controller;

// NES addressable memory bus implementing mapper 0 (NROM)
class NesBus : public Bus {
public:
    NesBus();
    ~NesBus();

    // Load iNES ROM into memory. Returns true on success.
    bool loadROM(const std::string &path);

    uint8_t read(c6502 *cpu, Addr addr, bool sync = false) override;
    void write(c6502 *cpu, Addr addr, uint8_t data) override;

    PPU    *ppu  = nullptr;
    APU    *apu  = nullptr;
    Controller *ctrl = nullptr;

private:
    std::vector<uint8_t> prgROM;   // PRG ROM data
    std::vector<uint8_t> chrROM;   // CHR ROM data (for PPU)

    std::array<uint8_t, 0x0800> ram{};      // 2KB internal RAM
    std::array<uint8_t, 0x2000> sram{};     // optional battery RAM
};
