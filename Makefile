CXX=g++
CXXFLAGS=-std=c++17 -Wall -O2

OBJS=c6502.o NesBus.o main.o

all: nes_emulator

nes_emulator: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) nes_emulator

.PHONY: clean
