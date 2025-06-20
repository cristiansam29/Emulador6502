#include "NESBus.h"
#include "c6502.h"

NESBus::NESBus() {
    cpu_ram.fill(0);
}

void NESBus::insertCartridge(Cartridge* cart) {
    cartridge = cart;
    ppu.connect(cart);
}

uint8_t NESBus::read(c6502* cpu, Addr addr, bool sync) {
    addr &= 0xFFFF;
    if(addr <= 0x1FFF) {
        return cpu_ram[addr & 0x07FF];
    } else if(addr >= 0x2000 && addr < 0x4000) {
        return ppu.cpuRead(0x2000 + (addr & 7));
    } else if(addr >= 0x4000 && addr < 0x4020) {
        return apu.cpuRead(addr);
    } else if(addr >= 0x8000) {
        if(cartridge)
            return cartridge->readPRG(addr - 0x8000);
    }
    return 0;
}

void NESBus::write(c6502* cpu, Addr addr, uint8_t data) {
    addr &= 0xFFFF;
    if(addr <= 0x1FFF) {
        cpu_ram[addr & 0x07FF] = data;
    } else if(addr >= 0x2000 && addr < 0x4000) {
        ppu.cpuWrite(0x2000 + (addr & 7), data);
    } else if(addr >= 0x4000 && addr < 0x4020) {
        apu.cpuWrite(addr, data);
    } else if(addr >= 0x8000) {
        if(cartridge)
            cartridge->writePRG(addr - 0x8000, data);
    }
}

