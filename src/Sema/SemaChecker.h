#pragma once

#include "AST/ASTVisitor.h"
#include "Basic/Forward.h"
#include <memory>

namespace elma {

class SemaChecker final : public ASTVisitor {
private:
    std::shared_ptr<DiagnosticHandler> diag;

public:
    explicit SemaChecker(const std::shared_ptr<DiagnosticHandler>& diag);

    void error(const Location& l, const std::string& err);

    void visit(std::shared_ptr<IfStmt> stmt) override;
    void visit(std::shared_ptr<WhileStmt> stmt) override;
    void visit(std::shared_ptr<ForStmt> stmt) override;

    void visit(std::shared_ptr<AssignExpr> expr) override;

    void visit(std::shared_ptr<TranslationUnitDecl> decl) override;
    void visit(std::shared_ptr<ClassDecl> decl) override;
};

} // namespace elma
