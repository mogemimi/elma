#include "AST/Expr.h"
#include <cassert>
#include <utility>

namespace elma {

std::shared_ptr<Type> Expr::getType() const
{
    return type;
}

void Expr::setType(const std::shared_ptr<Type>& t)
{
    assert(t);
    type = t;
}

IntegerLiteral::IntegerLiteral(const Location& loc, int64_t v)
    : location(loc)
    , value(v)
{
}

DoubleLiteral::DoubleLiteral(const Location& loc, double v)
    : location(loc)
    , value(v)
{
}

BoolLiteral::BoolLiteral(const Location& loc, bool v)
    : location(loc)
    , value(v)
{
}

StringLiteral::StringLiteral(const Location& loc, const std::string& v)
    : location(loc)
    , value(v)
{
}

NullLiteral::NullLiteral(const Location& loc)
    : location(loc)
{
}

IdentifierExpr::IdentifierExpr(const Location& loc, const std::shared_ptr<Identifier>& d)
    : location(loc)
    , decl(d)
{
}

ParenExpr::ParenExpr(const Location& loc, const std::shared_ptr<Expr>& e)
    : location(loc)
    , subExpr(e)
{
}

ExprValueKind ParenExpr::getValueKind() const
{
    assert(subExpr != nullptr);
    return subExpr->getValueKind();
}

UnaryExpr::UnaryExpr(const Location& loc, UnaryExprKind k, const std::shared_ptr<Expr>& e)
    : location(loc)
    , valueKind(ExprValueKind::RValue)
    , kind(k)
    , subExpr(e)
{
}

std::string UnaryExpr::toString(UnaryExprKind op)
{
    switch (op) {
    case UnaryExprKind::LogicalNot: return "!";
    case UnaryExprKind::Plus: return "+";
    case UnaryExprKind::Minus: return "-";
    case UnaryExprKind::PreDec: return "--";
    case UnaryExprKind::PreInc: return "++";
    case UnaryExprKind::PostDec: return "--";
    case UnaryExprKind::PostInc: return "++";
    }
    return "<unknown>";
}

bool UnaryExpr::isPrefix(UnaryExprKind op)
{
    switch (op) {
    case UnaryExprKind::LogicalNot: return true;
    case UnaryExprKind::Plus: return true;
    case UnaryExprKind::Minus: return true;
    case UnaryExprKind::PreDec: return true;
    case UnaryExprKind::PreInc: return true;
    case UnaryExprKind::PostDec: return false;
    case UnaryExprKind::PostInc: return false;
    }
    return false;
}

bool UnaryExpr::isPostfix(UnaryExprKind op)
{
    return UnaryExpr::isPrefix(op);
}

BinaryExpr::BinaryExpr(
    const Location& loc,
    BinaryExprKind k,
    const std::shared_ptr<Expr>& l,
    const std::shared_ptr<Expr>& r)
    : location(loc)
    , valueKind(ExprValueKind::RValue)
    , kind(k)
    , lhs(l)
    , rhs(r)
{
}

bool BinaryExpr::isMultiplicativeOp(BinaryExprKind kind)
{
    switch (kind) {
    case BinaryExprKind::Multiply: return true;
    case BinaryExprKind::Divide: return true;
    case BinaryExprKind::Mod: return true;
    default: break;
    }
    return false;
}

bool BinaryExpr::isMultiplicativeOp() const
{
    return isMultiplicativeOp(kind);
}

bool BinaryExpr::isAdditiveOp(BinaryExprKind kind)
{
    return (kind == BinaryExprKind::Add) || (kind == BinaryExprKind::Subtract);
}

bool BinaryExpr::isAdditiveOp() const
{
    return isAdditiveOp(kind);
}

bool BinaryExpr::isEqualityOp(BinaryExprKind kind)
{
    return (kind == BinaryExprKind::Equal) || (kind == BinaryExprKind::NotEqual);
}

bool BinaryExpr::isEqualityOp() const
{
    return isEqualityOp(kind);
}

bool BinaryExpr::isComparisonOp(BinaryExprKind kind)
{
    switch (kind) {
    case BinaryExprKind::GreaterThan: return true;
    case BinaryExprKind::GreaterThanOrEqual: return true;
    case BinaryExprKind::LessThan: return true;
    case BinaryExprKind::LessThanOrEqual: return true;
    default: break;
    }
    return false;
}

bool BinaryExpr::isComparisonOp() const
{
    return isComparisonOp(kind);
}

bool BinaryExpr::isLogicalOp(BinaryExprKind kind)
{
    return (kind == BinaryExprKind::LogicalAnd) || (kind == BinaryExprKind::LogicalOr);
}

bool BinaryExpr::isLogicalOp() const
{
    return isLogicalOp(kind);
}

std::string BinaryExpr::toString(BinaryExprKind kind)
{
    switch (kind) {
    case BinaryExprKind::Add: return "+";
    case BinaryExprKind::Subtract: return "-";
    case BinaryExprKind::Divide: return "/";
    case BinaryExprKind::Multiply: return "*";
    case BinaryExprKind::Mod: return "%";
    case BinaryExprKind::Equal: return "==";
    case BinaryExprKind::NotEqual: return "!=";
    case BinaryExprKind::LogicalAnd: return "&&";
    case BinaryExprKind::LogicalOr: return "||";
    case BinaryExprKind::GreaterThan: return ">";
    case BinaryExprKind::GreaterThanOrEqual: return ">=";
    case BinaryExprKind::LessThan: return "<";
    case BinaryExprKind::LessThanOrEqual: return "<=";
    case BinaryExprKind::NullCoalescing: return "??";
    }
    return "<unknown>";
}

AssignExpr::AssignExpr(
    const Location& loc,
    AssignExprKind k,
    const std::shared_ptr<Expr>& l,
    const std::shared_ptr<Expr>& r)
    : location(loc)
    , valueKind(ExprValueKind::RValue)
    , kind(k)
    , lhs(l)
    , rhs(r)
{
}

std::string AssignExpr::toString(AssignExprKind kind)
{
    switch (kind) {
    case AssignExprKind::Assign: return "=";
    }
    return "<unknown>";
}

ConditionalOperator::ConditionalOperator(
    const Location& loc,
    const std::shared_ptr<Expr>& cond,
    const std::shared_ptr<Expr>& lhs,
    const std::shared_ptr<Expr>& rhs)
    : location(loc)
    , valueKind(ExprValueKind::RValue)
    , condExpr(cond)
    , trueExpr(lhs)
    , falseExpr(rhs)
{
}

NullConditionalOperator::NullConditionalOperator(
    const Location& loc, const std::shared_ptr<Expr>& cond, const std::shared_ptr<Expr>& trueExprIn)
    : location(loc)
    , valueKind(ExprValueKind::RValue)
    , condExpr(cond)
    , trueExpr(trueExprIn)
{
}

MemberExpr::MemberExpr(
    const Location& loc, const std::shared_ptr<Expr>& baseIn, const std::shared_ptr<Identifier>& d)
    : location(loc)
    , base(baseIn)
    , memberDecl(d)
{
}

std::shared_ptr<Expr> MemberExpr::getBase() const
{
    return base;
}

std::shared_ptr<Identifier> MemberExpr::getMemberDecl() const
{
    return memberDecl;
}

std::shared_ptr<Expr> SubscriptExpr::getBase() const
{
    return base;
}

std::shared_ptr<Expr> SubscriptExpr::getIndex() const
{
    return index;
}

SubscriptExpr::SubscriptExpr(
    const Location& loc, const std::shared_ptr<Expr>& baseIn, const std::shared_ptr<Expr>& indexIn)
    : location(loc)
    , base(baseIn)
    , index(indexIn)
{
}

ArrayLiteral::ArrayLiteral(const Location& loc, const std::vector<std::shared_ptr<Expr>>& inits)
    : location(loc)
    , initializers(inits)
{
}

MapEntry::MapEntry(
    const Location& loc, const std::shared_ptr<Expr>& keyIn, const std::shared_ptr<Expr>& valueIn)
    : location(loc)
    , key(keyIn)
    , value(valueIn)
{
}

MapLiteral::MapLiteral(const Location& loc, const std::vector<std::shared_ptr<MapEntry>>& entriesIn)
    : location(loc)
    , entries(entriesIn)
{
}

CallExpr::CallExpr(
    const Location& loc,
    const std::shared_ptr<Expr>& fn,
    const std::vector<std::shared_ptr<Expr>>& args)
    : location(loc)
    , callee(fn)
    , arguments(args)
{
}

FuncLiteral::FuncLiteral(
    const Location& loc,
    const std::vector<std::shared_ptr<ParamDecl>>& parametersIn,
    const std::shared_ptr<TypeRepr>& returnTypeIn,
    const std::shared_ptr<CompoundStmt>& s)
    : location(loc)
    , parameters(parametersIn)
    , returnType(returnTypeIn)
    , compoundStmt(s)
{
}

const std::vector<std::shared_ptr<ParamDecl>>& FuncLiteral::getParameters() const
{
    return parameters;
}

std::shared_ptr<TypeRepr> FuncLiteral::getReturnType() const
{
    return returnType;
}

std::shared_ptr<CompoundStmt> FuncLiteral::getBody() const
{
    return compoundStmt;
}

ImplicitConversionExpr::ImplicitConversionExpr(const Location& loc, const std::shared_ptr<Expr>& e)
    : location(loc)
    , subExpr(e)
{
}

ExprValueKind ImplicitConversionExpr::getValueKind() const
{
    assert(subExpr != nullptr);
    return subExpr->getValueKind();
}

} // namespace elma
