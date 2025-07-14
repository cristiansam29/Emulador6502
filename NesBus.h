#pragma once
#include "Bus.h"
#include "CPU6502.h"
#include "PPU.h"
#include "APU.h"
#include "Controller.h"
#include "MapperRegistry.h"
#include <memory>
#include <string>
#include <array>

class NesBus : public Bus {
    std::array<uint8_t, 2048> ram{};
public:
    CPU6502 cpu;
    PPU ppu;
    APU apu;
    Controller pad1, pad2;
    std::unique_ptr<IMapper> mapper;

    NesBus();
    bool loadROM(const std::string& path);

    uint8_t read(CPU6502* cpu, Addr addr, bool sync=false) override;
    void write(CPU6502* cpu, Addr addr, uint8_t data) override;
};
