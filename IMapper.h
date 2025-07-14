#pragma once
#include <cstdint>
#include <vector>

// Interface for NES cartridge mappers
class IMapper {
public:
    virtual ~IMapper() = default;
    virtual uint8_t readPRG(uint16_t addr) = 0;
    virtual void writePRG(uint16_t addr, uint8_t data) = 0;
    virtual uint8_t readCHR(uint16_t addr) = 0;
    virtual void writeCHR(uint16_t addr, uint8_t data) = 0;
};
