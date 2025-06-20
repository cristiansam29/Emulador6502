#pragma once

#include <cstdint>
#include <vector>

class Cartridge;

// Emulaci\u00f3n simplificada de la PPU Ricoh 2C02
class PPU {
public:
    PPU();

    void connect(Cartridge* cart);

    // Acceso de la CPU a los registros de la PPU
    uint8_t cpuRead(uint16_t addr);
    void cpuWrite(uint16_t addr, uint8_t data);

    // Avanza n ciclos de PPU
    void clock(int cycles);

    // Indica si hay un cuadro completo listo para dibujar
    bool frameReady() const { return frame_complete; }

    // Devuelve el framebuffer actual (256x240 pixeles en formato ARGB)
    const std::vector<uint32_t>& frameBuffer() const { return framebuffer; }

private:
    Cartridge* cart = nullptr;

    // Memoria interna de la PPU
    std::vector<uint8_t> tbl_name;   // 2KB de VRAM de nombres
    std::vector<uint8_t> tbl_palette; // 32 bytes de paleta

    std::vector<uint32_t> framebuffer;

    int scanline = 0;
    int cycle = 0;
    bool frame_complete = false;
};

