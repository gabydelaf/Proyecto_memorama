cmake_minimum_required(VERSION 3.20)
project(proyecto_memorama C)

set(CMAKE_C_STANDARD 99)

add_executable(proyecto_memorama main.c memorama.c memorama.h)
