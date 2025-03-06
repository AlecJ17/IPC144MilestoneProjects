cmake_minimum_required(VERSION 3.26)
project(MS3 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(MS3
        a1ms3.c
        clinic.c
        clinic.h
        core.c
        core.h)
