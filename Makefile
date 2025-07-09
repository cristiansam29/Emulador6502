CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -O2

OBJS=c6502.o NesBus.o PPU.o main.o

all: nesemu

nesemu: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) nesemu

.PHONY: all clean
