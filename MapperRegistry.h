#pragma once
#include "IMapper.h"
#include <map>
#include <functional>
#include <vector>

class MapperRegistry {
public:
    using Maker = std::function<IMapper*(const std::vector<uint8_t>&, const std::vector<uint8_t>&)>;
    static std::map<uint8_t, Maker>& registry() {
        static std::map<uint8_t, Maker> inst;
        return inst;
    }
    static void registerMapper(uint8_t id, Maker m) {
        registry()[id] = m;
    }
};

// Helper macros to register mappers
#define REGISTER_MAPPER(ID, TYPE) \
    namespace { struct Reg##TYPE { Reg##TYPE(){ MapperRegistry::registerMapper(ID, \
        [](const std::vector<uint8_t>& p,const std::vector<uint8_t>& c){ return new TYPE(p,c); }); }} reg##TYPE; }
