#pragma once

#include "Basic/Forward.h"
#include <functional>
#include <memory>

namespace elma {

class ASTVisitor {
public:
    virtual ~ASTVisitor() = default;

    virtual bool begin(std::shared_ptr<Node> node);
    virtual void end(std::shared_ptr<Node> node);

    virtual void visit(std::shared_ptr<Identifier> ident);

    virtual void visit(std::shared_ptr<TranslationUnitDecl> decl);
    virtual void visit(std::shared_ptr<VarDecl> decl);
    virtual void visit(std::shared_ptr<BindingDecl> decl);
    virtual void visit(std::shared_ptr<DecompositionDecl> decl);
    virtual void visit(std::shared_ptr<FuncDecl> decl);
    virtual void visit(std::shared_ptr<ParamDecl> decl);
    virtual void visit(std::shared_ptr<ClassDecl> decl);
    virtual void visit(std::shared_ptr<NamedDecl> decl);

    virtual void visit(std::shared_ptr<IntegerLiteral> expr);
    virtual void visit(std::shared_ptr<DoubleLiteral> expr);
    virtual void visit(std::shared_ptr<BoolLiteral> expr);
    virtual void visit(std::shared_ptr<StringLiteral> expr);
    virtual void visit(std::shared_ptr<NullLiteral> expr);
    virtual void visit(std::shared_ptr<IdentifierExpr> expr);
    virtual void visit(std::shared_ptr<ParenExpr> expr);
    virtual void visit(std::shared_ptr<UnaryExpr> expr);
    virtual void visit(std::shared_ptr<BinaryExpr> expr);
    virtual void visit(std::shared_ptr<AssignExpr> expr);
    virtual void visit(std::shared_ptr<ConditionalOperator> expr);
    virtual void visit(std::shared_ptr<NullConditionalOperator> expr);
    virtual void visit(std::shared_ptr<MemberExpr> expr);
    virtual void visit(std::shared_ptr<SubscriptExpr> expr);
    virtual void visit(std::shared_ptr<ArrayLiteral> expr);
    virtual void visit(std::shared_ptr<MapEntry> expr);
    virtual void visit(std::shared_ptr<MapLiteral> expr);
    virtual void visit(std::shared_ptr<CallExpr> expr);
    virtual void visit(std::shared_ptr<FuncLiteral> expr);
    virtual void visit(std::shared_ptr<ImplicitConversionExpr> expr);

    virtual void visit(std::shared_ptr<CompoundStmt> stmt);
    virtual void visit(std::shared_ptr<DeclStmt> stmt);
    virtual void visit(std::shared_ptr<ExprStmt> stmt);
    virtual void visit(std::shared_ptr<ReturnStmt> stmt);
    virtual void visit(std::shared_ptr<DeferStmt> stmt);
    virtual void visit(std::shared_ptr<IfStmt> stmt);
    virtual void visit(std::shared_ptr<WhileStmt> stmt);
    virtual void visit(std::shared_ptr<ForStmt> stmt);
    virtual void visit(std::shared_ptr<ForEachStmt> stmt);

    virtual void visit(std::shared_ptr<SimpleIdentTypeRepr> repr);
    virtual void visit(std::shared_ptr<GenericIdentTypeRepr> repr);
    virtual void visit(std::shared_ptr<OptionalTypeRepr> repr);
};

namespace AST {

void walk(ASTVisitor* visitor, std::shared_ptr<Node> node);

} // namespace AST
} // namespace elma
