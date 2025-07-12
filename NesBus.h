#pragma once
#include <cstdint>

using NesAddr = uint16_t;

/** Interface representing the memory bus of the NES. */
class NesBus {
public:
    virtual ~NesBus() = default;
    virtual uint8_t read(NesAddr addr) = 0;
    virtual void write(NesAddr addr, uint8_t val) = 0;
};
