#include "MapperRegistry.h"
#include "IMapper.h"
#include <vector>

class Mapper1 : public IMapper {
    std::vector<uint8_t> prg, chr;
public:
    Mapper1(const std::vector<uint8_t>& p,const std::vector<uint8_t>& c):prg(p),chr(c){}
    uint8_t readPRG(uint16_t a) override { return prg[a%prg.size()]; }
    void writePRG(uint16_t, uint8_t) override {}
    uint8_t readCHR(uint16_t a) override { return chr[a%chr.size()]; }
    void writeCHR(uint16_t, uint8_t) override {}
};
REGISTER_MAPPER(1, Mapper1);
