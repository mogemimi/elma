#pragma once

#include "AST/Node.h"
#include "Basic/Forward.h"
#include <memory>
#include <string>
#include <vector>

namespace elma {

class Stmt : public Node {
public:
    virtual ~Stmt() = default;
};

class CompoundStmt final
    : public Stmt
    , public std::enable_shared_from_this<CompoundStmt> {
private:
    Location location;
    std::vector<std::shared_ptr<Stmt>> statements;

public:
    CompoundStmt(const Location& loc, const std::vector<std::shared_ptr<Stmt>>& s);

    NodeKind getKind() const noexcept override { return NodeKind::CompoundStmt; }

    Location getLocation() const noexcept override { return location; }

    std::vector<std::shared_ptr<Stmt>> getStatements() const { return statements; }
};

class DeclStmt final
    : public Stmt
    , public std::enable_shared_from_this<DeclStmt> {
private:
    Location location;
    std::shared_ptr<Decl> decl;

public:
    DeclStmt(const Location& loc, const std::shared_ptr<Decl>& d);

    NodeKind getKind() const noexcept override { return NodeKind::DeclStmt; }

    Location getLocation() const noexcept override { return location; }

    std::shared_ptr<Decl> getDecl() const { return decl; }
};

class ExprStmt final
    : public Stmt
    , public std::enable_shared_from_this<ExprStmt> {
private:
    Location location;
    std::shared_ptr<Expr> expr;

public:
    ExprStmt(const Location& loc, const std::shared_ptr<Expr>& e);

    NodeKind getKind() const noexcept override { return NodeKind::ExprStmt; }

    Location getLocation() const noexcept override { return location; }

    std::shared_ptr<Expr> getExpr() const { return expr; }
};

class ReturnStmt final
    : public Stmt
    , public std::enable_shared_from_this<ReturnStmt> {
private:
    Location location;
    std::shared_ptr<Expr> expr;

public:
    explicit ReturnStmt(const Location& loc);

    ReturnStmt(const Location& loc, const std::shared_ptr<Expr>& e);

    NodeKind getKind() const noexcept override { return NodeKind::ReturnStmt; }

    Location getLocation() const noexcept override { return location; }

    std::shared_ptr<Expr> getExpr() const;
};

class DeferStmt final
    : public Stmt
    , public std::enable_shared_from_this<DeferStmt> {
private:
    Location location;
    std::shared_ptr<Stmt> bodyStmt;

public:
    DeferStmt(const Location& loc, const std::shared_ptr<Stmt>& bodyStmt);

    NodeKind getKind() const noexcept override { return NodeKind::DeferStmt; }

    Location getLocation() const noexcept override { return location; }

    std::shared_ptr<Stmt> getBody() const;
    void setBody(const std::shared_ptr<Stmt>& b) { this->bodyStmt = b; }
};

class IfStmt final
    : public Stmt
    , public std::enable_shared_from_this<IfStmt> {
private:
    Location location;
    std::shared_ptr<Expr> condExpr;
    std::shared_ptr<Stmt> thenStmt;
    std::shared_ptr<Stmt> elseStmt;

public:
    IfStmt(
        const Location& loc,
        const std::shared_ptr<Expr>& condExpr,
        const std::shared_ptr<Stmt>& thenStmt);

    IfStmt(
        const Location& loc,
        const std::shared_ptr<Expr>& condExpr,
        const std::shared_ptr<Stmt>& thenStmt,
        const std::shared_ptr<Stmt>& elseStmt);

    NodeKind getKind() const noexcept override { return NodeKind::IfStmt; }

    Location getLocation() const noexcept override { return location; }

    std::shared_ptr<Expr> getCond() const;

    void setCond(const std::shared_ptr<Expr>& condExpr);

    std::shared_ptr<Stmt> getThen() const;
    void setThen(const std::shared_ptr<Stmt>& t) { this->thenStmt = t; }

    std::shared_ptr<Stmt> getElse() const;
    void setElse(const std::shared_ptr<Stmt>& e) { this->elseStmt = e; }
};

class WhileStmt final
    : public Stmt
    , public std::enable_shared_from_this<WhileStmt> {
private:
    Location location;
    std::shared_ptr<Expr> condExpr;
    std::shared_ptr<Stmt> bodyStmt;

public:
    WhileStmt(
        const Location& loc,
        const std::shared_ptr<Expr>& condExpr,
        const std::shared_ptr<Stmt>& bodyStmt);

    NodeKind getKind() const noexcept override { return NodeKind::WhileStmt; }

    Location getLocation() const noexcept override { return location; }

    std::shared_ptr<Expr> getCond() const;

    void setCond(const std::shared_ptr<Expr>& condExpr);

    std::shared_ptr<Stmt> getBody() const;
    void setBody(const std::shared_ptr<Stmt>& b) { this->bodyStmt = b; }
};

class ForStmt final
    : public Stmt
    , public std::enable_shared_from_this<ForStmt> {
private:
    Location location;
    std::shared_ptr<Stmt> initStmt;
    std::shared_ptr<Expr> condExpr;
    std::shared_ptr<Expr> incExpr;
    std::shared_ptr<Stmt> bodyStmt;

public:
    ForStmt(
        const Location& loc,
        const std::shared_ptr<Stmt>& initStmt,
        const std::shared_ptr<Expr>& condExpr,
        const std::shared_ptr<Expr>& incExpr,
        const std::shared_ptr<Stmt>& bodyStmt);

    NodeKind getKind() const noexcept override { return NodeKind::ForStmt; }

    Location getLocation() const noexcept override { return location; }

    std::shared_ptr<Stmt> getInit() const;

    std::shared_ptr<Expr> getCond() const;

    void setCond(const std::shared_ptr<Expr>& condExpr);

    std::shared_ptr<Expr> getInc() const;

    std::shared_ptr<Stmt> getBody() const;
    void setBody(const std::shared_ptr<Stmt>& b) { this->bodyStmt = b; }
};

class ForEachStmt final
    : public Stmt
    , public std::enable_shared_from_this<ForEachStmt> {
private:
    Location location;
    std::shared_ptr<Decl> loopVariable;
    std::shared_ptr<Expr> rangeExpr;
    std::shared_ptr<Stmt> bodyStmt;

public:
    ForEachStmt(
        const Location& loc,
        const std::shared_ptr<Decl>& loopVariable,
        const std::shared_ptr<Expr>& rangeExpr,
        const std::shared_ptr<Stmt>& bodyStmt);

    NodeKind getKind() const noexcept override { return NodeKind::ForEachStmt; }

    Location getLocation() const noexcept override { return location; }

    std::shared_ptr<Decl> getLoopVariable() const;

    std::shared_ptr<Expr> getRangeExpr() const;

    std::shared_ptr<Stmt> getBody() const;
    void setBody(const std::shared_ptr<Stmt>& b) { this->bodyStmt = b; }
};

} // namespace elma
