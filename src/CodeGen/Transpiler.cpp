#include "CodeGen/Transpiler.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Identifier.h"
#include "AST/Stmt.h"
#include "AST/TypeRepr.h"
#include <cassert>
#include <sstream>
#include <utility>

namespace elma {
namespace {

std::string makeIndent(int level)
{
    std::stringstream ss;
    for (int i = 0; i < level; i++) {
        ss << "    ";
    }
    return ss.str();
}

} // end of anonymous namespace

Transpiler::Transpiler()
{
    indent = 0;
}

void Transpiler::writeIndent()
{
    assert(indent >= 0);
    output += makeIndent(indent);
}

void Transpiler::writeString(const std::string& s)
{
    output += s;
}

std::tuple<NodeKind, bool> Transpiler::getOuterNodeKind() const
{
    if (outerStack.size() < 2) {
        return std::make_tuple(NodeKind::Identifier, false);
    }
    return std::make_tuple(outerStack[outerStack.size() - 2], true);
}

bool Transpiler::begin(std::shared_ptr<Node> node)
{
    outerStack.push_back(node->getKind());
    return true;
}

void Transpiler::end(std::shared_ptr<Node> node)
{
    assert(!outerStack.empty());
    outerStack.pop_back();
}

void Transpiler::visit(std::shared_ptr<Identifier> ident)
{
    writeString(ident->getName());
    ASTVisitor::visit(ident);
}

void Transpiler::visit(std::shared_ptr<VarDecl> decl)
{
    writeString(VarDecl::getSpecifierString(decl->getSpecifier()));
    writeString(" ");

    AST::walk(this, decl->getIdentifier());

    if (auto typeAnnotation = decl->getTypeAnnotation()) {
        assert(typeAnnotation);
        writeString(": ");
        AST::walk(this, typeAnnotation);
    }

    if (auto expr = decl->getExpr()) {
        writeString(" = ");
        AST::walk(this, expr);
    }
}

void Transpiler::visit(std::shared_ptr<BindingDecl> decl)
{
    AST::walk(this, decl->getIdentifier());
}

void Transpiler::visit(std::shared_ptr<DecompositionDecl> decl)
{
    writeString(VarDecl::getSpecifierString(decl->getSpecifier()));
    writeString(" (");

    bool needToInsertComma = false;

    for (const auto& binding : decl->getBindings()) {
        if (needToInsertComma) {
            writeString(", ");
        }
        AST::walk(this, binding);
        needToInsertComma = true;
    }

    writeString(")");

    if (auto expr = decl->getExpr()) {
        writeString(" = ");
        AST::walk(this, expr);
    }
}

void Transpiler::visit(std::shared_ptr<FuncDecl> decl)
{
    writeString("function ");

    if (auto ident = decl->getIdentifier()) {
        AST::walk(this, ident);
    }

    {
        writeString("(");
        indent++;
        bool needToInsertComma = false;
        for (const auto& param : decl->getParameters()) {
            if (needToInsertComma) {
                writeString(", ");
            }
            AST::walk(this, param);
            needToInsertComma = true;
        }
        indent--;
        assert(indent >= 0);
        writeString(")");
    }

    writeString(" {\n");

    {
        indent++;
        auto body = decl->getBody();
        assert(body);
        AST::walk(this, body);
        indent--;
        assert(indent >= 0);
    }

    writeIndent();
    writeString("}\n");
}

void Transpiler::visit(std::shared_ptr<ParamDecl> decl)
{
    AST::walk(this, decl->getIdentifier());
}

void Transpiler::visit(std::shared_ptr<ClassDecl> decl)
{
    writeString("class ");
    AST::walk(this, decl->getIdentifier());
    writeString(" {");

    {
        indent++;

        // TODO: Replace the following with std::optional<NodeKind>
        auto prevDeclKind = NodeKind::VarDecl;
        bool prevDeclKindEnabled = false;

        for (const auto& member : decl->getMembers()) {
            writeString("\n");
            if (prevDeclKindEnabled && (prevDeclKind != member->getKind())) {
                writeString("\n");
            }
            writeIndent();
            AST::walk(this, member);
            if (member->getKind() == NodeKind::VarDecl) {
                writeString(";");
            }
            prevDeclKind = member->getKind();
            prevDeclKindEnabled = true;
        }
        if (!prevDeclKindEnabled || (prevDeclKind == NodeKind::VarDecl)) {
            writeString("\n");
        }
        indent--;
        assert(indent >= 0);
    }

    writeIndent();
    writeString("}\n");
}

void Transpiler::visit(std::shared_ptr<IntegerLiteral> expr)
{
    writeString(std::to_string(expr->getValue()));
    ASTVisitor::visit(expr);
}

void Transpiler::visit(std::shared_ptr<DoubleLiteral> expr)
{
    writeString(std::to_string(expr->getValue()));
    ASTVisitor::visit(expr);
}

void Transpiler::visit(std::shared_ptr<BoolLiteral> expr)
{
    writeString(expr->getValue() ? "true" : "false");
    ASTVisitor::visit(expr);
}

void Transpiler::visit(std::shared_ptr<StringLiteral> expr)
{
    writeString('"' + expr->getValue() + '"');
    ASTVisitor::visit(expr);
}

void Transpiler::visit(std::shared_ptr<NullLiteral> expr)
{
    writeString("null");
    ASTVisitor::visit(expr);
}

void Transpiler::visit(std::shared_ptr<ParenExpr> expr)
{
    writeString("(");
    AST::walk(this, expr->getSubExpr());
    writeString(")");
}

void Transpiler::visit(std::shared_ptr<UnaryExpr> expr)
{
    auto op = UnaryExpr::toString(expr->getOpcode());
    auto isPrefix = UnaryExpr::isPrefix(expr->getOpcode());

    if (isPrefix) {
        writeString(op);
    }

    AST::walk(this, expr->getSubExpr());

    if (!isPrefix) {
        writeString(op);
    }
}

void Transpiler::visit(std::shared_ptr<BinaryExpr> expr)
{
    AST::walk(this, expr->getLHS());

    auto op = BinaryExpr::toString(expr->getOpcode());
    writeString(" " + op + " ");

    AST::walk(this, expr->getRHS());
}

void Transpiler::visit(std::shared_ptr<AssignExpr> expr)
{
    AST::walk(this, expr->getLHS());

    auto op = AssignExpr::toString(expr->getOpcode());
    writeString(" " + op + " ");

    AST::walk(this, expr->getRHS());
}

void Transpiler::visit(std::shared_ptr<ConditionalOperator> expr)
{
    // TODO: Not implemented
    AST::walk(this, expr->getCond());
    AST::walk(this, expr->getTrueExpr());
    AST::walk(this, expr->getFalseExpr());
}

void Transpiler::visit(std::shared_ptr<NullConditionalOperator> expr)
{
    AST::walk(this, expr->getTrueExpr());
}

void Transpiler::visit(std::shared_ptr<MemberExpr> expr)
{
    AST::walk(this, expr->getBase());
    if (auto [kind, ok] = getOuterNodeKind(); ok && (kind == NodeKind::NullConditionalOperator)) {
        writeString("?");
    }
    writeString(".");
    AST::walk(this, expr->getMemberDecl());
}

void Transpiler::visit(std::shared_ptr<SubscriptExpr> expr)
{
    AST::walk(this, expr->getBase());

    if (auto [kind, ok] = getOuterNodeKind(); ok && (kind == NodeKind::NullConditionalOperator)) {
        writeString("?");
    }

    writeString("[");
    AST::walk(this, expr->getIndex());
    writeString("]");
}

void Transpiler::visit(std::shared_ptr<ArrayLiteral> expr)
{
    writeString("[");

    indent++;
    bool needToInsertComma = false;
    bool multiline = expr->getLocation().begin.line < expr->getLocation().end.line;
    for (const auto& e : expr->getInits()) {
        if (multiline) {
            writeString("\n");
            writeIndent();
        }
        else {
            if (needToInsertComma) {
                writeString(", ");
            }
        }
        AST::walk(this, e);
        if (multiline) {
            writeString(",");
        }
        needToInsertComma = true;
    }
    indent--;
    if (multiline) {
        writeString("\n");
        writeIndent();
    }
    assert(indent >= 0);

    writeString("]");
}

void Transpiler::visit(std::shared_ptr<MapEntry> expr)
{
    AST::walk(this, expr->getKey());
    writeString(": ");
    AST::walk(this, expr->getValue());
}

void Transpiler::visit(std::shared_ptr<MapLiteral> expr)
{
    writeString("[");

    if (expr->getEntries().empty()) {
        writeString(":]");
        return;
    }

    indent++;
    bool needToInsertComma = false;
    bool multiline = expr->getLocation().begin.line < expr->getLocation().end.line;
    for (const auto& e : expr->getEntries()) {
        if (multiline) {
            writeString("\n");
            writeIndent();
        }
        else {
            if (needToInsertComma) {
                writeString(", ");
            }
        }
        AST::walk(this, e);
        if (multiline) {
            writeString(",");
        }
        needToInsertComma = true;
    }
    indent--;
    assert(indent >= 0);
    if (multiline) {
        writeString("\n");
        writeIndent();
    }

    writeString("]");
}

void Transpiler::visit(std::shared_ptr<CallExpr> expr)
{
    if (auto callee = expr->getCallee()) {
        AST::walk(this, callee);
    }

    if (auto [kind, ok] = getOuterNodeKind(); ok && (kind == NodeKind::NullConditionalOperator)) {
        writeString("?");
    }

    bool needToInsertSpace = false;
    writeString("(");
    for (auto& arg : expr->getArguments()) {
        if (needToInsertSpace) {
            writeString(", ");
        }
        AST::walk(this, arg);
        needToInsertSpace = true;
    }
    writeString(")");
}

void Transpiler::visit(std::shared_ptr<FuncLiteral> expr)
{
    writeString("function ");

    {
        writeString("(");
        indent++;
        bool needToInsertComma = false;
        for (const auto& param : expr->getParameters()) {
            if (needToInsertComma) {
                writeString(", ");
            }
            AST::walk(this, param);
            needToInsertComma = true;
        }
        indent--;
        assert(indent >= 0);
        writeString(")");
    }

    if (auto returnType = expr->getReturnType()) {
        writeString(" -> ");
        AST::walk(this, returnType);
    }

    writeString(" {\n");

    {
        indent++;
        auto body = expr->getBody();
        assert(body);
        AST::walk(this, body);
        indent--;
        assert(indent >= 0);
    }

    writeIndent();
    writeString("}");
}

void Transpiler::visit(std::shared_ptr<CompoundStmt> stmt)
{
    for (auto& subStmt : stmt->getStatements()) {
        writeIndent();
        AST::walk(this, subStmt);

        switch (subStmt->getKind()) {
        case NodeKind::DeclStmt:
        case NodeKind::ExprStmt: {
            writeString(";\n");
            break;
        }
        default: break;
        }
    }
}

void Transpiler::visit(std::shared_ptr<ReturnStmt> stmt)
{
    writeString("return");

    if (auto expr = stmt->getExpr()) {
        writeString(" ");

        indent++;
        AST::walk(this, expr);
        indent--;
        assert(indent >= 0);
    }

    writeString(";\n");
}

void Transpiler::visit(std::shared_ptr<DeferStmt> stmt)
{
    writeString("defer ");
    writeString("{\n");

    if (auto bodyStmt = stmt->getBody()) {
        indent++;
        AST::walk(this, bodyStmt);
        indent--;
        assert(indent >= 0);
    }

    writeIndent();
    writeString("}\n");
}

void Transpiler::visit(std::shared_ptr<IfStmt> stmt)
{
    writeString("if (");

    if (auto condExpr = stmt->getCond()) {
        AST::walk(this, condExpr);
    }

    writeString(") {\n");

    if (auto thenStmt = stmt->getThen()) {
        indent++;
        AST::walk(this, thenStmt);
        indent--;
        assert(indent >= 0);
    }
    if (auto elseStmt = stmt->getElse()) {
        indent++;
        AST::walk(this, elseStmt);
        indent--;
        assert(indent >= 0);
    }

    writeIndent();
    writeString("}\n");
}

void Transpiler::visit(std::shared_ptr<WhileStmt> stmt)
{
    writeString("while (");

    if (auto condExpr = stmt->getCond()) {
        AST::walk(this, condExpr);
    }

    writeString(") {\n");

    if (auto bodyStmt = stmt->getBody()) {
        indent++;
        AST::walk(this, bodyStmt);
        indent--;
        assert(indent >= 0);
    }

    writeIndent();
    writeString("}\n");
}

void Transpiler::visit(std::shared_ptr<ForStmt> stmt)
{
    writeString("for (");

    if (auto initStmt = stmt->getInit()) {
        AST::walk(this, initStmt);
    }
    writeString(";");

    if (auto condExpr = stmt->getCond()) {
        writeString(" ");
        AST::walk(this, condExpr);
    }
    writeString(";");

    if (auto incExpr = stmt->getInc()) {
        writeString(" ");
        indent++;
        AST::walk(this, incExpr);
        indent--;
        assert(indent >= 0);
    }
    writeString(") {\n");

    if (auto bodyStmt = stmt->getBody()) {
        indent++;
        AST::walk(this, bodyStmt);
        indent--;
        assert(indent >= 0);
    }

    writeIndent();
    writeString("}\n");
}

void Transpiler::visit(std::shared_ptr<ForEachStmt> stmt)
{
    // TODO: Not implemented
    if (auto loopVariable = stmt->getLoopVariable()) {
        AST::walk(this, loopVariable);
    }
    if (auto rangeExpr = stmt->getRangeExpr()) {
        AST::walk(this, rangeExpr);
    }
    if (auto bodyStmt = stmt->getBody()) {
        AST::walk(this, bodyStmt);
    }
}

} // namespace elma
