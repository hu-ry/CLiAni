cmake_minimum_required(VERSION 3.15) # cmake 3.15 (don't change)
project(cliAnimation)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS "-O3 -Wall -pthread -fcheck-new -g ")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ")

link_libraries(-lncurses -lmenu -lpanel)

include_directories(include)

add_executable(clani
        src/main.cpp src/cliview.cpp src/widdershins.cpp
        src/model/greasemonkey.cpp src/model/flavour/flavour.cpp
        src/model/flavour/perlinnoise.cpp src/model/flavour/voronoi.cpp
        src/model/flavour/cellular.cpp src/model/noiseattribute.cpp src/decidecation.cpp)
