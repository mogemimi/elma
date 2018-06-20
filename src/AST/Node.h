#pragma once

#include "Basic/Location.h"

namespace elma {

enum class NodeKind {
    Identifier,

    TranslationUnitDecl,
    NamedDecl,

    SimpleIdentTypeRepr,
    GenericIdentTypeRepr,
    OptionalTypeRepr,
};

class Node {
public:
    virtual ~Node() = default;

    virtual NodeKind getKind() const noexcept = 0;

    virtual Location getLocation() const noexcept = 0;
};

} // namespace elma
