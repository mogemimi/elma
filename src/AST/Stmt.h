#pragma once

#include "AST/Node.h"
#include "Basic/Forward.h"

namespace elma {

class Stmt : public Node {
public:
    virtual ~Stmt() = default;
};

} // namespace elma
