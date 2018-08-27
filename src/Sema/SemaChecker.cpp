#include "Sema/SemaChecker.h"
#include "AST/ASTVisitor.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Identifier.h"
#include "AST/Stmt.h"
#include "AST/Type.h"
#include "Basic/Diagnostic.h"
#include "Sema/Entity.h"
#include "Sema/InfiniteRecursion.h"
#include <cassert>
#include <sstream>
#include <utility>

namespace elma {
namespace {

bool hasConstantReassignedError(
    const std::shared_ptr<Expr>& lhs, const std::shared_ptr<DiagnosticHandler>& diag)
{
    assert(lhs);
    assert(diag);
    if (lhs->getKind() != NodeKind::IdentifierExpr) {
        return false;
    }
    auto declRef = std::static_pointer_cast<IdentifierExpr>(lhs);

    auto ident = declRef->getIdentifier();
    if (!ident) {
        return false;
    }
    auto entity = ident->getEntity();
    if (!entity) {
        return false;
    }
    if (entity->getKind() == EntityKind::Const) {
        diag->error(
            ident->getLocation(),
            "'" + ident->getName() + "' cannot be reassigned because it is a constant.");
        return true;
    }
    if (entity->getKind() == EntityKind::Type) {
        diag->error(
            ident->getLocation(),
            "'" + ident->getName() + "' cannot be assigned because it only refers to a type.");
        return true;
    }
    if (entity->getKind() != EntityKind::Var) {
        diag->error(lhs->getLocation(), "Cannot assign to '" + ident->getName() + "'.");
        return true;
    }
    return false;
}

} // end of anonymous namespace

SemaChecker::SemaChecker(const std::shared_ptr<DiagnosticHandler>& diagIn)
    : diag(diagIn)
{
    assert(diag);
}

void SemaChecker::error(const Location& l, const std::string& err)
{
    assert(diag);
    diag->error(l, err);
}

void SemaChecker::visit(std::shared_ptr<IfStmt> stmt)
{
    if (!stmt->getThen()) {
        diag->warn(stmt->getLocation(), "if statement has empty body");
    }

    ASTVisitor::visit(stmt);
}

void SemaChecker::visit(std::shared_ptr<WhileStmt> stmt)
{
    if (!stmt->getBody()) {
        diag->warn(stmt->getLocation(), "while statement has empty body");
    }

    ASTVisitor::visit(stmt);
}

void SemaChecker::visit(std::shared_ptr<ForStmt> stmt)
{
    if (!stmt->getBody()) {
        diag->warn(stmt->getLocation(), "for statement has empty body");
    }

    ASTVisitor::visit(stmt);
}

void SemaChecker::visit(std::shared_ptr<AssignExpr> expr)
{
    ASTVisitor::visit(expr);

    const auto lhs = expr->getLHS();
    assert(lhs);
    if (hasConstantReassignedError(lhs, diag)) {
        return;
    }

    if (!lhs->isLValue()) {
        error(lhs->getLocation(), "The left-hand side of an assignment must be a variable.");
        return;
    }
}

void SemaChecker::visit(std::shared_ptr<TranslationUnitDecl> decl)
{
    // NOTE: Using depth-first traversal as usual.
    ASTVisitor::visit(decl);

    for (auto& node : decl->getDeclarations()) {
        if (node->getKind() == NodeKind::VarDecl) {
            auto varDecl = std::static_pointer_cast<VarDecl>(node);
            if (auto result = Sema::findInfiniteRecursion(varDecl)) {
                auto ident = varDecl->getIdentifier();
                std::string err = "initialization loop\n";
                err += "  " + ident->getLocation().toString() + " '" + ident->getName() + "'\n";
                err += "  " + result->getLocation().toString() + " '" + result->getName() + "'";
                error(varDecl->getLocation(), err);
            }
        }
    }
}

void SemaChecker::visit(std::shared_ptr<ClassDecl> decl)
{
    // NOTE: A class declaration can't have a member of its own type such as the following code,
    // it must be a directed acyclic graph: `class Foo { var foo : Foo; }`
    if (auto result = Sema::findInfiniteRecursion(decl)) {
        auto ident = decl->getIdentifier();
        std::string err = "invalid recursive type '" + ident->getName() + "'\n";
        err += "  " + ident->getLocation().toString() + " '" + ident->getName() + "'\n";
        err += "  " + result->getLocation().toString() + " '" + result->getName() + "'";
        error(decl->getLocation(), err);
        return;
    }
}

} // namespace elma
