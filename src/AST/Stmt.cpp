#include "AST/Stmt.h"
#include <cassert>
#include <utility>

namespace elma {

CompoundStmt::CompoundStmt(const Location& loc, const std::vector<std::shared_ptr<Stmt>>& s)
    : location(loc)
    , statements(s)
{
}

DeclStmt::DeclStmt(const Location& loc, const std::shared_ptr<Decl>& d)
    : location(loc)
    , decl(d)
{
}

ExprStmt::ExprStmt(const Location& loc, const std::shared_ptr<Expr>& e)
    : location(loc)
    , expr(e)
{
}

ReturnStmt::ReturnStmt(const Location& loc)
    : location(loc)
{
}

ReturnStmt::ReturnStmt(const Location& loc, const std::shared_ptr<Expr>& e)
    : location(loc)
    , expr(e)
{
}

std::shared_ptr<Expr> ReturnStmt::getExpr() const
{
    return expr;
}

DeferStmt::DeferStmt(const Location& loc, const std::shared_ptr<Stmt>& bodyStmtIn)
    : location(loc)
    , bodyStmt(bodyStmtIn)
{
}

std::shared_ptr<Stmt> DeferStmt::getBody() const
{
    return bodyStmt;
}

IfStmt::IfStmt(
    const Location& loc,
    const std::shared_ptr<Expr>& condExprIn,
    const std::shared_ptr<Stmt>& thenStmtIn)
    : location(loc)
    , condExpr(condExprIn)
    , thenStmt(thenStmtIn)
{
}

IfStmt::IfStmt(
    const Location& loc,
    const std::shared_ptr<Expr>& condExprIn,
    const std::shared_ptr<Stmt>& thenStmtIn,
    const std::shared_ptr<Stmt>& elseStmtIn)
    : location(loc)
    , condExpr(condExprIn)
    , thenStmt(thenStmtIn)
    , elseStmt(elseStmtIn)
{
}

std::shared_ptr<Expr> IfStmt::getCond() const
{
    return condExpr;
}

void IfStmt::setCond(const std::shared_ptr<Expr>& c)
{
    condExpr = c;
}

std::shared_ptr<Stmt> IfStmt::getThen() const
{
    return thenStmt;
}

std::shared_ptr<Stmt> IfStmt::getElse() const
{
    return elseStmt;
}

WhileStmt::WhileStmt(
    const Location& loc,
    const std::shared_ptr<Expr>& condExprIn,
    const std::shared_ptr<Stmt>& bodyStmtIn)
    : location(loc)
    , condExpr(condExprIn)
    , bodyStmt(bodyStmtIn)
{
}

std::shared_ptr<Expr> WhileStmt::getCond() const
{
    return condExpr;
}

void WhileStmt::setCond(const std::shared_ptr<Expr>& c)
{
    condExpr = c;
}

std::shared_ptr<Stmt> WhileStmt::getBody() const
{
    return bodyStmt;
}

ForStmt::ForStmt(
    const Location& loc,
    const std::shared_ptr<Stmt>& initStmtIn,
    const std::shared_ptr<Expr>& condExprIn,
    const std::shared_ptr<Expr>& incExprIn,
    const std::shared_ptr<Stmt>& bodyStmtIn)
    : location(loc)
    , initStmt(initStmtIn)
    , condExpr(condExprIn)
    , incExpr(incExprIn)
    , bodyStmt(bodyStmtIn)
{
}

std::shared_ptr<Stmt> ForStmt::getInit() const
{
    return initStmt;
}

std::shared_ptr<Expr> ForStmt::getCond() const
{
    return condExpr;
}

void ForStmt::setCond(const std::shared_ptr<Expr>& c)
{
    condExpr = c;
}

std::shared_ptr<Expr> ForStmt::getInc() const
{
    return incExpr;
}

std::shared_ptr<Stmt> ForStmt::getBody() const
{
    return bodyStmt;
}

ForEachStmt::ForEachStmt(
    const Location& loc,
    const std::shared_ptr<Decl>& loopVariableIn,
    const std::shared_ptr<Expr>& rangeExprIn,
    const std::shared_ptr<Stmt>& bodyStmtIn)
    : location(loc)
    , loopVariable(loopVariableIn)
    , rangeExpr(rangeExprIn)
    , bodyStmt(bodyStmtIn)
{
}

std::shared_ptr<Decl> ForEachStmt::getLoopVariable() const
{
    return loopVariable;
}

std::shared_ptr<Expr> ForEachStmt::getRangeExpr() const
{
    return rangeExpr;
}

std::shared_ptr<Stmt> ForEachStmt::getBody() const
{
    return bodyStmt;
}

} // namespace elma
