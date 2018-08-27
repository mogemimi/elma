#include "CodeGen/Transpiler.h"
#include "AST/ASTContext.h"
#include "AST/Decl.h"
#include "AST/Identifier.h"
#include "Basic/Diagnostic.h"
#include "Driver/Driver.h"
#include "Printer/ASTFormatter.h"
#include "Sema/Entity.h"
#include "Sema/IdentifierResolver.h"
#include "Sema/SemaChecker.h"
#include "Sema/TypeInferer.h"
#include "Sema/TypeResolver.h"

#include "catch.hpp"

using namespace elma;

namespace {
std::string transpile(const std::shared_ptr<DiagnosticHandler>& diag, const std::string& source)
{
    elma::Driver driver;
    auto [ast, ok] = driver.parseString(source, diag);

    REQUIRE(ok);

    ASTFormatter formatter;
    AST::walk(&formatter, ast.translationUnit);

    IdentifierContext context;
    IdentifierResolver resolver(&ast, &context, diag);
    AST::walk(&resolver, ast.translationUnit);
    REQUIRE(!diag->hasError());

    SemaChecker semaChecker(diag);
    AST::walk(&semaChecker, ast.translationUnit);
    REQUIRE(!diag->hasError());

    TypeResolver typeResolver(diag);
    AST::walk(&typeResolver, ast.translationUnit);
    REQUIRE(!diag->hasError());

    Transpiler transpiler;
    AST::walk(&transpiler, ast.translationUnit);

    return transpiler.getResult();
}
} // end of anonymous namespace

TEST_CASE("Transpiler can convert program to ECMAScript", "[transpiler]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("transpiler can convert function declaration")
    {
        constexpr auto source = "func f() {\n"
                                "}\n";
        constexpr auto expect = "function f() {\n"
                                "}\n";
        REQUIRE(transpile(diag, source) == expect);
    }
    SECTION("transpiler prints function declaration without type annotations")
    {
        constexpr auto source = "func f(a : Int, b : String?) -> Void {\n"
                                "}\n";
        constexpr auto expect = "function f(a, b) {\n"
                                "}\n";
        REQUIRE(transpile(diag, source) == expect);
    }
}
