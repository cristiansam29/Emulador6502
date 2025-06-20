#pragma once

#include <cstdint>
#include <string>
#include <vector>

// Clase que representa un cartucho NES y se encarga de cargar la ROM
class Cartridge {
public:
    // Carga una ROM en formato iNES desde disco
    bool load(const std::string &path);

    // Lectura y escritura desde la memoria PRG
    uint8_t readPRG(uint16_t addr) const;
    void writePRG(uint16_t addr, uint8_t data);

    // Acceso a la memoria CHR utilizada por la PPU
    uint8_t readCHR(uint16_t addr) const;
    void writeCHR(uint16_t addr, uint8_t data);

    uint8_t mapper() const { return mapper_id; }
    bool mirroring() const { return mirroring_vertical; }

private:
    std::vector<uint8_t> prg_rom;
    std::vector<uint8_t> chr_mem;
    uint8_t mapper_id = 0;
    bool mirroring_vertical = false;
};

