#pragma once

#include "Bus.h"
#include "Cartridge.h"
#include "PPU.h"
#include "APU.h"

#include <array>

// Bus que conecta CPU, PPU, APU y cartucho
class NESBus : public Bus {
public:
    NESBus();

    void insertCartridge(Cartridge* cart);

    // Implementaci\u00f3n de Bus
    uint8_t read(c6502* cpu, Addr address, bool sync=false) override;
    void write(c6502* cpu, Addr address, uint8_t data) override;

    PPU ppu;
    APU apu;

private:
    Cartridge* cartridge = nullptr;
    std::array<uint8_t, 2048> cpu_ram{}; // RAM interna

    // Entrada de mandos
    uint8_t controller_state[2]{};
};

