#include "AST/Decl.h"
#include <cassert>
#include <utility>

namespace elma {

std::shared_ptr<TranslationUnitDecl> TranslationUnitDecl::make(
    const Location& loc, const std::vector<std::shared_ptr<Decl>>& declarations)
{
    auto decl = std::make_shared<TranslationUnitDecl>();
    decl->location = loc;
    decl->declarations = declarations;
    return decl;
}

std::string NamedDecl::getName() const
{
    return name;
}

std::shared_ptr<NamedDecl> NamedDecl::make(const Location& loc, const std::string& v)
{
    auto decl = std::make_shared<NamedDecl>();
    decl->location = loc;
    decl->name = v;
    return decl;
}

} // namespace elma
