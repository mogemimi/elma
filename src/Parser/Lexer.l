%{
#include "AST/ASTContext.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Identifier.h"
#include "AST/Stmt.h"
#include "Basic/Location.h"
#include "Driver/Driver.h"
#include "Parser/Parser.h"

#include <algorithm>
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <string>
#include <memory>

// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89.  See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
#undef yywrap
#define yywrap() 1

#define YYLTYPE elma::Location
#define YY_DECL elma::Parser::symbol_type yylex(elma::Driver& driver)

namespace {

using elma::Parser;
using elma::CommentKind;
using elma::BoolLiteral;
using elma::DoubleLiteral;
using elma::IntegerLiteral;
using elma::StringLiteral;
using elma::Identifier;

void initialize(elma::Location & loc)
{
    loc.begin.filename = "";
    loc.begin.line = 1;
    loc.begin.column = 1;
    loc.begin.offset = 0;
    loc.end = loc.begin;
}

void lines(elma::Location & loc, int count)
{
    assert(count > 0);
    auto& pos = loc.end;
    pos.column = 1;
    pos.line = std::max(pos.line + count, 1);
}

void columns(elma::Location & loc, int count)
{
    assert(count > 0);
    auto& pos = loc.end;
    pos.column = std::max(pos.column + count, 1);
    pos.offset = std::max(pos.offset + count, 0);
}

void step(elma::Location & loc)
{
    loc.begin = loc.end;
}

// The location of the current token.
elma::Location loc;
std::string comment;

} // end of anonymous namespace
%}

%option header-file="src/Parser/Lexer.h"
%option outfile="src/Parser/Lexer.cpp"
%option noyywrap nounput batch debug noinput
%option nounistd never-interactive

decimal     [1-9]?[0-9]+
integer     -?{decimal}
double      -?({decimal}\.[0-9]*|\.[0-9]+)([eE][-+]?[0-9]+)?
identifier  [a-zA-Z][a-zA-Z_0-9]*
blank       [ \t]
utf8_bom    \xEF\xBB\xBF
crlf        (\r\n|\n)

%{
    // Code run each time a pattern is matched.
    #define YY_USER_ACTION columns(loc, yyleng);
%}

%x CSTYLE_COMMENT
%%
%{
    // Code run each time yylex is called.
    step(loc);
%}

"/*"                    BEGIN(CSTYLE_COMMENT); comment = yytext;
<CSTYLE_COMMENT>"*/"    {
    BEGIN(INITIAL);
    driver.visitComment(loc, CommentKind::Block, comment + yytext);
    comment.clear();
}
<CSTYLE_COMMENT>\n      lines(loc, yyleng); comment += yytext;
<CSTYLE_COMMENT>.       comment += yytext;

"//".*      driver.visitComment(loc, CommentKind::Line, yytext);
{blank}+    step(loc);
{crlf}+     lines(loc, yyleng); step(loc);
^{utf8_bom} step(loc);

"-"         return Parser::make_MINUS(loc);
"+"         return Parser::make_PLUS(loc);
"*"         return Parser::make_STAR(loc);
"/"         return Parser::make_SLASH(loc);
"%"         return Parser::make_MOD(loc);
"="         return Parser::make_ASSIGN(loc);
"-="        return Parser::make_SUB_ASSIGN(loc);
"+="        return Parser::make_ADD_ASSIGN(loc);
"*="        return Parser::make_MUL_ASSIGN(loc);
"/="        return Parser::make_DIV_ASSIGN(loc);
"%="        return Parser::make_MOD_ASSIGN(loc);
"++"        return Parser::make_PLUS_PLUS(loc);
"--"        return Parser::make_MINUS_MINUS(loc);
"!"         return Parser::make_LOGICAL_NOT(loc);
"&&"        return Parser::make_LOGICAL_AND(loc);
"||"        return Parser::make_LOGICAL_OR(loc);
"=="        return Parser::make_EQUAL(loc);
"!="        return Parser::make_NOT_EQUAL(loc);
"<="        return Parser::make_LESS_THAN_EQUAL(loc);
">="        return Parser::make_GREATER_THAN_EQUAL(loc);
"<"         return Parser::make_LESS_THAN(loc);
">"         return Parser::make_GREATER_THAN(loc);
"("         return Parser::make_LEFT_PARENTHESIS(loc);
")"         return Parser::make_RIGHT_PARENTHESIS(loc);
"{"         return Parser::make_LEFT_CURLY_BRACKET(loc);
"}"         return Parser::make_RIGHT_CURLY_BRACKET(loc);
"["         return Parser::make_LEFT_SQUARE_BRACKET(loc);
"]"         return Parser::make_RIGHT_SQUARE_BRACKET(loc);
":"         return Parser::make_COLON(loc);
";"         return Parser::make_SEMICOLON(loc);
","         return Parser::make_COMMA(loc);
"."         return Parser::make_DOT(loc);
"?"         return Parser::make_QUESTION(loc);
"??"        return Parser::make_NULL_COALESCING(loc);
"->"        return Parser::make_ARROW(loc);

"func"      return Parser::make_FUNCTION(loc);
"return"    return Parser::make_RETURN(loc);
"let"       return Parser::make_LET(loc);
"var"       return Parser::make_VAR(loc);
"const"     return Parser::make_CONST(loc);
"if"        return Parser::make_IF(loc);
"else"      return Parser::make_ELSE(loc);
"while"     return Parser::make_WHILE(loc);
"for"       return Parser::make_FOR(loc);
"in"        return Parser::make_IN(loc);
"defer"     return Parser::make_DEFER(loc);
"class"     return Parser::make_CLASS(loc);
"import"    return Parser::make_IMPORT(loc);
"from"      return Parser::make_FROM(loc);
"true"      return Parser::make_BOOL_LITERAL(std::make_shared<BoolLiteral>(loc, true), loc);
"false"     return Parser::make_BOOL_LITERAL(std::make_shared<BoolLiteral>(loc, false), loc);
"null"      return Parser::make_NULL(loc);

\"(\\.|[^\\"])*\" {
    std::string s = yytext;

    // NOTE: Removing double quotes from string.
    assert(s.size() >= 2);
    s = s.substr(1, s.size() - 2);

    return Parser::make_STRING_LITERAL(std::make_shared<StringLiteral>(loc, s), loc);
}

{integer} {
    errno = 0;
    const auto n = strtol(yytext, nullptr, 10);
    if (!(INT_MIN <= n && n <= INT_MAX && errno != ERANGE)) {
        driver.error(loc, "integer is out of range");
    }
    return Parser::make_INTEGER_LITERAL(std::make_shared<IntegerLiteral>(loc, n), loc);
}

{double} {
    errno = 0;
    const auto d = strtod(yytext, nullptr);
    if (errno == ERANGE) {
        driver.error(loc, "double is out of range");
    }
    return Parser::make_DOUBLE_LITERAL(std::make_shared<DoubleLiteral>(loc, d), loc);
}

{identifier}    return Parser::make_IDENTIFIER(std::make_shared<Identifier>(loc, yytext), loc);
.               driver.error(loc, "invalid character");
<<EOF>>         return Parser::make_END(loc);

%%

namespace elma {

void Driver::scanBegin()
{
    yy_flex_debug = this->traceScanning;
    initialize(loc);
}

void Driver::scanEnd()
{
    if (this->defer) {
        this->defer();
        this->defer = nullptr;
    }
}

} // namespace elma
