#include "CPU6502.h"
#include "NesBus.h"
#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char** argv) {
    if(argc < 2) {
        std::cout << "Usage: " << argv[0] << " rom.nes\n";
        return 1;
    }

    NesBus bus;
    if(!bus.loadROM(argv[1])) {
        std::cerr << "Failed to load ROM\n";
        return 1;
    }

    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        std::cerr << "SDL init failed\n";
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("NES", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 256, 240, 0);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 256, 240);

    CPU6502 cpu(bus);
    cpu.setReset(true);
    cpu.setReset(false);

    bool running = true;
    while(running) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) running = false;
        }

        cpu.handleInstruction();
        bus.clock();

        SDL_UpdateTexture(tex, nullptr, bus.getPPU()->frameBuffer(), 256*4);
        SDL_RenderCopy(ren, tex, nullptr, nullptr);
        SDL_RenderPresent(ren);
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
