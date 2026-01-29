cmake_minimum_required(VERSION 4.1)
project(stego C)

set(CMAKE_C_STANDARD 11)

add_executable(stego
        main.c
        stego.c
        stego.h)
