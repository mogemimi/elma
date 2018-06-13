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
    std::vector<std::shared_ptr<Decl>> declarations;

public:
    std::vector<std::shared_ptr<Decl>> getDeclarations() const { return declarations; }

    NodeKind getKind() const noexcept override { return NodeKind::TranslationUnitDecl; }

    static std::shared_ptr<TranslationUnitDecl>
    make(const Location& loc, const std::vector<std::shared_ptr<Decl>>& declarations);
};

class NamedDecl final
    : public Decl
    , public std::enable_shared_from_this<NamedDecl> {
private:
    std::string name;

public:
    NodeKind getKind() const noexcept override { return NodeKind::NamedDecl; }

    std::string getName() const;

    static std::shared_ptr<NamedDecl> make(const Location& loc, const std::string& v);
};

} // namespace elma
