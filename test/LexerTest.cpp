#include "AST/ASTContext.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Identifier.h"
#include "AST/Stmt.h"
#include "AST/TypeRepr.h"
#include "Basic/Diagnostic.h"
#include "Driver/Driver.h"

#include "catch.hpp"

using namespace elma;

namespace {
bool lexerCheck(
    const std::shared_ptr<DiagnosticHandler>& diag,
    const std::string& source,
    ASTContext& astContextOut)
{
    Driver driver;
    auto [ast, ok] = driver.parseString(source, diag);
    astContextOut = ast;
    return ok;
}
} // end of anonymous namespace

TEST_CASE("lexer can treat basic sources consistently", "[lexer]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    ASTContext ast;

    SECTION("lexer can deal with an empty source.")
    {
        constexpr auto source = "";
        REQUIRE(lexerCheck(diag, source, ast));
        REQUIRE(!diag->hasError());
    }
    SECTION("lexer can skip UTF-8 BOM if it's present")
    {
        constexpr auto source = "\xEF\xBB\xBF"
                                "func f() {}\n";
        REQUIRE(lexerCheck(diag, source, ast));
        REQUIRE(!diag->hasError());
    }
    SECTION("lexer can skip CRLF if it's present")
    {
        constexpr auto source = "func f() {}\r\n";
        REQUIRE(lexerCheck(diag, source, ast));
        REQUIRE(!diag->hasError());
    }
    SECTION("lexer can treat BCPL-style comments")
    {
        constexpr auto source = R"(
// foo
func f() { // bar
    // TODO
	/// NOTE
	// // //
	// /*  */
	//*
	////////////
}
)";
        REQUIRE(lexerCheck(diag, source, ast));
        REQUIRE(!diag->hasError());
    }
    SECTION("lexer can treat C-style comments")
    {
        constexpr auto source = R"(
/* aaa */
func f() { /*
	aaa
	// TODO
	{
*/
	/******
	aaaaaaa
	******/
}
)";
        REQUIRE(lexerCheck(diag, source, ast));
        REQUIRE(!diag->hasError());
    }
    SECTION("lexer can treat C-style comments")
    {
        constexpr auto source = R"(
func f(/*){*/
}
)";
        REQUIRE(!lexerCheck(diag, source, ast));
        REQUIRE(diag->hasError());
    }
    SECTION("lexer provide source location information for AST")
    {
        constexpr auto source = R"(// foo
func max(a : Int, b : Int) -> Int {
    /* fizz
       buzz
       fizzbuzz */
    if (a >= b) {
        return a; // bar
    }
    return b;
}
)";
        REQUIRE(lexerCheck(diag, source, ast));
        REQUIRE(!diag->hasError());

        auto checkLocation =
            [&](Location loc, std::string begin, std::string end, int offsetBegin, int offsetEnd) {
                std::string s = source;
                REQUIRE(loc.begin.toString() == begin);
                REQUIRE(loc.end.toString() == end);
                REQUIRE(loc.begin.offset < s.size());
                REQUIRE(loc.end.offset < s.size());
                REQUIRE(loc.begin.offset == offsetBegin);
                REQUIRE(loc.end.offset == offsetEnd);
            };

        auto translationUnit = ast.getTranslationUnitDecl();
        auto funcDecl =
            std::static_pointer_cast<FuncDecl>(translationUnit->getDeclarations().front());
        auto funcName = funcDecl->getIdentifier();
        auto funcBody = funcDecl->getBody();
        auto param1 = funcDecl->getParameters().at(0);
        auto param2 = funcDecl->getParameters().at(1);
        auto ifStmt = std::static_pointer_cast<IfStmt>(funcBody->getStatements().at(0));
        auto ifCond = std::static_pointer_cast<BinaryExpr>(ifStmt->getCond());
        auto thenBody = std::static_pointer_cast<CompoundStmt>(ifStmt->getThen());
        auto thenReturn = std::static_pointer_cast<ReturnStmt>(thenBody->getStatements().front());
        auto returnStmt = std::static_pointer_cast<ReturnStmt>(funcBody->getStatements().at(1));

        checkLocation(translationUnit->getLocation(), "2:1", "10:2", 7, 150);
        checkLocation(funcDecl->getLocation(), "2:1", "10:2", 7, 150);
        checkLocation(funcName->getLocation(), "2:6", "2:9", 12, 15);
        checkLocation(funcBody->getLocation(), "2:35", "10:2", 41, 150);
        checkLocation(param1->getLocation(), "2:10", "2:17", 16, 23);
        checkLocation(param2->getLocation(), "2:19", "2:26", 25, 32);
        checkLocation(ifStmt->getLocation(), "6:5", "8:6", 90, 134);
        checkLocation(ifCond->getLocation(), "6:9", "6:15", 94, 100);
        checkLocation(ifCond->getLHS()->getLocation(), "6:9", "6:10", 94, 95);
        checkLocation(ifCond->getRHS()->getLocation(), "6:14", "6:15", 99, 100);
        checkLocation(thenBody->getLocation(), "6:17", "8:6", 102, 134);
        checkLocation(thenReturn->getLocation(), "7:9", "7:18", 112, 121);
        checkLocation(thenReturn->getExpr()->getLocation(), "7:16", "7:17", 119, 120);
        checkLocation(returnStmt->getLocation(), "9:5", "9:14", 139, 148);
        checkLocation(returnStmt->getExpr()->getLocation(), "9:12", "9:13", 146, 147);

        auto& comments = ast.comments;
        REQUIRE(comments[0]->getText() == "foo");
        REQUIRE(comments[1]->getText() == "fizz\n       buzz\n       fizzbuzz");
        REQUIRE(comments[2]->getText() == "bar");
        checkLocation(comments[0]->getLocation(), "1:1", "1:7", 0, 6);
        checkLocation(comments[1]->getLocation(), "3:5", "5:19", 47, 85);
        checkLocation(comments[2]->getLocation(), "7:19", "7:25", 122, 128);
    }
}
