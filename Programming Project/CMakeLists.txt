cmake_minimum_required(VERSION 3.27)
project(Programming_Project C)

set(CMAKE_C_STANDARD 17)

add_executable(Programming_Project main.c
        functions.h
        functions.c
        File_handling.h
        File_handling.c
)
