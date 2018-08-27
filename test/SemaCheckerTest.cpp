#include "Sema/SemaChecker.h"
#include "AST/ASTContext.h"
#include "AST/Decl.h"
#include "Basic/Diagnostic.h"
#include "Driver/Driver.h"
#include "Sema/Entity.h"
#include "Sema/IdentifierResolver.h"

#include "catch.hpp"

using namespace elma;

namespace {
bool semaCheck(const std::shared_ptr<DiagnosticHandler>& diag, const std::string& source)
{
    elma::Driver driver;
    auto [ast, ok] = driver.parseString(source, diag);
    REQUIRE(ok);

    IdentifierContext context;
    IdentifierResolver resolver(&ast, &context, diag);
    AST::walk(&resolver, ast.translationUnit);

    REQUIRE(!diag->hasError());

    SemaChecker semaChecker(diag);
    AST::walk(&semaChecker, ast.translationUnit);

    return !diag->hasError();
}
} // end of anonymous namespace

TEST_CASE("const can be defined as constant data types", "[semacheck]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("const can be defined as constant data types")
    {
        constexpr auto source = R"(func f() { const a = 42; })";
        REQUIRE(semaCheck(diag, source));
    }
    SECTION("const cannot be reassigned.")
    {
        constexpr auto source = R"(func f() {
            const a = 42;
            a = 100;
        })";
        REQUIRE(!semaCheck(diag, source));
        REQUIRE(stream->hasError("error: 'a' cannot be reassigned because it is a constant."));
    }
    SECTION("typename cannot be assigned.")
    {
        constexpr auto source = R"(func f() { Int = 42; })";
        REQUIRE(!semaCheck(diag, source));
        REQUIRE(
            stream->hasError("error: 'Int' cannot be assigned because it only refers to a type."));
    }
}

TEST_CASE("lvalue and rvalue", "[semacheck]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("The left-hand side of an assignment must be a variable.")
    {
        constexpr auto source = R"(func test() { 4 = 2; })";
        REQUIRE(!semaCheck(diag, source));
        REQUIRE(stream->hasError("error: The left-hand side of an assignment must be a variable."));
    }
    SECTION("The left-hand side of an assignment must be a variable.")
    {
        constexpr auto source = R"(func test() { "a" = "a"; })";
        REQUIRE(!semaCheck(diag, source));
        REQUIRE(stream->hasError("error: The left-hand side of an assignment must be a variable."));
    }
    SECTION("The LHS is correctly a variable.")
    {
        constexpr auto source = R"(func test() { let a = "a"; })";
        REQUIRE(semaCheck(diag, source));
    }
    SECTION("The left-hand side of an assignment must be a variable.")
    {
        constexpr auto source = R"(func test() {
            let a;
            let b;
            a = b = 2;
        })";
        REQUIRE(semaCheck(diag, source));
    }
    SECTION("The left-hand side of an assignment must be a variable.")
    {
        constexpr auto source = R"(func test() {
            let a;
            (a) = 2;
        })";
        REQUIRE(semaCheck(diag, source));
    }
    SECTION("The left-hand side of an assignment must be a variable.")
    {
        constexpr auto source = R"(func test() {
            let a;
            let b;
            a = (b = 2);
        })";
        REQUIRE(semaCheck(diag, source));
    }
    SECTION("The left-hand side of an assignment must be a variable.")
    {
        constexpr auto source = R"(func test() {
            let a;
            let b;
            (a = b) = 2;
        })";
        REQUIRE(!semaCheck(diag, source));
        REQUIRE(stream->hasError("error: The left-hand side of an assignment must be a variable."));
    }
    SECTION("The left-hand side of an assignment must be a variable.")
    {
        constexpr auto source = R"(func test() {
            let a = 42;
            (a = 0) = 2;
        })";
        REQUIRE(!semaCheck(diag, source));
        REQUIRE(stream->hasError("error: The left-hand side of an assignment must be a variable."));
    }
    SECTION("Function call is rvalue.")
    {
        constexpr auto source = R"(func f() { f() = 2; })";
        REQUIRE(!semaCheck(diag, source));
        REQUIRE(stream->hasError("error: The left-hand side of an assignment must be a variable."));
    }
    SECTION("Array literals are rvalue.")
    {
        constexpr auto source = R"(func f() { [] = 42; })";
        REQUIRE(!semaCheck(diag, source));
        REQUIRE(stream->hasError("error: The left-hand side of an assignment must be a variable."));
    }
    SECTION("Map literals are rvalue.")
    {
        constexpr auto source = R"(func f() { [:] = 42; })";
        REQUIRE(!semaCheck(diag, source));
        REQUIRE(stream->hasError("error: The left-hand side of an assignment must be a variable."));
    }
}

