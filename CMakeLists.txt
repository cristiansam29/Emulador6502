cmake_minimum_required(VERSION 3.10)
project(NesEmu CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
include_directories(include ${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES src/*.cpp)

add_executable(nesemu ${SOURCES})

target_link_libraries(nesemu SDL2::SDL2)
