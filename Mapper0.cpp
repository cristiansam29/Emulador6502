#include "MapperRegistry.h"
#include "IMapper.h"
#include <vector>

// Basic NROM mapper
class Mapper0 : public IMapper {
    std::vector<uint8_t> prg;
    std::vector<uint8_t> chr;
public:
    Mapper0(const std::vector<uint8_t>& p, const std::vector<uint8_t>& c)
        : prg(p), chr(c) {}

    uint8_t readPRG(uint16_t addr) override {
        addr &= (prg.size() - 1);
        return prg[addr];
    }
    void writePRG(uint16_t addr, uint8_t data) override {
        addr &= (prg.size() - 1);
        prg[addr] = data;
    }
    uint8_t readCHR(uint16_t addr) override {
        addr &= (chr.size() - 1);
        return chr[addr];
    }
    void writeCHR(uint16_t addr, uint8_t data) override {
        addr &= (chr.size() - 1);
        chr[addr] = data;
    }
};

// Factory function used by registration system
extern "C" IMapper* createMapper0(const std::vector<uint8_t>& prg,
                                   const std::vector<uint8_t>& chr) {
    return new Mapper0(prg, chr);
}
REGISTER_MAPPER(0, Mapper0);
