#include "Sema/InfiniteRecursion.h"
#include "AST/ASTVisitor.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Identifier.h"
#include "AST/Stmt.h"
#include "AST/Type.h"
#include "AST/TypeRepr.h"
#include "Basic/Diagnostic.h"
#include "Sema/Entity.h"
#include "Sema/TypeHelper.h"
#include <algorithm>
#include <cassert>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>

namespace elma {
namespace Sema {
namespace {

class RecursiveTypeChecker final : public ASTVisitor {
public:
    std::unordered_set<const Type*> visited;
    std::shared_ptr<Identifier> infiniteRecursion;

public:
    bool begin(std::shared_ptr<Node> node) override;
    void end(std::shared_ptr<Node> node) override;

    void error(const Location& l, const std::string& err);

    bool isVisited(const std::shared_ptr<ClassDecl>& decl) const;

    void visit(std::shared_ptr<VarDecl> decl) override;
    void visit(std::shared_ptr<FuncDecl> decl) override;
    void visit(std::shared_ptr<ClassDecl> decl) override;

    void visit(std::shared_ptr<SimpleIdentTypeRepr> repr) override;
    void visit(std::shared_ptr<GenericIdentTypeRepr> repr) override;
    void visit(std::shared_ptr<OptionalTypeRepr> repr) override;
};

bool RecursiveTypeChecker::isVisited(const std::shared_ptr<ClassDecl>& decl) const
{
    assert(decl);

    auto ident = decl->getIdentifier();
    assert(ident != nullptr);

    auto entity = ident->getEntity();
    assert(entity != nullptr);
    assert(entity->getKind() == EntityKind::Type);

    auto type = entity->getType();
    assert(type != nullptr);

    return (visited.find(type.get()) != std::end(visited));
}

bool RecursiveTypeChecker::begin(std::shared_ptr<Node> node)
{
    return (infiniteRecursion == nullptr);
}

void RecursiveTypeChecker::end(std::shared_ptr<Node> node)
{
    // NOTE: nothing to do
}

void RecursiveTypeChecker::visit(std::shared_ptr<VarDecl> decl)
{
    if (auto repr = decl->getTypeAnnotation()) {
        AST::walk(this, repr);
    }
}

void RecursiveTypeChecker::visit(std::shared_ptr<FuncDecl> decl)
{
    // NOTE: nothing to do
}

void RecursiveTypeChecker::visit(std::shared_ptr<ClassDecl> decl)
{
    assert(decl);

    auto ident = decl->getIdentifier();
    assert(ident != nullptr);

    auto entity = ident->getEntity();
    assert(entity != nullptr);
    assert(entity->getKind() == EntityKind::Type);

    auto type = entity->getType();
    assert(type != nullptr);

    if (visited.find(type.get()) != std::end(visited)) {
        infiniteRecursion = ident;
        return;
    }
    visited.emplace(type.get());

    for (auto& member : decl->getMembers()) {
        AST::walk(this, member);
    }
}

void RecursiveTypeChecker::visit(std::shared_ptr<SimpleIdentTypeRepr> repr)
{
    auto ident = repr->getIdentifier();
    assert(ident != nullptr);

    auto entity = ident->getEntity();
    assert(entity != nullptr);
    assert(entity->getKind() == EntityKind::Type);

    auto type = entity->getType();
    assert(type != nullptr);

    if (type->getKind() != TypeKind::ClassType) {
        return;
    }

    assert(type->getKind() == TypeKind::ClassType);
    auto classType = std::static_pointer_cast<ClassType>(type);

    if (visited.find(type.get()) != std::end(visited)) {
        infiniteRecursion = ident;
        return;
    }

    auto decl = classType->classDecl.lock();
    if (decl != nullptr) {
        AST::walk(this, decl);
    }
}

void RecursiveTypeChecker::visit(std::shared_ptr<GenericIdentTypeRepr> repr)
{
    auto ident = repr->getIdentifier();
    assert(ident != nullptr);

    auto entity = ident->getEntity();
    assert(entity != nullptr);
    assert(entity->getKind() == EntityKind::Type);

    auto baseType = entity->getType();
    assert(baseType != nullptr);

    if (TypeHelper::isArray(baseType) || TypeHelper::isMap(baseType)) {
        return;
    }

    AST::walk(this, repr->getIdentifier());
    for (auto& arg : repr->getArguments()) {
        AST::walk(this, arg);
    }
}

void RecursiveTypeChecker::visit(std::shared_ptr<OptionalTypeRepr> repr)
{
    // NOTE: nothing to do
}

} // end of anonymous namespace

std::shared_ptr<Identifier> findInfiniteRecursion(std::shared_ptr<ClassDecl> decl)
{
    RecursiveTypeChecker checker;
    AST::walk(&checker, decl);
    return checker.infiniteRecursion;
}

namespace {

class InfiniteRecursionChecker final : public ASTVisitor {
public:
    std::shared_ptr<DiagnosticHandler> diag;
    std::unordered_set<const Entity*> visited;
    const Entity* target = nullptr;
    std::shared_ptr<Identifier> infiniteRecursion;

public:
    bool begin(std::shared_ptr<Node> node) override;
    void visit(std::shared_ptr<Identifier> decl) override;
};

bool InfiniteRecursionChecker::begin(std::shared_ptr<Node> node)
{
    return (infiniteRecursion == nullptr);
}

void InfiniteRecursionChecker::visit(std::shared_ptr<Identifier> ident)
{
    auto entity = ident->getEntity();
    assert(entity != nullptr);

    if (entity->getKind() == EntityKind::Type) {
        return;
    }
    if (visited.find(entity.get()) != std::end(visited)) {
        return;
    }

    if (entity.get() == target) {
        infiniteRecursion = ident;
        return;
    }

    visited.emplace(entity.get());

    if (auto decl = entity->getDecl()) {
        AST::walk(this, decl);
    }
}

} // end of anonymous namespace

std::shared_ptr<Identifier> findInfiniteRecursion(std::shared_ptr<VarDecl> decl)
{
    auto expr = decl->getExpr();
    if (expr == nullptr) {
        return nullptr;
    }

    InfiniteRecursionChecker checker;

    auto ident = decl->getIdentifier();
    auto entity = ident->getEntity();
    checker.target = entity.get();

    AST::walk(&checker, expr);
    return checker.infiniteRecursion;
}

} // namespace Sema
} // namespace elma
