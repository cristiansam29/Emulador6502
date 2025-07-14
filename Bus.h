#pragma once

#include <cstdint>

using Addr = uint16_t;

class CPU6502;

class Bus {
public:
    virtual uint8_t read( CPU6502 *cpu, Addr address, bool sync = false ) = 0;
    virtual void write( CPU6502 *cpu, Addr address, uint8_t ) = 0;
};
