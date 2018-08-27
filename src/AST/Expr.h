#pragma once

#include "AST/Node.h"
#include "Basic/Forward.h"
#include <memory>
#include <string>
#include <vector>

namespace elma {

enum class ExprValueKind {
    LValue,
    RValue,
};

class Expr : public Node {
protected:
    std::shared_ptr<Type> type;

public:
    virtual ~Expr() = default;

    virtual ExprValueKind getValueKind() const = 0;

    bool isLValue() const { return getValueKind() == ExprValueKind::LValue; }

    // TODO: for constant folding
    // bool isEvaluatable();

    std::shared_ptr<Type> getType() const;
    void setType(const std::shared_ptr<Type>& t);
};

class IntegerLiteral final
    : public Expr
    , public std::enable_shared_from_this<IntegerLiteral> {
private:
    Location location;
    int64_t value;

public:
    IntegerLiteral(const Location& loc, int64_t v);

    NodeKind getKind() const noexcept override { return NodeKind::IntegerLiteral; }

    Location getLocation() const noexcept override { return location; }

    ExprValueKind getValueKind() const override { return ExprValueKind::RValue; }

    int64_t getValue() const noexcept { return value; }
};

class DoubleLiteral final
    : public Expr
    , public std::enable_shared_from_this<DoubleLiteral> {
private:
    Location location;
    double value;

public:
    DoubleLiteral(const Location& loc, double v);

    NodeKind getKind() const noexcept override { return NodeKind::DoubleLiteral; }

    Location getLocation() const noexcept override { return location; }

    ExprValueKind getValueKind() const override { return ExprValueKind::RValue; }

    double getValue() const noexcept { return value; }
};

class BoolLiteral final
    : public Expr
    , public std::enable_shared_from_this<BoolLiteral> {
private:
    Location location;
    bool value;

public:
    BoolLiteral(const Location& loc, bool v);

    NodeKind getKind() const noexcept override { return NodeKind::BoolLiteral; }

    Location getLocation() const noexcept override { return location; }

    ExprValueKind getValueKind() const override { return ExprValueKind::RValue; }

    bool getValue() const noexcept { return value; }
};

class StringLiteral final
    : public Expr
    , public std::enable_shared_from_this<StringLiteral> {
private:
    Location location;
    std::string value;

public:
    StringLiteral(const Location& loc, const std::string& v);

    NodeKind getKind() const noexcept override { return NodeKind::StringLiteral; }

    Location getLocation() const noexcept override { return location; }

    ExprValueKind getValueKind() const override { return ExprValueKind::RValue; }

    std::string getValue() const noexcept { return value; }
};

class NullLiteral final
    : public Expr
    , public std::enable_shared_from_this<NullLiteral> {
private:
    Location location;

public:
    explicit NullLiteral(const Location& loc);

    NodeKind getKind() const noexcept override { return NodeKind::NullLiteral; }

    Location getLocation() const noexcept override { return location; }

    ExprValueKind getValueKind() const override { return ExprValueKind::RValue; }
};

class IdentifierExpr final
    : public Expr
    , public std::enable_shared_from_this<IdentifierExpr> {
private:
    Location location;
    std::shared_ptr<Identifier> decl;

public:
    IdentifierExpr(const Location& loc, const std::shared_ptr<Identifier>& d);

    NodeKind getKind() const noexcept override { return NodeKind::IdentifierExpr; }

    Location getLocation() const noexcept override { return location; }

    ExprValueKind getValueKind() const override { return ExprValueKind::LValue; }

    std::shared_ptr<Identifier> getIdentifier() const { return decl; }
};

class ParenExpr final
    : public Expr
    , public std::enable_shared_from_this<ParenExpr> {
private:
    Location location;
    std::shared_ptr<Expr> subExpr;

public:
    ParenExpr(const Location& loc, const std::shared_ptr<Expr>& e);

    NodeKind getKind() const noexcept override { return NodeKind::ParenExpr; }

    Location getLocation() const noexcept override { return location; }

    ExprValueKind getValueKind() const override;

    std::shared_ptr<Expr> getSubExpr() const { return subExpr; }
    void setSubExpr(const std::shared_ptr<Expr>& s) { this->subExpr = s; }
};

enum class UnaryExprKind {
    PostInc,
    PostDec,
    PreInc,
    PreDec,
    // AddrOf,
    // Deref,
    Plus,
    Minus,
    LogicalNot, // !
};

class UnaryExpr final
    : public Expr
    , public std::enable_shared_from_this<UnaryExpr> {
private:
    Location location;
    ExprValueKind valueKind;
    UnaryExprKind kind;
    std::shared_ptr<Expr> subExpr;

public:
    UnaryExpr(const Location& loc, UnaryExprKind k, const std::shared_ptr<Expr>& e);

    NodeKind getKind() const noexcept override { return NodeKind::UnaryExpr; }

    Location getLocation() const noexcept override { return location; }

    ExprValueKind getValueKind() const override { return valueKind; }

    void setValueKind(ExprValueKind k) { valueKind = k; }

    UnaryExprKind getOpcode() const { return kind; }

    std::shared_ptr<Expr> getSubExpr() const { return subExpr; }

    void setSubExpr(const std::shared_ptr<Expr>& s) { subExpr = s; }

    static std::string toString(UnaryExprKind op);

    static bool isPrefix(UnaryExprKind op);

    static bool isPostfix(UnaryExprKind op);
};

enum class BinaryExprKind {
    Add,
    Subtract,
    Multiply,
    Divide,
    Mod,
    Equal,              // ==
    NotEqual,           // !=
    LogicalAnd,         // &&
    LogicalOr,          // ||
    GreaterThan,        // >
    GreaterThanOrEqual, // >=
    LessThan,           // <
    LessThanOrEqual,    // <=
    NullCoalescing,     // ??

