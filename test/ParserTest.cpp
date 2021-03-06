#include "AST/ASTContext.h"
#include "Basic/Diagnostic.h"
#include "Driver/Driver.h"

#include "catch.hpp"

using namespace elma;

namespace {
bool parse(const std::shared_ptr<DiagnosticHandler>& diag, const std::string& source)
{
    Driver driver;
    auto [ast, ok] = driver.parseString(source, diag);
    return ok && !diag->hasError();
}
} // end of anonymous namespace

TEST_CASE("parser can treat basic sources consistently", "[parser]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("parser can deal with an empty source")
    {
        constexpr auto source = " \t";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat null literal")
    {
        constexpr auto source = "func f() { return null; }\n";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat null-coalescing operators")
    {
        constexpr auto source = "func f(a) { return a ?? 42; }\n";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat optional evaluation operators")
    {
        constexpr auto source = "func f(a) { return a?.b; }\n";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat optional chaining operators")
    {
        constexpr auto source = "func f(a) { return a?[42].b?().c?.d?(42); }\n";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser does not allow using optional chaining without members")
    {
        constexpr auto source = "func f(a) { return a?; }\n";
        REQUIRE(!parse(diag, source));
    }
    SECTION("parser can treat conditional operators")
    {
        constexpr auto source = "func f(a, b, c) { return a ? b : c; }\n";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat subscript expression")
    {
        constexpr auto source = R"(
        func g(x) { return x; }
        func f() {
            let a = [40, 41, 42];
            a[0] = a[1];
            a[1] = a[0] + a[2];
            a[g(3)] = g(a[0]);
            a = [4, 3, 2, 1];
        })";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat type specifier")
    {
        constexpr auto source = R"(func f() {
            let a: Int = 42;
            let b: String = "hello";
            const c: Double = 3.141592;
        })";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat generic type specifier")
    {
        constexpr auto source = R"(func f() {
            let a: Int? = 42;
            let b: Array<Int> = [];
            let c: Map<String, Int> = [:];
            let d: Map<String, Array<Int?>>? = [:];
        })";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat defer statement")
    {
        constexpr auto source = R"(func f() {
            defer { print("hello"); }
        })";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat 'var' variable specifier")
    {
        constexpr auto source = R"(func f() {
            var a = 42;
            var b: String = "hello";
        })";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat variable declarations outside function body")
    {
        constexpr auto source = R"(
            var a = 42;
            var b: String = "hello";
            let c = [];
            let d: Map<String, Int?> = [:];
            const e = true;
            const f: Double = 3.14;
        )";
        REQUIRE(parse(diag, source));
    }
}

TEST_CASE("parser can treat function declarations", "[parser]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("parser can treat function declaration with type hints")
    {
        constexpr auto source = "func f(a : Int, b : Int) -> Int {}\n";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat return-type annotation")
    {
        constexpr auto source = "func f() -> Int {}\n";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can not use trailing commas with parameters")
    {
        constexpr auto source = "func f(a, b, c,) {}\n";
        REQUIRE(!parse(diag, source));
    }
    SECTION("parser can not use trailing commas with arguments")
    {
        constexpr auto source = "func f() { g(a, b, c,); }\n";
        REQUIRE(!parse(diag, source));
    }
}

TEST_CASE("parser can treat function literal", "[parser]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("parser can treat function literal")
    {
        constexpr auto source = R"(func f() {
            var a = func () { return 42; };
            var b = func (x) { return x; };
            var c = func (x, y, z) { return x + y + z; };
        })";
        REQUIRE(parse(diag, source));
    }
    SECTION("function literal must be lambda function")
    {
        constexpr auto source = R"(func f() {
            var a = func g() {};
        })";
        REQUIRE(!parse(diag, source));
    }
}

