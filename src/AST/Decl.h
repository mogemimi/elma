#pragma once

#include "AST/Node.h"
#include "Basic/Forward.h"

namespace elma {

class Decl : public Node {
public:
    virtual ~Decl() = default;
};

} // namespace elma
