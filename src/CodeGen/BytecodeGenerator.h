#pragma once

#include "AST/ASTVisitor.h"
#include "Basic/Forward.h"
#include "CodeGen/Instruction.h"
#include <memory>
#include <string>
#include <vector>

namespace elma {

class BytecodeGenerator final : public ASTVisitor {
private:
    BytecodeProgram program;

public:
    BytecodeProgram getProgram() const { return program; }

    void visit(const std::shared_ptr<CompoundStmt>& stmt, Invoke&& traverse) override;
    void visit(const std::shared_ptr<DeclStmt>& stmt, Invoke&& traverse) override;
    void visit(const std::shared_ptr<ReturnStmt>& stmt, Invoke&& traverse) override;
    void visit(const std::shared_ptr<IfStmt>& stmt, Invoke&& traverse) override;
    void visit(const std::shared_ptr<WhileStmt>& stmt, Invoke&& traverse) override;
    void visit(const std::shared_ptr<ForStmt>& stmt, Invoke&& traverse) override;

    void visit(const std::shared_ptr<CallExpr>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<FuncLiteral>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<IntegerLiteral>& expr) override;
    void visit(const std::shared_ptr<DoubleLiteral>& expr) override;
    void visit(const std::shared_ptr<BoolLiteral>& expr) override;
    void visit(const std::shared_ptr<StringLiteral>& expr) override;
    void visit(const std::shared_ptr<BinaryExpr>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<UnaryExpr>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<IdentifierExpr>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<MemberExpr>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<ImplicitConversionExpr>& expr, Invoke&& traverse) override;

    void visit(const std::shared_ptr<TranslationUnitDecl>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<FuncDecl>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<VarDecl>& decl, Invoke&& traverse) override;

private:
    void addInstruction(const std::shared_ptr<Instruction>& inst);
    // void addInstruction(Opcode opcode, int32_t operand);
};

} // namespace elma
