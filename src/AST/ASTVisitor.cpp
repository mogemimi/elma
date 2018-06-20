#include "AST/ASTVisitor.h"
#include "AST/ASTContext.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Identifier.h"
#include "AST/Stmt.h"
#include "AST/TypeRepr.h"
#include <cassert>
#include <utility>

namespace elma {
namespace AST {
namespace {

template <typename T> void walkChildren(ASTVisitor* visitor, const std::vector<T>& children)
{
    for (const auto& child : children) {
        assert(child != nullptr);
        walk(visitor, child);
    }
}

} // end of anonymous namespace

void walk(ASTVisitor* visitor, std::shared_ptr<Node> node)
{
    assert(visitor != nullptr);
    assert(node != nullptr);

    if (!visitor->begin(node)) {
        return;
    }

    switch (node->getKind()) {
    case NodeKind::Identifier: {
        visitor->visit(std::static_pointer_cast<Identifier>(node));
        break;
    }
    case NodeKind::TranslationUnitDecl: {
        visitor->visit(std::static_pointer_cast<TranslationUnitDecl>(node));
        break;
    }
    case NodeKind::NamedDecl: {
        visitor->visit(std::static_pointer_cast<NamedDecl>(node));
        break;
    }
    case NodeKind::SimpleIdentTypeRepr: {
        visitor->visit(std::static_pointer_cast<SimpleIdentTypeRepr>(node));
        break;
    }
    case NodeKind::GenericIdentTypeRepr: {
        visitor->visit(std::static_pointer_cast<GenericIdentTypeRepr>(node));
        break;
    }
    case NodeKind::OptionalTypeRepr: {
        visitor->visit(std::static_pointer_cast<OptionalTypeRepr>(node));
        break;
    }
    default:
        // error("unreachable");
        break;
    }

    visitor->end(node);
}

} // namespace AST

bool ASTVisitor::begin(std::shared_ptr<Node> node)
{
    assert(node);
    return true;
}

void ASTVisitor::end(std::shared_ptr<Node> node)
{
    assert(node);
}

void ASTVisitor::visit(std::shared_ptr<TranslationUnitDecl> decl)
{
    AST::walkChildren(this, decl->getDeclarations());
}

void ASTVisitor::visit(std::shared_ptr<NamedDecl> decl)
{
    // Nothing to do
}

void ASTVisitor::visit(std::shared_ptr<SimpleIdentTypeRepr> repr)
{
    AST::walk(this, repr->getIdentifier());
}

void ASTVisitor::visit(std::shared_ptr<GenericIdentTypeRepr> repr)
{
    AST::walk(this, repr->getIdentifier());
    AST::walkChildren(this, repr->getArguments());
}

void ASTVisitor::visit(std::shared_ptr<OptionalTypeRepr> repr)
{
    AST::walk(this, repr->getBase());
}

} // namespace elma
