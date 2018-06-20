#pragma once

#include "Basic/Forward.h"
#include <functional>
#include <memory>

namespace elma {

class ASTVisitor {
public:
    virtual ~ASTVisitor() = default;

    virtual bool begin(std::shared_ptr<Node> node);
    virtual void end(std::shared_ptr<Node> node);

    virtual void visit(std::shared_ptr<Identifier> ident);

    virtual void visit(std::shared_ptr<TranslationUnitDecl> decl);
    virtual void visit(std::shared_ptr<NamedDecl> decl);

    virtual void visit(std::shared_ptr<SimpleIdentTypeRepr> repr);
    virtual void visit(std::shared_ptr<GenericIdentTypeRepr> repr);
    virtual void visit(std::shared_ptr<OptionalTypeRepr> repr);
};

namespace AST {

void walk(ASTVisitor* visitor, std::shared_ptr<Node> node);

} // namespace AST
} // namespace elma
