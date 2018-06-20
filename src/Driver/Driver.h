#pragma once

#include "AST/ASTContext.h"
#include "AST/Comment.h"
#include "Basic/Forward.h"
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <tuple>

namespace elma {

class Driver final {
private:
    std::shared_ptr<DiagnosticHandler> diag;
    std::function<void()> defer;
    bool traceScanning;

public:
    ASTContext ast;
    std::string file;
    std::string sourceText;

    std::tuple<ASTContext, bool>
    parseFile(const std::string& filename, const std::shared_ptr<DiagnosticHandler>& diag);

    std::tuple<ASTContext, bool>
    parseString(const std::string& text, const std::shared_ptr<DiagnosticHandler>& diag);

    void scanBegin();
    void scanEnd();

    void visitComment(const Location& loc, CommentKind kind, const std::string& comment);
    void error(const Location& loc, const std::string& what);
    void error(const std::string& what);
};

} // namespace elma
