#pragma once

#include "Basic/Forward.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace elma {

class ASTContext final {
public:
    std::shared_ptr<TranslationUnitDecl> translationUnit;
    std::vector<std::shared_ptr<Comment>> comments;
    std::vector<std::shared_ptr<Identifier>> unresolvedIdentifiers;

public:
    std::shared_ptr<TranslationUnitDecl> getTranslationUnitDecl() const;

    void buildComments();

    std::vector<std::shared_ptr<Comment>> findComments(const Position& begin, const Position& end);
};

} // namespace elma
