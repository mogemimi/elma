#include "TypeRepr.h"

namespace elma {

SimpleIdentTypeRepr::SimpleIdentTypeRepr(
    const Location& loc, const std::shared_ptr<Identifier>& ident)
    : location(loc)
    , identifier(ident)
{
}

GenericIdentTypeRepr::GenericIdentTypeRepr(
    const Location& loc,
    const std::shared_ptr<Identifier>& ident,
    const std::vector<std::shared_ptr<TypeRepr>>& args)
    : location(loc)
    , identifier(ident)
    , arguments(args)
{
}

OptionalTypeRepr::OptionalTypeRepr(const Location& loc, const std::shared_ptr<TypeRepr>& baseIn)
    : location(loc)
    , base(baseIn)
{
}

} // namespace elma
