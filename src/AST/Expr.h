#pragma once

#include "AST/Node.h"
#include "Basic/Forward.h"

namespace elma {

enum class ExprValueKind {
    LValue,
    RValue,
};

class Expr : public Node {
public:
    virtual ~Expr() = default;

    virtual ExprValueKind getValueKind() const = 0;

    bool isLValue() const { return getValueKind() == ExprValueKind::LValue; }
};

} // namespace elma
