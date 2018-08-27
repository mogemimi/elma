#pragma once

#include "AST/Node.h"
#include "Basic/Forward.h"
#include <memory>
#include <string>
#include <vector>

namespace elma {

class Decl : public Node {
public:
    virtual ~Decl() = default;
};

class TranslationUnitDecl final
    : public Decl
    , public std::enable_shared_from_this<TranslationUnitDecl> {
private:
    Location location;
    std::vector<std::shared_ptr<Decl>> declarations;

public:
    TranslationUnitDecl(
        const Location& loc, const std::vector<std::shared_ptr<Decl>>& declarations);

    std::vector<std::shared_ptr<Decl>> getDeclarations() const { return declarations; }

    NodeKind getKind() const noexcept override { return NodeKind::TranslationUnitDecl; }

    Location getLocation() const noexcept override { return location; }
};

enum class VarDeclSpecifier {
    Let,
    Var,
    Const,
};

class VarDecl final
    : public Decl
    , public std::enable_shared_from_this<VarDecl> {
private:
    Location location;
    std::shared_ptr<Identifier> ident;
    std::shared_ptr<TypeRepr> typeAnnotation;
    std::shared_ptr<Expr> expr;
    VarDeclSpecifier specifier;

public:
    VarDecl(
        const Location& loc,
        const std::shared_ptr<Identifier>& n,
        VarDeclSpecifier sp,
        const std::shared_ptr<TypeRepr>& typeAnnotation,
        const std::shared_ptr<Expr>& e);

    NodeKind getKind() const noexcept override { return NodeKind::VarDecl; }

    Location getLocation() const noexcept override { return location; }

    std::shared_ptr<Identifier> getIdentifier() const { return ident; }
    std::shared_ptr<TypeRepr> getTypeAnnotation() const { return typeAnnotation; }
    VarDeclSpecifier getSpecifier() const { return specifier; }

    std::shared_ptr<Expr> getExpr() const { return expr; }
    void setExpr(const std::shared_ptr<Expr>& e) { expr = e; }

    static std::string getSpecifierString(VarDeclSpecifier specifier);
};

class BindingDecl final
    : public Decl
    , public std::enable_shared_from_this<BindingDecl> {
private:
    Location location;
    std::shared_ptr<Identifier> ident;
    std::shared_ptr<Expr> expr;

public:
    BindingDecl(const Location& loc, const std::shared_ptr<Identifier>& n);

    NodeKind getKind() const noexcept override { return NodeKind::BindingDecl; }

    Location getLocation() const noexcept override { return location; }

    std::shared_ptr<Identifier> getIdentifier() const { return ident; }

    std::shared_ptr<Expr> getExpr() const { return expr; }
    void setExpr(const std::shared_ptr<Expr>& e) { expr = e; }
};

class DecompositionDecl final
    : public Decl
    , public std::enable_shared_from_this<DecompositionDecl> {
private:
    Location location;
    std::vector<std::shared_ptr<BindingDecl>> bindings;
    std::shared_ptr<Expr> expr;
    VarDeclSpecifier specifier;

public:
    DecompositionDecl(
        const Location& loc,
        VarDeclSpecifier sp,
        const std::vector<std::shared_ptr<BindingDecl>>& bindings);

    DecompositionDecl(
        const Location& loc,
        VarDeclSpecifier sp,
        const std::vector<std::shared_ptr<BindingDecl>>& bindings,
        const std::shared_ptr<Expr>& e);

    NodeKind getKind() const noexcept override { return NodeKind::DecompositionDecl; }

    Location getLocation() const noexcept override { return location; }

    std::vector<std::shared_ptr<BindingDecl>> getBindings() const { return bindings; }
    VarDeclSpecifier getSpecifier() const { return specifier; }

    std::shared_ptr<Expr> getExpr() const { return expr; }
    void setExpr(const std::shared_ptr<Expr>& e) { expr = e; }
};

class FuncDecl final
    : public Decl
    , public std::enable_shared_from_this<FuncDecl> {
private:
    Location location;
    std::shared_ptr<Identifier> ident;
    std::vector<std::shared_ptr<ParamDecl>> parameters;
    std::shared_ptr<TypeRepr> returnType;
    std::shared_ptr<CompoundStmt> compoundStmt;
    std::shared_ptr<Type> funcType;

public:
    FuncDecl(
        const Location& loc,
        const std::shared_ptr<Identifier>& n,
        const std::vector<std::shared_ptr<ParamDecl>>& a,
        const std::shared_ptr<TypeRepr>& returnType,
        const std::shared_ptr<CompoundStmt>& s);

    NodeKind getKind() const noexcept override { return NodeKind::FuncDecl; }

    Location getLocation() const noexcept override { return location; }

    std::shared_ptr<Identifier> getIdentifier() const;

    const std::vector<std::shared_ptr<ParamDecl>>& getParameters() const;

    std::shared_ptr<TypeRepr> getReturnType() const;

    std::shared_ptr<CompoundStmt> getBody() const;

    std::shared_ptr<Type> getType() const { return funcType; }

    void setType(const std::shared_ptr<Type>& t) { funcType = t; }
};

class ParamDecl final
    : public Decl
    , public std::enable_shared_from_this<ParamDecl> {
private:
    Location location;
    std::shared_ptr<Identifier> ident;
    std::shared_ptr<TypeRepr> typeAnnotation;
    std::shared_ptr<Type> type;

public:
    ParamDecl(const Location& loc, const std::shared_ptr<Identifier>& name);

    ParamDecl(
        const Location& loc,
        const std::shared_ptr<Identifier>& name,
        const std::shared_ptr<TypeRepr>& typeAnnotation);

    NodeKind getKind() const noexcept override { return NodeKind::ParamDecl; }

    Location getLocation() const noexcept override { return location; }

    std::shared_ptr<Identifier> getIdentifier() const { return ident; }
    std::shared_ptr<TypeRepr> getTypeAnnotation() const { return typeAnnotation; }

    std::shared_ptr<Type> getType() const { return type; }

    void setType(const std::shared_ptr<Type>& t) { type = t; }
};

class ClassDecl final
    : public Decl
    , public std::enable_shared_from_this<ClassDecl> {
private:
    Location location;
    std::shared_ptr<Identifier> ident;

    // TODO: replace the following container with MemberLookupTable
    // using MemberLookupTable = std::map<std::string, std::shared_ptr<Decl>>;
    std::vector<std::shared_ptr<Decl>> members;

public:
    ClassDecl(const Location& loc, const std::shared_ptr<Identifier>& n);

    ClassDecl(
        const Location& loc,
        const std::shared_ptr<Identifier>& n,
        const std::vector<std::shared_ptr<Decl>>& members);

    NodeKind getKind() const noexcept override { return NodeKind::ClassDecl; }

    Location getLocation() const noexcept override { return location; }

    std::shared_ptr<Identifier> getIdentifier() const { return ident; }

    std::vector<std::shared_ptr<Decl>> getMembers() const { return members; }

    void addMember(const std::shared_ptr<Decl>& member);
};

class NamedDecl final
    : public Decl
    , public std::enable_shared_from_this<NamedDecl> {
private:
    Location location;
    std::shared_ptr<Identifier> ident;

public:
    NamedDecl(const Location& loc, const std::shared_ptr<Identifier>& n);

    NodeKind getKind() const noexcept override { return NodeKind::NamedDecl; }

    Location getLocation() const noexcept override { return location; }

    std::shared_ptr<Identifier> getIdentifier() const { return ident; }
};

} // namespace elma
