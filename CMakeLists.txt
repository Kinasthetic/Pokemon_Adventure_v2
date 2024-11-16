cmake_minimum_required(VERSION 3.29)
project(Pokemon_Adventure)

set(CMAKE_CXX_STANDARD 20)

add_executable(Pokemon_Adventure main.cpp
        globals.h
        globals.cpp
        BasePokemon.h
        KantoPokemon.h
        KantoPokemon.cpp
        Market.h
        Market.cpp
        Player.h
        Player.cpp)
