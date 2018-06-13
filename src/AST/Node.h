#pragma once

#include "Basic/Location.h"

namespace elma {

enum class NodeKind {
    TranslationUnitDecl,
    NamedDecl,
};

class Node {
protected:
    Location location;

public:
    virtual ~Node() = default;

    virtual NodeKind getKind() const noexcept = 0;

    Location getLocation() const { return location; }
};

} // namespace elma
