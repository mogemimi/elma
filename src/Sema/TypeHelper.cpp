#include "Sema/TypeHelper.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Identifier.h"
#include "AST/Stmt.h"
#include "AST/TypeRepr.h"
#include "Basic/Diagnostic.h"
#include "Sema/Entity.h"
#include "Sema/IdentifierResolver.h"
#include "Sema/TypeReprResolver.h"
#include <cassert>
#include <sstream>
#include <utility>

namespace elma {
namespace {

bool isBuiltinType(const std::shared_ptr<Type>& type, BuiltinTypeKind kind)
{
    assert(type);
    if (type->getKind() != TypeKind::BuiltinType) {
        return false;
    }
    auto t = std::static_pointer_cast<BuiltinType>(type);
    return (t->kind == kind);
}

} // end of anonymous namespace

std::tuple<BuiltinTypeKind, bool> TypeHelper::toBuiltinType(const std::shared_ptr<Type>& type)
{
    assert(type);
    switch (type->getKind()) {
    case TypeKind::BuiltinType: {
        auto t = std::static_pointer_cast<BuiltinType>(type);
        return std::make_tuple(t->kind, true);
    }
    default: break;
    }
    return std::make_tuple(BuiltinTypeKind::Any, false);
}

bool TypeHelper::isInteger(const std::shared_ptr<Type>& type)
{
    return isBuiltinType(type, BuiltinTypeKind::Int);
}

bool TypeHelper::isFloat(const std::shared_ptr<Type>& type)
{
    return isBuiltinType(type, BuiltinTypeKind::Double);
}

bool TypeHelper::isBoolean(const std::shared_ptr<Type>& type)
{
    return isBuiltinType(type, BuiltinTypeKind::Bool);
}

bool TypeHelper::isString(const std::shared_ptr<Type>& type)
{
    return isBuiltinType(type, BuiltinTypeKind::String);
}

bool TypeHelper::isVoid(const std::shared_ptr<Type>& type)
{
    return isBuiltinType(type, BuiltinTypeKind::Void);
}

bool TypeHelper::isAny(const std::shared_ptr<Type>& type)
{
    return isBuiltinType(type, BuiltinTypeKind::Any);
}

bool TypeHelper::isArray(const std::shared_ptr<Type>& type)
{
    return type->getKind() == TypeKind::ArrayType;
}

bool TypeHelper::isMap(const std::shared_ptr<Type>& type)
{
    return type->getKind() == TypeKind::MapType;
}

bool TypeHelper::isStaticallyResolved(const std::shared_ptr<Type>& type)
{
    assert(type);
    switch (type->getKind()) {
    case TypeKind::BuiltinType: {
        auto t = std::static_pointer_cast<BuiltinType>(type);
        return t->kind != BuiltinTypeKind::Any;
    }
    case TypeKind::ArrayType: {
        auto t = std::static_pointer_cast<ArrayType>(type);
        return isStaticallyResolved(t->primaryType);
    }
    case TypeKind::MapType: {
        auto t = std::static_pointer_cast<MapType>(type);
        return isStaticallyResolved(t->keyType) && isStaticallyResolved(t->valueType);
    }
    case TypeKind::ClassType: {
        return true;
    }
    default: break;
    }
    return false;
}

} // namespace elma
