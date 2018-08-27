#pragma once

#include "AST/ASTVisitor.h"
#include "AST/Type.h"
#include "Basic/Forward.h"
#include "Sema/TypeInferer.h"
#include <memory>
#include <string>
#include <tuple>
#include <vector>

namespace elma {
namespace TypeHelper {

std::tuple<BuiltinTypeKind, bool> toBuiltinType(const std::shared_ptr<Type>& type);

bool isInteger(const std::shared_ptr<Type>& type);
bool isFloat(const std::shared_ptr<Type>& type);
bool isBoolean(const std::shared_ptr<Type>& type);
bool isString(const std::shared_ptr<Type>& type);

bool isVoid(const std::shared_ptr<Type>& type);

bool isAny(const std::shared_ptr<Type>& type);

bool isArray(const std::shared_ptr<Type>& type);
bool isMap(const std::shared_ptr<Type>& type);

bool isStaticallyResolved(const std::shared_ptr<Type>& type);

} // namespace TypeHelper
} // namespace elma
