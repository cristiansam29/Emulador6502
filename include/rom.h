// Simple iNES ROM loader
#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct Rom {
    std::vector<uint8_t> prg;
    std::vector<uint8_t> chr;
    bool load(const std::string& path);
};
