cmake_minimum_required(VERSION 3.10)
project(elma)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if ((CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR (CMAKE_CXX_COMPILER_ID MATCHES "GNU"))
    add_compile_options(
        -Weffc++
        -Wextra
        -Wnon-virtual-dtor
        -Wuninitialized
        -Wunreachable-code
        -Wshadow

        -Wno-unused-parameter
        -Wno-unused-variable
    )
endif()

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
    src/AST/ASTContext.cpp
    src/AST/ASTContext.h
    src/AST/ASTVisitor.cpp
    src/AST/ASTVisitor.h
    src/AST/Comment.cpp
    src/AST/Comment.h
    src/AST/Decl.cpp
    src/AST/Decl.h
    src/AST/Expr.cpp
    src/AST/Expr.h
    src/AST/Identifier.cpp
    src/AST/Identifier.h
    src/AST/Node.h
    src/AST/Stmt.cpp
    src/AST/Stmt.h
    src/AST/Type.cpp
    src/AST/Type.h
    src/AST/TypeRepr.cpp
    src/AST/TypeRepr.h
    src/Basic/Diagnostic.cpp
    src/Basic/Diagnostic.h
    src/Basic/Forward.h
    src/Basic/Location.cpp
    src/Basic/Location.h
    src/Basic/StringHelper.cpp
    src/Basic/StringHelper.h
    src/Driver/Driver.cpp
    src/Driver/Driver.h
    src/Parser/Lexer.cpp
    src/Parser/Lexer.h
    src/Parser/Parser.cpp
    src/Parser/Parser.h
    src/Sema/Entity.cpp
    src/Sema/Entity.h
    thirdparty/duktape/duktape.c
)

add_executable(unittest
    test/CommentTest.cpp
    test/LexerTest.cpp
    test/main.cpp
    test/ParserTest.cpp
)

target_link_libraries(unittest elma)
