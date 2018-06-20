#pragma once

namespace elma {

// NOTE: Basic
class Location;
class Position;

// NOTE: Driver
class Driver;

// NOTE: Preprocessor
class Comment;
enum class CommentKind;

// NOTE: AST
class ASTContext;
class ASTVisitor;
class Identifier;
class Node;
enum class NodeKind;

// NOTE: Declarations
class Decl;
class TranslationUnitDecl;
class VarDecl;
class BindingDecl;
class DecompositionDecl;
class FuncDecl;
class ParamDecl;
class ClassDecl;
class NamedDecl;

// NOTE: Expressions
class Expr;
class IntegerLiteral;
class DoubleLiteral;
class BoolLiteral;
class StringLiteral;
class NullLiteral;
class IdentifierExpr;
class ParenExpr;
class UnaryExpr;
class BinaryExpr;
class AssignExpr;
class ConditionalOperator;
class NullConditionalOperator;
class MemberExpr;
class SubscriptExpr;
class ArrayLiteral;
class MapEntry;
class MapLiteral;
class CallExpr;
class FuncLiteral;
class ImplicitConversionExpr;
enum class UnaryExprKind;
enum class BinaryExprKind;
enum class AssignExprKind;

// NOTE: Statements
class Stmt;
class CompoundStmt;
class DeclStmt;
class ExprStmt;
class ReturnStmt;
class DeferStmt;
class IfStmt;
class WhileStmt;
class ForStmt;
class ForEachStmt;

// NOTE: Type Representations
class TypeRepr;
class SimpleIdentTypeRepr;
class GenericIdentTypeRepr;
class OptionalTypeRepr;

// NOTE: Type
class Type;

// NOTE: Sema
class Entity;

// NOTE: Diagnostic
class DiagnosticHandler;

} // namespace elma