TEST_CASE("recursive referencing", "[semacheck]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("SemaChecker emits an invalid recursive type error.")
    {
        constexpr auto source = R"(
        class Foo { var foo : Foo; }
        )";
        REQUIRE(!semaCheck(diag, source));
        REQUIRE(
            stream->hasError("error: invalid recursive type 'Foo'\n  2:15 'Foo'\n  2:31 'Foo'"));
    }
    SECTION("Recursive type with optional can be using for member inside class declaration.")
    {
        constexpr auto source = R"(
        class Foo { var foo : Foo?; }
        )";
        REQUIRE(semaCheck(diag, source));
    }
    SECTION("Recursive type with Array can be using for member inside class declaration.")
    {
        constexpr auto source = R"(
        class Foo { var foo : Array<Foo>; }
        )";
        REQUIRE(semaCheck(diag, source));
    }
    SECTION("Recursive type with Map can be using for member inside class declaration.")
    {
        constexpr auto source = R"(
        class Foo { var foo : Map<Foo, Foo>; }
        )";
        REQUIRE(semaCheck(diag, source));
    }
    SECTION("SemaChecker emits invalid recursive type errors.")
    {
        constexpr auto source = R"(
        class Foo { var bar : Bar; }
        class Bar { var foo : Foo; }
        )";
        REQUIRE(!semaCheck(diag, source));
        REQUIRE(
            stream->hasError("error: invalid recursive type 'Foo'\n  2:15 'Foo'\n  3:31 'Foo'"));
        REQUIRE(
            stream->hasError("error: invalid recursive type 'Bar'\n  3:15 'Bar'\n  2:31 'Bar'"));
    }
    SECTION("SemaChecker checks nested invalid recursive types.")
    {
        constexpr auto source = R"(
        class Foo { var bar : Bar; }
        class Bar { var baz : Baz; }
        class Baz { var foo : Foo; }
        )";
        REQUIRE(!semaCheck(diag, source));
        REQUIRE(
            stream->hasError("error: invalid recursive type 'Foo'\n  2:15 'Foo'\n  4:31 'Foo'"));
        REQUIRE(
            stream->hasError("error: invalid recursive type 'Bar'\n  3:15 'Bar'\n  2:31 'Bar'"));
        REQUIRE(
            stream->hasError("error: invalid recursive type 'Baz'\n  4:15 'Baz'\n  3:31 'Baz'"));
    }
    SECTION("top-level constant used before its declaration in expression")
    {
        constexpr auto source = R"(
        const a = b;
        const b = 42;
        )";
        REQUIRE(semaCheck(diag, source));
    }
    SECTION("initialization loop")
    {
        constexpr auto source = R"(
        const a = b;
        const b = a;
        )";
        REQUIRE(!semaCheck(diag, source));
        REQUIRE(stream->hasError("error: initialization loop\n  2:15 'a'\n  3:19 'a'"));
        REQUIRE(stream->hasError("error: initialization loop\n  3:15 'b'\n  2:19 'b'"));
    }
    SECTION("nested initialization loop")
    {
        constexpr auto source = R"(
        const a = b;
        const b = c;
        const c = a;
        )";
        REQUIRE(!semaCheck(diag, source));
        REQUIRE(stream->hasError("error: initialization loop\n  2:15 'a'\n  4:19 'a'"));
        REQUIRE(stream->hasError("error: initialization loop\n  3:15 'b'\n  2:19 'b'"));
        REQUIRE(stream->hasError("error: initialization loop\n  4:15 'c'\n  3:19 'c'"));
    }
    SECTION("initialization loop with closure")
    {
        constexpr auto source = R"(
        var a = (func () { return a; })();
        )";
        REQUIRE(!semaCheck(diag, source));
        REQUIRE(stream->hasError("error: initialization loop\n  2:13 'a'\n  2:35 'a'"));
    }
    SECTION("top-level constant used before its declaration in expression")
    {
        constexpr auto source = R"(
        func f() { return a; }
        const a = 42;
        )";
        REQUIRE(semaCheck(diag, source));
    }
    SECTION("initialization loop with function")
    {
        constexpr auto source = R"(
        func f() { return a; }
        var a = f();
        )";
        REQUIRE(!semaCheck(diag, source));
        REQUIRE(stream->hasError("error: initialization loop\n  3:13 'a'\n  2:27 'a'"));
    }
    SECTION("nested initialization loop with function")
    {
        constexpr auto source = R"(
        func g() { return a; }
        func f() { return g(); }
        var a = f();
        )";
        REQUIRE(!semaCheck(diag, source));
        REQUIRE(stream->hasError("error: initialization loop\n  4:13 'a'\n  2:27 'a'"));
    }
    SECTION("avoiding infinite loop when checking initializer")
    {
        constexpr auto source = R"(
        func f() { return f(); }
        var a = f();
        )";
        REQUIRE(semaCheck(diag, source));
    }
}
