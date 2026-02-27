cmake_minimum_required(VERSION 3.20)
project(ZorkClone)

set(CMAKE_CXX_STANDARD 20)

add_executable(ZorkClone main.cpp
        types.hpp
        parser.hpp
        parser.cpp
        commands.cpp
        commands.hpp
        world.cpp
        world.hpp
        log.cpp
        log.hpp
        colors.hpp)
