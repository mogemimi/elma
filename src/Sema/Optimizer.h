#pragma once

#include "AST/ASTVisitor.h"
#include "AST/Type.h"
#include "Basic/Forward.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace elma {

class Optimizer final : public ASTVisitor {
    std::shared_ptr<DiagnosticHandler> diag;
    // std::unordered_map<const Entity*, Value> constants;

public:
    explicit Optimizer(const std::shared_ptr<DiagnosticHandler>& diag);

    void error(const Location& l, const std::string& err);

    void visit(const std::shared_ptr<BinaryExpr>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<UnaryExpr>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<IdentifierExpr>& expr, Invoke&& traverse) override;

    void visit(const std::shared_ptr<VarDecl>& decl, Invoke&& traverse) override;
};

} // namespace elma
