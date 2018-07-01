%skeleton "lalr1.cc"
%require "3.0.4"
%defines "src/Parser/Parser.h"
%output "src/Parser/Parser.cpp"
%define parser_class_name {Parser}
%define api.namespace {elma}
%define api.token.constructor
%define api.value.type variant
%define api.location.type {elma::Location}
%define parse.assert

%code requires
{
#include "AST/ASTContext.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Identifier.h"
#include "AST/Stmt.h"
#include "AST/TypeRepr.h"
#include "Basic/Location.h"
#include "Basic/Forward.h"
#include <memory>
#include <string>
#include <tuple>
#include <vector>

#ifndef YY_NULLPTR
#define YY_NULLPTR nullptr
#endif

namespace elma {
class Driver;

using CallSignature = std::tuple<
    std::vector<std::shared_ptr<ParamDecl>>,
    std::shared_ptr<TypeRepr>>;
} // namespace elma
}

%param { elma::Driver& driver }

%locations
%initial-action
{
    // Initialize the initial location.
    @$.begin.filename = driver.file;
    @$.end.filename = driver.file;
};

%define parse.trace
%define parse.error verbose

%code
{
#include "Driver/Driver.h"

elma::Parser::symbol_type yylex(elma::Driver& driver);
}

%define api.token.prefix {TOK_}

%token END 0                "end of file"
%token ASSIGN               "="
%token MINUS                "-"
%token PLUS                 "+"
%token STAR                 "*"
%token SLASH                "/"
%token MOD                  "%"
%token SUB_ASSIGN           "-="
%token ADD_ASSIGN           "+="
%token MUL_ASSIGN           "*="
%token DIV_ASSIGN           "/="
%token MOD_ASSIGN           "%="
%token PLUS_PLUS            "++"
%token MINUS_MINUS          "--"
%token LOGICAL_NOT          "!"
%token LOGICAL_AND          "&&"
%token LOGICAL_OR           "||"
%token EQUAL                "=="
%token NOT_EQUAL            "!="
%token LESS_THAN_EQUAL      "<="
%token GREATER_THAN_EQUAL   ">="
%token LESS_THAN            "<"
%token GREATER_THAN         ">"
%token LEFT_PARENTHESIS     "("
%token RIGHT_PARENTHESIS    ")"
%token LEFT_CURLY_BRACKET   "{"
%token RIGHT_CURLY_BRACKET  "}"
%token LEFT_SQUARE_BRACKET  "["
%token RIGHT_SQUARE_BRACKET "]"
%token COLON                ":"
%token SEMICOLON            ";"
%token COMMA                ","
%token DOT                  "."
%token QUESTION             "?"
%token NULL_COALESCING      "??"
%token ARROW                "->"
%token FUNCTION             "func"
%token RETURN               "return"
%token LET                  "let"
%token VAR                  "var"
%token CONST                "const"
%token IF                   "if"
%token ELSE                 "else"
%token WHILE                "while"
%token FOR                  "for"
%token IN                   "in"
%token DEFER                "defer"
%token CLASS                "class"
%token NULL                 "null"

%token <std::shared_ptr<Identifier>>                IDENTIFIER "identifier"
%token <std::shared_ptr<IntegerLiteral>>            INTEGER_LITERAL "integer_literal"
%token <std::shared_ptr<DoubleLiteral>>             DOUBLE_LITERAL "double_literal"
%token <std::shared_ptr<BoolLiteral>>               BOOL_LITERAL "bool_literal"
%token <std::shared_ptr<StringLiteral>>             STRING_LITERAL "string_literal"

%type  <std::shared_ptr<Expr>>                      Literal
%type  <std::shared_ptr<NullLiteral>>               NullLiteral
%type  <std::shared_ptr<ArrayLiteral>>              ArrayLiteral
%type  <std::shared_ptr<MapLiteral>>                MapLiteral
%type  <std::vector<std::shared_ptr<MapEntry>>>     MapEntryList
%type  <std::shared_ptr<MapEntry>>                  MapEntry
%type  <std::shared_ptr<FuncLiteral>>               FuncLiteral

