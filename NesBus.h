#pragma once

#include "Bus.h"
#include <array>
#include <vector>

class NesBus : public Bus {
public:
    explicit NesBus(const std::vector<uint8_t> &prg);

    uint8_t read(c6502 *cpu, Addr address, bool sync = false) override;
    void write(c6502 *cpu, Addr address, uint8_t data) override;

private:
    std::vector<uint8_t> prg_rom;
    std::array<uint8_t, 2 * 1024> ram{};
};
