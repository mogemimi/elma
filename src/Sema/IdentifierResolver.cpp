#include "Sema/IdentifierResolver.h"
#include "AST/ASTContext.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Identifier.h"
#include "AST/Stmt.h"
#include "AST/Type.h"
#include "AST/TypeRepr.h"
#include "Basic/Diagnostic.h"
#include "Sema/Entity.h"
#include <cassert>
#include <utility>

namespace elma {
namespace {

bool hasScope(NodeKind kind)
{
    switch (kind) {
    case NodeKind::IfStmt:
    case NodeKind::WhileStmt:
    case NodeKind::ForStmt:
    case NodeKind::ForEachStmt: return true; break;
    default: break;
    }
    return false;
}

std::shared_ptr<Entity> makeBuiltinType(const std::string& name, BuiltinTypeKind kind)
{
    return Entity::makeType(name, std::make_shared<BuiltinType>(kind));
}

} // end of anonymous namespace

IdentifierResolver::IdentifierResolver(
    ASTContext* astContextIn,
    IdentifierContext* contextIn,
    const std::shared_ptr<DiagnosticHandler>& diagIn)
    : astContext(astContextIn)
    , context(contextIn)
    , diag(diagIn)
{
    assert(astContext != nullptr);
    assert(diag);

    auto scope = std::make_shared<Scope>();
    pushScope(scope);

    scope->insert(makeBuiltinType("Int", BuiltinTypeKind::Int));
    scope->insert(makeBuiltinType("Bool", BuiltinTypeKind::Bool));
    scope->insert(makeBuiltinType("Double", BuiltinTypeKind::Double));
    scope->insert(makeBuiltinType("String", BuiltinTypeKind::String));
    scope->insert(makeBuiltinType("Void", BuiltinTypeKind::Void));
    scope->insert(makeBuiltinType("Any", BuiltinTypeKind::Any));

    // TODO: Redesign entity lookup table for generic types such as Map<K, V> and Array<T>.
    scope->insert(Entity::makeType("Map", std::make_shared<MapType>()));
    scope->insert(Entity::makeType("Array", std::make_shared<ArrayType>()));
}

std::shared_ptr<Scope> IdentifierResolver::getCurrentScope()
{
    assert(!scopeStack.empty());
    return scopeStack.back();
}

void IdentifierResolver::pushScope(const std::shared_ptr<Scope>& scope)
{
    scopeStack.push_back(std::move(scope));
}

void IdentifierResolver::popScope()
{
    assert(!scopeStack.empty());
    scopeStack.pop_back();
}

void IdentifierResolver::error(const Location& l, const std::string& err)
{
    assert(diag);
    diag->error(l, err);
}

bool IdentifierResolver::begin(std::shared_ptr<Node> node)
{
    if (hasScope(node->getKind())) {
        auto scope = std::make_shared<Scope>(getCurrentScope());
        pushScope(scope);
    }
    return !diag->hasError();
}

void IdentifierResolver::end(std::shared_ptr<Node> node)
{
    if (hasScope(node->getKind())) {
        popScope();
    }
}

void IdentifierResolver::visit(std::shared_ptr<IdentifierExpr> expr)
{
    auto scope = getCurrentScope();
    assert(scope);

    auto decl = expr->getIdentifier();
    assert(decl);

    auto entity = scope->lookup(decl->getName());
    if (!entity) {
        // TODO: Please look for the unresolved identifiers from outside the file.
        astContext->unresolvedIdentifiers.push_back(decl);
        error(decl->getLocation(), "'" + decl->getName() + "' was not declared in this scope.");
        return;
    }

    decl->setEntity(entity);
}

void IdentifierResolver::visit(std::shared_ptr<VarDecl> decl)
{
    auto scope = getCurrentScope();
    assert(scope);

    auto ident = decl->getIdentifier();
    assert(ident);

    auto alt = scope->findAlt(ident->getName());
    if (alt) {
        error(ident->getLocation(), "'" + ident->getName() + "' redeclared in this block.");
        return;
    }

    auto entity = [&]() -> std::shared_ptr<Entity> {
        if (decl->getSpecifier() == VarDeclSpecifier::Const) {
            return Entity::makeConstant(ident->getName(), ident);
        }
        return Entity::makeVariable(ident->getName(), ident);
    }();
    scope->insert(entity);
    ident->setEntity(entity);

    if (context) {
        context->entities.push_back(entity);
    }

    ASTVisitor::visit(decl);
}

void IdentifierResolver::visit(std::shared_ptr<FuncDecl> decl)
{
    if (auto ident = decl->getIdentifier()) {
        auto scope = getCurrentScope();
        assert(scope);

        auto entity = Entity::makeVariable(ident->getName(), ident);
        scope->insert(entity);
        ident->setEntity(entity);

        if (context) {
            context->entities.push_back(entity);
        }
    }

    ASTVisitor::visit(decl);
}

void IdentifierResolver::visit(std::shared_ptr<ParamDecl> decl)
{
    auto scope = getCurrentScope();
    assert(scope);

    auto ident = decl->getIdentifier();
    assert(ident);
    assert(!ident->getName().empty());

    auto entity = Entity::makeVariable(ident->getName(), ident);
    scope->insert(entity);
    ident->setEntity(entity);

    if (context) {
        context->entities.push_back(entity);
    }

    ASTVisitor::visit(decl);
}

void IdentifierResolver::visit(std::shared_ptr<SimpleIdentTypeRepr> repr)
{
    auto scope = getCurrentScope();
    assert(scope);

    auto ident = repr->getIdentifier();
    assert(ident);

    auto type = scope->lookup(ident->getName());
    if (!type) {
        error(ident->getLocation(), "Cannot find name '" + ident->getName() + "'.");
        return;
    }
    if (type->getKind() != EntityKind::Type) {
        error(ident->getLocation(), "'" + ident->getName() + "' is not a type name.");
        return;
    }
    ident->setEntity(type);
}

void IdentifierResolver::visit(std::shared_ptr<GenericIdentTypeRepr> repr)
{
    auto scope = getCurrentScope();
    assert(scope);

    auto ident = repr->getIdentifier();
    assert(ident);

    auto isGenericTypeEnabled = [](const std::string& s) -> bool {
        if (s == "Map") {
            return true;
        }
        if (s == "Array") {
            return true;
        }
        return false;
    };
    if (!isGenericTypeEnabled(ident->getName())) {
        error(ident->getLocation(), "Type '" + ident->getName() + "' is not generic.");
        return;
    }

    auto type = scope->lookup(ident->getName());
    if (!type) {
        error(ident->getLocation(), "Cannot find name '" + ident->getName() + "'.");
        return;
    }

    if (type->getKind() != EntityKind::Type) {
        error(ident->getLocation(), "'" + ident->getName() + "' is not a type name.");
        return;
    }
    ident->setEntity(type);

    for (const auto& arg : repr->getArguments()) {
        AST::walk(this, arg);
    }
}

void IdentifierResolver::visit(std::shared_ptr<OptionalTypeRepr> repr)
{
    AST::walk(this, repr->getBase());
}

} // namespace elma
