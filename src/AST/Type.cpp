#include "AST/Type.h"
#include "AST/Decl.h"
#include "AST/Identifier.h"
#include <cassert>

namespace elma {
namespace {

std::string stringify(const std::vector<std::shared_ptr<Type>>& types)
{
    std::string result;
    bool needToInsertComma = false;
    for (const auto& t : types) {
        if (needToInsertComma) {
            result += ", ";
        }
        assert(t);
        result += t->dump();
        needToInsertComma = true;
    }
    return result;
}

} // end of anonymous namespace

BuiltinType::BuiltinType(BuiltinTypeKind kindIn)
    : kind(kindIn)
{
}

std::string BuiltinType::dump() const
{
    return toString(kind);
}

TypeKind BuiltinType::getKind() const
{
    return TypeKind::BuiltinType;
}

std::string BuiltinType::toString(BuiltinTypeKind kind)
{
    switch (kind) {
    case BuiltinTypeKind::Bool: return "Bool";
    case BuiltinTypeKind::Int: return "Int";
    case BuiltinTypeKind::Double: return "Double";
    case BuiltinTypeKind::String: return "String";
    case BuiltinTypeKind::Void: return "Void";
    case BuiltinTypeKind::Any: return "Any";
    case BuiltinTypeKind::Null: return "null";
    }
    return "<unknown-builtin-type>";
}

ArrayType::ArrayType() = default;

std::string ArrayType::dump() const
{
    if (!primaryType) {
        return "Array";
    }
    assert(primaryType);
    return "Array<" + primaryType->dump() + ">";
}

TypeKind ArrayType::getKind() const
{
    return TypeKind::ArrayType;
}

MapType::MapType() = default;

std::string MapType::dump() const
{
    if (!keyType || !valueType) {
        return "Map";
    }
    assert(keyType);
    assert(valueType);
    return "Map<" + keyType->dump() + ", " + valueType->dump() + ">";
}

TypeKind MapType::getKind() const
{
    return TypeKind::MapType;
}

OptionalType::OptionalType() = default;

std::string OptionalType::dump() const
{
    if (!baseType) {
        return "Optional";
    }
    assert(baseType);
    return baseType->dump() + "?";
}

TypeKind OptionalType::getKind() const
{
    return TypeKind::OptionalType;
}

TupleType::TupleType(std::initializer_list<std::shared_ptr<Type>> typesIn)
    : types(typesIn)
{
}

std::string TupleType::dump() const
{
    return "Tuple<" + stringify(types) + ">";
}

TypeKind TupleType::getKind() const
{
    return TypeKind::TupleType;
}

FunctionType::FunctionType(
    const std::shared_ptr<Type>& to, const std::vector<std::shared_ptr<Type>>& from)
    : returnType(to)
    , parameterTypes(from)
{
}

std::string FunctionType::dump() const
{
    return "(" + stringify(parameterTypes) + ") -> " + returnType->dump();
}

TypeKind FunctionType::getKind() const
{
    return TypeKind::FunctionType;
}

ClassType::ClassType(const std::shared_ptr<ClassDecl>& classDeclIn)
    : classDecl(classDeclIn)
{
}

std::string ClassType::dump() const
{
    assert(!classDecl.expired());
    auto decl = classDecl.lock();
    assert(decl);
    auto ident = decl->getIdentifier();
    assert(ident);
    return ident->getName();
}

TypeKind ClassType::getKind() const
{
    return TypeKind::ClassType;
}

TypeVariable::TypeVariable()
{
    static TypeID nextID = 100;
    ++nextID;
    this->id = nextID;
}

std::string TypeVariable::dump() const
{
    //    if (instance) {
    //        return instance->dump();
    //    }
    return "<" + std::to_string(id) + ">";
}

TypeKind TypeVariable::getKind() const
{
    return TypeKind::TypeVariable;
}

TypeID TypeVariable::getTypeID() const
{
    return id;
}

std::shared_ptr<Type> TypeVariable::getType() const
{
    return instance;
}

void TypeVariable::setType(const std::shared_ptr<Type>& typeIn)
{
    assert(typeIn);
    instance = typeIn;
}

ReturnType::ReturnType(
    const std::shared_ptr<Type>& callableTypeIn,
    const std::vector<std::shared_ptr<Type>>& argumentTypesIn)
    : callableType(callableTypeIn)
    , argumentTypes(argumentTypesIn)
{
}

std::string ReturnType::dump() const
{
    return "((" + callableType->dump() + ")(" + stringify(argumentTypes) + "))";
}

TypeKind ReturnType::getKind() const
{
    return TypeKind::ReturnType;
}

} // namespace elma
