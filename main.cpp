#include "c6502.h"
#include "NesBus.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>

int main(int argc, char *argv[])
{
    if(argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <rom.nes>\n";
        return 1;
    }

    std::ifstream rom(argv[1], std::ios::binary);
    if(!rom) {
        std::cerr << "Could not open ROM file\n";
        return 1;
    }

    uint8_t header[16];
    rom.read(reinterpret_cast<char*>(header), 16);
    if(std::strncmp(reinterpret_cast<char*>(header), "NES\x1a", 4) != 0) {
        std::cerr << "Invalid iNES header\n";
        return 1;
    }

    size_t prgSize = header[4] * 16384;
    std::vector<uint8_t> prg(prgSize);
    rom.read(reinterpret_cast<char*>(prg.data()), prgSize);

    NesBus bus(prg);
    c6502 cpu(bus);

    cpu.setReset(true);
    cpu.setReset(false);

    for(int i = 0; i < 100000; ++i) {
        cpu.handleInstruction();
        if(cpu.isIncompatible())
            break;
    }

    return 0;
}
