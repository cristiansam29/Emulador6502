#include "NESCPU.h"

#include <cstring>

NESCPU::NESCPU(NesBus& bus) : bus_(bus) {}

void NESCPU::reset() {
    // Fetch reset vector at 0xFFFC
    uint8_t lo = read(0xFFFC);
    uint8_t hi = read(0xFFFD);
    PC_ = uint16_t(hi) << 8 | lo;
    SP_ -= 3; // stack reset
    P_ |= UNUSED;
    nmi_pending_ = irq_pending_ = false;
}

void NESCPU::requestNMI() { nmi_pending_ = true; }
void NESCPU::requestIRQ() { irq_pending_ = true; }

uint8_t NESCPU::read(uint16_t addr) { return bus_.read(addr); }
void NESCPU::write(uint16_t addr, uint8_t val) { bus_.write(addr, val); }

void NESCPU::push(uint8_t val) { write(0x0100 | SP_--, val); }
uint8_t NESCPU::pull() { return read(0x0100 | ++SP_); }

uint8_t NESCPU::fetch() { return read(PC_++); }
uint16_t NESCPU::fetch16() { uint8_t lo = fetch(); return uint16_t(fetch())<<8 | lo; }

void NESCPU::lda(uint16_t addr) {
    A_ = read(addr);
    P_ = (P_ & ~(NEGATIVE|ZERO)) | (A_ ? 0:ZERO) | (A_ & 0x80);
}

void NESCPU::sta(uint16_t addr) { write(addr, A_); }

void NESCPU::tax() {
    X_ = A_;
    P_ = (P_ & ~(NEGATIVE|ZERO)) | (X_ ? 0:ZERO) | (X_ & 0x80);
}

void NESCPU::inx() {
    ++X_;
    P_ = (P_ & ~(NEGATIVE|ZERO)) | (X_ ? 0:ZERO) | (X_ & 0x80);
}

void NESCPU::execute(uint8_t op) {
    switch(op) {
    case 0xA9: { // LDA immediate
        uint16_t addr = PC_++;
        lda(addr);
        break; }
    case 0xA5: { // LDA zeropage
        uint16_t addr = read(PC_++);
        lda(addr);
        break; }
    case 0x8D: { // STA abs
        uint16_t addr = fetch16();
        sta(addr);
        break; }
    case 0xAA: // TAX
        tax();
        break;
    case 0xE8: // INX
        inx();
        break;
    default:
        // Unimplemented opcode - treat as NOP
        break;
    }
}

void NESCPU::step() {
    if (nmi_pending_) {
        nmi_pending_ = false;
        push(PC_ >> 8);
        push(PC_ & 0xFF);
        push(P_ & ~BREAK);
        P_ |= IRQB;
        uint16_t lo = read(0xFFFA);
        uint16_t hi = read(0xFFFB);
        PC_ = uint16_t(hi) << 8 | lo;
        return;
    }
    if (irq_pending_ && !(P_ & IRQB)) {
        irq_pending_ = false;
        push(PC_ >> 8);
        push(PC_ & 0xFF);
        push(P_ & ~BREAK);
        P_ |= IRQB;
        uint16_t lo = read(0xFFFE);
        uint16_t hi = read(0xFFFF);
        PC_ = uint16_t(hi) << 8 | lo;
        return;
    }

    uint8_t opcode = fetch();
    execute(opcode);
}

