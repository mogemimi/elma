#pragma once

#include "AST/Node.h"
#include "Basic/Forward.h"

namespace elma {

class Expr : public Node {
public:
    virtual ~Expr() = default;
};

} // namespace elma
