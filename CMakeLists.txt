cmake_minimum_required(VERSION 3.26)
project(pa1 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_C_FLAGS "-std=c99 -Wall -Werror -pedantic")
add_executable(pa1 main.c
        ipc.c
        logging.h
        logging.c
        process.h
        util.c
        util.h
)
