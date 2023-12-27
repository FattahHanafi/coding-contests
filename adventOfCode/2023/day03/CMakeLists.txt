cmake_minimum_required(VERSION 3.0)
project(advent_of_code_2023)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(input.txt input.txt COPYONLY)

add_executable(solution solution.cpp)
