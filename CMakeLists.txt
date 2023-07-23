cmake_minimum_required(VERSION 3.16)

project(aoc-2022)

set(CMAKE_CXX_STANDARD 20)

file(GLOB AOC_2022_SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${AOC_2022_SOURCES})