    // And, // &
    // Xor, // ^
    // Or, // |
};

class BinaryExpr final
    : public Expr
    , public std::enable_shared_from_this<BinaryExpr> {
private:
    Location location;
    ExprValueKind valueKind;
    BinaryExprKind kind;
    std::shared_ptr<Expr> lhs;
    std::shared_ptr<Expr> rhs;

public:
    BinaryExpr(
        const Location& loc,
        BinaryExprKind k,
        const std::shared_ptr<Expr>& l,
        const std::shared_ptr<Expr>& r);

    NodeKind getKind() const noexcept override { return NodeKind::BinaryExpr; }

    Location getLocation() const noexcept override { return location; }

    ExprValueKind getValueKind() const override { return valueKind; }

    void setValueKind(ExprValueKind k) { valueKind = k; }

    static bool isMultiplicativeOp(BinaryExprKind kind);
    bool isMultiplicativeOp() const;

    static bool isAdditiveOp(BinaryExprKind kind);
    bool isAdditiveOp() const;

    static bool isEqualityOp(BinaryExprKind kind);
    bool isEqualityOp() const;

    static bool isComparisonOp(BinaryExprKind kind);
    bool isComparisonOp() const;

    static bool isLogicalOp(BinaryExprKind kind);
    bool isLogicalOp() const;

    BinaryExprKind getOpcode() const { return kind; }

    std::shared_ptr<Expr> getLHS() const { return lhs; }
    std::shared_ptr<Expr> getRHS() const { return rhs; }

    void setLHS(const std::shared_ptr<Expr>& e) { lhs = e; }
    void setRHS(const std::shared_ptr<Expr>& e) { rhs = e; }

    static std::string toString(BinaryExprKind kind);
};

enum class AssignExprKind {
    Assign,
};

class AssignExpr final
    : public Expr
    , public std::enable_shared_from_this<AssignExpr> {
private:
    Location location;
    ExprValueKind valueKind;
    AssignExprKind kind;
    std::shared_ptr<Expr> lhs;
    std::shared_ptr<Expr> rhs;

public:
    AssignExpr(
        const Location& loc,
        AssignExprKind k,
        const std::shared_ptr<Expr>& l,
        const std::shared_ptr<Expr>& r);

    NodeKind getKind() const noexcept override { return NodeKind::AssignExpr; }

    Location getLocation() const noexcept override { return location; }

    ExprValueKind getValueKind() const override { return valueKind; }

    void setValueKind(ExprValueKind k) { valueKind = k; }

    AssignExprKind getOpcode() const { return kind; }

    std::shared_ptr<Expr> getLHS() const { return lhs; }
    std::shared_ptr<Expr> getRHS() const { return rhs; }

    void setLHS(const std::shared_ptr<Expr>& e) { lhs = e; }
    void setRHS(const std::shared_ptr<Expr>& e) { rhs = e; }

    static std::string toString(AssignExprKind kind);
};

class ConditionalOperator final
    : public Expr
    , public std::enable_shared_from_this<ConditionalOperator> {
private:
    Location location;
    ExprValueKind valueKind;
    std::shared_ptr<Expr> condExpr;
    std::shared_ptr<Expr> trueExpr;
    std::shared_ptr<Expr> falseExpr;

public:
    ConditionalOperator(
        const Location& loc,
        const std::shared_ptr<Expr>& cond,
        const std::shared_ptr<Expr>& lhs,
        const std::shared_ptr<Expr>& rhs);

    NodeKind getKind() const noexcept override { return NodeKind::ConditionalOperator; }

    Location getLocation() const noexcept override { return location; }

    ExprValueKind getValueKind() const override { return valueKind; }

    void setValueKind(ExprValueKind k) { valueKind = k; }

    std::shared_ptr<Expr> getCond() const { return condExpr; }
    std::shared_ptr<Expr> getTrueExpr() const { return trueExpr; }
    std::shared_ptr<Expr> getFalseExpr() const { return falseExpr; }
};

class NullConditionalOperator final
    : public Expr
    , public std::enable_shared_from_this<NullConditionalOperator> {
private:
    Location location;
    ExprValueKind valueKind;
    std::shared_ptr<Expr> condExpr;
    std::shared_ptr<Expr> trueExpr;

public:
    NullConditionalOperator(
        const Location& loc,
        const std::shared_ptr<Expr>& cond,
        const std::shared_ptr<Expr>& trueExpr);

    NodeKind getKind() const noexcept override { return NodeKind::NullConditionalOperator; }

    Location getLocation() const noexcept override { return location; }

    ExprValueKind getValueKind() const override { return valueKind; }

    void setValueKind(ExprValueKind k) { valueKind = k; }

    std::shared_ptr<Expr> getCond() const { return condExpr; }
    std::shared_ptr<Expr> getTrueExpr() const { return trueExpr; }
};

class MemberExpr final
    : public Expr
    , public std::enable_shared_from_this<MemberExpr> {
private:
    Location location;
    std::shared_ptr<Expr> base;
    std::shared_ptr<Identifier> memberDecl;

public:
    MemberExpr(
        const Location& loc,
        const std::shared_ptr<Expr>& base,
        const std::shared_ptr<Identifier>& d);

    NodeKind getKind() const noexcept override { return NodeKind::MemberExpr; }

    Location getLocation() const noexcept override { return location; }

    ExprValueKind getValueKind() const override { return ExprValueKind::LValue; }

    std::shared_ptr<Expr> getBase() const;

    std::shared_ptr<Identifier> getMemberDecl() const;
};

class SubscriptExpr final
    : public Expr
    , public std::enable_shared_from_this<SubscriptExpr> {
private:
    Location location;
    std::shared_ptr<Expr> base;
    std::shared_ptr<Expr> index;

public:
    SubscriptExpr(
        const Location& loc, const std::shared_ptr<Expr>& base, const std::shared_ptr<Expr>& index);

    NodeKind getKind() const noexcept override { return NodeKind::SubscriptExpr; }

    Location getLocation() const noexcept override { return location; }

    ExprValueKind getValueKind() const override { return ExprValueKind::LValue; }

    std::shared_ptr<Expr> getBase() const;

    std::shared_ptr<Expr> getIndex() const;
};

class ArrayLiteral final
    : public Expr
    , public std::enable_shared_from_this<ArrayLiteral> {
private:
    Location location;
    std::vector<std::shared_ptr<Expr>> initializers;

public:
    ArrayLiteral(const Location& loc, const std::vector<std::shared_ptr<Expr>>& inits);

    NodeKind getKind() const noexcept override { return NodeKind::ArrayLiteral; }

    Location getLocation() const noexcept override { return location; }

    ExprValueKind getValueKind() const override { return ExprValueKind::RValue; }

    std::vector<std::shared_ptr<Expr>> getInits() const { return initializers; }
};

class MapEntry final
    : public Expr
    , public std::enable_shared_from_this<MapEntry> {
private:
    Location location;
    std::shared_ptr<Expr> key;
    std::shared_ptr<Expr> value;

public:
    MapEntry(
        const Location& loc, const std::shared_ptr<Expr>& key, const std::shared_ptr<Expr>& value);

    NodeKind getKind() const noexcept override { return NodeKind::MapEntry; }

    Location getLocation() const noexcept override { return location; }

    ExprValueKind getValueKind() const override { return ExprValueKind::RValue; }

    std::shared_ptr<Expr> getKey() const { return key; }
    std::shared_ptr<Expr> getValue() const { return value; }
};

class MapLiteral final
    : public Expr
    , public std::enable_shared_from_this<MapLiteral> {
private:
    Location location;
    std::vector<std::shared_ptr<MapEntry>> entries;

public:
    MapLiteral(const Location& loc, const std::vector<std::shared_ptr<MapEntry>>& entries);

    NodeKind getKind() const noexcept override { return NodeKind::MapLiteral; }

    Location getLocation() const noexcept override { return location; }

    ExprValueKind getValueKind() const override { return ExprValueKind::RValue; }

    std::vector<std::shared_ptr<MapEntry>> getEntries() const { return entries; }
};

class CallExpr final
    : public Expr
    , public std::enable_shared_from_this<CallExpr> {
private:
    Location location;
    std::shared_ptr<Expr> callee;
    std::vector<std::shared_ptr<Expr>> arguments;

public:
    CallExpr(
        const Location& loc,
        const std::shared_ptr<Expr>& fn,
        const std::vector<std::shared_ptr<Expr>>& args);

    NodeKind getKind() const noexcept override { return NodeKind::CallExpr; }

    Location getLocation() const noexcept override { return location; }

    ExprValueKind getValueKind() const override { return ExprValueKind::RValue; }

    std::shared_ptr<Expr> getCallee() const { return callee; }
    std::vector<std::shared_ptr<Expr>> getArguments() const { return arguments; }
};

class FuncLiteral final
    : public Expr
    , public std::enable_shared_from_this<FuncLiteral> {
private:
    Location location;
    std::vector<std::shared_ptr<ParamDecl>> parameters;
    std::shared_ptr<TypeRepr> returnType;
    std::shared_ptr<CompoundStmt> compoundStmt;

public:
    FuncLiteral(
        const Location& loc,
        const std::vector<std::shared_ptr<ParamDecl>>& parameters,
        const std::shared_ptr<TypeRepr>& returnType,
        const std::shared_ptr<CompoundStmt>& s);

    NodeKind getKind() const noexcept override { return NodeKind::FuncLiteral; }

    Location getLocation() const noexcept override { return location; }

    ExprValueKind getValueKind() const override { return ExprValueKind::RValue; }

    const std::vector<std::shared_ptr<ParamDecl>>& getParameters() const;

    std::shared_ptr<TypeRepr> getReturnType() const;

    std::shared_ptr<CompoundStmt> getBody() const;
};

class ImplicitConversionExpr final
    : public Expr
    , public std::enable_shared_from_this<ImplicitConversionExpr> {
private:
    Location location;
    std::shared_ptr<Expr> subExpr;

public:
    ImplicitConversionExpr(const Location& loc, const std::shared_ptr<Expr>& e);

    NodeKind getKind() const noexcept override { return NodeKind::ImplicitConversionExpr; }

    Location getLocation() const noexcept override { return location; }

    ExprValueKind getValueKind() const override;

    std::shared_ptr<Expr> getSubExpr() const { return subExpr; }
};

class OptionalEvaluation final {
public:
};

} // namespace elma
