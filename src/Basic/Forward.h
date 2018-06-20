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

// NOTE: Statements
class Stmt;

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
