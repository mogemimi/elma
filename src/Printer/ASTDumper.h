#pragma once

#include "AST/ASTVisitor.h"
#include "Basic/Forward.h"
#include <memory>
#include <string>

namespace elma {

class ASTDumper final : public ASTVisitor {
private:
    std::string output;
    int level = 0;

public:
    ASTDumper();

    std::string getResult() const { return output; }

    bool begin(std::shared_ptr<Node> node) override;
    void end(std::shared_ptr<Node> node) override;

    void visit(std::shared_ptr<Identifier> ident) override;

    void visit(std::shared_ptr<TranslationUnitDecl> decl) override;
    void visit(std::shared_ptr<VarDecl> decl) override;
    void visit(std::shared_ptr<BindingDecl> decl) override;
    void visit(std::shared_ptr<DecompositionDecl> decl) override;
    void visit(std::shared_ptr<FuncDecl> decl) override;
    void visit(std::shared_ptr<ParamDecl> decl) override;
    void visit(std::shared_ptr<ClassDecl> decl) override;
    void visit(std::shared_ptr<NamedDecl> decl) override;

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
    void visit(std::shared_ptr<ConditionalOperator> expr) override;
    void visit(std::shared_ptr<NullConditionalOperator> expr) override;
    void visit(std::shared_ptr<MemberExpr> expr) override;
    void visit(std::shared_ptr<SubscriptExpr> expr) override;
    void visit(std::shared_ptr<ArrayLiteral> expr) override;
    void visit(std::shared_ptr<MapEntry> expr) override;
    void visit(std::shared_ptr<MapLiteral> expr) override;
    void visit(std::shared_ptr<CallExpr> expr) override;
    void visit(std::shared_ptr<FuncLiteral> expr) override;
    void visit(std::shared_ptr<ImplicitConversionExpr> expr) override;

    void visit(std::shared_ptr<CompoundStmt> stmt) override;
    void visit(std::shared_ptr<DeclStmt> stmt) override;
    void visit(std::shared_ptr<ExprStmt> stmt) override;
    void visit(std::shared_ptr<ReturnStmt> stmt) override;
    void visit(std::shared_ptr<DeferStmt> stmt) override;
    void visit(std::shared_ptr<IfStmt> stmt) override;
    void visit(std::shared_ptr<WhileStmt> stmt) override;
    void visit(std::shared_ptr<ForStmt> stmt) override;
    void visit(std::shared_ptr<ForEachStmt> stmt) override;
};

} // namespace elma
