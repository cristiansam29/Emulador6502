#pragma once

#include "NesBus.h"
#include <cstdint>

/**
 * Basic emulation of the Ricoh 2A03 CPU used in the NES.
 * This is a simplified 6502 derivative (without BCD mode).
 */
class NESCPU {
public:
    explicit NESCPU(NesBus& bus);

    uint8_t A() const { return A_; }
    uint8_t X() const { return X_; }
    uint8_t Y() const { return Y_; }
    uint8_t P() const { return P_; }
    uint8_t SP() const { return SP_; }
    uint16_t PC() const { return PC_; }

    // Reset CPU state and load the reset vector
    void reset();

    // Execute one instruction (roughly one CPU step)
    void step();

    // External interrupt lines
    void requestNMI();
    void requestIRQ();

private:
    NesBus& bus_;

    // CPU Registers
    uint8_t A_ = 0; // Accumulator
    uint8_t X_ = 0; // Index X
    uint8_t Y_ = 0; // Index Y
    uint8_t P_ = 0x34; // Processor status
    uint8_t SP_ = 0xFD; // Stack pointer
    uint16_t PC_ = 0xC000; // Program counter

    bool nmi_pending_ = false;
    bool irq_pending_ = false;

    // Status flags
    enum Flags : uint8_t {
        CARRY     = 1 << 0,
        ZERO      = 1 << 1,
        IRQB      = 1 << 2,
        DECIMAL   = 1 << 3,
        BREAK     = 1 << 4,
        UNUSED    = 1 << 5,
        OVERFLOW  = 1 << 6,
        NEGATIVE  = 1 << 7,
    };

    // Helper memory operations
    uint8_t read(uint16_t addr);
    void    write(uint16_t addr, uint8_t val);

    void push(uint8_t val);
    uint8_t pull();

    // Fetch helper
    uint8_t fetch();
    uint16_t fetch16();

    // Instruction implementations (only a small subset for now)
    void lda(uint16_t addr);
    void sta(uint16_t addr);
    void tax();
    void inx();

    void execute(uint8_t opcode);
};

