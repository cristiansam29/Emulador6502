CXX=g++
CXXFLAGS=-std=c++17 $(shell sdl3-config --cflags)
LDFLAGS=$(shell sdl3-config --libs)
OBJS=main.o CPU6502.o NesBus.o PPU.o APU.o Controller.o Mapper0.o Mapper1.o Mapper2.o Mapper3.o Mapper4.o

all: nes_emulator

nes_emulator: $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) nes_emulator
