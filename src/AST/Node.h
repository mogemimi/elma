#pragma once

#include "Basic/Location.h"

namespace elma {

enum class NodeKind {
    Identifier,

    TranslationUnitDecl,
    VarDecl,
    BindingDecl,
    DecompositionDecl,
    FuncDecl,
    ParamDecl,
    ClassDecl,
    NamedDecl,

    IntegerLiteral,
    DoubleLiteral,
    BoolLiteral,
    StringLiteral,
    NullLiteral,
    IdentifierExpr,
    ParenExpr,
    UnaryExpr,
    BinaryExpr,
    AssignExpr,
    ConditionalOperator,
    NullConditionalOperator,
    MemberExpr,
    SubscriptExpr,
    ArrayLiteral,
    MapEntry,
    MapLiteral,
    CallExpr,
    FuncLiteral,
    ImplicitConversionExpr,

    CompoundStmt,
    DeclStmt,
    ExprStmt,
    ReturnStmt,
    DeferStmt,
    IfStmt,
    WhileStmt,
    ForStmt,
    ForEachStmt,

    SimpleIdentTypeRepr,
    GenericIdentTypeRepr,
    OptionalTypeRepr,
};

class Node {
public:
    virtual ~Node() = default;

    virtual NodeKind getKind() const noexcept = 0;

    virtual Location getLocation() const noexcept = 0;
};

} // namespace elma
