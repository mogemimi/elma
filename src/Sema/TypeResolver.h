#pragma once

#include "AST/ASTVisitor.h"
#include "AST/Type.h"
#include "Basic/Forward.h"
#include "Sema/TypeInferer.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace elma {

struct TypeResolverScope final {
    std::vector<std::shared_ptr<Type>> returnTypes;
    std::shared_ptr<Type> expectReturnType;
    TypeEnvironment env;
};

class TypeResolver final : public ASTVisitor {
    std::vector<std::shared_ptr<TypeResolverScope>> scopeStack;
    std::shared_ptr<DiagnosticHandler> diag;

public:
    explicit TypeResolver(const std::shared_ptr<DiagnosticHandler>& diag);

    std::shared_ptr<TypeResolverScope> getCurrentScope();

    void pushScope(const std::shared_ptr<TypeResolverScope>& scope);
    void popScope();

    void error(const Location& l, const std::string& err);

    void visit(std::shared_ptr<ReturnStmt> stmt) override;
    void visit(std::shared_ptr<IfStmt> stmt) override;
    void visit(std::shared_ptr<WhileStmt> stmt) override;
    void visit(std::shared_ptr<ForStmt> stmt) override;

    void visit(std::shared_ptr<IntegerLiteral> expr) override;
    void visit(std::shared_ptr<DoubleLiteral> expr) override;
    void visit(std::shared_ptr<BoolLiteral> expr) override;
    void visit(std::shared_ptr<StringLiteral> expr) override;
    void visit(std::shared_ptr<NullLiteral> expr) override;
    void visit(std::shared_ptr<IdentifierExpr> expr) override;
    void visit(std::shared_ptr<ParenExpr> expr) override;
    void visit(std::shared_ptr<UnaryExpr> expr) override;
    void visit(std::shared_ptr<BinaryExpr> expr) override;
    void visit(std::shared_ptr<AssignExpr> expr) override;
    void visit(std::shared_ptr<MemberExpr> expr) override;
    void visit(std::shared_ptr<SubscriptExpr> expr) override;
    void visit(std::shared_ptr<ArrayLiteral> expr) override;
    void visit(std::shared_ptr<MapEntry> expr) override;
    void visit(std::shared_ptr<MapLiteral> expr) override;
    void visit(std::shared_ptr<CallExpr> expr) override;
    void visit(std::shared_ptr<FuncLiteral> expr) override;

    void visit(std::shared_ptr<VarDecl> decl) override;
    void visit(std::shared_ptr<FuncDecl> decl) override;
    void visit(std::shared_ptr<ParamDecl> decl) override;
};

} // namespace elma
