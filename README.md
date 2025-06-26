# NES Emulator Skeleton

This project provides an initial modular structure for a NES emulator in C++17.
It uses SDL2 for graphics and input. The current implementation is a starting
point which loads a ROM and sets up the CPU, memory and a basic PPU.

## Building

```
mkdir build
cd build
cmake ..
make
```

Run the emulator with a NES ROM:

```
./nesemu path/to/rom.nes
```

## Project Structure

- `include/` – public headers (CPU, PPU, memory, ROM loader).
- `src/` – implementations and main program.

The CPU class implements a 6502 compatible core. Memory mapping and the PPU are
kept simple to focus on a working base.