%type  <std::shared_ptr<TranslationUnitDecl>>       TranslationUnitDecl
%type  <std::vector<std::shared_ptr<Decl>>>         TopLevelDeclarationList
%type  <std::shared_ptr<Decl>>                      TopLevelDeclaration
%type  <std::shared_ptr<VarDecl>>                   VarDecl
%type  <VarDeclSpecifier>                           VarDeclSpecifier
%type  <std::shared_ptr<DecompositionDecl>>         DecompositionDecl
%type  <std::vector<std::shared_ptr<BindingDecl>>>  BindingDeclList
%type  <std::shared_ptr<BindingDecl>>               BindingDecl
%type  <std::shared_ptr<ClassDecl>>                 ClassDecl
%type  <std::vector<std::shared_ptr<Decl>>>         ClassMemberDeclList
%type  <std::shared_ptr<Decl>>                      ClassMemberDecl
%type  <std::shared_ptr<FuncDecl>>                  FuncDecl
%type  <CallSignature>                              CallSignature
%type  <std::vector<std::shared_ptr<ParamDecl>>>    ParamDeclList
%type  <std::shared_ptr<ParamDecl>>                 ParamDecl

%type  <std::shared_ptr<Expr>>                      Expression
%type  <std::vector<std::shared_ptr<Expr>>>         ExpressionList
%type  <std::shared_ptr<Expr>>                      PrimaryExpr
%type  <std::shared_ptr<NullConditionalOperator>>   NullConditionalOperator
%type  <std::shared_ptr<UnaryExpr>>                 UnaryExpr
%type  <UnaryExprKind>                              unary_op
%type  <std::shared_ptr<BinaryExpr>>                BinaryExpr
%type  <BinaryExprKind>                             binary_op
%type  <std::shared_ptr<AssignExpr>>                AssignExpr
%type  <std::shared_ptr<ConditionalOperator>>       ConditionalOperator
%type  <std::shared_ptr<ParenExpr>>                 ParenExpr
%type  <std::shared_ptr<MemberExpr>>                MemberExpr
%type  <std::shared_ptr<SubscriptExpr>>             SubscriptExpr
%type  <std::shared_ptr<CallExpr>>                  CallExpr

%type  <std::shared_ptr<Stmt>>                      Statement
%type  <std::vector<std::shared_ptr<Stmt>>>         StatementList
%type  <std::shared_ptr<CompoundStmt>>              CompoundStmt
%type  <std::shared_ptr<ReturnStmt>>                ReturnStmt
%type  <std::shared_ptr<DeferStmt>>                 DeferStmt
%type  <std::shared_ptr<IfStmt>>                    IfStmt
%type  <std::shared_ptr<WhileStmt>>                 WhileStmt
%type  <std::shared_ptr<ForStmt>>                   ForStmt
%type  <std::shared_ptr<Stmt>>                      ForInitStmt
%type  <std::shared_ptr<ForEachStmt>>               ForEachStmt
%type  <std::shared_ptr<Decl>>                      ForEachInitDecl

%type  <std::shared_ptr<TypeRepr>>                  TypeRepr
%type  <std::vector<std::shared_ptr<TypeRepr>>>     TypeReprList

%left ",";
%right "=";
%right "conditional_expression";
%left "binary_op";
%left "||";
%left "&&";
%left "==" "!=";
%left "<=" ">=" "<" ">";
%right "??";
%left "+" "-";
%left "*" "/" "%";
%left ":";
%right "unary_plus" "unary_minus";
%right "++" "--" "!";
%right "ternary_question";
%left "." "[" "]";
%nonassoc "(" ")" "grouping";
%nonassoc "then";
%nonassoc "else";

%%
%start TranslationUnitDecl;

TranslationUnitDecl:
  %empty                  { driver.ast.translationUnit = std::make_shared<TranslationUnitDecl>(@$, std::vector<std::shared_ptr<Decl>>{}); }
| TopLevelDeclarationList { driver.ast.translationUnit = std::make_shared<TranslationUnitDecl>(@$, $1); }
;

TopLevelDeclarationList:
  TopLevelDeclaration                         { $$.push_back($1); }
| TopLevelDeclarationList TopLevelDeclaration { $1.push_back($2); $$ = std::move($1); }
;

TopLevelDeclaration:
  ClassDecl   { $$ = $1; }
| FuncDecl    { $$ = $1; }
| VarDecl ";" { $$ = $1; }
;

FuncDecl:
  "func" "identifier" CallSignature CompoundStmt { $$ = std::make_shared<FuncDecl>(@$, $2, std::get<0>($3), std::get<1>($3), $4); }
