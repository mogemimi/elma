#pragma once

namespace elma {

enum class TypeKind {
};

class Type {
public:
    virtual ~Type() = default;
    virtual TypeKind getKind() const = 0;
};

} // namespace elma
