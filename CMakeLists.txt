cmake_minimum_required(VERSION 3.15)
project(shelldown C)

set(CMAKE_C_STANDARD 99)

add_executable(shelldown src/main.c src/builtins.h src/builtins.c src/stdutils.c src/stdutils.h)