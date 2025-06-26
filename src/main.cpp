#include <SDL2/SDL.h>
#include "cpu.h"
#include "memory.h"
#include "rom.h"
#include "ppu.h"
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: nesemu <rom.nes>\n";
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0) {
        std::cerr << "SDL init failed: " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("NES", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          256, 240, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Rom rom;
    if (!rom.load(argv[1])) {
        std::cerr << "Failed to load ROM\n";
        return 1;
    }

    PPU ppu;
    Memory mem(ppu, rom);
    c6502 cpu(mem);

    cpu.setReset(true);
    cpu.runCpu(); // Note: infinite loop; for skeleton only

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
