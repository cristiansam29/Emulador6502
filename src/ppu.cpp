#include "ppu.h"

PPU::PPU() { reset(); }
PPU::~PPU() {}

void PPU::reset() {
    for (auto &p : framebuffer) p = 0x000000FF; // black
}

void PPU::clock() {
    // Placeholder for PPU cycles
}

void PPU::renderFrame(SDL_Renderer* renderer) {
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                             SDL_TEXTUREACCESS_STREAMING, 256, 240);
    SDL_UpdateTexture(texture, nullptr, framebuffer, 256 * sizeof(uint32_t));
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_DestroyTexture(texture);
}