TEST_CASE("parser can treat array literal", "[parser]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("parser can treat array literal")
    {
        constexpr auto source = "func f() { return [1, 2, 3, 4]; }\n";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat empty array literal")
    {
        constexpr auto source = "func f() { return []; }\n";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat single array literal")
    {
        constexpr auto source = "func f() { return [42]; }\n";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat trailing comma")
    {
        constexpr auto source = "func f() { return [1, 2, 3, 4,]; }\n";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser cannot allow trailing comma without elements")
    {
        constexpr auto source = "func f() { return [,]; }\n";
        REQUIRE(!parse(diag, source));
    }
    SECTION("parser cannot allow comma without elements")
    {
        constexpr auto source = "func f() { return [, 2]; }\n";
        REQUIRE(!parse(diag, source));
    }
}

TEST_CASE("parser can treat map literal", "[parser]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("parser can treat map literal")
    {
        constexpr auto source = R"(func f() { return ["a": 1, "b": 2, "c": 3]; })";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat empty map literal")
    {
        constexpr auto source = "func f() { return [:]; }\n";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat single map literal")
    {
        constexpr auto source = R"(func f() { return ["a" : 42]; })";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat trailing comma with map literal")
    {
        constexpr auto source = R"(func f() { return ["a" : 42,]; })";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser cannot allow comma without elements")
    {
        constexpr auto source = R"(func f() { return [, "a" : 42,]; })";
        REQUIRE(!parse(diag, source));
    }
#if 0
	// ECMAScript-like map literal
	SECTION("parser can treat map literal")
	{
		constexpr auto source = "func f() { return {\"a\": 1, \"b\": 2, \"c\": 3}; }\n";
		REQUIRE(parse(diag, source));
	}
	SECTION("parser can treat single map literal")
	{
		constexpr auto source = "func f() { return {\"a\": 42}; }\n";
		REQUIRE(parse(diag, source));
	}
	SECTION("parser can treat trailing comma with map literal")
	{
		constexpr auto source = "func f() { return {\"a\": 42,}; }\n";
		REQUIRE(parse(diag, source));
	}
	SECTION("parser cannot allow trailing comma without elements")
	{
		constexpr auto source = "func f() { return {,}; }\n";
		REQUIRE(!parse(diag, source));
	}
	SECTION("parser cannot allow comma without elements")
	{
		constexpr auto source = "func f() { return {, \"a\":42}; }\n";
		REQUIRE(!parse(diag, source));
	}
	SECTION("block scope and unary expression, not binary expression with map and integer literals")
	{
		constexpr auto source = "func f() { {} - 1; }\n";
		REQUIRE(parse(diag, source));
	}
	SECTION("block scope (not map literal) and empty statement.")
	{
		constexpr auto source = "func f() { {}; }\n";
		REQUIRE(parse(diag, source));
	}
	SECTION("empty map literal can be used as an experession statement with parentheses.")
	{
		constexpr auto source = "func f() { ({}); }\n";
		REQUIRE(parse(diag, source));
	}
	SECTION("map literal can't be used as an experession statement.")
	{
		constexpr auto source = "func f() { {\"a\":42}; }\n";
		REQUIRE(!parse(diag, source));
	}
	SECTION("map literal can be used as an experession statement with parentheses.")
	{
		constexpr auto source = "func f() { ({\"a\":42}); }\n";
		REQUIRE(parse(diag, source));
	}
	SECTION("map literal with indexer can't be used as an experession statement.")
	{
		constexpr auto source = "func f() { {\"a\":42}[\"a\"]; }\n";
		REQUIRE(!parse(diag, source));
	}
	SECTION("map literal with indexer can be used as an experession statement with parentheses.")
	{
		constexpr auto source = "func f() { ({\"a\":42})[\"a\"]; }\n";
		REQUIRE(parse(diag, source));
	}
#endif
}

TEST_CASE("parser can treat if, while, for and for...in statements", "[parser]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("parser can treat if statement")
    {
        constexpr auto source = R"(func f() {
            let a = 42;
            if (a > 0) {}
            //if (let b = a) {} // TODO: Not implemented
        })";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat while statement")
    {
        constexpr auto source = R"(func f() {
            let i = 0;
            while (i < 42) {
                ++i;
            }
        })";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat for statement")
    {
        constexpr auto source = R"(func f() {
            for (let i = 0; i < 42; i++) {
                print(i);
            }
        })";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat for...in statement")
    {
        constexpr auto source = R"(func f() {
            let a = [42, 43, 44];
            let m;
            for (m in a) { print(m); }
            for (let n in a) { print(n); }
            for (const n in a) { print(n); }
        })";
        REQUIRE(parse(diag, source));
    }
}

TEST_CASE("parser can treat binding declaration", "[parser]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("parser can treat binding declaration")
    {
        constexpr auto source = R"(func f() {
            let (a, b, c) = [1, 2, 3];
            let (x) = [42];
        })";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat binding declaration with 'var' specifier")
    {
        constexpr auto source = R"(func f() {
            var (a, b, c) = [1, 2, 3];
            var (x) = [42];
        })";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat binding declaration for constants")
    {
        constexpr auto source = R"(func f() {
            const (a, b, c) = [1, 2, 3];
            const (x) = [42];
        })";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can not use trailing commas with bindings")
    {
        constexpr auto source = "func f() { let (a, b, c,) = v; }\n";
        REQUIRE(!parse(diag, source));
    }
    SECTION("parser can not use an empty binding declaration")
    {
        constexpr auto source = "func f() { let () = v; }\n";
        REQUIRE(!parse(diag, source));
    }
    SECTION("parser can treat binding declaration in for-in loop")
    {
        constexpr auto source = R"(func f() {
            for (let (a, b) in v) {}
            for (var (a, b) in v) {}
            for (const (a, b) in v) {}
        })";
        REQUIRE(parse(diag, source));
    }
}

TEST_CASE("parser can treat class declarations", "[parser]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("parser can treat class declaration")
    {
        constexpr auto source = R"(
        class Vector2 {
            let x = 0;
            let y = 0;
            func dot(v : Vector2) { return x * v.x + y * v.y; }
            func cross(v : Vector2) { return x * v.y - y * v.x; }
        }
        )";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat members with type annotations")
    {
        constexpr auto source = R"(class Vector2 {
            let x;
            let y : Int;
            let z : Int = 42;
        })";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat empty class definition")
    {
        constexpr auto source = "class Foo {}\n";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat const member")
    {
        constexpr auto source = R"(class Math {
            const Epsilon = 2.71828;
            const Pi : Double = 3.141592;
        })";
        REQUIRE(parse(diag, source));
    }
}
