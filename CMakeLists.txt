cmake_minimum_required(VERSION 3.21)
project(projekt_z_jezyka_c_scrabble C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(projekt_z_jezyka_c_scrabble
        dzewa_na_tablicach.h
        operacje_drzewa.c
        projekt_na_pc.c)
