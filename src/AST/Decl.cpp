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

NamedDecl::NamedDecl(const Location& loc, const std::shared_ptr<Identifier>& n)
    : location(loc)
    , ident(n)
{
}

} // namespace elma
