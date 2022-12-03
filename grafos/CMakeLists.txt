cmake_minimum_required(VERSION 3.11)
project(Grafos)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")

set(target_sources main.cpp Aresta.cpp Grafo.cpp Vertice.cpp)
list(TRANSFORM target_sources PREPEND "src/")

include_directories(include)
add_executable(Grafos ${target_sources})