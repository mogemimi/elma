#include "Sema/IdentifierResolver.h"
#include "AST/ASTContext.h"
#include "AST/Decl.h"
#include "Basic/Diagnostic.h"
#include "Driver/Driver.h"
#include "Sema/Entity.h"

#include "catch.hpp"

using namespace elma;

namespace {
bool resolveIdentifiers(const std::shared_ptr<DiagnosticHandler>& diag, const std::string& source)
{
    elma::Driver driver;
    auto [ast, ok] = driver.parseString(source, diag);
    REQUIRE(ok);

    IdentifierContext context;
    IdentifierResolver resolver(&ast, &context, diag);
    AST::walk(&resolver, ast.translationUnit);

    return !diag->hasError();
}
} // end of anonymous namespace

TEST_CASE("IdentifierResolver can resolve identifier", "[identifier-resolve]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("redeclared in this block.")
    {
        constexpr auto source = R"(func f() {
            let x;
            let x;
        })";
        REQUIRE(!resolveIdentifiers(diag, source));
        REQUIRE(stream->hasError("error: 'x' redeclared in this block."));
    }
    SECTION("resolver emits an undefined identifier when using unknown symbols")
    {
        constexpr auto source = R"(func f() {
            x = 42;
        })";
        REQUIRE(!resolveIdentifiers(diag, source));
        REQUIRE(stream->hasError("error: 'x' was not declared in this scope."));
    }
    SECTION("resolver emits an undefined identifier when using unknown symbols")
    {
        constexpr auto source = R"(func f() {
            x = 42;
            let x;
        })";
        REQUIRE(!resolveIdentifiers(diag, source));
        REQUIRE(stream->hasError("error: 'x' was not declared in this scope."));
    }
    SECTION("resolver prevents misuse of the variable before its declaration")
    {
        constexpr auto source = R"(func f() {
            let x = x;
        })";
        REQUIRE(!resolveIdentifiers(diag, source));
        REQUIRE(stream->hasError("error: 'x' was not declared in this scope."));
    }
    SECTION("resolving function parameter name")
    {
        constexpr auto source = R"(func f(x) {
            x = 42;
        })";
        REQUIRE(resolveIdentifiers(diag, source));
    }
    SECTION("resolver emits an error when using unknown types")
    {
        constexpr auto source = R"(func f(x: Foo) {})";
        REQUIRE(!resolveIdentifiers(diag, source));
        REQUIRE(stream->hasError("error: Cannot find name 'Foo'."));
    }
    SECTION("resolving type name with function parameters")
    {
        constexpr auto source = R"(func f(x: Int) {})";
        REQUIRE(resolveIdentifiers(diag, source));
    }
    SECTION("resolving map type with function parameters")
    {
        constexpr auto source = R"(func f(x: Map<String, Int>) {})";
        REQUIRE(resolveIdentifiers(diag, source));
    }
    SECTION("resolving array type with function parameters")
    {
        constexpr auto source = R"(func f(x: Array<Int>) {})";
        REQUIRE(resolveIdentifiers(diag, source));
    }
    SECTION("resolver emits an error when using non-generic type as a generic type")
    {
        constexpr auto source = R"(func f(x: Int<String>) {})";
        REQUIRE(!resolveIdentifiers(diag, source));
        REQUIRE(stream->hasError("error: Type 'Int' is not generic."));
    }
    SECTION("resolver emits an undefined identifier when calling unknown function")
    {
        constexpr auto source = R"(
        func f() { g(); }
        )";
        REQUIRE(!resolveIdentifiers(diag, source));
        REQUIRE(stream->hasError("error: 'g' was not declared in this scope."));
    }
    SECTION("resolving function name")
    {
        constexpr auto source = R"(
        func g() { }
        func f() { g(); }
        )";
        REQUIRE(resolveIdentifiers(diag, source));
    }
    SECTION("resolving type representations inside function body")
    {
        constexpr auto source = R"(func test() {
            let a : Int;
            let b : Double;
            let c : Bool;
            let d : String;
            let e : Any;
            let f : Array<Int>;
            let g : Map<String, Double>;
            let h : String?;
        })";
        REQUIRE(resolveIdentifiers(diag, source));
    }
    SECTION("resolving type representations inside function signature")
    {
        constexpr auto source = R"(func f(a : Int, b : String?) -> Void {})";
        REQUIRE(resolveIdentifiers(diag, source));
    }
    SECTION("resolving type representations inside class body")
    {
        constexpr auto source = R"(class Foo {
            let a : Int;
            let b : Double;
            let c : Bool;
            let d : String;
            let e : Any;
            let f : Array<Int>;
            let g : Map<String, Double>;
            let h : String?;
        })";
        REQUIRE(resolveIdentifiers(diag, source));
    }
    SECTION("resolving type representation using user-defined class")
    {
        constexpr auto source = R"(
        class Foo {}
        func f(x : Foo) -> Foo {
            let a : Foo;
            return x;
        }
        )";
        REQUIRE(resolveIdentifiers(diag, source));
    }
    SECTION("resolver emits an error when declaring duplicate function")
    {
        constexpr auto source = R"(
        func Foo() {}
        func Foo() {}
        )";
        REQUIRE(!resolveIdentifiers(diag, source));
        REQUIRE(stream->hasError("error: 'Foo' redeclared in this block."));
    }
    SECTION("resolver emits an error when declaring function using duplicate identifier")
    {
        constexpr auto source = R"(
        class Foo {}
        func Foo() {}
        )";
        REQUIRE(!resolveIdentifiers(diag, source));
        REQUIRE(stream->hasError("error: 'Foo' redeclared in this block."));
    }
    SECTION("resolver emits an error when declaring class using duplicate identifier")
    {
        constexpr auto source = R"(
        func Foo() {}
        class Foo {}
        )";
        REQUIRE(!resolveIdentifiers(diag, source));
        REQUIRE(stream->hasError("error: 'Foo' redeclared in this block."));
    }
    SECTION("resolver emits an error when declaring duplicate classes")
    {
        constexpr auto source = R"(
        class Foo {}
        class Foo {}
        )";
        REQUIRE(!resolveIdentifiers(diag, source));
        REQUIRE(stream->hasError("error: 'Foo' redeclared in this block."));
    }
    SECTION("resolver ignores duplicate identifier inside function parameters")
    {
        constexpr auto source = R"(
        class Foo {}
        func f(Foo : Int) {}
        )";
        REQUIRE(resolveIdentifiers(diag, source));
    }
    SECTION("resolver emits an error when declaring duplicate parameters")
    {
        constexpr auto source = R"(func f(x, x) {})";
        REQUIRE(!resolveIdentifiers(diag, source));
        REQUIRE(stream->hasError("error: 'x' redeclared in this block."));
    }
}
