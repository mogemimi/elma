#include "AST/ASTVisitor.h"
#include "AST/ASTContext.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Identifier.h"
#include "AST/Stmt.h"
#include "AST/TypeRepr.h"
#include <cassert>
#include <utility>

namespace elma {
namespace AST {
namespace {

template <typename T> void walkChildren(ASTVisitor* visitor, const std::vector<T>& children)
{
    for (const auto& child : children) {
        assert(child != nullptr);
        walk(visitor, child);
    }
}

} // end of anonymous namespace

void walk(ASTVisitor* visitor, std::shared_ptr<Node> node)
{
    assert(visitor != nullptr);
    assert(node != nullptr);

    if (!visitor->begin(node)) {
        return;
    }

    switch (node->getKind()) {
    case NodeKind::Identifier: {
        visitor->visit(std::static_pointer_cast<Identifier>(node));
        break;
    }
    case NodeKind::TranslationUnitDecl: {
        visitor->visit(std::static_pointer_cast<TranslationUnitDecl>(node));
        break;
    }
    case NodeKind::VarDecl: {
        visitor->visit(std::static_pointer_cast<VarDecl>(node));
        break;
    }
    case NodeKind::BindingDecl: {
        visitor->visit(std::static_pointer_cast<BindingDecl>(node));
        break;
    }
    case NodeKind::DecompositionDecl: {
        visitor->visit(std::static_pointer_cast<DecompositionDecl>(node));
        break;
    }
    case NodeKind::FuncDecl: {
        visitor->visit(std::static_pointer_cast<FuncDecl>(node));
        break;
    }
    case NodeKind::ParamDecl: {
        visitor->visit(std::static_pointer_cast<ParamDecl>(node));
        break;
    }
    case NodeKind::ClassDecl: {
        visitor->visit(std::static_pointer_cast<ClassDecl>(node));
        break;
    }
    case NodeKind::NamedDecl: {
        visitor->visit(std::static_pointer_cast<NamedDecl>(node));
        break;
    }
    case NodeKind::IntegerLiteral: {
        visitor->visit(std::static_pointer_cast<IntegerLiteral>(node));
        break;
    }
    case NodeKind::DoubleLiteral: {
        visitor->visit(std::static_pointer_cast<DoubleLiteral>(node));
        break;
    }
    case NodeKind::BoolLiteral: {
        visitor->visit(std::static_pointer_cast<BoolLiteral>(node));
        break;
    }
    case NodeKind::StringLiteral: {
        visitor->visit(std::static_pointer_cast<StringLiteral>(node));
        break;
    }
    case NodeKind::NullLiteral: {
        visitor->visit(std::static_pointer_cast<NullLiteral>(node));
        break;
    }
    case NodeKind::IdentifierExpr: {
        visitor->visit(std::static_pointer_cast<IdentifierExpr>(node));
        break;
    }
    case NodeKind::ParenExpr: {
        visitor->visit(std::static_pointer_cast<ParenExpr>(node));
        break;
    }
    case NodeKind::UnaryExpr: {
        visitor->visit(std::static_pointer_cast<UnaryExpr>(node));
        break;
    }
    case NodeKind::BinaryExpr: {
        visitor->visit(std::static_pointer_cast<BinaryExpr>(node));
        break;
    }
    case NodeKind::AssignExpr: {
        visitor->visit(std::static_pointer_cast<AssignExpr>(node));
        break;
    }
    case NodeKind::ConditionalOperator: {
        visitor->visit(std::static_pointer_cast<ConditionalOperator>(node));
        break;
    }
    case NodeKind::NullConditionalOperator: {
        visitor->visit(std::static_pointer_cast<NullConditionalOperator>(node));
        break;
    }
    case NodeKind::MemberExpr: {
        visitor->visit(std::static_pointer_cast<MemberExpr>(node));
        break;
    }
    case NodeKind::SubscriptExpr: {
        visitor->visit(std::static_pointer_cast<SubscriptExpr>(node));
        break;
    }
    case NodeKind::ArrayLiteral: {
        visitor->visit(std::static_pointer_cast<ArrayLiteral>(node));
        break;
    }
    case NodeKind::MapEntry: {
        visitor->visit(std::static_pointer_cast<MapEntry>(node));
        break;
    }
    case NodeKind::MapLiteral: {
        visitor->visit(std::static_pointer_cast<MapLiteral>(node));
        break;
    }
    case NodeKind::CallExpr: {
        visitor->visit(std::static_pointer_cast<CallExpr>(node));
        break;
    }
    case NodeKind::FuncLiteral: {
        visitor->visit(std::static_pointer_cast<FuncLiteral>(node));
        break;
    }
    case NodeKind::ImplicitConversionExpr: {
        visitor->visit(std::static_pointer_cast<ImplicitConversionExpr>(node));
        break;
    }
    case NodeKind::CompoundStmt: {
        visitor->visit(std::static_pointer_cast<CompoundStmt>(node));
        break;
    }
    case NodeKind::DeclStmt: {
        visitor->visit(std::static_pointer_cast<DeclStmt>(node));
        break;
    }
    case NodeKind::ExprStmt: {
        visitor->visit(std::static_pointer_cast<ExprStmt>(node));
        break;
    }
    case NodeKind::ReturnStmt: {
        visitor->visit(std::static_pointer_cast<ReturnStmt>(node));
        break;
    }
    case NodeKind::DeferStmt: {
        visitor->visit(std::static_pointer_cast<DeferStmt>(node));
        break;
    }
    case NodeKind::IfStmt: {
        visitor->visit(std::static_pointer_cast<IfStmt>(node));
        break;
    }
    case NodeKind::WhileStmt: {
        visitor->visit(std::static_pointer_cast<WhileStmt>(node));
        break;
    }
    case NodeKind::ForStmt: {
        visitor->visit(std::static_pointer_cast<ForStmt>(node));
        break;
    }
    case NodeKind::ForEachStmt: {
        visitor->visit(std::static_pointer_cast<ForEachStmt>(node));
        break;
    }
    case NodeKind::SimpleIdentTypeRepr: {
        visitor->visit(std::static_pointer_cast<SimpleIdentTypeRepr>(node));
        break;
    }
    case NodeKind::GenericIdentTypeRepr: {
        visitor->visit(std::static_pointer_cast<GenericIdentTypeRepr>(node));
        break;
    }
    case NodeKind::OptionalTypeRepr: {
        visitor->visit(std::static_pointer_cast<OptionalTypeRepr>(node));
        break;
    }
    default:
        // error("unreachable");
        break;
    }

    visitor->end(node);
}

} // namespace AST

bool ASTVisitor::begin(std::shared_ptr<Node> node)
{
    assert(node);
    return true;
}

void ASTVisitor::end(std::shared_ptr<Node> node)
{
    assert(node);
}

void ASTVisitor::visit(std::shared_ptr<Identifier> ident)
{
    // Nothing to do
}

void ASTVisitor::visit(std::shared_ptr<TranslationUnitDecl> decl)
{
    AST::walkChildren(this, decl->getDeclarations());
}

void ASTVisitor::visit(std::shared_ptr<VarDecl> decl)
{
    AST::walk(this, decl->getIdentifier());
    if (auto expr = decl->getExpr()) {
        AST::walk(this, expr);
    }
    if (auto repr = decl->getTypeAnnotation()) {
        AST::walk(this, repr);
    }
}

void ASTVisitor::visit(std::shared_ptr<BindingDecl> decl)
{
    AST::walk(this, decl->getIdentifier());
    if (auto expr = decl->getExpr()) {
        AST::walk(this, expr);
    }
}

void ASTVisitor::visit(std::shared_ptr<DecompositionDecl> decl)
{
    AST::walkChildren(this, decl->getBindings());
    if (auto expr = decl->getExpr()) {
        AST::walk(this, expr);
    }
}

void ASTVisitor::visit(std::shared_ptr<FuncDecl> decl)
{
    if (auto ident = decl->getIdentifier()) {
        AST::walk(this, ident);
    }
    AST::walkChildren(this, decl->getParameters());
    AST::walk(this, decl->getBody());
}

void ASTVisitor::visit(std::shared_ptr<ParamDecl> decl)
{
    AST::walk(this, decl->getIdentifier());
    if (auto repr = decl->getTypeAnnotation()) {
        AST::walk(this, repr);
    }
}

void ASTVisitor::visit(std::shared_ptr<ClassDecl> decl)
{
    AST::walk(this, decl->getIdentifier());
    AST::walkChildren(this, decl->getMembers());
}

void ASTVisitor::visit(std::shared_ptr<NamedDecl> decl)
{
    if (auto ident = decl->getIdentifier()) {
        AST::walk(this, ident);
    }
}

void ASTVisitor::visit(std::shared_ptr<CompoundStmt> stmt)
{
    AST::walkChildren(this, stmt->getStatements());
}

void ASTVisitor::visit(std::shared_ptr<DeclStmt> stmt)
{
    AST::walk(this, stmt->getDecl());
}

void ASTVisitor::visit(std::shared_ptr<ExprStmt> stmt)
{
    AST::walk(this, stmt->getExpr());
}

void ASTVisitor::visit(std::shared_ptr<ReturnStmt> stmt)
{
    AST::walk(this, stmt->getExpr());
}

void ASTVisitor::visit(std::shared_ptr<IfStmt> stmt)
{
    if (auto condExpr = stmt->getCond()) {
        AST::walk(this, condExpr);
    }
    if (auto thenStmt = stmt->getThen()) {
        AST::walk(this, thenStmt);
    }
    if (auto elseStmt = stmt->getElse()) {
        AST::walk(this, elseStmt);
    }
}

void ASTVisitor::visit(std::shared_ptr<WhileStmt> stmt)
{
    if (auto condExpr = stmt->getCond()) {
        AST::walk(this, condExpr);
    }
    if (auto bodyStmt = stmt->getBody()) {
        AST::walk(this, bodyStmt);
    }
}

void ASTVisitor::visit(std::shared_ptr<ForStmt> stmt)
{
    if (auto initStmt = stmt->getInit()) {
        AST::walk(this, initStmt);
    }
    if (auto condExpr = stmt->getCond()) {
        AST::walk(this, condExpr);
    }
    if (auto incExpr = stmt->getInc()) {
        AST::walk(this, incExpr);
    }
    if (auto bodyStmt = stmt->getBody()) {
        AST::walk(this, bodyStmt);
    }
}

void ASTVisitor::visit(std::shared_ptr<ForEachStmt> stmt)
{
    if (auto loopVariable = stmt->getLoopVariable()) {
        AST::walk(this, loopVariable);
    }
    if (auto rangeExpr = stmt->getRangeExpr()) {
        AST::walk(this, rangeExpr);
    }
    if (auto bodyStmt = stmt->getBody()) {
        AST::walk(this, bodyStmt);
    }
}

void ASTVisitor::visit(std::shared_ptr<DeferStmt> stmt)
{
    if (auto bodyStmt = stmt->getBody()) {
        AST::walk(this, bodyStmt);
    }
}

void ASTVisitor::visit(std::shared_ptr<CallExpr> expr)
{
    if (auto callee = expr->getCallee()) {
        AST::walk(this, callee);
    }
    AST::walkChildren(this, expr->getArguments());
}

void ASTVisitor::visit(std::shared_ptr<FuncLiteral> expr)
{
    AST::walkChildren(this, expr->getParameters());
    if (auto compoundStmt = expr->getBody()) {
        AST::walk(this, compoundStmt);
    }
}

void ASTVisitor::visit(std::shared_ptr<IntegerLiteral> expr)
{
    // Nothing to do
}

void ASTVisitor::visit(std::shared_ptr<DoubleLiteral> expr)
{
    // Nothing to do
}

void ASTVisitor::visit(std::shared_ptr<BoolLiteral> expr)
{
    // Nothing to do
}

void ASTVisitor::visit(std::shared_ptr<StringLiteral> expr)
{
    // Nothing to do
}

void ASTVisitor::visit(std::shared_ptr<NullLiteral> expr)
{
    // Nothing to do
}

void ASTVisitor::visit(std::shared_ptr<BinaryExpr> expr)
{
    AST::walk(this, expr->getLHS());
    AST::walk(this, expr->getRHS());
}

void ASTVisitor::visit(std::shared_ptr<UnaryExpr> expr)
{
    AST::walk(this, expr->getSubExpr());
}

void ASTVisitor::visit(std::shared_ptr<AssignExpr> expr)
{
    AST::walk(this, expr->getLHS());
    AST::walk(this, expr->getRHS());
}

void ASTVisitor::visit(std::shared_ptr<ConditionalOperator> expr)
{
    AST::walk(this, expr->getCond());
    AST::walk(this, expr->getTrueExpr());
    AST::walk(this, expr->getFalseExpr());
}

void ASTVisitor::visit(std::shared_ptr<NullConditionalOperator> expr)
{
    AST::walk(this, expr->getCond());
    AST::walk(this, expr->getTrueExpr());
}

void ASTVisitor::visit(std::shared_ptr<IdentifierExpr> expr)
{
    AST::walk(this, expr->getIdentifier());
}

void ASTVisitor::visit(std::shared_ptr<ParenExpr> expr)
{
    AST::walk(this, expr->getSubExpr());
}

void ASTVisitor::visit(std::shared_ptr<MemberExpr> expr)
{
    AST::walk(this, expr->getBase());
    AST::walk(this, expr->getMemberDecl());
}

void ASTVisitor::visit(std::shared_ptr<SubscriptExpr> expr)
{
    AST::walk(this, expr->getBase());
    AST::walk(this, expr->getIndex());
}

void ASTVisitor::visit(std::shared_ptr<ArrayLiteral> expr)
{
    AST::walkChildren(this, expr->getInits());
}

void ASTVisitor::visit(std::shared_ptr<MapEntry> expr)
{
    AST::walk(this, expr->getKey());
    AST::walk(this, expr->getValue());
}

void ASTVisitor::visit(std::shared_ptr<MapLiteral> expr)
{
    AST::walkChildren(this, expr->getEntries());
}

void ASTVisitor::visit(std::shared_ptr<ImplicitConversionExpr> expr)
{
    AST::walk(this, expr->getSubExpr());
}

void ASTVisitor::visit(std::shared_ptr<SimpleIdentTypeRepr> repr)
{
    AST::walk(this, repr->getIdentifier());
}

void ASTVisitor::visit(std::shared_ptr<GenericIdentTypeRepr> repr)
{
    AST::walk(this, repr->getIdentifier());
    AST::walkChildren(this, repr->getArguments());
}

void ASTVisitor::visit(std::shared_ptr<OptionalTypeRepr> repr)
{
    AST::walk(this, repr->getBase());
}

} // namespace elma
