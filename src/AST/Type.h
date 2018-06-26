#pragma once

#include "Basic/Forward.h"
#include <memory>
#include <string>
#include <vector>

namespace elma {

enum class TypeKind {
    BuiltinType,
    ArrayType,
    MapType,
    OptionalType,
    FunctionType,
    ClassType,
};

class Type {
public:
    virtual ~Type() = default;
    virtual std::string dump() const = 0;
    virtual TypeKind getKind() const = 0;
};

enum class BuiltinTypeKind {
    Bool,
    Int,
    Double,
    String,
    Void,
    Any,
    Null,
};

class BuiltinType final : public Type {
public:
    BuiltinTypeKind kind;

public:
    explicit BuiltinType(BuiltinTypeKind kind);

    std::string dump() const override;

    TypeKind getKind() const override;

    static std::string toString(BuiltinTypeKind kind);
};

class ArrayType final : public Type {
public:
    std::shared_ptr<Type> primaryType;

public:
    ArrayType();

    std::string dump() const override;

    TypeKind getKind() const override;
};

class MapType final : public Type {
public:
    std::shared_ptr<Type> keyType;
    std::shared_ptr<Type> valueType;

public:
    MapType();

    std::string dump() const override;

    TypeKind getKind() const override;
};

class OptionalType final : public Type {
public:
    std::shared_ptr<Type> baseType;

public:
    OptionalType();

    std::string dump() const override;

    TypeKind getKind() const override;
};

class FunctionType final : public Type {
public:
    std::shared_ptr<Type> returnType;
    std::vector<std::shared_ptr<Type>> parameterTypes;

public:
    FunctionType(const std::shared_ptr<Type>& to, const std::vector<std::shared_ptr<Type>>& from);

    std::string dump() const override;

    TypeKind getKind() const override;
};

class ClassType final : public Type {
public:
    std::weak_ptr<ClassDecl> classDecl;

public:
    explicit ClassType(const std::shared_ptr<ClassDecl>& classDecl);

    std::string dump() const override;

    TypeKind getKind() const override;
};

} // namespace elma
