cmake_minimum_required(VERSION 3.10)
project(elma)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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
    # src/CodeGen/BytecodeGenerator.cpp
    # src/CodeGen/BytecodeGenerator.h
    src/CodeGen/Instruction.cpp
    src/CodeGen/Instruction.h
    src/CodeGen/Opcode.h
    # src/CodeGen/Runtime.cpp
    # src/CodeGen/Runtime.h
    src/CodeGen/Transpiler.cpp
    src/CodeGen/Transpiler.h
    src/Driver/Driver.cpp
    src/Driver/Driver.h
    src/Parser/Lexer.cpp
    src/Parser/Lexer.h
    src/Parser/Parser.cpp
    src/Parser/Parser.h
    src/Printer/ASTDumper.cpp
    src/Printer/ASTDumper.h
    src/Printer/ASTFormatter.cpp
    src/Printer/ASTFormatter.h
    src/Printer/PrettyPrinter.cpp
    src/Printer/PrettyPrinter.h
    # src/Sema/ASTEvaluator.cpp
    # src/Sema/ASTEvaluator.h
    src/Sema/Entity.cpp
    src/Sema/Entity.h
    src/Sema/IdentifierResolver.cpp
    src/Sema/IdentifierResolver.h
    src/Sema/InfiniteRecursion.cpp
    src/Sema/InfiniteRecursion.h
    # src/Sema/Optimizier.cpp
    # src/Sema/Optimizier.h
    src/Sema/Scope.cpp
    src/Sema/Scope.h
    src/Sema/SemaChecker.cpp
    src/Sema/SemaChecker.h
    src/Sema/TypeHelper.cpp
    src/Sema/TypeHelper.h
    src/Sema/TypeInferer.cpp
    src/Sema/TypeInferer.h
    src/Sema/TypeReprResolver.cpp
    src/Sema/TypeReprResolver.h
    src/Sema/TypeResolver.cpp
    src/Sema/TypeResolver.h
    src/Sema/Value.cpp
    src/Sema/Value.h
    thirdparty/duktape/duktape.c
)

target_include_directories(elma PRIVATE
    src
)

target_compile_options(elma PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
        -Weffc++
        -Wextra
        -Wnon-virtual-dtor
        -Wuninitialized
        -Wunreachable-code
        -Wshadow
        -Wno-unused-parameter
        -Wno-unused-variable
        $<$<CONFIG:DEBUG>:-g;-O0>
        $<$<CONFIG:RELEASE>:-O3>
    >
)

add_executable(elmac
    tools/driver/main.cpp
)

target_link_libraries(elmac elma)

target_include_directories(elmac PRIVATE
    src
)

target_compile_options(elmac PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
        -Weffc++
        -Wextra
        -Wnon-virtual-dtor
        -Wuninitialized
        -Wunreachable-code
        -Wshadow
        -Wno-unused-parameter
        -Wno-unused-variable
        $<$<CONFIG:DEBUG>:-g;-O0>
        $<$<CONFIG:RELEASE>:-O3>
    >
)

add_executable(unittest
    test/CommentTest.cpp
    test/ASTDumperTest.cpp
    test/IdentifierResolverTest.cpp
    test/LexerTest.cpp
    test/main.cpp
    test/ParserTest.cpp
    test/PrettyPrinterTest.cpp
    test/SemaCheckerTest.cpp
    test/TranspilerTest.cpp
    test/TypeResolverTest.cpp
)

target_link_libraries(unittest elma)

target_include_directories(unittest PRIVATE
    src
    thirdparty/catch2
    thirdparty
)

target_compile_options(unittest PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
        -Weffc++
        -Wextra
        -Wnon-virtual-dtor
        -Wuninitialized
        -Wunreachable-code
        -Wshadow
        -Wno-unused-parameter
        -Wno-unused-variable
        $<$<CONFIG:DEBUG>:-g;-O0>
        $<$<CONFIG:RELEASE>:-O3>
    >
)
