#include "Printer/ASTFormatter.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Stmt.h"
#include <cassert>
#include <utility>

namespace elma {

void ASTFormatter::visit(std::shared_ptr<IfStmt> stmt)
{
    ASTVisitor::visit(stmt);

    if (auto thenStmt = stmt->getThen()) {
        if (!std::dynamic_pointer_cast<CompoundStmt>(thenStmt)) {
            // NOTE: Formatter does not allow single line if statements.
            auto compound = std::make_shared<CompoundStmt>(
                thenStmt->getLocation(), std::vector<std::shared_ptr<Stmt>>{thenStmt});
            stmt->setThen(compound);
        }
    }

    if (auto elseStmt = stmt->getElse()) {
        if ((!std::dynamic_pointer_cast<CompoundStmt>(elseStmt)) &&
            (!std::dynamic_pointer_cast<IfStmt>(elseStmt))) {
            // NOTE: Formatter does not allow single line else statements.
            auto compound = std::make_shared<CompoundStmt>(
                elseStmt->getLocation(), std::vector<std::shared_ptr<Stmt>>{elseStmt});
            stmt->setElse(compound);
        }
    }
}

void ASTFormatter::visit(std::shared_ptr<WhileStmt> stmt)
{
    ASTVisitor::visit(stmt);

    if (auto body = stmt->getBody()) {
        if (!std::dynamic_pointer_cast<CompoundStmt>(body)) {
            // NOTE: Formatter does not allow single line while statements.
            auto compound = std::make_shared<CompoundStmt>(
                body->getLocation(), std::vector<std::shared_ptr<Stmt>>{body});
            stmt->setBody(compound);
        }
    }
}

void ASTFormatter::visit(std::shared_ptr<ForStmt> stmt)
{
    ASTVisitor::visit(stmt);

    if (auto body = stmt->getBody()) {
        if (!std::dynamic_pointer_cast<CompoundStmt>(body)) {
            // NOTE: Formatter does not allow single line for-statements.
            auto compound = std::make_shared<CompoundStmt>(
                body->getLocation(), std::vector<std::shared_ptr<Stmt>>{body});
            stmt->setBody(compound);
        }
    }
}

void ASTFormatter::visit(std::shared_ptr<ForEachStmt> stmt)
{
    ASTVisitor::visit(stmt);

    if (auto body = stmt->getBody()) {
        if (!std::dynamic_pointer_cast<CompoundStmt>(body)) {
            // NOTE: Formatter does not allow single line for...in statements.
            auto compound = std::make_shared<CompoundStmt>(
                body->getLocation(), std::vector<std::shared_ptr<Stmt>>{body});
            stmt->setBody(compound);
        }
    }
}

void ASTFormatter::visit(std::shared_ptr<ParenExpr> expr)
{
    ASTVisitor::visit(expr);

    if (auto subExpr = expr->getSubExpr()) {
        if (auto subParen = std::dynamic_pointer_cast<ParenExpr>(subExpr)) {
            // NOTE: Formatter abbreviates redundant parentheses.
            expr->setSubExpr(subParen->getSubExpr());
        }
    }
}

} // namespace elma
