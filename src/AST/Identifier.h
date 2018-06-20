#pragma once

#include "AST/Node.h"
#include "Basic/Forward.h"
#include <memory>
#include <string>

namespace elma {

class Identifier final
    : public Node
    , public std::enable_shared_from_this<Identifier> {
private:
    Location location;
    std::string name;
    std::shared_ptr<Entity> entity;

public:
    Identifier(const Location& loc, const std::string& v);

    NodeKind getKind() const noexcept override { return NodeKind::Identifier; }

    Location getLocation() const noexcept override { return location; }

    std::string getName() const;

    std::shared_ptr<Entity> getEntity() const;
    void setEntity(const std::shared_ptr<Entity>& entity);
};

} // namespace elma
