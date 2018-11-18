cmake_minimum_required(VERSION 3.12)
project(untitled C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled config.c client.c main.h main.c)