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
