#include "rom.h"
#include <fstream>

bool Rom::load(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) return false;
    uint8_t header[16];
    file.read((char*)header, 16);
    if (header[0] != 'N' || header[1] != 'E' || header[2] != 'S')
        return false;
    size_t prg_size = header[4] * 16384;
    size_t chr_size = header[5] * 8192;
    prg.resize(prg_size);
    chr.resize(chr_size);
    file.read((char*)prg.data(), prg_size);
    file.read((char*)chr.data(), chr_size);
    return true;
}