;

FuncLiteral:
  "func" CallSignature CompoundStmt { $$ = std::make_shared<FuncLiteral>(@$, std::get<0>($2), std::get<1>($2), $3); }
;

CallSignature:
  "(" ")"                             { std::get<1>($$) = nullptr; }
| "(" ")" "->" TypeRepr               { std::get<1>($$) = $4; }
| "(" ParamDeclList ")"               { std::get<0>($$) = $2; std::get<1>($$) = nullptr; }
| "(" ParamDeclList ")" "->" TypeRepr { std::get<0>($$) = $2; std::get<1>($$) = $5; }
;

ParamDeclList:
  ParamDecl                   { $$.push_back($1); }
| ParamDeclList "," ParamDecl { $1.push_back($3); $$ = std::move($1); }
;

ParamDecl:
  "identifier"              { $$ = std::make_shared<ParamDecl>(@$, $1); }
| "identifier" ":" TypeRepr { $$ = std::make_shared<ParamDecl>(@$, $1, $3); }
;

TypeRepr:
  "identifier"                      { $$ = std::make_shared<SimpleIdentTypeRepr>(@$, $1); }
| "identifier" "<" TypeReprList ">" { $$ = std::make_shared<GenericIdentTypeRepr>(@$, $1, $3); }
| TypeRepr "?"                      { $$ = std::make_shared<OptionalTypeRepr>(@$, $1); }
;

TypeReprList:
  TypeRepr                    { $$.push_back($1); }
| TypeReprList  "," TypeRepr  { $1.push_back($3); $$ = std::move($1); }
;

ClassDecl:
  "class" "identifier" "{" "}"                      { $$ = std::make_shared<ClassDecl>(@$, $2, std::vector<std::shared_ptr<Decl>>{}); }
| "class" "identifier" "{" ClassMemberDeclList "}"  { $$ = std::make_shared<ClassDecl>(@$, $2, $4); }
;

ClassMemberDeclList:
  ClassMemberDecl                     { $$.push_back($1); }
| ClassMemberDeclList ClassMemberDecl { $1.push_back($2); $$ = std::move($1); }
;

ClassMemberDecl:
  FuncDecl    { $$ = $1; }
| VarDecl ";" { $$ = $1; }
;

Statement:
  CompoundStmt          { $$ = $1; }
| Expression ";"        { $$ = std::make_shared<ExprStmt>(@$, $1); }
| ReturnStmt            { $$ = $1; }
| VarDecl ";"           { $$ = std::make_shared<DeclStmt>(@$, $1); }
| DecompositionDecl ";" { $$ = std::make_shared<DeclStmt>(@$, $1); }
| IfStmt                { $$ = $1; }
| WhileStmt             { $$ = $1; }
| ForStmt               { $$ = $1; }
| ForEachStmt           { $$ = $1; }
| DeferStmt             { $$ = $1; }
;

CompoundStmt:
  "{" "}"               { $$ = std::make_shared<CompoundStmt>(@$, std::vector<std::shared_ptr<Stmt>>{}); }
| "{" StatementList "}" { $$ = std::make_shared<CompoundStmt>(@$, $2); }
;

StatementList:
  Statement               { $$.push_back($1); }
| StatementList Statement { $1.push_back($2); $$ = std::move($1); }
;

ReturnStmt:
  "return" ";"            { $$ = std::make_shared<ReturnStmt>(@$); }
| "return" Expression ";" { $$ = std::make_shared<ReturnStmt>(@$, $2); }
;

IfStmt:
  "if" "(" Expression ")" Statement %prec "then"      { $$ = std::make_shared<IfStmt>(@$, $3, $5); }
| "if" "(" Expression ")" Statement "else" Statement  { $$ = std::make_shared<IfStmt>(@$, $3, $5, $7); }
;

WhileStmt:
  "while" "(" Expression ")" Statement { $$ = std::make_shared<WhileStmt>(@$, $3, $5); }
;

ForStmt:
  "for" "(" ForInitStmt Expression ";" Expression ")" Statement  { $$ = std::make_shared<ForStmt>(@$, $3, $4, $6, $8); }
;

ForInitStmt:
  ";"             { }
