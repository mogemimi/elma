#pragma once

#include "Basic/Forward.h"
#include <memory>
#include <string>

namespace elma {

enum class EntityKind {
    Type,
    Var,
    Const,
    Func,
};

class Entity final {
private:
    std::string name;
    std::weak_ptr<Decl> decl;
    std::shared_ptr<Type> type;
    EntityKind kind;

public:
    EntityKind getKind() const;

    std::string getName() const;

    std::shared_ptr<Decl> getDecl() const;

    std::shared_ptr<Type> getType() const;

    void setType(const std::shared_ptr<Type>& type);

    static std::shared_ptr<Entity>
    makeVariable(const std::string& name, const std::shared_ptr<Decl>& decl);

    static std::shared_ptr<Entity>
    makeConstant(const std::string& name, const std::shared_ptr<Decl>& decl);

    static std::shared_ptr<Entity>
    makeFunction(const std::string& name, const std::shared_ptr<FuncDecl>& decl);

    static std::shared_ptr<Entity>
    makeType(const std::string& name, const std::shared_ptr<Type>& type);
};

} // namespace elma
