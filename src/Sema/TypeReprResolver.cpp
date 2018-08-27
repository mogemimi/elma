#include "Sema/TypeReprResolver.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Identifier.h"
#include "AST/Stmt.h"
#include "AST/TypeRepr.h"
#include "Basic/Diagnostic.h"
#include "Sema/Entity.h"
#include "Sema/IdentifierResolver.h"
#include <cassert>
#include <sstream>
#include <utility>

namespace elma {
namespace {

std::shared_ptr<Type>
visit(const std::shared_ptr<DiagnosticHandler>& diag, std::shared_ptr<SimpleIdentTypeRepr> repr)
{
    assert(repr);

    auto ident = repr->getIdentifier();
    assert(ident);

    auto entity = ident->getEntity();
    assert(entity);

    auto type = entity->getType();
    return type;
}

std::shared_ptr<Type>
visit(const std::shared_ptr<DiagnosticHandler>& diag, std::shared_ptr<GenericIdentTypeRepr> repr)
{
    assert(repr);

    auto ident = repr->getIdentifier();
    assert(ident);

    auto entity = ident->getEntity();
    assert(entity);

    auto args = repr->getArguments();

    if (entity->getType()->getKind() == TypeKind::ArrayType) {
        constexpr size_t argumentCount = 1;

        if (args.size() != argumentCount) {
            diag->error(
                repr->getLocation(),
                "Generic type '" + ident->getName() + "' requires " +
                    std::to_string(argumentCount) + " type argument(s).");
            return nullptr;
        }

        auto type = std::make_shared<ArrayType>();

        assert(args.size() == argumentCount);
        type->primaryType = TypeReprResolver::getType(diag, args.front());

        return type;
    }

    if (entity->getType()->getKind() == TypeKind::MapType) {
        constexpr size_t argumentCount = 2;
        if (args.size() != argumentCount) {
            diag->error(
                repr->getLocation(),
                "Generic type '" + ident->getName() + "' requires " +
                    std::to_string(argumentCount) + " type argument(s).");
            return nullptr;
        }
        auto type = std::make_shared<MapType>();

        assert(args.size() == argumentCount);
        type->keyType = TypeReprResolver::getType(diag, args[0]);
        type->valueType = TypeReprResolver::getType(diag, args[1]);

        return type;
    }

    return nullptr;
}

std::shared_ptr<Type>
visit(const std::shared_ptr<DiagnosticHandler>& diag, std::shared_ptr<OptionalTypeRepr> repr)
{
    auto base = repr->getBase();
    assert(base);

    auto type = std::make_shared<OptionalType>();
    type->baseType = TypeReprResolver::getType(diag, base);

    return type;
}

} // end of anonymous namespace

std::shared_ptr<Type> TypeReprResolver::getType(
    const std::shared_ptr<DiagnosticHandler>& diag, std::shared_ptr<TypeRepr> repr)
{
    switch (repr->getKind()) {
    case NodeKind::SimpleIdentTypeRepr:
        return visit(diag, std::static_pointer_cast<SimpleIdentTypeRepr>(repr));
        break;
    case NodeKind::GenericIdentTypeRepr:
        return visit(diag, std::static_pointer_cast<GenericIdentTypeRepr>(repr));
        break;
    case NodeKind::OptionalTypeRepr:
        return visit(diag, std::static_pointer_cast<OptionalTypeRepr>(repr));
        break;
    default:
        // unreachable
        break;
    }
    return nullptr;
}

} // namespace elma
