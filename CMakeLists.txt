cmake_minimum_required(VERSION 3.10)
project(elma)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
    src
    thirdparty/catch2
)

add_library(elma STATIC
    src/Driver/Driver.cpp
    src/Driver/Driver.h
)

add_executable(unittest
    test/main.cpp
)

target_link_libraries(unittest elma)