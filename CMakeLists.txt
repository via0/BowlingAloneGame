cmake_minimum_required(VERSION 3.10)
project(bowling C)

# set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# find SDL2
find_package(SDL2 REQUIRED)

# include directories
include_directories(${SDL2_INCLUDE_DIRS})

# add executable
add_executable(bowling
  src/main.c
  src/game.c
  src/renderer.c
)

# Link SDL2
target_link_libraries(bowling ${SDL2_LIBRARIES})
