cmake_minimum_required(VERSION 3.10)
project(elma)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
    src
    thirdparty/catch2
    thirdparty
)

add_library(elma STATIC
    src/Basic/Forward.h
    src/Basic/Location.cpp
    src/Basic/Location.h
    src/Driver/Driver.cpp
    src/Driver/Driver.h
    thirdparty/duktape/duktape.c
)

add_executable(unittest
    test/main.cpp
)

target_link_libraries(unittest elma)
