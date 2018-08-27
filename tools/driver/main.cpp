#include "AST/ASTContext.h"
#include "AST/Decl.h"
#include "AST/Identifier.h"
#include "Basic/Diagnostic.h"
#include "CodeGen/Transpiler.h"
#include "Driver/Driver.h"
#include "Printer/ASTFormatter.h"
#include "Sema/Entity.h"
#include "Sema/IdentifierResolver.h"
#include "Sema/SemaChecker.h"
#include "Sema/TypeInferer.h"
#include "Sema/TypeResolver.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace elma;

namespace {

struct CommandLineParser final {
    std::string executablePath;
    std::vector<std::string> arguments;

    void parse(int argc, const char *argv[])
    {
        assert(argc > 0);
        assert(argv != nullptr);

        if (argc >= 1) {
            executablePath = argv[0];
        }

        for (int i = 1; i < argc; i++) {
            std::string arg = argv[i];
            arguments.push_back(arg);
        }
    }
};

void fatalError(const std::string &what)
{
    std::cerr << what << std::endl;
}

} // end of anonymous namespace

int main(int argc, const char *argv[])
{
    CommandLineParser cmd;
    cmd.parse(argc, argv);

    if (cmd.arguments.empty()) {
        fatalError("no file");
        return 1;
    }

    auto filePath = cmd.arguments.front();
    auto stream = std::make_shared<StdoutDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    elma::Driver driver;
    auto [ast, ok] = driver.parseFile(filePath, diag);

    if (!ok) {
        fatalError("parse error");
        return 1;
    }

    ASTFormatter formatter;
    AST::walk(&formatter, ast.translationUnit);

    IdentifierContext context;
    IdentifierResolver resolver(&ast, &context, diag);
    AST::walk(&resolver, ast.translationUnit);
    if (diag->hasError()) {
        fatalError("identifier resolver error");
        return 1;
    }

    SemaChecker semaChecker(diag);
    AST::walk(&semaChecker, ast.translationUnit);
    if (diag->hasError()) {
        fatalError("sema check error");
        return 1;
    }

    TypeResolver typeResolver(diag);
    AST::walk(&typeResolver, ast.translationUnit);
    if (diag->hasError()) {
        fatalError("type resolver error");
        return 1;
    }

    Transpiler transpiler;
    AST::walk(&transpiler, ast.translationUnit);
    if (diag->hasError()) {
        fatalError("transpiler error");
        return 1;
    }

    std::cout << transpiler.getResult();
    return 0;
}
