#pragma once

#include "AST/ASTVisitor.h"
#include "Basic/Forward.h"
#include <memory>
#include <string>
#include <vector>

namespace elma {

class ASTFormatter final : public ASTVisitor {
public:
    void visit(std::shared_ptr<IfStmt> stmt) override;
    void visit(std::shared_ptr<WhileStmt> stmt) override;
    void visit(std::shared_ptr<ForStmt> stmt) override;
    void visit(std::shared_ptr<ForEachStmt> stmt) override;
    void visit(std::shared_ptr<ParenExpr> stmt) override;
};

} // namespace elma
