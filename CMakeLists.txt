cmake_minimum_required(VERSION 3.5)
project(NESemulator)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(nes
    main.cpp
    c6502.cpp
    Cartridge.cpp
    NESBus.cpp
    PPU.cpp
)

target_link_libraries(nes ${SDL2_LIBRARIES})

