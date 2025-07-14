#include "Controller.h"

void Controller::update(const SDL_Event& ev) {
    if (ev.type == SDL_EVENT_KEY_DOWN || ev.type == SDL_EVENT_KEY_UP) {
        bool pressed = ev.type == SDL_EVENT_KEY_DOWN;
        switch(ev.key.keysym.sym) {
            case SDLK_a: state = pressed ? (state|0x01) : (state&~0x01); break; // A
            case SDLK_s: state = pressed ? (state|0x02) : (state&~0x02); break; // B
            case SDLK_SPACE: state = pressed ? (state|0x04) : (state&~0x04); break; // Select
            case SDLK_RETURN: state = pressed ? (state|0x08) : (state&~0x08); break; // Start
            case SDLK_UP: state = pressed ? (state|0x10) : (state&~0x10); break;
            case SDLK_DOWN: state = pressed ? (state|0x20) : (state&~0x20); break;
            case SDLK_LEFT: state = pressed ? (state|0x40) : (state&~0x40); break;
            case SDLK_RIGHT: state = pressed ? (state|0x80) : (state&~0x80); break;
        }
    }
}

uint8_t Controller::read() {
    uint8_t val = (latched & 0x80) ? 1 : 0;
    latched <<= 1;
    return val;
}

void Controller::write(uint8_t data) {
    if (data & 1) {
        latched = state;
    }
}
