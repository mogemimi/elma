#include "AST/Decl.h"
#include <cassert>
#include <utility>

namespace elma {

TranslationUnitDecl::TranslationUnitDecl(
    const Location& loc, const std::vector<std::shared_ptr<Decl>>& d)
    : location(loc)
    , declarations(d)
{
}

VarDecl::VarDecl(
    const Location& loc,
    const std::shared_ptr<Identifier>& n,
    VarDeclSpecifier sp,
    const std::shared_ptr<TypeRepr>& typeAnnotationIn,
    const std::shared_ptr<Expr>& e)
    : location(loc)
    , ident(n)
    , typeAnnotation(typeAnnotationIn)
    , expr(e)
    , specifier(sp)
{
}

std::string VarDecl::getSpecifierString(VarDeclSpecifier specifier)
{
    switch (specifier) {
    case VarDeclSpecifier::Let: return "let";
    case VarDeclSpecifier::Var: return "var";
    case VarDeclSpecifier::Const: return "const";
    }
    return "<unknown-specifier>";
}

BindingDecl::BindingDecl(const Location& loc, const std::shared_ptr<Identifier>& n)
    : location(loc)
    , ident(n)
{
}

DecompositionDecl::DecompositionDecl(
    const Location& loc,
    VarDeclSpecifier sp,
    const std::vector<std::shared_ptr<BindingDecl>>& bindingsIn)
    : location(loc)
    , bindings(bindingsIn)
    , specifier(sp)
{
}

DecompositionDecl::DecompositionDecl(
    const Location& loc,
    VarDeclSpecifier sp,
    const std::vector<std::shared_ptr<BindingDecl>>& bindingsIn,
    const std::shared_ptr<Expr>& e)
    : location(loc)
    , bindings(bindingsIn)
    , expr(e)
    , specifier(sp)
{
}

FuncDecl::FuncDecl(
    const Location& loc,
    const std::shared_ptr<Identifier>& n,
    const std::vector<std::shared_ptr<ParamDecl>>& parametersIn,
    const std::shared_ptr<TypeRepr>& returnTypeIn,
    const std::shared_ptr<CompoundStmt>& s)
    : location(loc)
    , ident(n)
    , parameters(parametersIn)
    , returnType(returnTypeIn)
    , compoundStmt(s)
{
}

std::shared_ptr<Identifier> FuncDecl::getIdentifier() const
{
    return ident;
}

const std::vector<std::shared_ptr<ParamDecl>>& FuncDecl::getParameters() const
{
    return parameters;
}

std::shared_ptr<TypeRepr> FuncDecl::getReturnType() const
{
    return returnType;
}

std::shared_ptr<CompoundStmt> FuncDecl::getBody() const
{
    return compoundStmt;
}

ParamDecl::ParamDecl(const Location& loc, const std::shared_ptr<Identifier>& name)
{
    this->location = loc;
    this->ident = name;
}

ParamDecl::ParamDecl(
    const Location& loc,
    const std::shared_ptr<Identifier>& name,
    const std::shared_ptr<TypeRepr>& typeAnnotationIn)
    : location(loc)
    , ident(name)
    , typeAnnotation(typeAnnotationIn)
{
}

ClassDecl::ClassDecl(const Location& loc, const std::shared_ptr<Identifier>& n)
    : location(loc)
    , ident(n)
{
}

ClassDecl::ClassDecl(
    const Location& loc,
    const std::shared_ptr<Identifier>& n,
    const std::vector<std::shared_ptr<Decl>>& membersIn)
    : location(loc)
    , ident(n)
    , members(membersIn)
{
}

void ClassDecl::addMember(const std::shared_ptr<Decl>& member)
{
    assert(member);
    members.push_back(member);
}

NamedDecl::NamedDecl(const Location& loc, const std::shared_ptr<Identifier>& n)
    : location(loc)
    , ident(n)
{
}

} // namespace elma
