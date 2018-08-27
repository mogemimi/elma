#pragma once

#include "AST/ASTVisitor.h"
#include "AST/Type.h"
#include "Basic/Forward.h"
#include "Sema/TypeInferer.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace elma {

struct TypeReprResolver final {
    static std::shared_ptr<Type>
    getType(const std::shared_ptr<DiagnosticHandler>& diag, std::shared_ptr<TypeRepr> repr);
};

} // namespace elma
