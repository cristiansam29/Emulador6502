#pragma once

#include <cstdint>

// Implementaci\u00f3n b\u00e1sica del APU. Solo se define la interfaz.
class APU {
public:
    void cpuWrite(uint16_t addr, uint8_t data) {}
    uint8_t cpuRead(uint16_t addr) { return 0; }

    void clock(int cycles) {}
};