| Expression ";"  { $$ = std::make_shared<ExprStmt>(@$, $1); }
| VarDecl ";"     { $$ = std::make_shared<DeclStmt>(@$, $1); }
;

ForEachStmt:
  "for" "(" ForEachInitDecl "in" Expression ")" Statement { $$ = std::make_shared<ForEachStmt>(@$, $3, $5, $7); }
;

ForEachInitDecl:
  "identifier"                              { $$ = std::make_shared<NamedDecl>(@$, $1); }
| VarDeclSpecifier "identifier"             { $$ = std::make_shared<VarDecl>(@$, $2, $1, nullptr, nullptr); }
| VarDeclSpecifier "(" BindingDeclList ")"  { $$ = std::make_shared<DecompositionDecl>(@$, $1, $3); }
;

DeferStmt:
  "defer" Statement { $$ = std::make_shared<DeferStmt>(@$, $2); }
;

VarDecl:
  VarDeclSpecifier "identifier"                             { $$ = std::make_shared<VarDecl>(@$, $2, $1, nullptr, nullptr); }
| VarDeclSpecifier "identifier" "=" Expression              { $$ = std::make_shared<VarDecl>(@$, $2, $1, nullptr, $4); }
| VarDeclSpecifier "identifier" ":" TypeRepr                { $$ = std::make_shared<VarDecl>(@$, $2, $1, $4, nullptr); }
| VarDeclSpecifier "identifier" ":" TypeRepr "=" Expression { $$ = std::make_shared<VarDecl>(@$, $2, $1, $4, $6); }
;

VarDeclSpecifier:
  "let"   { $$ = VarDeclSpecifier::Let; }
| "var"   { $$ = VarDeclSpecifier::Var; }
| "const" { $$ = VarDeclSpecifier::Const; }
;

DecompositionDecl:
  VarDeclSpecifier "(" BindingDeclList ")" "=" Expression { $$ = std::make_shared<DecompositionDecl>(@$, $1, $3, $6); }
;

BindingDeclList:
  BindingDecl                     { $$.push_back($1); }
| BindingDeclList "," BindingDecl { $1.push_back($3); $$ = std::move($1); }
;

BindingDecl:
  "identifier"  { $$ = std::make_shared<BindingDecl>(@$, $1); }
;

comma_opt:
  %empty  { }
| ","     { }
;

Literal:
  "integer_literal" { $$ = $1; }
| "double_literal"  { $$ = $1; }
| "bool_literal"    { $$ = $1; }
| "string_literal"  { $$ = $1; }
;

PrimaryExpr:
  Literal                 { $$ = $1; }
| NullLiteral             { $$ = $1; }
| "identifier"            { $$ = std::make_shared<IdentifierExpr>(@$, $1); }
| ParenExpr               { $$ = $1; }
| ArrayLiteral            { $$ = $1; }
| MapLiteral              { $$ = $1; }
| CallExpr                { $$ = $1; }
| MemberExpr              { $$ = $1; }
| SubscriptExpr           { $$ = $1; }
| NullConditionalOperator { $$ = $1; }
;

ParenExpr:
  "(" Expression ")" %prec "grouping" { $$ = std::make_shared<ParenExpr>(@$, $2); }
;

NullLiteral:
  "null"  { $$ = std::make_shared<NullLiteral>(@$); }
;

ArrayLiteral:
  "[" "]"                           { $$ = std::make_shared<ArrayLiteral>(@$, std::vector<std::shared_ptr<Expr>>{}); }
| "[" ExpressionList comma_opt "]"  { $$ = std::make_shared<ArrayLiteral>(@$, $2); }
;

MapLiteral:
  "[" ":" "]"                     { $$ = std::make_shared<MapLiteral>(@$, std::vector<std::shared_ptr<MapEntry>>{}); }
| "[" MapEntryList comma_opt "]"  { $$ = std::make_shared<MapLiteral>(@$, $2); }
;

MapEntry:
  Expression ":" Expression { $$ = std::make_shared<MapEntry>(@$, $1, $3); }
;

MapEntryList:
  MapEntry                  { $$.push_back($1); }
| MapEntryList "," MapEntry { $1.push_back($3); $$ = std::move($1); }
;

MemberExpr:
  PrimaryExpr "." "identifier" { $$ = std::make_shared<MemberExpr>(@$, $1, $3); }
;

