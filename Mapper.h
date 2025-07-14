#pragma once
#include <cstdint>
#include <vector>

class IMapper {
public:
    virtual ~IMapper() = default;
    virtual uint8_t readPrg(uint16_t addr) = 0;
    virtual void writePrg(uint16_t addr, uint8_t data) = 0;
    virtual uint8_t readChr(uint16_t addr) = 0;
    virtual void writeChr(uint16_t addr, uint8_t data) = 0;
};

class Mapper0 : public IMapper {
public:
    Mapper0(const std::vector<uint8_t>&prg, const std::vector<uint8_t>&chr);
    uint8_t readPrg(uint16_t addr) override;
    void writePrg(uint16_t addr, uint8_t data) override;
    uint8_t readChr(uint16_t addr) override;
    void writeChr(uint16_t addr, uint8_t data) override;
private:
    std::vector<uint8_t> prgRom;
    std::vector<uint8_t> chrRom;
};

class MapperFactory {
public:
    static IMapper* create(uint8_t id, const std::vector<uint8_t>&prg, const std::vector<uint8_t>&chr);
};
