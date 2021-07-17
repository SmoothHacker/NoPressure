cmake_minimum_required(VERSION 3.16)
project(NoPressure C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lcapstone")

add_executable(NoPressure src/main.c src/debugger.c src/debugger.h)