SubscriptExpr:
  PrimaryExpr "[" Expression "]" { $$ = std::make_shared<SubscriptExpr>(@$, $1, $3); }
;

CallExpr:
  PrimaryExpr "(" ")"                 { $$ = std::make_shared<CallExpr>(@$, $1, std::vector<std::shared_ptr<Expr>>{}); }
| PrimaryExpr "(" ExpressionList ")"  { $$ = std::make_shared<CallExpr>(@$, $1, $3); }
;

NullConditionalOperator:
  PrimaryExpr "?" "." "identifier"        { $$ = std::make_shared<NullConditionalOperator>(@$, $1, std::make_shared<MemberExpr>(@$, $1, $4)); }
| PrimaryExpr "?" "[" Expression "]"      { $$ = std::make_shared<NullConditionalOperator>(@$, $1, std::make_shared<SubscriptExpr>(@$, $1, $4)); }
| PrimaryExpr "?" "(" ")"                 { $$ = std::make_shared<NullConditionalOperator>(@$, $1, std::make_shared<CallExpr>(@$, $1, std::vector<std::shared_ptr<Expr>>{})); }
| PrimaryExpr "?" "(" ExpressionList ")"  { $$ = std::make_shared<NullConditionalOperator>(@$, $1, std::make_shared<CallExpr>(@$, $1, $4)); }
;

UnaryExpr:
  unary_op PrimaryExpr  { $$ = std::make_shared<UnaryExpr>(@$, $1, $2); }
| PrimaryExpr "++"      { $$ = std::make_shared<UnaryExpr>(@$, UnaryExprKind::PostInc, $1); }
| PrimaryExpr "--"      { $$ = std::make_shared<UnaryExpr>(@$, UnaryExprKind::PostDec, $1); }
;

unary_op:
  "++"                    { $$ = UnaryExprKind::PreInc; }
| "--"                    { $$ = UnaryExprKind::PreDec; }
| "+" %prec "unary_plus"  { $$ = UnaryExprKind::Plus; }
| "-" %prec "unary_minus" { $$ = UnaryExprKind::Minus; }
| "!"                     { $$ = UnaryExprKind::LogicalNot; }
;

BinaryExpr:
  Expression binary_op Expression %prec "binary_op" { $$ = std::make_shared<BinaryExpr>(@$, $2, $1, $3); }
;

binary_op:
  "+"   { $$ = BinaryExprKind::Add; }
| "-"   { $$ = BinaryExprKind::Subtract; }
| "*"   { $$ = BinaryExprKind::Multiply; }
| "/"   { $$ = BinaryExprKind::Divide; }
| "%"   { $$ = BinaryExprKind::Mod; }
| "=="  { $$ = BinaryExprKind::Equal; }
| "!="  { $$ = BinaryExprKind::NotEqual; }
| "&&"  { $$ = BinaryExprKind::LogicalAnd; }
| "||"  { $$ = BinaryExprKind::LogicalOr; }
| ">"   { $$ = BinaryExprKind::GreaterThan; }
| ">="  { $$ = BinaryExprKind::GreaterThanOrEqual; }
| "<"   { $$ = BinaryExprKind::LessThan; }
| "<="  { $$ = BinaryExprKind::LessThanOrEqual; }
| "??"  { $$ = BinaryExprKind::NullCoalescing; }
;

ConditionalOperator:
  PrimaryExpr ternary_question Expression ":" Expression %prec "conditional_expression" { $$ = std::make_shared<ConditionalOperator>(@$, $1, $3, $5); }
;

ternary_question:
  "?" %prec "ternary_question"  { }
;

AssignExpr:
  Expression "=" Expression     { $$ = std::make_shared<AssignExpr>(@$, AssignExprKind::Assign, $1, $3); }
;

ExpressionList:
  Expression                    { $$.push_back($1); }
| ExpressionList "," Expression { $1.push_back($3); $$ = std::move($1); }
;

Expression:
  PrimaryExpr         { $$ = $1; }
| AssignExpr          { $$ = $1; }
| BinaryExpr          { $$ = $1; }
| UnaryExpr           { $$ = $1; }
| ConditionalOperator { $$ = $1; }
| FuncLiteral         { $$ = $1; }
;

%%

namespace elma {

void Parser::error(const location_type& loc, const std::string& what)
{
    driver.error(loc, what);
}

} // namespace elma
