#pragma once

#include "Basic/Forward.h"
#include <memory>

namespace elma {
namespace Sema {

std::shared_ptr<Identifier> findInfiniteRecursion(std::shared_ptr<ClassDecl> decl);

std::shared_ptr<Identifier> findInfiniteRecursion(std::shared_ptr<VarDecl> decl);

} // namespace Sema
} // namespace elma
