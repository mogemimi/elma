#include "AST/Identifier.h"
#include <cassert>
#include <utility>

namespace elma {

Identifier::Identifier(const Location& loc, const std::string& v)
    : location(loc)
    , name(v)
{
}

std::string Identifier::getName() const
{
    return name;
}

std::shared_ptr<Entity> Identifier::getEntity() const
{
    return entity;
}

void Identifier::setEntity(const std::shared_ptr<Entity>& e)
{
    entity = e;
}

} // namespace elma
