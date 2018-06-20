#include "Printer/ASTDumper.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Identifier.h"
#include "AST/Stmt.h"
#include "AST/Type.h"
#include <cassert>
#include <sstream>
#include <tuple>
#include <utility>

namespace elma {
namespace {

std::string makeIndent(int level)
{
    std::stringstream ss;
    for (int i = 0; i < level; i++) {
        ss << ".  ";
    }
    return ss.str();
}

std::string dump(
    int level,
    const std::string& name,
    const std::vector<std::tuple<std::string, std::string>>& options)
{
    std::string s = makeIndent(level) + name + " {\n";
    for (const auto& opt : options) {
        s += makeIndent(level + 1);
        s += std::get<0>(opt);
        s += ": ";
        s += std::get<1>(opt);
        s += "\n";
    }
    return s;
}

} // end of anonymous namespace

ASTDumper::ASTDumper()
{
    level = -1;
}

bool ASTDumper::begin(std::shared_ptr<Node> node)
{
    assert(level >= -1);
    ++level;
    return true;
}

void ASTDumper::end(std::shared_ptr<Node> node)
{
    assert(level >= 0);
    output += makeIndent(level) + "}\n";

    --level;
    assert(level >= -1);
}

void ASTDumper::visit(std::shared_ptr<Identifier> ident)
{
    std::vector<std::tuple<std::string, std::string>> options;
    options.emplace_back("Name", ident->getName());
    output += dump(level, "Identifier", options);

    ASTVisitor::visit(ident);
}

void ASTDumper::visit(std::shared_ptr<TranslationUnitDecl> decl)
{
    assert(level >= 0);
    output += dump(level, "TranslationUnitDecl", {});

    ASTVisitor::visit(decl);
}

void ASTDumper::visit(std::shared_ptr<VarDecl> decl)
{
    output += dump(level, "VarDecl", {});

    ASTVisitor::visit(decl);
}

void ASTDumper::visit(std::shared_ptr<BindingDecl> decl)
{
    output += dump(level, "BindingDecl", {});

    ASTVisitor::visit(decl);
}

void ASTDumper::visit(std::shared_ptr<DecompositionDecl> decl)
{
    output += dump(level, "DecompositionDecl", {});

    ASTVisitor::visit(decl);
}

void ASTDumper::visit(std::shared_ptr<FuncDecl> decl)
{
    output += dump(level, "FuncDecl", {});

    ASTVisitor::visit(decl);
}

void ASTDumper::visit(std::shared_ptr<ParamDecl> decl)
{
    output += dump(level, "ParamDecl", {});

    ASTVisitor::visit(decl);
}

void ASTDumper::visit(std::shared_ptr<ClassDecl> decl)
{
    output += dump(level, "ClassDecl", {});

    ASTVisitor::visit(decl);
}

void ASTDumper::visit(std::shared_ptr<NamedDecl> decl)
{
    std::vector<std::tuple<std::string, std::string>> options;
    output += dump(level, "NamedDecl", options);

    ASTVisitor::visit(decl);
}

void ASTDumper::visit(std::shared_ptr<IntegerLiteral> expr)
{
    output += dump(level, "IntegerLiteral", {});

    ASTVisitor::visit(expr);
}

void ASTDumper::visit(std::shared_ptr<DoubleLiteral> expr)
{
    output += dump(level, "DoubleLiteral", {});

    ASTVisitor::visit(expr);
}

void ASTDumper::visit(std::shared_ptr<BoolLiteral> expr)
{
    output += dump(level, "BoolLiteral", {});

    ASTVisitor::visit(expr);
}

void ASTDumper::visit(std::shared_ptr<StringLiteral> expr)
{
    output += dump(level, "StringLiteral", {});

    ASTVisitor::visit(expr);
}

void ASTDumper::visit(std::shared_ptr<NullLiteral> expr)
{
    output += dump(level, "NullLiteral", {});

    ASTVisitor::visit(expr);
}

void ASTDumper::visit(std::shared_ptr<IdentifierExpr> expr)
{
    output += dump(level, "IdentifierExpr", {});

    ASTVisitor::visit(expr);
}

void ASTDumper::visit(std::shared_ptr<ParenExpr> expr)
{
    output += dump(level, "ParenExpr", {});

    ASTVisitor::visit(expr);
}

void ASTDumper::visit(std::shared_ptr<UnaryExpr> expr)
{
    output += dump(level, "UnaryExpr", {});

    ASTVisitor::visit(expr);
}

void ASTDumper::visit(std::shared_ptr<BinaryExpr> expr)
{
    output += dump(level, "BinaryExpr", {});

    ASTVisitor::visit(expr);
}

void ASTDumper::visit(std::shared_ptr<AssignExpr> expr)
{
    output += dump(level, "AssignExpr", {});

    ASTVisitor::visit(expr);
}

void ASTDumper::visit(std::shared_ptr<ConditionalOperator> expr)
{
    output += dump(level, "ConditionalOperator", {});

    ASTVisitor::visit(expr);
}

void ASTDumper::visit(std::shared_ptr<NullConditionalOperator> expr)
{
    output += dump(level, "NullConditionalOperator", {});

    ASTVisitor::visit(expr);
}

void ASTDumper::visit(std::shared_ptr<MemberExpr> expr)
{
    output += dump(level, "MemberExpr", {});

    ASTVisitor::visit(expr);
}

void ASTDumper::visit(std::shared_ptr<SubscriptExpr> expr)
{
    output += dump(level, "SubscriptExpr", {});

    ASTVisitor::visit(expr);
}

void ASTDumper::visit(std::shared_ptr<ArrayLiteral> expr)
{
    output += dump(level, "ArrayLiteral", {});

    ASTVisitor::visit(expr);
}

void ASTDumper::visit(std::shared_ptr<MapEntry> expr)
{
    output += dump(level, "MapEntry", {});

    ASTVisitor::visit(expr);
}

void ASTDumper::visit(std::shared_ptr<MapLiteral> expr)
{
    output += dump(level, "MapLiteral", {});

    ASTVisitor::visit(expr);
}

void ASTDumper::visit(std::shared_ptr<CallExpr> expr)
{
    output += dump(level, "CallExpr", {});

    ASTVisitor::visit(expr);
}

void ASTDumper::visit(std::shared_ptr<FuncLiteral> expr)
{
    output += dump(level, "FuncLiteral", {});

    ASTVisitor::visit(expr);
}

void ASTDumper::visit(std::shared_ptr<ImplicitConversionExpr> expr)
{
    output += dump(level, "ImplicitConversionExpr", {});

    ASTVisitor::visit(expr);
}

void ASTDumper::visit(std::shared_ptr<CompoundStmt> stmt)
{
    output += dump(level, "CompoundStmt", {});

    ASTVisitor::visit(stmt);
}

void ASTDumper::visit(std::shared_ptr<DeclStmt> stmt)
{
    output += dump(level, "DeclStmt", {});

    ASTVisitor::visit(stmt);
}

void ASTDumper::visit(std::shared_ptr<ExprStmt> stmt)
{
    output += dump(level, "ExprStmt", {});

    ASTVisitor::visit(stmt);
}

void ASTDumper::visit(std::shared_ptr<ReturnStmt> stmt)
{
    output += dump(level, "ReturnStmt", {});

    ASTVisitor::visit(stmt);
}

void ASTDumper::visit(std::shared_ptr<DeferStmt> stmt)
{
    output += dump(level, "DeferStmt", {});

    ASTVisitor::visit(stmt);
}

void ASTDumper::visit(std::shared_ptr<IfStmt> stmt)
{
    output += dump(level, "IfStmt", {});

    ASTVisitor::visit(stmt);
}

void ASTDumper::visit(std::shared_ptr<WhileStmt> stmt)
{
    output += dump(level, "WhileStmt", {});

    ASTVisitor::visit(stmt);
}

void ASTDumper::visit(std::shared_ptr<ForStmt> stmt)
{
    output += dump(level, "ForStmt", {});

    ASTVisitor::visit(stmt);
}

void ASTDumper::visit(std::shared_ptr<ForEachStmt> stmt)
{
    output += dump(level, "ForEachStmt", {});

    ASTVisitor::visit(stmt);
}

} // namespace elma
