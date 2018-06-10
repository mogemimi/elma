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

source_group(AST REGULAR_EXPRESSION src/AST/*)
source_group(Basic REGULAR_EXPRESSION src/Basic/*)
source_group(CodeGen REGULAR_EXPRESSION src/CodeGen/*)
source_group(Driver REGULAR_EXPRESSION src/Driver/*)
source_group(Parser REGULAR_EXPRESSION src/Parser/*)
source_group(Printer REGULAR_EXPRESSION src/Printer/*)
source_group(Sema REGULAR_EXPRESSION src/Sema/*)
source_group(thirdparty\\duktape REGULAR_EXPRESSION thirdparty/duktape/*)

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
