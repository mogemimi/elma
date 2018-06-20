#pragma once

#include "AST/Node.h"
#include "Basic/Forward.h"
#include <memory>
#include <string>
#include <vector>

namespace elma {

class TypeRepr : public Node {
public:
    virtual ~TypeRepr() = default;

    virtual NodeKind getKind() const noexcept = 0;

    virtual Location getLocation() const noexcept = 0;
};

class SimpleIdentTypeRepr final
    : public TypeRepr
    , public std::enable_shared_from_this<SimpleIdentTypeRepr> {
private:
    Location location;
    std::shared_ptr<Identifier> identifier;

public:
    SimpleIdentTypeRepr(const Location& loc, const std::shared_ptr<Identifier>& ident);

    NodeKind getKind() const noexcept override { return NodeKind::SimpleIdentTypeRepr; }

    Location getLocation() const noexcept override { return location; }

    std::shared_ptr<Identifier> getIdentifier() const { return identifier; }
};

class GenericIdentTypeRepr final
    : public TypeRepr
    , public std::enable_shared_from_this<GenericIdentTypeRepr> {
private:
    Location location;
    std::shared_ptr<Identifier> identifier;
    std::vector<std::shared_ptr<TypeRepr>> arguments;

public:
    GenericIdentTypeRepr(
        const Location& loc,
        const std::shared_ptr<Identifier>& ident,
        const std::vector<std::shared_ptr<TypeRepr>>& args);

    NodeKind getKind() const noexcept override { return NodeKind::GenericIdentTypeRepr; }

    Location getLocation() const noexcept override { return location; }

    std::shared_ptr<Identifier> getIdentifier() const { return identifier; }

    std::vector<std::shared_ptr<TypeRepr>> getArguments() const { return arguments; }
};

class OptionalTypeRepr final
    : public TypeRepr
    , public std::enable_shared_from_this<OptionalTypeRepr> {
private:
    Location location;
    std::shared_ptr<TypeRepr> base;

public:
    OptionalTypeRepr(const Location& loc, const std::shared_ptr<TypeRepr>& base);

    NodeKind getKind() const noexcept override { return NodeKind::OptionalTypeRepr; }

    Location getLocation() const noexcept override { return location; }

    std::shared_ptr<TypeRepr> getBase() const { return base; }
};

} // namespace elma
