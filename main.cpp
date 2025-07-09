#include "c6502.h"
#include "NesBus.h"
#include "PPU.h"
#include "APU.h"
#include "Controller.h"
#include <iostream>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <rom.nes>\n";
        return 1;
    }

    PPU ppu;
    APU apu;
    Controller ctrl;
    NesBus bus;
    bus.ppu = &ppu;
    bus.apu = &apu;
    bus.ctrl = &ctrl;

    if(!bus.loadROM(argv[1])) {
        std::cerr << "Failed to load ROM\n";
        return 1;
    }

    c6502 cpu(bus);
    cpu.resetSequence();

    // run for a limited number of cycles as example
    for(int i=0;i<1000;i++) {
        cpu.handleInstruction();
    }

    std::cout << "Finished." << std::endl;
    return 0;
}
