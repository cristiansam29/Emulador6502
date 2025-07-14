#pragma once
#include <cstdint>
#include <SDL3/SDL.h>

class Controller {
    uint8_t state = 0;
    uint8_t latched = 0;
public:
    void update(const SDL_Event& ev);
    uint8_t read();
    void write(uint8_t data);
};
