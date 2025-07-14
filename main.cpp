#include "NesBus.h"
#include <SDL3/SDL.h>
#include <cstdio>

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s romfile\n", argv[0]);
        return 0;
    }
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) return 1;
    SDL_Window* window = SDL_CreateWindow("NES Emulator",
        256, 240, SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 256, 240);

    NesBus nes;
    if (!nes.loadROM(argv[1])) {
        printf("Failed to load ROM\n");
        return 1;
    }

    bool running = true;
    while (running) {
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_EVENT_QUIT) running = false;
            nes.pad1.update(ev);
        }

        // simple CPU/PPU clocking
        nes.cpu.handleInstruction();
        for (int i = 0; i < 3; ++i) nes.ppu.clock();
        if (nes.ppu.pollNMI()) nes.cpu.setNmi(true);

        SDL_UpdateTexture(texture, nullptr, nes.ppu.getFrameBuffer(), 256 * sizeof(uint32_t));
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
