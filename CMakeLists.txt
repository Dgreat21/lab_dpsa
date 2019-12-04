cmake_minimum_required(VERSION 3.15)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        ./includes)

link_directories(./includes)

add_executable(untitled "lab1 list/main.cpp" "lab1 list/list.h" "lab3 recursive/main.cpp")