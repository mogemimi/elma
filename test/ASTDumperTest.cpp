#include "Printer/ASTDumper.h"
#include "AST/ASTContext.h"
#include "AST/Decl.h"
#include "Basic/Diagnostic.h"
#include "Driver/Driver.h"

#include "catch.hpp"

using namespace elma;

namespace {
std::string dump(const std::shared_ptr<DiagnosticHandler>& diag, const std::string& source)
{
    elma::Driver driver;
    auto [ast, ok] = driver.parseString(source, diag);

    REQUIRE(ok);

    ASTDumper dumper;
    AST::walk(&dumper, ast.translationUnit);

    return dumper.getResult();
}
} // end of anonymous namespace

TEST_CASE("ast dumper", "[ast-dumper]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("ast-dumper prints function declaration")
    {
        constexpr auto source = "func f() {\n"
                                "}\n";
        constexpr auto expect = R"(TranslationUnitDecl {
.  FuncDecl {
.  .  Identifier {
.  .  .  Name: f
.  .  }
.  .  CompoundStmt {
.  .  }
.  }
}
)";
        REQUIRE(dump(diag, source) == expect);
    }
}
