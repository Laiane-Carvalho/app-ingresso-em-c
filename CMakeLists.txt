cmake_minimum_required(VERSION 3.12)
project(app_ingresso C)

set(CMAKE_C_STANDARD 99)

add_executable(app_ingresso vars.c main.h main.c cliente.h cliente.c)