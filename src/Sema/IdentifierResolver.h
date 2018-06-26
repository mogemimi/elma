#pragma once

#include "AST/ASTVisitor.h"
#include "Basic/Forward.h"
#include "Sema/Scope.h"
#include <memory>
#include <string>
#include <vector>

namespace elma {

struct IdentifierContext final {
    std::vector<std::shared_ptr<Entity>> entities;
};

class IdentifierResolver final : public ASTVisitor {
private:
    std::vector<std::shared_ptr<Scope>> scopeStack;
    ASTContext* astContext;
    IdentifierContext* context;
    std::shared_ptr<DiagnosticHandler> diag;

public:
    IdentifierResolver(
        ASTContext* astContext,
        IdentifierContext* context,
        const std::shared_ptr<DiagnosticHandler>& diag);

    std::shared_ptr<Scope> getCurrentScope();

    void pushScope(const std::shared_ptr<Scope>& scope);
    void popScope();

    void error(const Location& l, const std::string& err);

    bool begin(std::shared_ptr<Node> node) override;
    void end(std::shared_ptr<Node> node) override;

    void visit(std::shared_ptr<VarDecl> decl) override;
    void visit(std::shared_ptr<FuncDecl> decl) override;
    void visit(std::shared_ptr<ParamDecl> decl) override;
    void visit(std::shared_ptr<ClassDecl> decl) override;

    void visit(std::shared_ptr<IdentifierExpr> expr) override;

    void visit(std::shared_ptr<SimpleIdentTypeRepr> repr) override;
    void visit(std::shared_ptr<GenericIdentTypeRepr> repr) override;
    void visit(std::shared_ptr<OptionalTypeRepr> repr) override;
};

} // namespace elma
