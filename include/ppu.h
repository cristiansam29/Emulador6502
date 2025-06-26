// Basic PPU placeholder class
#pragma once

#include <cstdint>
#include <SDL2/SDL.h>

class PPU {
public:
    PPU();
    ~PPU();

    void reset();
    void clock();
    void renderFrame(SDL_Renderer* renderer);

private:
    uint32_t framebuffer[256 * 240];
};
