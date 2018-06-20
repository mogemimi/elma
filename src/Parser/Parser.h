// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

/**
 ** \file src/Parser/Parser.h
 ** Define the elma::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

#ifndef YY_YY_SRC_PARSER_PARSER_H_INCLUDED
# define YY_YY_SRC_PARSER_PARSER_H_INCLUDED
// //                    "%code requires" blocks.
#line 13 "src/Parser/Parser.y" // lalr1.cc:392

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

#line 71 "src/Parser/Parser.h" // lalr1.cc:392

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>
# include "stack.hh"

#include <typeinfo>
#ifndef YYASSERT
# include <cassert>
# define YYASSERT assert
#endif


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

#line 6 "src/Parser/Parser.y" // lalr1.cc:392
namespace elma {
#line 148 "src/Parser/Parser.h" // lalr1.cc:392



  /// A char[S] buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current state.
  template <size_t S>
  struct variant
  {
    /// Type of *this.
    typedef variant<S> self_type;

    /// Empty construction.
    variant ()
      : yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    variant (const T& t)
      : yytypeid_ (&typeid (T))
    {
      YYASSERT (sizeof (T) <= S);
      new (yyas_<T> ()) T (t);
    }

    /// Destruction, allowed only if empty.
    ~variant ()
    {
      YYASSERT (!yytypeid_);
    }

    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    build ()
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T;
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    build (const T& t)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as ()
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Swap the content with \a other, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsability.
    /// Swapping between built and (possibly) non-built is done with
    /// variant::move ().
    template <typename T>
    void
    swap (self_type& other)
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == *other.yytypeid_);
      std::swap (as<T> (), other.as<T> ());
    }

    /// Move the content of \a other to this.
    ///
    /// Destroys \a other.
    template <typename T>
    void
    move (self_type& other)
    {
      build<T> ();
      swap<T> (other);
      other.destroy<T> ();
    }

    /// Copy the content of \a other to this.
    template <typename T>
    void
    copy (const self_type& other)
    {
      build<T> (other.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
    /// Prohibit blind copies.
    self_type& operator=(const self_type&);
    variant (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ ()
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[S];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };


  /// A Bison parser.
  class Parser
  {
  public:
#ifndef YYSTYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // binary_op
      char dummy1[sizeof(BinaryExprKind)];

      // CallSignature
      char dummy2[sizeof(CallSignature)];

      // unary_op
      char dummy3[sizeof(UnaryExprKind)];

      // VarDeclSpecifier
      char dummy4[sizeof(VarDeclSpecifier)];

      // ArrayLiteral
      char dummy5[sizeof(std::shared_ptr<ArrayLiteral>)];

      // AssignExpr
      char dummy6[sizeof(std::shared_ptr<AssignExpr>)];

      // BinaryExpr
      char dummy7[sizeof(std::shared_ptr<BinaryExpr>)];

      // BindingDecl
      char dummy8[sizeof(std::shared_ptr<BindingDecl>)];

      // "bool_literal"
      char dummy9[sizeof(std::shared_ptr<BoolLiteral>)];

      // CallExpr
      char dummy10[sizeof(std::shared_ptr<CallExpr>)];

      // ClassDecl
      char dummy11[sizeof(std::shared_ptr<ClassDecl>)];

      // CompoundStmt
      char dummy12[sizeof(std::shared_ptr<CompoundStmt>)];

      // ConditionalOperator
      char dummy13[sizeof(std::shared_ptr<ConditionalOperator>)];

      // TopLevelDeclaration
      // ClassMemberDecl
      // ForEachInitDecl
      char dummy14[sizeof(std::shared_ptr<Decl>)];

      // DecompositionDecl
      char dummy15[sizeof(std::shared_ptr<DecompositionDecl>)];

      // DeferStmt
      char dummy16[sizeof(std::shared_ptr<DeferStmt>)];

      // "double_literal"
      char dummy17[sizeof(std::shared_ptr<DoubleLiteral>)];

      // Literal
      // PrimaryExpr
      // Expression
      char dummy18[sizeof(std::shared_ptr<Expr>)];

      // ForEachStmt
      char dummy19[sizeof(std::shared_ptr<ForEachStmt>)];

      // ForStmt
      char dummy20[sizeof(std::shared_ptr<ForStmt>)];

      // FuncDecl
      char dummy21[sizeof(std::shared_ptr<FuncDecl>)];

      // FuncLiteral
      char dummy22[sizeof(std::shared_ptr<FuncLiteral>)];

      // "identifier"
      char dummy23[sizeof(std::shared_ptr<Identifier>)];

      // IfStmt
      char dummy24[sizeof(std::shared_ptr<IfStmt>)];

      // "integer_literal"
      char dummy25[sizeof(std::shared_ptr<IntegerLiteral>)];

      // MapEntry
      char dummy26[sizeof(std::shared_ptr<MapEntry>)];

      // MapLiteral
      char dummy27[sizeof(std::shared_ptr<MapLiteral>)];

      // MemberExpr
      char dummy28[sizeof(std::shared_ptr<MemberExpr>)];

      // NullConditionalOperator
      char dummy29[sizeof(std::shared_ptr<NullConditionalOperator>)];

      // NullLiteral
      char dummy30[sizeof(std::shared_ptr<NullLiteral>)];

      // ParamDecl
      char dummy31[sizeof(std::shared_ptr<ParamDecl>)];

      // ParenExpr
      char dummy32[sizeof(std::shared_ptr<ParenExpr>)];

      // ReturnStmt
      char dummy33[sizeof(std::shared_ptr<ReturnStmt>)];

      // Statement
      // ForInitStmt
      char dummy34[sizeof(std::shared_ptr<Stmt>)];

      // "string_literal"
      char dummy35[sizeof(std::shared_ptr<StringLiteral>)];

      // SubscriptExpr
      char dummy36[sizeof(std::shared_ptr<SubscriptExpr>)];

      // TranslationUnitDecl
      char dummy37[sizeof(std::shared_ptr<TranslationUnitDecl>)];

      // TypeRepr
      char dummy38[sizeof(std::shared_ptr<TypeRepr>)];

      // UnaryExpr
      char dummy39[sizeof(std::shared_ptr<UnaryExpr>)];

      // VarDecl
      char dummy40[sizeof(std::shared_ptr<VarDecl>)];

      // WhileStmt
      char dummy41[sizeof(std::shared_ptr<WhileStmt>)];

      // BindingDeclList
      char dummy42[sizeof(std::vector<std::shared_ptr<BindingDecl>>)];

      // TopLevelDeclarationList
      // ClassMemberDeclList
      char dummy43[sizeof(std::vector<std::shared_ptr<Decl>>)];

      // ExpressionList
      char dummy44[sizeof(std::vector<std::shared_ptr<Expr>>)];

      // MapEntryList
      char dummy45[sizeof(std::vector<std::shared_ptr<MapEntry>>)];

      // ParamDeclList
      char dummy46[sizeof(std::vector<std::shared_ptr<ParamDecl>>)];

      // StatementList
      char dummy47[sizeof(std::vector<std::shared_ptr<Stmt>>)];

      // TypeReprList
      char dummy48[sizeof(std::vector<std::shared_ptr<TypeRepr>>)];
};

    /// Symbol semantic values.
    typedef variant<sizeof(union_type)> semantic_type;
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef elma::Location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m);
      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        TOK_END = 0,
        TOK_ASSIGN = 258,
        TOK_MINUS = 259,
        TOK_PLUS = 260,
        TOK_STAR = 261,
        TOK_SLASH = 262,
        TOK_MOD = 263,
        TOK_SUB_ASSIGN = 264,
        TOK_ADD_ASSIGN = 265,
        TOK_MUL_ASSIGN = 266,
        TOK_DIV_ASSIGN = 267,
        TOK_MOD_ASSIGN = 268,
        TOK_PLUS_PLUS = 269,
        TOK_MINUS_MINUS = 270,
        TOK_LOGICAL_NOT = 271,
        TOK_LOGICAL_AND = 272,
        TOK_LOGICAL_OR = 273,
        TOK_EQUAL = 274,
        TOK_NOT_EQUAL = 275,
        TOK_LESS_THAN_EQUAL = 276,
        TOK_GREATER_THAN_EQUAL = 277,
        TOK_LESS_THAN = 278,
        TOK_GREATER_THAN = 279,
        TOK_LEFT_PARENTHESIS = 280,
        TOK_RIGHT_PARENTHESIS = 281,
        TOK_LEFT_CURLY_BRACKET = 282,
        TOK_RIGHT_CURLY_BRACKET = 283,
        TOK_LEFT_SQUARE_BRACKET = 284,
        TOK_RIGHT_SQUARE_BRACKET = 285,
        TOK_COLON = 286,
        TOK_SEMICOLON = 287,
        TOK_COMMA = 288,
        TOK_DOT = 289,
        TOK_QUESTION = 290,
        TOK_NULL_COALESCING = 291,
        TOK_ARROW = 292,
        TOK_FUNCTION = 293,
        TOK_RETURN = 294,
        TOK_LET = 295,
        TOK_VAR = 296,
        TOK_CONST = 297,
        TOK_IF = 298,
        TOK_ELSE = 299,
        TOK_WHILE = 300,
        TOK_FOR = 301,
        TOK_IN = 302,
        TOK_DEFER = 303,
        TOK_CLASS = 304,
        TOK_NULL = 305,
        TOK_IDENTIFIER = 306,
        TOK_INTEGER_LITERAL = 307,
        TOK_DOUBLE_LITERAL = 308,
        TOK_BOOL_LITERAL = 309,
        TOK_STRING_LITERAL = 310
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols, and symbols from each type.

  basic_symbol (typename Base::kind_type t, const location_type& l);

  basic_symbol (typename Base::kind_type t, const BinaryExprKind v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const CallSignature v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const UnaryExprKind v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const VarDeclSpecifier v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<ArrayLiteral> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<AssignExpr> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<BinaryExpr> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<BindingDecl> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<BoolLiteral> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<CallExpr> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<ClassDecl> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<CompoundStmt> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<ConditionalOperator> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<Decl> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<DecompositionDecl> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<DeferStmt> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<DoubleLiteral> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<Expr> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<ForEachStmt> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<ForStmt> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<FuncDecl> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<FuncLiteral> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<Identifier> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<IfStmt> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<IntegerLiteral> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<MapEntry> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<MapLiteral> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<MemberExpr> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<NullConditionalOperator> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<NullLiteral> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<ParamDecl> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<ParenExpr> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<ReturnStmt> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<Stmt> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<StringLiteral> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<SubscriptExpr> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<TranslationUnitDecl> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<TypeRepr> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<UnaryExpr> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<VarDecl> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<WhileStmt> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<BindingDecl>> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<Decl>> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<Expr>> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<MapEntry>> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<ParamDecl>> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<Stmt>> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<TypeRepr>> v, const location_type& l);


      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v,
                    const location_type& l);

      /// Destroy the symbol.
      ~basic_symbol ();

      /// Destroy contents, and record that is empty.
      void clear ();

      /// Whether empty.
      bool empty () const;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;

    // Symbol constructors declarations.
    static inline
    symbol_type
    make_END (const location_type& l);

    static inline
    symbol_type
    make_ASSIGN (const location_type& l);

    static inline
    symbol_type
    make_MINUS (const location_type& l);

    static inline
    symbol_type
    make_PLUS (const location_type& l);

    static inline
    symbol_type
    make_STAR (const location_type& l);

    static inline
    symbol_type
    make_SLASH (const location_type& l);

    static inline
    symbol_type
    make_MOD (const location_type& l);

    static inline
    symbol_type
    make_SUB_ASSIGN (const location_type& l);

    static inline
    symbol_type
    make_ADD_ASSIGN (const location_type& l);

    static inline
    symbol_type
    make_MUL_ASSIGN (const location_type& l);

    static inline
    symbol_type
    make_DIV_ASSIGN (const location_type& l);

    static inline
    symbol_type
    make_MOD_ASSIGN (const location_type& l);

    static inline
    symbol_type
    make_PLUS_PLUS (const location_type& l);

    static inline
    symbol_type
    make_MINUS_MINUS (const location_type& l);

    static inline
    symbol_type
    make_LOGICAL_NOT (const location_type& l);

    static inline
    symbol_type
    make_LOGICAL_AND (const location_type& l);

    static inline
    symbol_type
    make_LOGICAL_OR (const location_type& l);

    static inline
    symbol_type
    make_EQUAL (const location_type& l);

    static inline
    symbol_type
    make_NOT_EQUAL (const location_type& l);

    static inline
    symbol_type
    make_LESS_THAN_EQUAL (const location_type& l);

    static inline
    symbol_type
    make_GREATER_THAN_EQUAL (const location_type& l);

    static inline
    symbol_type
    make_LESS_THAN (const location_type& l);

    static inline
    symbol_type
    make_GREATER_THAN (const location_type& l);

    static inline
    symbol_type
    make_LEFT_PARENTHESIS (const location_type& l);

    static inline
    symbol_type
    make_RIGHT_PARENTHESIS (const location_type& l);

    static inline
    symbol_type
    make_LEFT_CURLY_BRACKET (const location_type& l);

    static inline
    symbol_type
    make_RIGHT_CURLY_BRACKET (const location_type& l);

    static inline
    symbol_type
    make_LEFT_SQUARE_BRACKET (const location_type& l);

    static inline
    symbol_type
    make_RIGHT_SQUARE_BRACKET (const location_type& l);

    static inline
    symbol_type
    make_COLON (const location_type& l);

    static inline
    symbol_type
    make_SEMICOLON (const location_type& l);

    static inline
    symbol_type
    make_COMMA (const location_type& l);

    static inline
    symbol_type
    make_DOT (const location_type& l);

    static inline
    symbol_type
    make_QUESTION (const location_type& l);

    static inline
    symbol_type
    make_NULL_COALESCING (const location_type& l);

    static inline
    symbol_type
    make_ARROW (const location_type& l);

    static inline
    symbol_type
    make_FUNCTION (const location_type& l);

    static inline
    symbol_type
    make_RETURN (const location_type& l);

    static inline
    symbol_type
    make_LET (const location_type& l);

    static inline
    symbol_type
    make_VAR (const location_type& l);

    static inline
    symbol_type
    make_CONST (const location_type& l);

    static inline
    symbol_type
    make_IF (const location_type& l);

    static inline
    symbol_type
    make_ELSE (const location_type& l);

    static inline
    symbol_type
    make_WHILE (const location_type& l);

    static inline
    symbol_type
    make_FOR (const location_type& l);

    static inline
    symbol_type
    make_IN (const location_type& l);

    static inline
    symbol_type
    make_DEFER (const location_type& l);

    static inline
    symbol_type
    make_CLASS (const location_type& l);

    static inline
    symbol_type
    make_NULL (const location_type& l);

    static inline
    symbol_type
    make_IDENTIFIER (const std::shared_ptr<Identifier>& v, const location_type& l);

    static inline
    symbol_type
    make_INTEGER_LITERAL (const std::shared_ptr<IntegerLiteral>& v, const location_type& l);

    static inline
    symbol_type
    make_DOUBLE_LITERAL (const std::shared_ptr<DoubleLiteral>& v, const location_type& l);

    static inline
    symbol_type
    make_BOOL_LITERAL (const std::shared_ptr<BoolLiteral>& v, const location_type& l);

    static inline
    symbol_type
    make_STRING_LITERAL (const std::shared_ptr<StringLiteral>& v, const location_type& l);


    /// Build a parser object.
    Parser (elma::Driver& driver_yyarg);
    virtual ~Parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

  private:
    /// This class is not copyable.
    Parser (const Parser&);
    Parser& operator= (const Parser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short int yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short int yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short int yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const short int yytable_[];

  static const short int yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if YYDEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short int yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 760,     ///< Last index in yytable_.
      yynnts_ = 52,  ///< Number of nonterminal symbols.
      yyfinal_ = 10, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 63  ///< Number of tokens.
    };


    // User arguments.
    elma::Driver& driver;
  };

  // Symbol number corresponding to token number t.
  inline
  Parser::token_number_type
  Parser::yytranslate_ (token_type t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62
    };
    const unsigned int user_token_number_max_ = 317;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
  Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
      switch (other.type_get ())
    {
      case 109: // binary_op
        value.copy< BinaryExprKind > (other.value);
        break;

      case 69: // CallSignature
        value.copy< CallSignature > (other.value);
        break;

      case 107: // unary_op
        value.copy< UnaryExprKind > (other.value);
        break;

      case 89: // VarDeclSpecifier
        value.copy< VarDeclSpecifier > (other.value);
        break;

      case 98: // ArrayLiteral
        value.copy< std::shared_ptr<ArrayLiteral> > (other.value);
        break;

      case 112: // AssignExpr
        value.copy< std::shared_ptr<AssignExpr> > (other.value);
        break;

      case 108: // BinaryExpr
        value.copy< std::shared_ptr<BinaryExpr> > (other.value);
        break;

      case 92: // BindingDecl
        value.copy< std::shared_ptr<BindingDecl> > (other.value);
        break;

      case 54: // "bool_literal"
        value.copy< std::shared_ptr<BoolLiteral> > (other.value);
        break;

      case 104: // CallExpr
        value.copy< std::shared_ptr<CallExpr> > (other.value);
        break;

      case 74: // ClassDecl
        value.copy< std::shared_ptr<ClassDecl> > (other.value);
        break;

      case 78: // CompoundStmt
        value.copy< std::shared_ptr<CompoundStmt> > (other.value);
        break;

      case 110: // ConditionalOperator
        value.copy< std::shared_ptr<ConditionalOperator> > (other.value);
        break;

      case 66: // TopLevelDeclaration
      case 76: // ClassMemberDecl
      case 86: // ForEachInitDecl
        value.copy< std::shared_ptr<Decl> > (other.value);
        break;

      case 90: // DecompositionDecl
        value.copy< std::shared_ptr<DecompositionDecl> > (other.value);
        break;

      case 87: // DeferStmt
        value.copy< std::shared_ptr<DeferStmt> > (other.value);
        break;

      case 53: // "double_literal"
        value.copy< std::shared_ptr<DoubleLiteral> > (other.value);
        break;

      case 94: // Literal
      case 95: // PrimaryExpr
      case 114: // Expression
        value.copy< std::shared_ptr<Expr> > (other.value);
        break;

      case 85: // ForEachStmt
        value.copy< std::shared_ptr<ForEachStmt> > (other.value);
        break;

      case 83: // ForStmt
        value.copy< std::shared_ptr<ForStmt> > (other.value);
        break;

      case 67: // FuncDecl
        value.copy< std::shared_ptr<FuncDecl> > (other.value);
        break;

      case 68: // FuncLiteral
        value.copy< std::shared_ptr<FuncLiteral> > (other.value);
        break;

      case 51: // "identifier"
        value.copy< std::shared_ptr<Identifier> > (other.value);
        break;

      case 81: // IfStmt
        value.copy< std::shared_ptr<IfStmt> > (other.value);
        break;

      case 52: // "integer_literal"
        value.copy< std::shared_ptr<IntegerLiteral> > (other.value);
        break;

      case 100: // MapEntry
        value.copy< std::shared_ptr<MapEntry> > (other.value);
        break;

      case 99: // MapLiteral
        value.copy< std::shared_ptr<MapLiteral> > (other.value);
        break;

      case 102: // MemberExpr
        value.copy< std::shared_ptr<MemberExpr> > (other.value);
        break;

      case 105: // NullConditionalOperator
        value.copy< std::shared_ptr<NullConditionalOperator> > (other.value);
        break;

      case 97: // NullLiteral
        value.copy< std::shared_ptr<NullLiteral> > (other.value);
        break;

      case 71: // ParamDecl
        value.copy< std::shared_ptr<ParamDecl> > (other.value);
        break;

      case 96: // ParenExpr
        value.copy< std::shared_ptr<ParenExpr> > (other.value);
        break;

      case 80: // ReturnStmt
        value.copy< std::shared_ptr<ReturnStmt> > (other.value);
        break;

      case 77: // Statement
      case 84: // ForInitStmt
        value.copy< std::shared_ptr<Stmt> > (other.value);
        break;

      case 55: // "string_literal"
        value.copy< std::shared_ptr<StringLiteral> > (other.value);
        break;

      case 103: // SubscriptExpr
        value.copy< std::shared_ptr<SubscriptExpr> > (other.value);
        break;

      case 64: // TranslationUnitDecl
        value.copy< std::shared_ptr<TranslationUnitDecl> > (other.value);
        break;

      case 72: // TypeRepr
        value.copy< std::shared_ptr<TypeRepr> > (other.value);
        break;

      case 106: // UnaryExpr
        value.copy< std::shared_ptr<UnaryExpr> > (other.value);
        break;

      case 88: // VarDecl
        value.copy< std::shared_ptr<VarDecl> > (other.value);
        break;

      case 82: // WhileStmt
        value.copy< std::shared_ptr<WhileStmt> > (other.value);
        break;

      case 91: // BindingDeclList
        value.copy< std::vector<std::shared_ptr<BindingDecl>> > (other.value);
        break;

      case 65: // TopLevelDeclarationList
      case 75: // ClassMemberDeclList
        value.copy< std::vector<std::shared_ptr<Decl>> > (other.value);
        break;

      case 113: // ExpressionList
        value.copy< std::vector<std::shared_ptr<Expr>> > (other.value);
        break;

      case 101: // MapEntryList
        value.copy< std::vector<std::shared_ptr<MapEntry>> > (other.value);
        break;

      case 70: // ParamDeclList
        value.copy< std::vector<std::shared_ptr<ParamDecl>> > (other.value);
        break;

      case 79: // StatementList
        value.copy< std::vector<std::shared_ptr<Stmt>> > (other.value);
        break;

      case 73: // TypeReprList
        value.copy< std::vector<std::shared_ptr<TypeRepr>> > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {
    (void) v;
      switch (this->type_get ())
    {
      case 109: // binary_op
        value.copy< BinaryExprKind > (v);
        break;

      case 69: // CallSignature
        value.copy< CallSignature > (v);
        break;

      case 107: // unary_op
        value.copy< UnaryExprKind > (v);
        break;

      case 89: // VarDeclSpecifier
        value.copy< VarDeclSpecifier > (v);
        break;

      case 98: // ArrayLiteral
        value.copy< std::shared_ptr<ArrayLiteral> > (v);
        break;

      case 112: // AssignExpr
        value.copy< std::shared_ptr<AssignExpr> > (v);
        break;

      case 108: // BinaryExpr
        value.copy< std::shared_ptr<BinaryExpr> > (v);
        break;

      case 92: // BindingDecl
        value.copy< std::shared_ptr<BindingDecl> > (v);
        break;

      case 54: // "bool_literal"
        value.copy< std::shared_ptr<BoolLiteral> > (v);
        break;

      case 104: // CallExpr
        value.copy< std::shared_ptr<CallExpr> > (v);
        break;

      case 74: // ClassDecl
        value.copy< std::shared_ptr<ClassDecl> > (v);
        break;

      case 78: // CompoundStmt
        value.copy< std::shared_ptr<CompoundStmt> > (v);
        break;

      case 110: // ConditionalOperator
        value.copy< std::shared_ptr<ConditionalOperator> > (v);
        break;

      case 66: // TopLevelDeclaration
      case 76: // ClassMemberDecl
      case 86: // ForEachInitDecl
        value.copy< std::shared_ptr<Decl> > (v);
        break;

      case 90: // DecompositionDecl
        value.copy< std::shared_ptr<DecompositionDecl> > (v);
        break;

      case 87: // DeferStmt
        value.copy< std::shared_ptr<DeferStmt> > (v);
        break;

      case 53: // "double_literal"
        value.copy< std::shared_ptr<DoubleLiteral> > (v);
        break;

      case 94: // Literal
      case 95: // PrimaryExpr
      case 114: // Expression
        value.copy< std::shared_ptr<Expr> > (v);
        break;

      case 85: // ForEachStmt
        value.copy< std::shared_ptr<ForEachStmt> > (v);
        break;

      case 83: // ForStmt
        value.copy< std::shared_ptr<ForStmt> > (v);
        break;

      case 67: // FuncDecl
        value.copy< std::shared_ptr<FuncDecl> > (v);
        break;

      case 68: // FuncLiteral
        value.copy< std::shared_ptr<FuncLiteral> > (v);
        break;

      case 51: // "identifier"
        value.copy< std::shared_ptr<Identifier> > (v);
        break;

      case 81: // IfStmt
        value.copy< std::shared_ptr<IfStmt> > (v);
        break;

      case 52: // "integer_literal"
        value.copy< std::shared_ptr<IntegerLiteral> > (v);
        break;

      case 100: // MapEntry
        value.copy< std::shared_ptr<MapEntry> > (v);
        break;

      case 99: // MapLiteral
        value.copy< std::shared_ptr<MapLiteral> > (v);
        break;

      case 102: // MemberExpr
        value.copy< std::shared_ptr<MemberExpr> > (v);
        break;

      case 105: // NullConditionalOperator
        value.copy< std::shared_ptr<NullConditionalOperator> > (v);
        break;

      case 97: // NullLiteral
        value.copy< std::shared_ptr<NullLiteral> > (v);
        break;

      case 71: // ParamDecl
        value.copy< std::shared_ptr<ParamDecl> > (v);
        break;

      case 96: // ParenExpr
        value.copy< std::shared_ptr<ParenExpr> > (v);
        break;

      case 80: // ReturnStmt
        value.copy< std::shared_ptr<ReturnStmt> > (v);
        break;

      case 77: // Statement
      case 84: // ForInitStmt
        value.copy< std::shared_ptr<Stmt> > (v);
        break;

      case 55: // "string_literal"
        value.copy< std::shared_ptr<StringLiteral> > (v);
        break;

      case 103: // SubscriptExpr
        value.copy< std::shared_ptr<SubscriptExpr> > (v);
        break;

      case 64: // TranslationUnitDecl
        value.copy< std::shared_ptr<TranslationUnitDecl> > (v);
        break;

      case 72: // TypeRepr
        value.copy< std::shared_ptr<TypeRepr> > (v);
        break;

      case 106: // UnaryExpr
        value.copy< std::shared_ptr<UnaryExpr> > (v);
        break;

      case 88: // VarDecl
        value.copy< std::shared_ptr<VarDecl> > (v);
        break;

      case 82: // WhileStmt
        value.copy< std::shared_ptr<WhileStmt> > (v);
        break;

      case 91: // BindingDeclList
        value.copy< std::vector<std::shared_ptr<BindingDecl>> > (v);
        break;

      case 65: // TopLevelDeclarationList
      case 75: // ClassMemberDeclList
        value.copy< std::vector<std::shared_ptr<Decl>> > (v);
        break;

      case 113: // ExpressionList
        value.copy< std::vector<std::shared_ptr<Expr>> > (v);
        break;

      case 101: // MapEntryList
        value.copy< std::vector<std::shared_ptr<MapEntry>> > (v);
        break;

      case 70: // ParamDeclList
        value.copy< std::vector<std::shared_ptr<ParamDecl>> > (v);
        break;

      case 79: // StatementList
        value.copy< std::vector<std::shared_ptr<Stmt>> > (v);
        break;

      case 73: // TypeReprList
        value.copy< std::vector<std::shared_ptr<TypeRepr>> > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const BinaryExprKind v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const CallSignature v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const UnaryExprKind v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const VarDeclSpecifier v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<ArrayLiteral> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<AssignExpr> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<BinaryExpr> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<BindingDecl> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<BoolLiteral> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<CallExpr> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<ClassDecl> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<CompoundStmt> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<ConditionalOperator> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<Decl> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<DecompositionDecl> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<DeferStmt> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<DoubleLiteral> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<Expr> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<ForEachStmt> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<ForStmt> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<FuncDecl> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<FuncLiteral> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<Identifier> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<IfStmt> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<IntegerLiteral> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<MapEntry> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<MapLiteral> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<MemberExpr> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<NullConditionalOperator> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<NullLiteral> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<ParamDecl> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<ParenExpr> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<ReturnStmt> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<Stmt> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<StringLiteral> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<SubscriptExpr> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<TranslationUnitDecl> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<TypeRepr> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<UnaryExpr> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<VarDecl> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<WhileStmt> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<BindingDecl>> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<Decl>> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<Expr>> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<MapEntry>> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<ParamDecl>> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<Stmt>> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<TypeRepr>> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 109: // binary_op
        value.template destroy< BinaryExprKind > ();
        break;

      case 69: // CallSignature
        value.template destroy< CallSignature > ();
        break;

      case 107: // unary_op
        value.template destroy< UnaryExprKind > ();
        break;

      case 89: // VarDeclSpecifier
        value.template destroy< VarDeclSpecifier > ();
        break;

      case 98: // ArrayLiteral
        value.template destroy< std::shared_ptr<ArrayLiteral> > ();
        break;

      case 112: // AssignExpr
        value.template destroy< std::shared_ptr<AssignExpr> > ();
        break;

      case 108: // BinaryExpr
        value.template destroy< std::shared_ptr<BinaryExpr> > ();
        break;

      case 92: // BindingDecl
        value.template destroy< std::shared_ptr<BindingDecl> > ();
        break;

      case 54: // "bool_literal"
        value.template destroy< std::shared_ptr<BoolLiteral> > ();
        break;

      case 104: // CallExpr
        value.template destroy< std::shared_ptr<CallExpr> > ();
        break;

      case 74: // ClassDecl
        value.template destroy< std::shared_ptr<ClassDecl> > ();
        break;

      case 78: // CompoundStmt
        value.template destroy< std::shared_ptr<CompoundStmt> > ();
        break;

      case 110: // ConditionalOperator
        value.template destroy< std::shared_ptr<ConditionalOperator> > ();
        break;

      case 66: // TopLevelDeclaration
      case 76: // ClassMemberDecl
      case 86: // ForEachInitDecl
        value.template destroy< std::shared_ptr<Decl> > ();
        break;

      case 90: // DecompositionDecl
        value.template destroy< std::shared_ptr<DecompositionDecl> > ();
        break;

      case 87: // DeferStmt
        value.template destroy< std::shared_ptr<DeferStmt> > ();
        break;

      case 53: // "double_literal"
        value.template destroy< std::shared_ptr<DoubleLiteral> > ();
        break;

      case 94: // Literal
      case 95: // PrimaryExpr
      case 114: // Expression
        value.template destroy< std::shared_ptr<Expr> > ();
        break;

      case 85: // ForEachStmt
        value.template destroy< std::shared_ptr<ForEachStmt> > ();
        break;

      case 83: // ForStmt
        value.template destroy< std::shared_ptr<ForStmt> > ();
        break;

      case 67: // FuncDecl
        value.template destroy< std::shared_ptr<FuncDecl> > ();
        break;

      case 68: // FuncLiteral
        value.template destroy< std::shared_ptr<FuncLiteral> > ();
        break;

      case 51: // "identifier"
        value.template destroy< std::shared_ptr<Identifier> > ();
        break;

      case 81: // IfStmt
        value.template destroy< std::shared_ptr<IfStmt> > ();
        break;

      case 52: // "integer_literal"
        value.template destroy< std::shared_ptr<IntegerLiteral> > ();
        break;

      case 100: // MapEntry
        value.template destroy< std::shared_ptr<MapEntry> > ();
        break;

      case 99: // MapLiteral
        value.template destroy< std::shared_ptr<MapLiteral> > ();
        break;

      case 102: // MemberExpr
        value.template destroy< std::shared_ptr<MemberExpr> > ();
        break;

      case 105: // NullConditionalOperator
        value.template destroy< std::shared_ptr<NullConditionalOperator> > ();
        break;

      case 97: // NullLiteral
        value.template destroy< std::shared_ptr<NullLiteral> > ();
        break;

      case 71: // ParamDecl
        value.template destroy< std::shared_ptr<ParamDecl> > ();
        break;

      case 96: // ParenExpr
        value.template destroy< std::shared_ptr<ParenExpr> > ();
        break;

      case 80: // ReturnStmt
        value.template destroy< std::shared_ptr<ReturnStmt> > ();
        break;

      case 77: // Statement
      case 84: // ForInitStmt
        value.template destroy< std::shared_ptr<Stmt> > ();
        break;

      case 55: // "string_literal"
        value.template destroy< std::shared_ptr<StringLiteral> > ();
        break;

      case 103: // SubscriptExpr
        value.template destroy< std::shared_ptr<SubscriptExpr> > ();
        break;

      case 64: // TranslationUnitDecl
        value.template destroy< std::shared_ptr<TranslationUnitDecl> > ();
        break;

      case 72: // TypeRepr
        value.template destroy< std::shared_ptr<TypeRepr> > ();
        break;

      case 106: // UnaryExpr
        value.template destroy< std::shared_ptr<UnaryExpr> > ();
        break;

      case 88: // VarDecl
        value.template destroy< std::shared_ptr<VarDecl> > ();
        break;

      case 82: // WhileStmt
        value.template destroy< std::shared_ptr<WhileStmt> > ();
        break;

      case 91: // BindingDeclList
        value.template destroy< std::vector<std::shared_ptr<BindingDecl>> > ();
        break;

      case 65: // TopLevelDeclarationList
      case 75: // ClassMemberDeclList
        value.template destroy< std::vector<std::shared_ptr<Decl>> > ();
        break;

      case 113: // ExpressionList
        value.template destroy< std::vector<std::shared_ptr<Expr>> > ();
        break;

      case 101: // MapEntryList
        value.template destroy< std::vector<std::shared_ptr<MapEntry>> > ();
        break;

      case 70: // ParamDeclList
        value.template destroy< std::vector<std::shared_ptr<ParamDecl>> > ();
        break;

      case 79: // StatementList
        value.template destroy< std::vector<std::shared_ptr<Stmt>> > ();
        break;

      case 73: // TypeReprList
        value.template destroy< std::vector<std::shared_ptr<TypeRepr>> > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 109: // binary_op
        value.move< BinaryExprKind > (s.value);
        break;

      case 69: // CallSignature
        value.move< CallSignature > (s.value);
        break;

      case 107: // unary_op
        value.move< UnaryExprKind > (s.value);
        break;

      case 89: // VarDeclSpecifier
        value.move< VarDeclSpecifier > (s.value);
        break;

      case 98: // ArrayLiteral
        value.move< std::shared_ptr<ArrayLiteral> > (s.value);
        break;

      case 112: // AssignExpr
        value.move< std::shared_ptr<AssignExpr> > (s.value);
        break;

      case 108: // BinaryExpr
        value.move< std::shared_ptr<BinaryExpr> > (s.value);
        break;

      case 92: // BindingDecl
        value.move< std::shared_ptr<BindingDecl> > (s.value);
        break;

      case 54: // "bool_literal"
        value.move< std::shared_ptr<BoolLiteral> > (s.value);
        break;

      case 104: // CallExpr
        value.move< std::shared_ptr<CallExpr> > (s.value);
        break;

      case 74: // ClassDecl
        value.move< std::shared_ptr<ClassDecl> > (s.value);
        break;

      case 78: // CompoundStmt
        value.move< std::shared_ptr<CompoundStmt> > (s.value);
        break;

      case 110: // ConditionalOperator
        value.move< std::shared_ptr<ConditionalOperator> > (s.value);
        break;

      case 66: // TopLevelDeclaration
      case 76: // ClassMemberDecl
      case 86: // ForEachInitDecl
        value.move< std::shared_ptr<Decl> > (s.value);
        break;

      case 90: // DecompositionDecl
        value.move< std::shared_ptr<DecompositionDecl> > (s.value);
        break;

      case 87: // DeferStmt
        value.move< std::shared_ptr<DeferStmt> > (s.value);
        break;

      case 53: // "double_literal"
        value.move< std::shared_ptr<DoubleLiteral> > (s.value);
        break;

      case 94: // Literal
      case 95: // PrimaryExpr
      case 114: // Expression
        value.move< std::shared_ptr<Expr> > (s.value);
        break;

      case 85: // ForEachStmt
        value.move< std::shared_ptr<ForEachStmt> > (s.value);
        break;

      case 83: // ForStmt
        value.move< std::shared_ptr<ForStmt> > (s.value);
        break;

      case 67: // FuncDecl
        value.move< std::shared_ptr<FuncDecl> > (s.value);
        break;

      case 68: // FuncLiteral
        value.move< std::shared_ptr<FuncLiteral> > (s.value);
        break;

      case 51: // "identifier"
        value.move< std::shared_ptr<Identifier> > (s.value);
        break;

      case 81: // IfStmt
        value.move< std::shared_ptr<IfStmt> > (s.value);
        break;

      case 52: // "integer_literal"
        value.move< std::shared_ptr<IntegerLiteral> > (s.value);
        break;

      case 100: // MapEntry
        value.move< std::shared_ptr<MapEntry> > (s.value);
        break;

      case 99: // MapLiteral
        value.move< std::shared_ptr<MapLiteral> > (s.value);
        break;

      case 102: // MemberExpr
        value.move< std::shared_ptr<MemberExpr> > (s.value);
        break;

      case 105: // NullConditionalOperator
        value.move< std::shared_ptr<NullConditionalOperator> > (s.value);
        break;

      case 97: // NullLiteral
        value.move< std::shared_ptr<NullLiteral> > (s.value);
        break;

      case 71: // ParamDecl
        value.move< std::shared_ptr<ParamDecl> > (s.value);
        break;

      case 96: // ParenExpr
        value.move< std::shared_ptr<ParenExpr> > (s.value);
        break;

      case 80: // ReturnStmt
        value.move< std::shared_ptr<ReturnStmt> > (s.value);
        break;

      case 77: // Statement
      case 84: // ForInitStmt
        value.move< std::shared_ptr<Stmt> > (s.value);
        break;

      case 55: // "string_literal"
        value.move< std::shared_ptr<StringLiteral> > (s.value);
        break;

      case 103: // SubscriptExpr
        value.move< std::shared_ptr<SubscriptExpr> > (s.value);
        break;

      case 64: // TranslationUnitDecl
        value.move< std::shared_ptr<TranslationUnitDecl> > (s.value);
        break;

      case 72: // TypeRepr
        value.move< std::shared_ptr<TypeRepr> > (s.value);
        break;

      case 106: // UnaryExpr
        value.move< std::shared_ptr<UnaryExpr> > (s.value);
        break;

      case 88: // VarDecl
        value.move< std::shared_ptr<VarDecl> > (s.value);
        break;

      case 82: // WhileStmt
        value.move< std::shared_ptr<WhileStmt> > (s.value);
        break;

      case 91: // BindingDeclList
        value.move< std::vector<std::shared_ptr<BindingDecl>> > (s.value);
        break;

      case 65: // TopLevelDeclarationList
      case 75: // ClassMemberDeclList
        value.move< std::vector<std::shared_ptr<Decl>> > (s.value);
        break;

      case 113: // ExpressionList
        value.move< std::vector<std::shared_ptr<Expr>> > (s.value);
        break;

      case 101: // MapEntryList
        value.move< std::vector<std::shared_ptr<MapEntry>> > (s.value);
        break;

      case 70: // ParamDeclList
        value.move< std::vector<std::shared_ptr<ParamDecl>> > (s.value);
        break;

      case 79: // StatementList
        value.move< std::vector<std::shared_ptr<Stmt>> > (s.value);
        break;

      case 73: // TypeReprList
        value.move< std::vector<std::shared_ptr<TypeRepr>> > (s.value);
        break;

      default:
        break;
    }

    location = s.location;
  }

  // by_type.
  inline
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  Parser::by_type::type_get () const
  {
    return type;
  }

  inline
  Parser::token_type
  Parser::by_type::token () const
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short int
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }
  // Implementation of make_symbol for each symbol type.
  Parser::symbol_type
  Parser::make_END (const location_type& l)
  {
    return symbol_type (token::TOK_END, l);
  }

  Parser::symbol_type
  Parser::make_ASSIGN (const location_type& l)
  {
    return symbol_type (token::TOK_ASSIGN, l);
  }

  Parser::symbol_type
  Parser::make_MINUS (const location_type& l)
  {
    return symbol_type (token::TOK_MINUS, l);
  }

  Parser::symbol_type
  Parser::make_PLUS (const location_type& l)
  {
    return symbol_type (token::TOK_PLUS, l);
  }

  Parser::symbol_type
  Parser::make_STAR (const location_type& l)
  {
    return symbol_type (token::TOK_STAR, l);
  }

  Parser::symbol_type
  Parser::make_SLASH (const location_type& l)
  {
    return symbol_type (token::TOK_SLASH, l);
  }

  Parser::symbol_type
  Parser::make_MOD (const location_type& l)
  {
    return symbol_type (token::TOK_MOD, l);
  }

  Parser::symbol_type
  Parser::make_SUB_ASSIGN (const location_type& l)
  {
    return symbol_type (token::TOK_SUB_ASSIGN, l);
  }

  Parser::symbol_type
  Parser::make_ADD_ASSIGN (const location_type& l)
  {
    return symbol_type (token::TOK_ADD_ASSIGN, l);
  }

  Parser::symbol_type
  Parser::make_MUL_ASSIGN (const location_type& l)
  {
    return symbol_type (token::TOK_MUL_ASSIGN, l);
  }

  Parser::symbol_type
  Parser::make_DIV_ASSIGN (const location_type& l)
  {
    return symbol_type (token::TOK_DIV_ASSIGN, l);
  }

  Parser::symbol_type
  Parser::make_MOD_ASSIGN (const location_type& l)
  {
    return symbol_type (token::TOK_MOD_ASSIGN, l);
  }

  Parser::symbol_type
  Parser::make_PLUS_PLUS (const location_type& l)
  {
    return symbol_type (token::TOK_PLUS_PLUS, l);
  }

  Parser::symbol_type
  Parser::make_MINUS_MINUS (const location_type& l)
  {
    return symbol_type (token::TOK_MINUS_MINUS, l);
  }

  Parser::symbol_type
  Parser::make_LOGICAL_NOT (const location_type& l)
  {
    return symbol_type (token::TOK_LOGICAL_NOT, l);
  }

  Parser::symbol_type
  Parser::make_LOGICAL_AND (const location_type& l)
  {
    return symbol_type (token::TOK_LOGICAL_AND, l);
  }

  Parser::symbol_type
  Parser::make_LOGICAL_OR (const location_type& l)
  {
    return symbol_type (token::TOK_LOGICAL_OR, l);
  }

  Parser::symbol_type
  Parser::make_EQUAL (const location_type& l)
  {
    return symbol_type (token::TOK_EQUAL, l);
  }

  Parser::symbol_type
  Parser::make_NOT_EQUAL (const location_type& l)
  {
    return symbol_type (token::TOK_NOT_EQUAL, l);
  }

  Parser::symbol_type
  Parser::make_LESS_THAN_EQUAL (const location_type& l)
  {
    return symbol_type (token::TOK_LESS_THAN_EQUAL, l);
  }

  Parser::symbol_type
  Parser::make_GREATER_THAN_EQUAL (const location_type& l)
  {
    return symbol_type (token::TOK_GREATER_THAN_EQUAL, l);
  }

  Parser::symbol_type
  Parser::make_LESS_THAN (const location_type& l)
  {
    return symbol_type (token::TOK_LESS_THAN, l);
  }

  Parser::symbol_type
  Parser::make_GREATER_THAN (const location_type& l)
  {
    return symbol_type (token::TOK_GREATER_THAN, l);
  }

  Parser::symbol_type
  Parser::make_LEFT_PARENTHESIS (const location_type& l)
  {
    return symbol_type (token::TOK_LEFT_PARENTHESIS, l);
  }

  Parser::symbol_type
  Parser::make_RIGHT_PARENTHESIS (const location_type& l)
  {
    return symbol_type (token::TOK_RIGHT_PARENTHESIS, l);
  }

  Parser::symbol_type
  Parser::make_LEFT_CURLY_BRACKET (const location_type& l)
  {
    return symbol_type (token::TOK_LEFT_CURLY_BRACKET, l);
  }

  Parser::symbol_type
  Parser::make_RIGHT_CURLY_BRACKET (const location_type& l)
  {
    return symbol_type (token::TOK_RIGHT_CURLY_BRACKET, l);
  }

  Parser::symbol_type
  Parser::make_LEFT_SQUARE_BRACKET (const location_type& l)
  {
    return symbol_type (token::TOK_LEFT_SQUARE_BRACKET, l);
  }

  Parser::symbol_type
  Parser::make_RIGHT_SQUARE_BRACKET (const location_type& l)
  {
    return symbol_type (token::TOK_RIGHT_SQUARE_BRACKET, l);
  }

  Parser::symbol_type
  Parser::make_COLON (const location_type& l)
  {
    return symbol_type (token::TOK_COLON, l);
  }

  Parser::symbol_type
  Parser::make_SEMICOLON (const location_type& l)
  {
    return symbol_type (token::TOK_SEMICOLON, l);
  }

  Parser::symbol_type
  Parser::make_COMMA (const location_type& l)
  {
    return symbol_type (token::TOK_COMMA, l);
  }

  Parser::symbol_type
  Parser::make_DOT (const location_type& l)
  {
    return symbol_type (token::TOK_DOT, l);
  }

  Parser::symbol_type
  Parser::make_QUESTION (const location_type& l)
  {
    return symbol_type (token::TOK_QUESTION, l);
  }

  Parser::symbol_type
  Parser::make_NULL_COALESCING (const location_type& l)
  {
    return symbol_type (token::TOK_NULL_COALESCING, l);
  }

  Parser::symbol_type
  Parser::make_ARROW (const location_type& l)
  {
    return symbol_type (token::TOK_ARROW, l);
  }

  Parser::symbol_type
  Parser::make_FUNCTION (const location_type& l)
  {
    return symbol_type (token::TOK_FUNCTION, l);
  }

  Parser::symbol_type
  Parser::make_RETURN (const location_type& l)
  {
    return symbol_type (token::TOK_RETURN, l);
  }

  Parser::symbol_type
  Parser::make_LET (const location_type& l)
  {
    return symbol_type (token::TOK_LET, l);
  }

  Parser::symbol_type
  Parser::make_VAR (const location_type& l)
  {
    return symbol_type (token::TOK_VAR, l);
  }

  Parser::symbol_type
  Parser::make_CONST (const location_type& l)
  {
    return symbol_type (token::TOK_CONST, l);
  }

  Parser::symbol_type
  Parser::make_IF (const location_type& l)
  {
    return symbol_type (token::TOK_IF, l);
  }

  Parser::symbol_type
  Parser::make_ELSE (const location_type& l)
  {
    return symbol_type (token::TOK_ELSE, l);
  }

  Parser::symbol_type
  Parser::make_WHILE (const location_type& l)
  {
    return symbol_type (token::TOK_WHILE, l);
  }

  Parser::symbol_type
  Parser::make_FOR (const location_type& l)
  {
    return symbol_type (token::TOK_FOR, l);
  }

  Parser::symbol_type
  Parser::make_IN (const location_type& l)
  {
    return symbol_type (token::TOK_IN, l);
  }

  Parser::symbol_type
  Parser::make_DEFER (const location_type& l)
  {
    return symbol_type (token::TOK_DEFER, l);
  }

  Parser::symbol_type
  Parser::make_CLASS (const location_type& l)
  {
    return symbol_type (token::TOK_CLASS, l);
  }

  Parser::symbol_type
  Parser::make_NULL (const location_type& l)
  {
    return symbol_type (token::TOK_NULL, l);
  }

  Parser::symbol_type
  Parser::make_IDENTIFIER (const std::shared_ptr<Identifier>& v, const location_type& l)
  {
    return symbol_type (token::TOK_IDENTIFIER, v, l);
  }

  Parser::symbol_type
  Parser::make_INTEGER_LITERAL (const std::shared_ptr<IntegerLiteral>& v, const location_type& l)
  {
    return symbol_type (token::TOK_INTEGER_LITERAL, v, l);
  }

  Parser::symbol_type
  Parser::make_DOUBLE_LITERAL (const std::shared_ptr<DoubleLiteral>& v, const location_type& l)
  {
    return symbol_type (token::TOK_DOUBLE_LITERAL, v, l);
  }

  Parser::symbol_type
  Parser::make_BOOL_LITERAL (const std::shared_ptr<BoolLiteral>& v, const location_type& l)
  {
    return symbol_type (token::TOK_BOOL_LITERAL, v, l);
  }

  Parser::symbol_type
  Parser::make_STRING_LITERAL (const std::shared_ptr<StringLiteral>& v, const location_type& l)
  {
    return symbol_type (token::TOK_STRING_LITERAL, v, l);
  }


#line 6 "src/Parser/Parser.y" // lalr1.cc:392
} // elma
#line 2851 "src/Parser/Parser.h" // lalr1.cc:392




#endif // !YY_YY_SRC_PARSER_PARSER_H_INCLUDED
