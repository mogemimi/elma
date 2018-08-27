#include "Sema/Optimizer.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Stmt.h"
#include "Basic/Diagnostic.h"
#include "Sema/ASTEvaluator.h"
#include "Sema/Entity.h"
#include "Sema/IdentifierResolver.h"
#include "Sema/Value.h"
#include <cassert>
#include <sstream>
#include <utility>

namespace elma {
namespace {

template <class ValueType, class LiteralType>
std::shared_ptr<Expr> makeLiteral(const std::shared_ptr<Expr>& expr, const Value* value)
{
    auto v = static_cast<const ValueType*>(value)->getValue();
    auto literal = LiteralType::make(expr->getLocation(), v);
    literal->setType(expr->getType());
    return literal;
}

std::shared_ptr<Expr>
constantFolding(const std::shared_ptr<Expr>& expr, const std::shared_ptr<DiagnosticHandler>& diag)
{
    auto [value, evalResult] = ASTEvaluator::evaluate(expr, diag);

    if (evalResult != ASTEvaluateResult::StaticEvaluation) {
        return expr;
    }

    assert(evalResult == ASTEvaluateResult::StaticEvaluation);

    if (value->getKind() == ValueKind::Int64) {
        return makeLiteral<Int64Value, IntegerLiteral>(expr, value.get());
    }
    if (value->getKind() == ValueKind::Double) {
        return makeLiteral<DoubleValue, DoubleLiteral>(expr, value.get());
    }
    if (value->getKind() == ValueKind::Bool) {
        return makeLiteral<BoolValue, BoolLiteral>(expr, value.get());
    }
    if (value->getKind() == ValueKind::String) {
        return makeLiteral<StringValue, StringLiteral>(expr, value.get());
    }
    return expr;
}

} // end of anonymous namespace

Optimizer::Optimizer(const std::shared_ptr<DiagnosticHandler>& diagIn)
    : diag(diagIn)
{
    assert(diag);
}

void Optimizer::error(const Location& l, const std::string& err)
{
    assert(diag);
    diag->error(l, err);
}

void Optimizer::visit(const std::shared_ptr<BinaryExpr>& expr, Invoke&& traverse)
{
    traverse();

    expr->setLHS(constantFolding(expr->getLHS(), diag));
    expr->setRHS(constantFolding(expr->getRHS(), diag));
}

void Optimizer::visit(const std::shared_ptr<UnaryExpr>& expr, Invoke&& traverse)
{
    traverse();
}

void Optimizer::visit(const std::shared_ptr<IdentifierExpr>& expr, Invoke&& traverse)
{
    traverse();
}

void Optimizer::visit(const std::shared_ptr<VarDecl>& decl, Invoke&& traverse)
{
    traverse();

    if (auto expr = decl->getExpr()) {
        decl->setExpr(constantFolding(expr, diag));
    }
}

} // namespace elma
