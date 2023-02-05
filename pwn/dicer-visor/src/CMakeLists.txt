cmake_minimum_required(VERSION 3.16)
project(dicer-visor C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER clang)

add_executable(dicer-visor src/main.c src/kernelVM.c)
