#include "Sema/TypeResolver.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Identifier.h"
#include "AST/Stmt.h"
#include "AST/TypeRepr.h"
#include "Basic/Diagnostic.h"
#include "Sema/Entity.h"
#include "Sema/IdentifierResolver.h"
#include "Sema/TypeHelper.h"
#include "Sema/TypeReprResolver.h"
#include <algorithm>
#include <cassert>
#include <sstream>
#include <utility>

namespace elma {
namespace {

template <class ASTNode>
void substition(
    const std::shared_ptr<ASTNode>& ast,
    const std::shared_ptr<TypeVariable>& variable,
    const std::shared_ptr<Type>& type)
{
    if (variable == type) {
        return;
    }
    variable->setType(type);

    assert(ast->getType() == variable);
    ast->setType(type);
}

bool isSameType(const std::shared_ptr<Type>& a, const std::shared_ptr<Type>& b);

bool isSameTypeOrNull(const std::shared_ptr<Type>& a, const std::shared_ptr<Type>& b)
{
    if (a == nullptr) {
        return b == nullptr;
    }
    if (b == nullptr) {
        return false;
    }
    assert(a);
    assert(b);
    return isSameType(a, b);
}

bool isSameType(const std::shared_ptr<Type>& a, const std::shared_ptr<Type>& b)
{
    assert(a);
    assert(b);

    if (a->getKind() != b->getKind()) {
        return false;
    }

    switch (a->getKind()) {
    case TypeKind::TypeVariable: {
        const auto x = std::static_pointer_cast<TypeVariable>(a);
        const auto y = std::static_pointer_cast<TypeVariable>(b);
        assert(x);
        assert(y);
        return (x->getTypeID() == y->getTypeID());
    }
    case TypeKind::BuiltinType: {
        const auto x = std::static_pointer_cast<BuiltinType>(a);
        const auto y = std::static_pointer_cast<BuiltinType>(b);
        assert(x);
        assert(y);
        return (x->kind == y->kind);
    }
    case TypeKind::ArrayType: {
        assert(a->getKind() == TypeKind::ArrayType);
        assert(b->getKind() == TypeKind::ArrayType);
        const auto x = std::static_pointer_cast<ArrayType>(a);
        const auto y = std::static_pointer_cast<ArrayType>(b);
        assert(x);
        assert(y);
        return isSameTypeOrNull(x->primaryType, y->primaryType);
    }
    case TypeKind::MapType: {
        assert(a->getKind() == TypeKind::MapType);
        assert(b->getKind() == TypeKind::MapType);
        const auto x = std::static_pointer_cast<MapType>(a);
        const auto y = std::static_pointer_cast<MapType>(b);
        assert(x);
        assert(y);
        return isSameTypeOrNull(x->keyType, y->keyType) &&
               isSameTypeOrNull(x->valueType, y->valueType);
    }
    case TypeKind::OptionalType: {
        assert(a->getKind() == TypeKind::OptionalType);
        assert(b->getKind() == TypeKind::OptionalType);
        const auto x = std::static_pointer_cast<OptionalType>(a);
        const auto y = std::static_pointer_cast<OptionalType>(b);
        assert(x);
        assert(y);
        return isSameTypeOrNull(x->baseType, y->baseType);
    }
    case TypeKind::TupleType: {
        const auto x = std::static_pointer_cast<TupleType>(a);
        const auto y = std::static_pointer_cast<TupleType>(b);
        assert(x);
        assert(y);
        if (x->types.size() != y->types.size()) {
            return false;
        }
        for (size_t i = 0; i < x->types.size(); i++) {
            if (!isSameType(x->types[i], y->types[i])) {
                return false;
            }
        }
        return true;
    }
    case TypeKind::ClassType: {
        const auto x = std::static_pointer_cast<ClassType>(a);
        const auto y = std::static_pointer_cast<ClassType>(b);
        assert(x);
        assert(y);
        auto lhsDecl = x->classDecl.lock();
        auto rhsDecl = y->classDecl.lock();
        if (!lhsDecl || !rhsDecl) {
            return false;
        }
        auto lhsIdent = lhsDecl->getIdentifier();
        auto rhsIdent = rhsDecl->getIdentifier();
        if (!lhsIdent || !rhsIdent) {
            return false;
        }
        return lhsIdent->getName() == rhsIdent->getName();
    }
    case TypeKind::ReturnType:
        // TODO: not implemented
        return false;
    case TypeKind::FunctionType:
        // TODO: not implemented
        return false;
    }
    return false;
}

std::shared_ptr<Type> inferReturnType(const std::shared_ptr<TypeResolverScope>& scope)
{
    if (scope->returnTypes.empty()) {
        return std::make_shared<BuiltinType>(BuiltinTypeKind::Void);
    }
    auto candidate = TypeInferer::infer(scope->env, scope->returnTypes.front());
    assert(candidate);
    for (const auto& ret : scope->returnTypes) {
        auto t = TypeInferer::infer(scope->env, ret);
        if (!isSameType(candidate, t)) {
            // TODO: Not implemented
            // if (t->getKind() != TypeKind::TypeVariable) {
            //     error("Type mismatch");
            // }
            return std::make_shared<BuiltinType>(BuiltinTypeKind::Any);
        }
    }
    return candidate;
}

std::vector<std::shared_ptr<Type>>
getParameterTypes(const std::vector<std::shared_ptr<ParamDecl>>& parameters)
{
    std::vector<std::shared_ptr<Type>> parameterTypes;
    for (const auto& param : parameters) {
        assert(param);
        assert(param->getType());
        parameterTypes.push_back(param->getType());
    }
    return parameterTypes;
}

constexpr int anyBit = 0b0000001;
constexpr int intBit = 0b0000010;
constexpr int doubleBit = 0b0000100;
constexpr int boolBit = 0b0001000;
constexpr int stringBit = 0b0010000;

int toBinaryOpTypeCastBits(BuiltinTypeKind type)
{
    switch (type) {
    case BuiltinTypeKind::Any: return anyBit;
    case BuiltinTypeKind::Int: return intBit | doubleBit;
    case BuiltinTypeKind::Double: return doubleBit;
    case BuiltinTypeKind::Bool: return boolBit;
    case BuiltinTypeKind::String: return stringBit;
    case BuiltinTypeKind::Void: return 0b0;
    case BuiltinTypeKind::Null: return anyBit;
    }
    return anyBit;
}

enum class BinaryOpTypeCastResult {
    Resolved,
    ResolveOnRuntime,
    TypeMismatch,
};

std::tuple<BuiltinTypeKind, BinaryOpTypeCastResult>
inferBinaryOpTypeCast(BuiltinTypeKind a, BuiltinTypeKind b)
{
    const auto lhsBits = toBinaryOpTypeCastBits(a);
    const auto rhsBits = toBinaryOpTypeCastBits(b);

    if (((lhsBits | rhsBits) & anyBit) != 0) {
        return std::make_tuple(BuiltinTypeKind::Any, BinaryOpTypeCastResult::ResolveOnRuntime);
    }

    const auto castBits = lhsBits & rhsBits;
    if ((castBits & intBit) != 0) {
        return std::make_tuple(BuiltinTypeKind::Int, BinaryOpTypeCastResult::Resolved);
    }
    if ((castBits & doubleBit) != 0) {
        return std::make_tuple(BuiltinTypeKind::Double, BinaryOpTypeCastResult::Resolved);
    }
    if ((castBits & boolBit) != 0) {
        return std::make_tuple(BuiltinTypeKind::Bool, BinaryOpTypeCastResult::Resolved);
    }
    if ((castBits & stringBit) != 0) {
        return std::make_tuple(BuiltinTypeKind::String, BinaryOpTypeCastResult::Resolved);
    }

    return std::make_tuple(BuiltinTypeKind::Any, BinaryOpTypeCastResult::TypeMismatch);
}

template <class GetCond, class SetCond>
void ImplicitCastifyConditionExpr(
    const std::shared_ptr<TypeResolverScope>& scope,
    const std::shared_ptr<DiagnosticHandler>& diag,
    GetCond&& getCond,
    SetCond&& setCond)
{
    const auto condExpr = getCond();
    assert(condExpr);
    assert(condExpr->getType());

    const auto condType = TypeInferer::infer(scope->env, condExpr->getType());

    if (TypeHelper::isVoid(condType)) {
        diag->error(
            condExpr->getLocation(),
            "cond is '" + BuiltinType::toString(BuiltinTypeKind::Void) + "' type.");
        return;
    }

    if (!TypeHelper::isStaticallyResolved(condType) || !TypeHelper::isAny(condType)) {
        // NOTE: resolving type on runtime, so this process is skipped
        return;
    }

    if (TypeHelper::isBoolean(condType)) {
        // NOTE: The operator doesn't need to implicitly cast types of operands.
        return;
    }

    auto typeCastExpr = std::make_shared<ImplicitConversionExpr>(condExpr->getLocation(), condExpr);
    typeCastExpr->setType(std::make_shared<BuiltinType>(BuiltinTypeKind::Bool));
    setCond(typeCastExpr);
}

using TypeCapability = uint64_t;
constexpr uint64_t hasBinaryExprAdd = 0b00000000000000001;
constexpr uint64_t hasBinaryExprSubtract = 0b00000000000000010;
constexpr uint64_t hasBinaryExprMultiply = 0b00000000000000100;
constexpr uint64_t hasBinaryExprDivide = 0b00000000000001000;
constexpr uint64_t hasBinaryExprMod = 0b00000000000010000;
constexpr uint64_t hasBinaryExprEqual = 0b00000000001000000;
constexpr uint64_t hasBinaryExprNotEqual = 0b00000000010000000;
constexpr uint64_t hasBinaryExprLogicalAnd = 0b00000000100000000;
constexpr uint64_t hasBinaryExprLogicalOr = 0b00000001000000000;
constexpr uint64_t hasBinaryExprGreaterThan = 0b00000010000000000;
constexpr uint64_t hasBinaryExprGreaterThanOrEqual = 0b00000100000000000;
constexpr uint64_t hasBinaryExprLessThan = 0b00001000000000000;
constexpr uint64_t hasBinaryExprLessThanOrEqual = 0b00010000000000000;
constexpr uint64_t hasBinaryExprNullCoalescing = 0b00100000000000000;

constexpr TypeCapability disableMask(TypeCapability c, uint64_t mask)
{
    return c & (~mask);
}

constexpr TypeCapability enableMask(TypeCapability c, uint64_t mask)
{
    return c | mask;
}

TypeCapability getTypeCapability(BuiltinTypeKind type)
{
    TypeCapability c = 0;
    switch (type) {
    case BuiltinTypeKind::Any:
        c = enableMask(c, hasBinaryExprAdd);
        c = enableMask(c, hasBinaryExprSubtract);
        c = enableMask(c, hasBinaryExprMultiply);
        c = enableMask(c, hasBinaryExprDivide);
        c = enableMask(c, hasBinaryExprMod);
        c = enableMask(c, hasBinaryExprEqual);
        c = enableMask(c, hasBinaryExprNotEqual);
        c = enableMask(c, hasBinaryExprLogicalAnd);
        c = enableMask(c, hasBinaryExprLogicalOr);
        c = enableMask(c, hasBinaryExprGreaterThan);
        c = enableMask(c, hasBinaryExprGreaterThanOrEqual);
        c = enableMask(c, hasBinaryExprLessThan);
        c = enableMask(c, hasBinaryExprLessThanOrEqual);
        break;
    case BuiltinTypeKind::Bool:
        c = disableMask(c, hasBinaryExprAdd);
        c = disableMask(c, hasBinaryExprSubtract);
        c = disableMask(c, hasBinaryExprMultiply);
        c = disableMask(c, hasBinaryExprDivide);
        c = disableMask(c, hasBinaryExprMod);
        c = enableMask(c, hasBinaryExprEqual);
        c = enableMask(c, hasBinaryExprNotEqual);
        c = enableMask(c, hasBinaryExprLogicalAnd);
        c = enableMask(c, hasBinaryExprLogicalOr);
        c = disableMask(c, hasBinaryExprGreaterThan);
        c = disableMask(c, hasBinaryExprGreaterThanOrEqual);
        c = disableMask(c, hasBinaryExprLessThan);
        c = disableMask(c, hasBinaryExprLessThanOrEqual);
        break;
    case BuiltinTypeKind::Double:
        c = enableMask(c, hasBinaryExprAdd);
        c = enableMask(c, hasBinaryExprSubtract);
        c = enableMask(c, hasBinaryExprMultiply);
        c = enableMask(c, hasBinaryExprDivide);
        c = disableMask(c, hasBinaryExprMod);
        c = enableMask(c, hasBinaryExprEqual);
        c = enableMask(c, hasBinaryExprNotEqual);
        c = enableMask(c, hasBinaryExprLogicalAnd);
        c = enableMask(c, hasBinaryExprLogicalOr);
        c = enableMask(c, hasBinaryExprGreaterThan);
        c = enableMask(c, hasBinaryExprGreaterThanOrEqual);
        c = enableMask(c, hasBinaryExprLessThan);
        c = enableMask(c, hasBinaryExprLessThanOrEqual);
        break;
    case BuiltinTypeKind::Int:
        c = enableMask(c, hasBinaryExprAdd);
        c = enableMask(c, hasBinaryExprSubtract);
        c = enableMask(c, hasBinaryExprMultiply);
        c = enableMask(c, hasBinaryExprDivide);
        c = enableMask(c, hasBinaryExprMod);
        c = enableMask(c, hasBinaryExprEqual);
        c = enableMask(c, hasBinaryExprNotEqual);
        c = enableMask(c, hasBinaryExprLogicalAnd);
        c = enableMask(c, hasBinaryExprLogicalOr);
        c = enableMask(c, hasBinaryExprGreaterThan);
        c = enableMask(c, hasBinaryExprGreaterThanOrEqual);
        c = enableMask(c, hasBinaryExprLessThan);
        c = enableMask(c, hasBinaryExprLessThanOrEqual);
        break;
    case BuiltinTypeKind::Null:
        c = disableMask(c, hasBinaryExprAdd);
        c = disableMask(c, hasBinaryExprSubtract);
        c = disableMask(c, hasBinaryExprMultiply);
        c = disableMask(c, hasBinaryExprDivide);
        c = disableMask(c, hasBinaryExprMod);
        c = disableMask(c, hasBinaryExprEqual);
        c = disableMask(c, hasBinaryExprNotEqual);
        c = disableMask(c, hasBinaryExprLogicalAnd);
        c = disableMask(c, hasBinaryExprLogicalOr);
        c = disableMask(c, hasBinaryExprGreaterThan);
        c = disableMask(c, hasBinaryExprGreaterThanOrEqual);
        c = disableMask(c, hasBinaryExprLessThan);
        c = disableMask(c, hasBinaryExprLessThanOrEqual);
        break;
    case BuiltinTypeKind::String:
        c = enableMask(c, hasBinaryExprAdd);
        c = disableMask(c, hasBinaryExprSubtract);
        c = disableMask(c, hasBinaryExprMultiply);
        c = disableMask(c, hasBinaryExprDivide);
        c = disableMask(c, hasBinaryExprMod);
        c = enableMask(c, hasBinaryExprEqual);
        c = enableMask(c, hasBinaryExprNotEqual);
        c = disableMask(c, hasBinaryExprLogicalAnd);
        c = disableMask(c, hasBinaryExprLogicalOr);
        c = disableMask(c, hasBinaryExprGreaterThan);
        c = disableMask(c, hasBinaryExprGreaterThanOrEqual);
        c = disableMask(c, hasBinaryExprLessThan);
        c = disableMask(c, hasBinaryExprLessThanOrEqual);
        break;
    case BuiltinTypeKind::Void:
        c = disableMask(c, hasBinaryExprAdd);
        c = disableMask(c, hasBinaryExprSubtract);
        c = disableMask(c, hasBinaryExprMultiply);
        c = disableMask(c, hasBinaryExprDivide);
        c = disableMask(c, hasBinaryExprMod);
        c = disableMask(c, hasBinaryExprEqual);
        c = disableMask(c, hasBinaryExprNotEqual);
        c = disableMask(c, hasBinaryExprLogicalAnd);
        c = disableMask(c, hasBinaryExprLogicalOr);
        c = disableMask(c, hasBinaryExprGreaterThan);
        c = disableMask(c, hasBinaryExprGreaterThanOrEqual);
        c = disableMask(c, hasBinaryExprLessThan);
        c = disableMask(c, hasBinaryExprLessThanOrEqual);
        break;
    }
    return c;
}

TypeCapability getTypeCapability(const std::shared_ptr<Type>& type)
{
    TypeCapability c = 0;
    switch (type->getKind()) {
    case TypeKind::BuiltinType: {
        auto t = std::static_pointer_cast<BuiltinType>(type);
        assert(t == std::dynamic_pointer_cast<BuiltinType>(type));
        c = getTypeCapability(t->kind);
        break;
    }
    case TypeKind::ArrayType:
    case TypeKind::MapType:
    case TypeKind::OptionalType:
    case TypeKind::TupleType:
    case TypeKind::ClassType:
    case TypeKind::FunctionType: {
        c = disableMask(c, hasBinaryExprAdd);
        c = disableMask(c, hasBinaryExprSubtract);
        c = disableMask(c, hasBinaryExprMultiply);
        c = disableMask(c, hasBinaryExprDivide);
        c = disableMask(c, hasBinaryExprMod);
        c = enableMask(c, hasBinaryExprEqual);
        c = enableMask(c, hasBinaryExprNotEqual);
        c = disableMask(c, hasBinaryExprLogicalAnd);
        c = disableMask(c, hasBinaryExprLogicalOr);
        c = disableMask(c, hasBinaryExprGreaterThan);
        c = disableMask(c, hasBinaryExprGreaterThanOrEqual);
        c = disableMask(c, hasBinaryExprLessThan);
        c = disableMask(c, hasBinaryExprLessThanOrEqual);
        break;
    }
    case TypeKind::TypeVariable:
    case TypeKind::ReturnType: {
        c = enableMask(c, hasBinaryExprAdd);
        c = enableMask(c, hasBinaryExprSubtract);
        c = enableMask(c, hasBinaryExprMultiply);
        c = enableMask(c, hasBinaryExprDivide);
        c = enableMask(c, hasBinaryExprMod);
        c = enableMask(c, hasBinaryExprEqual);
        c = enableMask(c, hasBinaryExprNotEqual);
        c = enableMask(c, hasBinaryExprLogicalAnd);
        c = enableMask(c, hasBinaryExprLogicalOr);
        c = enableMask(c, hasBinaryExprGreaterThan);
        c = enableMask(c, hasBinaryExprGreaterThanOrEqual);
        c = enableMask(c, hasBinaryExprLessThan);
        c = enableMask(c, hasBinaryExprLessThanOrEqual);
        break;
    }
    }
    return c;
}

uint64_t binaryOperatorMask(BinaryExprKind op)
{
    switch (op) {
    case BinaryExprKind::Add: return hasBinaryExprAdd;
    case BinaryExprKind::Subtract: return hasBinaryExprSubtract;
    case BinaryExprKind::Multiply: return hasBinaryExprMultiply;
    case BinaryExprKind::Divide: return hasBinaryExprDivide;
    case BinaryExprKind::Mod: return hasBinaryExprMod;
    case BinaryExprKind::Equal: return hasBinaryExprEqual;
    case BinaryExprKind::NotEqual: return hasBinaryExprNotEqual;
    case BinaryExprKind::LogicalAnd: return hasBinaryExprLogicalAnd;
    case BinaryExprKind::LogicalOr: return hasBinaryExprLogicalOr;
    case BinaryExprKind::GreaterThan: return hasBinaryExprGreaterThan;
    case BinaryExprKind::GreaterThanOrEqual: return hasBinaryExprGreaterThanOrEqual;
    case BinaryExprKind::LessThan: return hasBinaryExprLessThan;
    case BinaryExprKind::LessThanOrEqual: return hasBinaryExprLessThanOrEqual;
    case BinaryExprKind::NullCoalescing: return hasBinaryExprNullCoalescing;
    }
    return 0;
}

bool isBinaryExprValid(BinaryExprKind op, const std::shared_ptr<Type>& type)
{
    const auto mask = binaryOperatorMask(op);
    return (getTypeCapability(type) & mask) != 0;
}

std::string getDiagnosticString(const std::shared_ptr<Type>& type)
{
    switch (type->getKind()) {
    case TypeKind::BuiltinType:
    case TypeKind::ArrayType:
    case TypeKind::MapType:
    case TypeKind::OptionalType:
    case TypeKind::TupleType:
    case TypeKind::ClassType:
    case TypeKind::FunctionType:
    case TypeKind::ReturnType: break;
    case TypeKind::TypeVariable: return BuiltinType::toString(BuiltinTypeKind::Any);
    }
    return type->dump();
}

std::shared_ptr<TypeResolverScope> makeScope(const std::shared_ptr<TypeResolverScope>& outerScope)
{
    auto scope = std::make_shared<TypeResolverScope>();
    scope->env = outerScope->env;
    return scope;
}

} // end of anonymous namespace

TypeResolver::TypeResolver(const std::shared_ptr<DiagnosticHandler>& diagIn)
    : diag(diagIn)
{
    assert(diag);
    auto scope = std::make_shared<TypeResolverScope>();
    pushScope(scope);
}

std::shared_ptr<TypeResolverScope> TypeResolver::getCurrentScope()
{
    assert(!scopeStack.empty());
    return scopeStack.back();
}

void TypeResolver::pushScope(const std::shared_ptr<TypeResolverScope>& scope)
{
    scopeStack.push_back(std::move(scope));
}

void TypeResolver::popScope()
{
    assert(!scopeStack.empty());
    scopeStack.pop_back();
}

void TypeResolver::error(const Location& l, const std::string& err)
{
    assert(diag);
    diag->error(l, err);
}

void TypeResolver::visit(std::shared_ptr<ReturnStmt> stmt)
{
    const auto scope = getCurrentScope();

    ASTVisitor::visit(stmt);

    if (diag->hasError()) {
        return;
    }

    // TODO: Support for checking tuples as return multiple values
    if (scope->expectReturnType != nullptr) {
        if (TypeHelper::isVoid(scope->expectReturnType)) {
            if (stmt->getExpr() != nullptr) {
                error(stmt->getLocation(), "too many arguments to return.");
                return;
            }
        }
        else {
            if (stmt->getExpr() == nullptr) {
                error(stmt->getLocation(), "not enough arguments to return.");
                return;
            }
        }
    }

    if (auto expr = stmt->getExpr()) {
        assert(expr->getType());
        scope->returnTypes.push_back(expr->getType());
    }
}

void TypeResolver::visit(std::shared_ptr<IfStmt> stmt)
{
    ASTVisitor::visit(stmt);

    const auto scope = getCurrentScope();

    ImplicitCastifyConditionExpr(
        scope, diag, [&] { return stmt->getCond(); }, [&](auto cond) { stmt->setCond(cond); });
    if (diag->hasError()) {
        return;
    }
}

void TypeResolver::visit(std::shared_ptr<WhileStmt> stmt)
{
    ASTVisitor::visit(stmt);

    const auto scope = getCurrentScope();

    ImplicitCastifyConditionExpr(
        scope, diag, [&] { return stmt->getCond(); }, [&](auto cond) { stmt->setCond(cond); });
    if (diag->hasError()) {
        return;
    }
}

void TypeResolver::visit(std::shared_ptr<ForStmt> stmt)
{
    ASTVisitor::visit(stmt);

    const auto scope = getCurrentScope();

    ImplicitCastifyConditionExpr(
        scope, diag, [&] { return stmt->getCond(); }, [&](auto cond) { stmt->setCond(cond); });
    if (diag->hasError()) {
        return;
    }
}

void TypeResolver::visit(std::shared_ptr<IntegerLiteral> expr)
{
    ASTVisitor::visit(expr);

    assert(!expr->getType());
    expr->setType(std::make_shared<BuiltinType>(BuiltinTypeKind::Int));
}

void TypeResolver::visit(std::shared_ptr<DoubleLiteral> expr)
{
    ASTVisitor::visit(expr);

    assert(!expr->getType());
    expr->setType(std::make_shared<BuiltinType>(BuiltinTypeKind::Double));
}

void TypeResolver::visit(std::shared_ptr<BoolLiteral> expr)
{
    ASTVisitor::visit(expr);

    assert(!expr->getType());
    expr->setType(std::make_shared<BuiltinType>(BuiltinTypeKind::Bool));
}

void TypeResolver::visit(std::shared_ptr<StringLiteral> expr)
{
    ASTVisitor::visit(expr);

    assert(!expr->getType());
    expr->setType(std::make_shared<BuiltinType>(BuiltinTypeKind::String));
}

void TypeResolver::visit(std::shared_ptr<NullLiteral> expr)
{
    ASTVisitor::visit(expr);

    assert(!expr->getType());
    expr->setType(std::make_shared<BuiltinType>(BuiltinTypeKind::Null));
}

void TypeResolver::visit(std::shared_ptr<IdentifierExpr> expr)
{
    ASTVisitor::visit(expr);

    assert(!expr->getType());

    auto ident = expr->getIdentifier();
    assert(ident);

    auto entity = ident->getEntity();
    assert(entity);
    assert(
        (entity->getKind() == EntityKind::Var) || (entity->getKind() == EntityKind::Const) ||
        (entity->getKind() == EntityKind::Func));

    auto type = entity->getType();
    assert(type != nullptr);
    expr->setType(type);
}

void TypeResolver::visit(std::shared_ptr<ParenExpr> expr)
{
    ASTVisitor::visit(expr);

    assert(!expr->getType());
    auto subExpr = expr->getSubExpr();
    assert(subExpr);
    expr->setType(subExpr->getType());
}

void TypeResolver::visit(std::shared_ptr<UnaryExpr> expr)
{
    const auto outerScope = getCurrentScope();
    const auto scope = makeScope(outerScope);
    pushScope(scope);

    ASTVisitor::visit(expr);
    popScope();

    const auto subExpr = expr->getSubExpr();
    assert(subExpr);
    assert(subExpr->getType());

    const auto t = TypeInferer::infer(scope->env, subExpr->getType());
    assert(t);

    switch (expr->getOpcode()) {
    case UnaryExprKind::Plus:
    case UnaryExprKind::Minus:
    case UnaryExprKind::PostDec:
    case UnaryExprKind::PreDec:
    case UnaryExprKind::PostInc:
    case UnaryExprKind::PreInc:
        if (TypeHelper::isFloat(t) || TypeHelper::isInteger(t)) {
            assert(!expr->getType());
            expr->setType(t);
            return;
        }
        break;
    case UnaryExprKind::LogicalNot: {
        ImplicitCastifyConditionExpr(
            scope,
            diag,
            [&] { return expr->getSubExpr(); },
            [&](auto cond) { expr->setSubExpr(cond); });

        if (TypeHelper::isBoolean(t)) {
            assert(!expr->getType());
            expr->setType(t);
            return;
        }
        expr->setType(std::make_shared<BuiltinType>(BuiltinTypeKind::Bool));
        return;
        break;
    }
    }
    assert(!expr->getType());
    expr->setType(subExpr->getType());
}

void TypeResolver::visit(std::shared_ptr<BinaryExpr> expr)
{
    ASTVisitor::visit(expr);

    if (diag->hasError()) {
        return;
    }

    if (expr->isEqualityOp() || expr->isComparisonOp() || expr->isLogicalOp()) {
        assert(!expr->getType());
        expr->setType(std::make_shared<BuiltinType>(BuiltinTypeKind::Bool));
        return;
    }

    auto lhs = expr->getLHS();
    auto rhs = expr->getRHS();
    assert(lhs);
    assert(rhs);
    assert(lhs->getType());
    assert(rhs->getType());

    const auto scope = getCurrentScope();
    const auto lhsTypeInferred = TypeInferer::infer(scope->env, lhs->getType());
    const auto rhsTypeInferred = TypeInferer::infer(scope->env, rhs->getType());

    if (!isBinaryExprValid(expr->getOpcode(), lhsTypeInferred)) {
        error(
            lhs->getLocation(),
            "invalid operands to binary expression ('" + getDiagnosticString(lhsTypeInferred) +
                "' and '" + getDiagnosticString(rhsTypeInferred) + "').");
        return;
    }
    if (!isBinaryExprValid(expr->getOpcode(), rhsTypeInferred)) {
        error(
            rhs->getLocation(),
            "invalid operands to binary expression ('" + getDiagnosticString(lhsTypeInferred) +
                "' and '" + getDiagnosticString(rhsTypeInferred) + "').");
        return;
    }

    const auto [lhsType, lhsTypeEnabled] = TypeHelper::toBuiltinType(lhsTypeInferred);
    const auto [rhsType, rhsTypeEnabled] = TypeHelper::toBuiltinType(rhsTypeInferred);

    if (TypeHelper::isVoid(lhsTypeInferred)) {
        error(
            lhs->getLocation(),
            "lhs is '" + BuiltinType::toString(BuiltinTypeKind::Void) + "' type.");
        return;
    }
    if (TypeHelper::isVoid(rhsTypeInferred)) {
        error(
            rhs->getLocation(),
            "rhs is '" + BuiltinType::toString(BuiltinTypeKind::Void) + "' type.");
        return;
    }

    if (lhsTypeInferred->getKind() == TypeKind::MapType) {
        if (rhsTypeInferred->getKind() == TypeKind::MapType) {
            // NOTE: The operator doesn't need to implicitly cast types of operands.
            assert(!expr->getType());
            expr->setType(lhs->getType());
            return;
        }
        error(
            expr->getLocation(),
            "Operator '" + BinaryExpr::toString(expr->getOpcode()) +
                "' cannot be applied to types '" + getDiagnosticString(lhsTypeInferred) +
                "' and '" + getDiagnosticString(rhsTypeInferred) + "'.");
        return;
    }
    if (lhsTypeInferred->getKind() == TypeKind::ArrayType) {
        if (rhsTypeInferred->getKind() == TypeKind::ArrayType) {
            // NOTE: The operator doesn't need to implicitly cast types of operands.
            assert(!expr->getType());
            expr->setType(lhs->getType());
            return;
        }
        error(
            expr->getLocation(),
            "Operator '" + BinaryExpr::toString(expr->getOpcode()) +
                "' cannot be applied to types '" + getDiagnosticString(lhsTypeInferred) +
                "' and '" + getDiagnosticString(rhsTypeInferred) + "'.");
        return;
    }

    if (!lhsTypeEnabled || !rhsTypeEnabled) {
        // NOTE: resolving types on runtime, so this process is skipped
        assert(!expr->getType());
        expr->setType(std::make_shared<BuiltinType>(BuiltinTypeKind::Any));
        return;
    }

    if (lhsType == rhsType) {
        // NOTE: The operator doesn't need to implicitly cast types of operands.
        assert(!expr->getType());
        expr->setType(lhs->getType());
        return;
    }

    const auto [castType, castResult] = inferBinaryOpTypeCast(lhsType, rhsType);
    assert(castType != BuiltinTypeKind::Void);

    if (castResult == BinaryOpTypeCastResult::TypeMismatch) {
        error(
            expr->getLocation(),
            "Operator '" + BinaryExpr::toString(expr->getOpcode()) +
                "' cannot be applied to types '" + lhsTypeInferred->dump() + "' and '" +
                rhsTypeInferred->dump() + "'.");
        return;
    }

    if (castResult == BinaryOpTypeCastResult::ResolveOnRuntime) {
        // NOTE: resolving types on runtime, so this process is skipped
        assert(!expr->getType());
        expr->setType(std::make_shared<BuiltinType>(BuiltinTypeKind::Any));
        return;
    }

    if (lhsType != castType) {
        assert(rhsType == castType);
        auto typeCastExpr = std::make_shared<ImplicitConversionExpr>(lhs->getLocation(), lhs);
        typeCastExpr->setType(std::make_shared<BuiltinType>(castType));
        expr->setLHS(typeCastExpr);
        lhs = typeCastExpr;
    }
    else {
        assert(rhsType != castType);
        assert(lhsType == castType);
        auto typeCastExpr = std::make_shared<ImplicitConversionExpr>(rhs->getLocation(), rhs);
        typeCastExpr->setType(std::make_shared<BuiltinType>(castType));
        expr->setRHS(typeCastExpr);
        rhs = typeCastExpr;
    }

    assert(!expr->getType());
    expr->setType(lhs->getType());
}

void TypeResolver::visit(std::shared_ptr<AssignExpr> expr)
{
    ASTVisitor::visit(expr);

    if (diag->hasError()) {
        return;
    }

    auto lhs = expr->getLHS();
    auto rhs = expr->getRHS();
    assert(lhs);
    assert(rhs);
    assert(lhs->getType());
    assert(rhs->getType());

    const auto scope = getCurrentScope();
    const auto lhsTypeInferred = TypeInferer::infer(scope->env, lhs->getType());
    const auto rhsTypeInferred = TypeInferer::infer(scope->env, rhs->getType());

    const auto [lhsType, lhsTypeEnabled] = TypeHelper::toBuiltinType(lhsTypeInferred);
    const auto [rhsType, rhsTypeEnabled] = TypeHelper::toBuiltinType(rhsTypeInferred);

    if (TypeHelper::isVoid(lhsTypeInferred)) {
        error(
            lhs->getLocation(),
            "lhs is '" + BuiltinType::toString(BuiltinTypeKind::Void) + "' type.");
        return;
    }
    if (TypeHelper::isVoid(rhsTypeInferred)) {
        error(
            rhs->getLocation(),
            "rhs is '" + BuiltinType::toString(BuiltinTypeKind::Void) + "' type.");
        return;
    }

    if (lhsTypeInferred->getKind() == TypeKind::MapType) {
        if (rhsTypeInferred->getKind() == TypeKind::MapType) {
            // NOTE: The operator doesn't need to implicitly cast types of operands.
            assert(!expr->getType());
            expr->setType(lhs->getType());
            return;
        }
        error(
            expr->getLocation(),
            "Operator '" + AssignExpr::toString(expr->getOpcode()) +
                "' cannot be applied to types '" + getDiagnosticString(lhsTypeInferred) +
                "' and '" + getDiagnosticString(rhsTypeInferred) + "'.");
        return;
    }
    if (lhsTypeInferred->getKind() == TypeKind::ArrayType) {
        if (rhsTypeInferred->getKind() == TypeKind::ArrayType) {
            // NOTE: The operator doesn't need to implicitly cast types of operands.
            assert(!expr->getType());
            expr->setType(lhs->getType());
            return;
        }
        error(
            expr->getLocation(),
            "Operator '" + AssignExpr::toString(expr->getOpcode()) +
                "' cannot be applied to types '" + getDiagnosticString(lhsTypeInferred) +
                "' and '" + getDiagnosticString(rhsTypeInferred) + "'.");
        return;
    }

    if (!lhsTypeEnabled || !rhsTypeEnabled) {
        // NOTE: resolving types on runtime, so this process is skipped
        assert(!expr->getType());
        expr->setType(std::make_shared<BuiltinType>(BuiltinTypeKind::Any));
        return;
    }

    if (lhsType == rhsType) {
        // NOTE: The operator doesn't need to implicitly cast types of operands.
        assert(!expr->getType());
        expr->setType(lhs->getType());
        return;
    }

    const auto [castType, castResult] = inferBinaryOpTypeCast(lhsType, rhsType);
    assert(castType != BuiltinTypeKind::Void);

    if (castResult == BinaryOpTypeCastResult::TypeMismatch) {
        assert(lhsTypeInferred);
        assert(rhsTypeInferred);
        error(
            expr->getLocation(),
            "Type '" + rhsTypeInferred->dump() + "' is not assignable to '" +
                lhsTypeInferred->dump() + "'.");
        return;
    }

    if (castResult == BinaryOpTypeCastResult::ResolveOnRuntime) {
        // NOTE: resolving types on runtime, so this process is skipped
        assert(!expr->getType());

        expr->setType(lhs->getType());
        return;
    }

    if (lhsType != castType) {
        assert(lhsTypeInferred);
        assert(rhsTypeInferred);
        error(
            expr->getLocation(),
            "Type '" + rhsTypeInferred->dump() + "' is not assignable to '" +
                lhsTypeInferred->dump() + "'.");
        return;
    }
    else {
        assert(rhsType != castType);
        assert(lhsType == castType);
        auto typeCastExpr = std::make_shared<ImplicitConversionExpr>(rhs->getLocation(), rhs);
        typeCastExpr->setType(std::make_shared<BuiltinType>(castType));
        expr->setRHS(typeCastExpr);
        rhs = typeCastExpr;
    }

    assert(!expr->getType());
    expr->setType(lhs->getType());
}

void TypeResolver::visit(std::shared_ptr<MemberExpr> expr)
{
    ASTVisitor::visit(expr);

    const auto base = expr->getBase();
    assert(base);

    const auto baseType = base->getType();
    assert(baseType);

    const auto memberDecl = expr->getMemberDecl();
    assert(memberDecl);

    const auto memberName = memberDecl->getName();
    assert(!memberName.empty());

    if (!TypeHelper::isStaticallyResolved(baseType)) {
        expr->setType(std::make_shared<BuiltinType>(BuiltinTypeKind::Any));
        return;
    }
    assert(!TypeHelper::isAny(baseType));

    if (baseType->getKind() == TypeKind::BuiltinType) {
        error(
            expr->getLocation(),
            "Type '" + baseType->dump() + "' has no member '" + memberName + "'.");
        return;
    }
    if (baseType->getKind() != TypeKind::ClassType) {
        error(
            expr->getLocation(),
            "Type '" + baseType->dump() + "' has no member '" + memberName + "'.");
        return;
    }
    assert(baseType->getKind() == TypeKind::ClassType);

    auto classType = std::static_pointer_cast<ClassType>(baseType);
    auto classDecl = classType->classDecl.lock();
    assert(classDecl);

    auto members = classDecl->getMembers();

    auto iter = std::find_if(
        std::begin(members), std::end(members), [&](const std::shared_ptr<Decl>& member) {
            assert(member);
            switch (member->getKind()) {
            case NodeKind::VarDecl: {
                auto decl = std::static_pointer_cast<VarDecl>(member);
                auto ident = decl->getIdentifier();
                assert(ident);
                return ident->getName() == memberName;
                break;
            }
            case NodeKind::FuncDecl: {
                auto decl = std::static_pointer_cast<FuncDecl>(member);
                auto ident = decl->getIdentifier();
                assert(ident);
                return ident->getName() == memberName;
                break;
            }
            default: break;
            }
            return false;
        });

    if (iter == std::end(members)) {
        error(
            expr->getLocation(),
            "Type '" + baseType->dump() + "' has no member '" + memberName + "'.");
        return;
    }

    auto member = *iter;
    switch (member->getKind()) {
    case NodeKind::VarDecl: {
        auto decl = std::static_pointer_cast<VarDecl>(member);
        auto ident = decl->getIdentifier();
        assert(ident);
        assert(ident->getEntity());
        assert(ident->getEntity()->getType());
        expr->setType(ident->getEntity()->getType());
        break;
    }
    case NodeKind::FuncDecl: {
        auto decl = std::static_pointer_cast<FuncDecl>(member);
        auto ident = decl->getIdentifier();
        assert(ident);
        assert(ident->getEntity());
        assert(ident->getEntity()->getType());
        expr->setType(ident->getEntity()->getType());
        break;
    }
    default: break;
    }

    assert(expr->getType() != nullptr);
}

void TypeResolver::visit(std::shared_ptr<SubscriptExpr> expr)
{
    ASTVisitor::visit(expr);

    assert(expr->getBase());
    assert(expr->getIndex());

    auto baseType = expr->getBase()->getType();
    assert(baseType);

    auto indexType = expr->getIndex()->getType();
    assert(indexType);

    switch (baseType->getKind()) {
    case TypeKind::ArrayType: {
        auto arrayType = std::static_pointer_cast<ArrayType>(baseType);
        assert(arrayType == std::dynamic_pointer_cast<ArrayType>(baseType));

        if (arrayType->primaryType) {
            expr->setType(arrayType->primaryType);
            return;
        }
        break;
    }
    case TypeKind::MapType: {
        auto mapType = std::static_pointer_cast<MapType>(baseType);
        assert(mapType == std::dynamic_pointer_cast<MapType>(baseType));

        if (mapType->valueType) {
            expr->setType(mapType->valueType);
            return;
        }
        break;
    }
    default: break;
    }

    // TODO: Not implemented for class/struct
    expr->setType(std::make_shared<BuiltinType>(BuiltinTypeKind::Any));
}

void TypeResolver::visit(std::shared_ptr<ArrayLiteral> expr)
{
    ASTVisitor::visit(expr);

    assert(!expr->getType());

    auto arrayType = std::make_shared<ArrayType>();
    auto scope = getCurrentScope();

    for (auto& init : expr->getInits()) {
        auto t = init->getType();
        if (t->getKind() == TypeKind::TypeVariable) {
            auto typeVariable = std::dynamic_pointer_cast<TypeVariable>(t);
            auto s = TypeInferer::infer(scope->env, t);
            substition(init, typeVariable, s);
        }
    }

    if (!expr->getInits().empty()) {
        // TODO: Use union type instead of type of first element
        auto first = expr->getInits().front();
        auto primaryType = first->getType();
        for (auto& init : expr->getInits()) {
            if (primaryType == init->getType()) {
                continue;
            }
            if (!isSameType(primaryType, init->getType())) {
                primaryType = nullptr;
                break;
            }
        }
        arrayType->primaryType = primaryType;
    }

    expr->setType(arrayType);
}

void TypeResolver::visit(std::shared_ptr<MapEntry> expr)
{
    ASTVisitor::visit(expr);

    assert(!expr->getType());

    auto key = expr->getKey();
    auto value = expr->getValue();

    assert(key);
    assert(key->getType());
    assert(value);
    assert(value->getType());

    auto scope = getCurrentScope();

    auto infer = [&](std::shared_ptr<Expr>& ast) {
        auto t = ast->getType();
        if (t->getKind() == TypeKind::TypeVariable) {
            auto typeVariable = std::dynamic_pointer_cast<TypeVariable>(t);
            auto s = TypeInferer::infer(scope->env, t);
            substition(ast, typeVariable, s);
        }
    };
    infer(key);
    infer(value);

    auto type = std::make_shared<TupleType>(
        std::initializer_list<std::shared_ptr<Type>>{key->getType(), value->getType()});
    expr->setType(type);
}

void TypeResolver::visit(std::shared_ptr<MapLiteral> expr)
{
    ASTVisitor::visit(expr);

    assert(!expr->getType());

    auto mapType = std::make_shared<MapType>();

    if (!expr->getEntries().empty()) {
        auto first = expr->getEntries().front();
        assert(first->getType());
        assert(first->getType()->getKind() == TypeKind::TupleType);

        auto tupleType = std::dynamic_pointer_cast<TupleType>(first->getType());
        assert(tupleType);
        assert(tupleType->types.size() == 2);

        // TODO: Use union type instead of type of first element
        for (auto& entry : expr->getEntries()) {
            if (tupleType == entry->getType()) {
                continue;
            }
            if (!isSameType(tupleType, entry->getType())) {
                tupleType = nullptr;
                break;
            }
        }

        if (tupleType != nullptr) {
            mapType->keyType = tupleType->types[0];
            mapType->valueType = tupleType->types[1];
        }
    }

    expr->setType(mapType);
}

void TypeResolver::visit(std::shared_ptr<CallExpr> expr)
{
    ASTVisitor::visit(expr);

    assert(!expr->getType());

    const auto callee = expr->getCallee();
    assert(callee);

    const auto functionType = callee->getType();
    assert(functionType);

    const auto isCallable = [&]() -> bool {
        switch (functionType->getKind()) {
        case TypeKind::ArrayType:
        case TypeKind::MapType:
        case TypeKind::OptionalType:
        case TypeKind::TupleType:
        case TypeKind::ClassType: {
            return false;
        }
        case TypeKind::FunctionType:
        case TypeKind::ReturnType:
        case TypeKind::TypeVariable: {
            return true;
        }
        case TypeKind::BuiltinType: break;
        }
        assert(functionType->getKind() == TypeKind::BuiltinType);

        auto builtinType = std::static_pointer_cast<BuiltinType>(functionType);
        assert(builtinType == std::dynamic_pointer_cast<BuiltinType>(functionType));
        switch (builtinType->kind) {
        case BuiltinTypeKind::Bool:
        case BuiltinTypeKind::Double:
        case BuiltinTypeKind::Void:
        case BuiltinTypeKind::String:
        case BuiltinTypeKind::Int:
        case BuiltinTypeKind::Null: return false; break;
        case BuiltinTypeKind::Any: return true; break;
        }
        return true;
    }();

    if (!isCallable) {
        error(
            callee->getLocation(),
            "Cannot call a non-function whose type is '" + getDiagnosticString(functionType) +
                "'.");
        return;
    }

    std::vector<std::shared_ptr<Type>> argumentTypes;
    for (const auto& arg : expr->getArguments()) {
        assert(arg);
        assert(arg->getType());
        argumentTypes.push_back(arg->getType());
    }

    expr->setType(std::make_shared<ReturnType>(functionType, argumentTypes));
}

void TypeResolver::visit(std::shared_ptr<FuncLiteral> expr)
{
    const auto outerScope = getCurrentScope();
    const auto scope = makeScope(outerScope);
    pushScope(scope);

    std::shared_ptr<Type> returnType;
    if (auto typeAnnotation = expr->getReturnType()) {
        returnType = TypeReprResolver::getType(diag, typeAnnotation);
        scope->expectReturnType = returnType;
    }

    ASTVisitor::visit(expr);
    popScope();

    if (returnType == nullptr) {
        returnType = inferReturnType(scope);
    }

    auto parameterTypes = getParameterTypes(expr->getParameters());
    auto functionType =
        std::make_shared<FunctionType>(std::move(returnType), std::move(parameterTypes));

    assert(!expr->getType());
    expr->setType(functionType);
}

void TypeResolver::visit(std::shared_ptr<VarDecl> decl)
{
    auto ident = decl->getIdentifier();
    assert(ident);
    assert(!ident->getName().empty());

    auto entity = ident->getEntity();
    assert(!entity->getType());

    const auto typeVariable = std::make_shared<TypeVariable>();
    entity->setType(typeVariable);

    ASTVisitor::visit(decl);

    auto scope = getCurrentScope();

    if (diag->hasError()) {
        return;
    }

    if (auto expr = decl->getExpr()) {
        assert(expr->getType());
        auto type = TypeInferer::infer(scope->env, expr->getType());
        if (TypeHelper::isVoid(type)) {
            error(
                expr->getLocation(),
                "rhs is '" + BuiltinType::toString(BuiltinTypeKind::Void) + "' type.");
        }
    }

    if (auto typeAnnotation = decl->getTypeAnnotation()) {
        auto type = TypeReprResolver::getType(diag, typeAnnotation);
        substition(entity, typeVariable, type);
    }
    else if (auto expr = decl->getExpr()) {
        assert(expr->getType());
        auto type = TypeInferer::infer(scope->env, expr->getType());
        substition(entity, typeVariable, type);
    }
    else {
        auto type = std::make_shared<BuiltinType>(BuiltinTypeKind::Any);
        substition(entity, typeVariable, type);
    }

    // TODO: type check
}

void TypeResolver::visit(std::shared_ptr<FuncDecl> decl)
{
    const auto outerScope = getCurrentScope();
    const auto scope = makeScope(outerScope);
    pushScope(scope);

    const auto typeVariable = std::make_shared<TypeVariable>();
    if (auto ident = decl->getIdentifier()) {
        auto entity = ident->getEntity();
        assert(entity->getKind() == EntityKind::Func);
        assert(!entity->getType());
        entity->setType(typeVariable);
    }

    std::shared_ptr<Type> returnType;
    if (auto typeAnnotation = decl->getReturnType()) {
        returnType = TypeReprResolver::getType(diag, typeAnnotation);
        scope->expectReturnType = returnType;
    }

    ASTVisitor::visit(decl);
    popScope();

    if (returnType == nullptr) {
        returnType = inferReturnType(scope);
    }

    auto parameterTypes = getParameterTypes(decl->getParameters());
    auto functionType =
        std::make_shared<FunctionType>(std::move(returnType), std::move(parameterTypes));

    if (auto ident = decl->getIdentifier()) {
        auto entity = ident->getEntity();
        substition(entity, typeVariable, functionType);
    }

    assert(!decl->getType());
    decl->setType(functionType);
}

void TypeResolver::visit(std::shared_ptr<ParamDecl> decl)
{
    auto ident = decl->getIdentifier();
    assert(ident);
    assert(!ident->getName().empty());

    auto entity = ident->getEntity();
    assert((entity->getKind() == EntityKind::Var) || (entity->getKind() == EntityKind::Const));
    assert(!entity->getType());

    if (auto typeAnnotation = decl->getTypeAnnotation()) {
        auto type = TypeReprResolver::getType(diag, typeAnnotation);
        entity->setType(type);
    }
    else {
        auto typeVariable = std::make_shared<TypeVariable>();
        entity->setType(typeVariable);
    }

    ASTVisitor::visit(decl);

    assert(entity->getType());
    assert(!decl->getType());
    decl->setType(entity->getType());
}

} // namespace elma
