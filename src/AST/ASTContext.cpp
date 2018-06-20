#include "AST/ASTContext.h"

namespace elma {

std::shared_ptr<TranslationUnitDecl> ASTContext::getTranslationUnitDecl() const
{
    return translationUnit;
}

} // namespace elma
