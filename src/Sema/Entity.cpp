#include "Sema/Entity.h"
#include <cassert>
#include <utility>

namespace elma {

EntityKind Entity::getKind() const
{
    return kind;
}

std::string Entity::getName() const
{
    return name;
}

std::shared_ptr<Identifier> Entity::getDecl() const
{
    assert((kind == EntityKind::Var) || (kind == EntityKind::Const));
    return decl.lock();
}

std::shared_ptr<Type> Entity::getType() const
{
    return type;
}

void Entity::setType(const std::shared_ptr<Type>& t)
{
    type = t;
}

std::shared_ptr<Entity>
Entity::makeVariable(const std::string& name, const std::shared_ptr<Identifier>& decl)
{
    auto entity = std::make_shared<Entity>();
    entity->kind = EntityKind::Var;
    entity->name = name;
    entity->decl = decl;
    return entity;
}

std::shared_ptr<Entity>
Entity::makeConstant(const std::string& name, const std::shared_ptr<Identifier>& decl)
{
    auto entity = std::make_shared<Entity>();
    entity->kind = EntityKind::Const;
    entity->name = name;
    entity->decl = decl;
    return entity;
}

std::shared_ptr<Entity> Entity::makeType(const std::string& name, const std::shared_ptr<Type>& type)
{
    auto entity = std::make_shared<Entity>();
    entity->kind = EntityKind::Type;
    entity->name = name;
    entity->type = type;
    return entity;
}

} // namespace elma
