#pragma once

#include "Basic/Forward.h"
#include <memory>
#include <string>

namespace elma {

enum class EntityKind {
    Type,
    Var,
    Const,
};

class Entity final {
private:
    std::string name;
    std::weak_ptr<Identifier> decl;
    std::shared_ptr<Type> type;
    EntityKind kind;

public:
    EntityKind getKind() const;

    std::string getName() const;

    std::shared_ptr<Identifier> getDecl() const;

    std::shared_ptr<Type> getType() const;

    void setType(const std::shared_ptr<Type>& type);

    static std::shared_ptr<Entity>
    makeVariable(const std::string& name, const std::shared_ptr<Identifier>& decl);

    static std::shared_ptr<Entity>
    makeConstant(const std::string& name, const std::shared_ptr<Identifier>& decl);

    static std::shared_ptr<Entity>
    makeType(const std::string& name, const std::shared_ptr<Type>& type);
};

} // namespace elma
