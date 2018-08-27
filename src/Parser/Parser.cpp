// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

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


// First part of user declarations.

#line 37 "src/Parser/Parser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "Parser.h"

// User implementation prologue.

#line 51 "src/Parser/Parser.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 54 "src/Parser/Parser.y" // lalr1.cc:413

#include "Driver/Driver.h"

elma::Parser::symbol_type yylex(elma::Driver& driver);

#line 59 "src/Parser/Parser.cpp" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 6 "src/Parser/Parser.y" // lalr1.cc:479
namespace elma {
#line 145 "src/Parser/Parser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (elma::Driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 113: // binary_op
        value.move< BinaryExprKind > (that.value);
        break;

      case 73: // CallSignature
        value.move< CallSignature > (that.value);
        break;

      case 111: // unary_op
        value.move< UnaryExprKind > (that.value);
        break;

      case 93: // VarDeclSpecifier
        value.move< VarDeclSpecifier > (that.value);
        break;

      case 102: // ArrayLiteral
        value.move< std::shared_ptr<ArrayLiteral> > (that.value);
        break;

      case 116: // AssignExpr
        value.move< std::shared_ptr<AssignExpr> > (that.value);
        break;

      case 112: // BinaryExpr
        value.move< std::shared_ptr<BinaryExpr> > (that.value);
        break;

      case 96: // BindingDecl
        value.move< std::shared_ptr<BindingDecl> > (that.value);
        break;

      case 56: // "bool_literal"
        value.move< std::shared_ptr<BoolLiteral> > (that.value);
        break;

      case 108: // CallExpr
        value.move< std::shared_ptr<CallExpr> > (that.value);
        break;

      case 78: // ClassDecl
        value.move< std::shared_ptr<ClassDecl> > (that.value);
        break;

      case 82: // CompoundStmt
        value.move< std::shared_ptr<CompoundStmt> > (that.value);
        break;

      case 114: // ConditionalOperator
        value.move< std::shared_ptr<ConditionalOperator> > (that.value);
        break;

      case 70: // TopLevelDeclaration
      case 80: // ClassMemberDecl
      case 90: // ForEachInitDecl
        value.move< std::shared_ptr<Decl> > (that.value);
        break;

      case 94: // DecompositionDecl
        value.move< std::shared_ptr<DecompositionDecl> > (that.value);
        break;

      case 91: // DeferStmt
        value.move< std::shared_ptr<DeferStmt> > (that.value);
        break;

      case 55: // "double_literal"
        value.move< std::shared_ptr<DoubleLiteral> > (that.value);
        break;

      case 98: // Literal
      case 99: // PrimaryExpr
      case 118: // Expression
        value.move< std::shared_ptr<Expr> > (that.value);
        break;

      case 89: // ForEachStmt
        value.move< std::shared_ptr<ForEachStmt> > (that.value);
        break;

      case 87: // ForStmt
        value.move< std::shared_ptr<ForStmt> > (that.value);
        break;

      case 71: // FuncDecl
        value.move< std::shared_ptr<FuncDecl> > (that.value);
        break;

      case 72: // FuncLiteral
        value.move< std::shared_ptr<FuncLiteral> > (that.value);
        break;

      case 53: // "identifier"
        value.move< std::shared_ptr<Identifier> > (that.value);
        break;

      case 85: // IfStmt
        value.move< std::shared_ptr<IfStmt> > (that.value);
        break;

      case 67: // ImportDecl
        value.move< std::shared_ptr<ImportDecl> > (that.value);
        break;

      case 54: // "integer_literal"
        value.move< std::shared_ptr<IntegerLiteral> > (that.value);
        break;

      case 104: // MapEntry
        value.move< std::shared_ptr<MapEntry> > (that.value);
        break;

      case 103: // MapLiteral
        value.move< std::shared_ptr<MapLiteral> > (that.value);
        break;

      case 106: // MemberExpr
        value.move< std::shared_ptr<MemberExpr> > (that.value);
        break;

      case 109: // NullConditionalOperator
        value.move< std::shared_ptr<NullConditionalOperator> > (that.value);
        break;

      case 101: // NullLiteral
        value.move< std::shared_ptr<NullLiteral> > (that.value);
        break;

      case 75: // ParamDecl
        value.move< std::shared_ptr<ParamDecl> > (that.value);
        break;

      case 100: // ParenExpr
        value.move< std::shared_ptr<ParenExpr> > (that.value);
        break;

      case 84: // ReturnStmt
        value.move< std::shared_ptr<ReturnStmt> > (that.value);
        break;

      case 81: // Statement
      case 88: // ForInitStmt
        value.move< std::shared_ptr<Stmt> > (that.value);
        break;

      case 57: // "string_literal"
        value.move< std::shared_ptr<StringLiteral> > (that.value);
        break;

      case 107: // SubscriptExpr
        value.move< std::shared_ptr<SubscriptExpr> > (that.value);
        break;

      case 66: // TranslationUnitDecl
        value.move< std::shared_ptr<TranslationUnitDecl> > (that.value);
        break;

      case 76: // TypeRepr
        value.move< std::shared_ptr<TypeRepr> > (that.value);
        break;

      case 110: // UnaryExpr
        value.move< std::shared_ptr<UnaryExpr> > (that.value);
        break;

      case 92: // VarDecl
        value.move< std::shared_ptr<VarDecl> > (that.value);
        break;

      case 86: // WhileStmt
        value.move< std::shared_ptr<WhileStmt> > (that.value);
        break;

      case 95: // BindingDeclList
        value.move< std::vector<std::shared_ptr<BindingDecl>> > (that.value);
        break;

      case 69: // TopLevelDeclarationList
      case 79: // ClassMemberDeclList
        value.move< std::vector<std::shared_ptr<Decl>> > (that.value);
        break;

      case 117: // ExpressionList
        value.move< std::vector<std::shared_ptr<Expr>> > (that.value);
        break;

      case 68: // ImportDeclList
        value.move< std::vector<std::shared_ptr<ImportDecl>> > (that.value);
        break;

      case 105: // MapEntryList
        value.move< std::vector<std::shared_ptr<MapEntry>> > (that.value);
        break;

      case 74: // ParamDeclList
        value.move< std::vector<std::shared_ptr<ParamDecl>> > (that.value);
        break;

      case 83: // StatementList
        value.move< std::vector<std::shared_ptr<Stmt>> > (that.value);
        break;

      case 77: // TypeReprList
        value.move< std::vector<std::shared_ptr<TypeRepr>> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 113: // binary_op
        value.copy< BinaryExprKind > (that.value);
        break;

      case 73: // CallSignature
        value.copy< CallSignature > (that.value);
        break;

      case 111: // unary_op
        value.copy< UnaryExprKind > (that.value);
        break;

      case 93: // VarDeclSpecifier
        value.copy< VarDeclSpecifier > (that.value);
        break;

      case 102: // ArrayLiteral
        value.copy< std::shared_ptr<ArrayLiteral> > (that.value);
        break;

      case 116: // AssignExpr
        value.copy< std::shared_ptr<AssignExpr> > (that.value);
        break;

      case 112: // BinaryExpr
        value.copy< std::shared_ptr<BinaryExpr> > (that.value);
        break;

      case 96: // BindingDecl
        value.copy< std::shared_ptr<BindingDecl> > (that.value);
        break;

      case 56: // "bool_literal"
        value.copy< std::shared_ptr<BoolLiteral> > (that.value);
        break;

      case 108: // CallExpr
        value.copy< std::shared_ptr<CallExpr> > (that.value);
        break;

      case 78: // ClassDecl
        value.copy< std::shared_ptr<ClassDecl> > (that.value);
        break;

      case 82: // CompoundStmt
        value.copy< std::shared_ptr<CompoundStmt> > (that.value);
        break;

      case 114: // ConditionalOperator
        value.copy< std::shared_ptr<ConditionalOperator> > (that.value);
        break;

      case 70: // TopLevelDeclaration
      case 80: // ClassMemberDecl
      case 90: // ForEachInitDecl
        value.copy< std::shared_ptr<Decl> > (that.value);
        break;

      case 94: // DecompositionDecl
        value.copy< std::shared_ptr<DecompositionDecl> > (that.value);
        break;

      case 91: // DeferStmt
        value.copy< std::shared_ptr<DeferStmt> > (that.value);
        break;

      case 55: // "double_literal"
        value.copy< std::shared_ptr<DoubleLiteral> > (that.value);
        break;

      case 98: // Literal
      case 99: // PrimaryExpr
      case 118: // Expression
        value.copy< std::shared_ptr<Expr> > (that.value);
        break;

      case 89: // ForEachStmt
        value.copy< std::shared_ptr<ForEachStmt> > (that.value);
        break;

      case 87: // ForStmt
        value.copy< std::shared_ptr<ForStmt> > (that.value);
        break;

      case 71: // FuncDecl
        value.copy< std::shared_ptr<FuncDecl> > (that.value);
        break;

      case 72: // FuncLiteral
        value.copy< std::shared_ptr<FuncLiteral> > (that.value);
        break;

      case 53: // "identifier"
        value.copy< std::shared_ptr<Identifier> > (that.value);
        break;

      case 85: // IfStmt
        value.copy< std::shared_ptr<IfStmt> > (that.value);
        break;

      case 67: // ImportDecl
        value.copy< std::shared_ptr<ImportDecl> > (that.value);
        break;

      case 54: // "integer_literal"
        value.copy< std::shared_ptr<IntegerLiteral> > (that.value);
        break;

      case 104: // MapEntry
        value.copy< std::shared_ptr<MapEntry> > (that.value);
        break;

      case 103: // MapLiteral
        value.copy< std::shared_ptr<MapLiteral> > (that.value);
        break;

      case 106: // MemberExpr
        value.copy< std::shared_ptr<MemberExpr> > (that.value);
        break;

      case 109: // NullConditionalOperator
        value.copy< std::shared_ptr<NullConditionalOperator> > (that.value);
        break;

      case 101: // NullLiteral
        value.copy< std::shared_ptr<NullLiteral> > (that.value);
        break;

      case 75: // ParamDecl
        value.copy< std::shared_ptr<ParamDecl> > (that.value);
        break;

      case 100: // ParenExpr
        value.copy< std::shared_ptr<ParenExpr> > (that.value);
        break;

      case 84: // ReturnStmt
        value.copy< std::shared_ptr<ReturnStmt> > (that.value);
        break;

      case 81: // Statement
      case 88: // ForInitStmt
        value.copy< std::shared_ptr<Stmt> > (that.value);
        break;

      case 57: // "string_literal"
        value.copy< std::shared_ptr<StringLiteral> > (that.value);
        break;

      case 107: // SubscriptExpr
        value.copy< std::shared_ptr<SubscriptExpr> > (that.value);
        break;

      case 66: // TranslationUnitDecl
        value.copy< std::shared_ptr<TranslationUnitDecl> > (that.value);
        break;

      case 76: // TypeRepr
        value.copy< std::shared_ptr<TypeRepr> > (that.value);
        break;

      case 110: // UnaryExpr
        value.copy< std::shared_ptr<UnaryExpr> > (that.value);
        break;

      case 92: // VarDecl
        value.copy< std::shared_ptr<VarDecl> > (that.value);
        break;

      case 86: // WhileStmt
        value.copy< std::shared_ptr<WhileStmt> > (that.value);
        break;

      case 95: // BindingDeclList
        value.copy< std::vector<std::shared_ptr<BindingDecl>> > (that.value);
        break;

      case 69: // TopLevelDeclarationList
      case 79: // ClassMemberDeclList
        value.copy< std::vector<std::shared_ptr<Decl>> > (that.value);
        break;

      case 117: // ExpressionList
        value.copy< std::vector<std::shared_ptr<Expr>> > (that.value);
        break;

      case 68: // ImportDeclList
        value.copy< std::vector<std::shared_ptr<ImportDecl>> > (that.value);
        break;

      case 105: // MapEntryList
        value.copy< std::vector<std::shared_ptr<MapEntry>> > (that.value);
        break;

      case 74: // ParamDeclList
        value.copy< std::vector<std::shared_ptr<ParamDecl>> > (that.value);
        break;

      case 83: // StatementList
        value.copy< std::vector<std::shared_ptr<Stmt>> > (that.value);
        break;

      case 77: // TypeReprList
        value.copy< std::vector<std::shared_ptr<TypeRepr>> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 44 "src/Parser/Parser.y" // lalr1.cc:745
{
    // Initialize the initial location.
    yyla.location.begin.filename = driver.file;
    yyla.location.end.filename = driver.file;
}

#line 832 "src/Parser/Parser.cpp" // lalr1.cc:745

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 113: // binary_op
        yylhs.value.build< BinaryExprKind > ();
        break;

      case 73: // CallSignature
        yylhs.value.build< CallSignature > ();
        break;

      case 111: // unary_op
        yylhs.value.build< UnaryExprKind > ();
        break;

      case 93: // VarDeclSpecifier
        yylhs.value.build< VarDeclSpecifier > ();
        break;

      case 102: // ArrayLiteral
        yylhs.value.build< std::shared_ptr<ArrayLiteral> > ();
        break;

      case 116: // AssignExpr
        yylhs.value.build< std::shared_ptr<AssignExpr> > ();
        break;

      case 112: // BinaryExpr
        yylhs.value.build< std::shared_ptr<BinaryExpr> > ();
        break;

      case 96: // BindingDecl
        yylhs.value.build< std::shared_ptr<BindingDecl> > ();
        break;

      case 56: // "bool_literal"
        yylhs.value.build< std::shared_ptr<BoolLiteral> > ();
        break;

      case 108: // CallExpr
        yylhs.value.build< std::shared_ptr<CallExpr> > ();
        break;

      case 78: // ClassDecl
        yylhs.value.build< std::shared_ptr<ClassDecl> > ();
        break;

      case 82: // CompoundStmt
        yylhs.value.build< std::shared_ptr<CompoundStmt> > ();
        break;

      case 114: // ConditionalOperator
        yylhs.value.build< std::shared_ptr<ConditionalOperator> > ();
        break;

      case 70: // TopLevelDeclaration
      case 80: // ClassMemberDecl
      case 90: // ForEachInitDecl
        yylhs.value.build< std::shared_ptr<Decl> > ();
        break;

      case 94: // DecompositionDecl
        yylhs.value.build< std::shared_ptr<DecompositionDecl> > ();
        break;

      case 91: // DeferStmt
        yylhs.value.build< std::shared_ptr<DeferStmt> > ();
        break;

      case 55: // "double_literal"
        yylhs.value.build< std::shared_ptr<DoubleLiteral> > ();
        break;

      case 98: // Literal
      case 99: // PrimaryExpr
      case 118: // Expression
        yylhs.value.build< std::shared_ptr<Expr> > ();
        break;

      case 89: // ForEachStmt
        yylhs.value.build< std::shared_ptr<ForEachStmt> > ();
        break;

      case 87: // ForStmt
        yylhs.value.build< std::shared_ptr<ForStmt> > ();
        break;

      case 71: // FuncDecl
        yylhs.value.build< std::shared_ptr<FuncDecl> > ();
        break;

      case 72: // FuncLiteral
        yylhs.value.build< std::shared_ptr<FuncLiteral> > ();
        break;

      case 53: // "identifier"
        yylhs.value.build< std::shared_ptr<Identifier> > ();
        break;

      case 85: // IfStmt
        yylhs.value.build< std::shared_ptr<IfStmt> > ();
        break;

      case 67: // ImportDecl
        yylhs.value.build< std::shared_ptr<ImportDecl> > ();
        break;

      case 54: // "integer_literal"
        yylhs.value.build< std::shared_ptr<IntegerLiteral> > ();
        break;

      case 104: // MapEntry
        yylhs.value.build< std::shared_ptr<MapEntry> > ();
        break;

      case 103: // MapLiteral
        yylhs.value.build< std::shared_ptr<MapLiteral> > ();
        break;

      case 106: // MemberExpr
        yylhs.value.build< std::shared_ptr<MemberExpr> > ();
        break;

      case 109: // NullConditionalOperator
        yylhs.value.build< std::shared_ptr<NullConditionalOperator> > ();
        break;

      case 101: // NullLiteral
        yylhs.value.build< std::shared_ptr<NullLiteral> > ();
        break;

      case 75: // ParamDecl
        yylhs.value.build< std::shared_ptr<ParamDecl> > ();
        break;

      case 100: // ParenExpr
        yylhs.value.build< std::shared_ptr<ParenExpr> > ();
        break;

      case 84: // ReturnStmt
        yylhs.value.build< std::shared_ptr<ReturnStmt> > ();
        break;

      case 81: // Statement
      case 88: // ForInitStmt
        yylhs.value.build< std::shared_ptr<Stmt> > ();
        break;

      case 57: // "string_literal"
        yylhs.value.build< std::shared_ptr<StringLiteral> > ();
        break;

      case 107: // SubscriptExpr
        yylhs.value.build< std::shared_ptr<SubscriptExpr> > ();
        break;

      case 66: // TranslationUnitDecl
        yylhs.value.build< std::shared_ptr<TranslationUnitDecl> > ();
        break;

      case 76: // TypeRepr
        yylhs.value.build< std::shared_ptr<TypeRepr> > ();
        break;

      case 110: // UnaryExpr
        yylhs.value.build< std::shared_ptr<UnaryExpr> > ();
        break;

      case 92: // VarDecl
        yylhs.value.build< std::shared_ptr<VarDecl> > ();
        break;

      case 86: // WhileStmt
        yylhs.value.build< std::shared_ptr<WhileStmt> > ();
        break;

      case 95: // BindingDeclList
        yylhs.value.build< std::vector<std::shared_ptr<BindingDecl>> > ();
        break;

      case 69: // TopLevelDeclarationList
      case 79: // ClassMemberDeclList
        yylhs.value.build< std::vector<std::shared_ptr<Decl>> > ();
        break;

      case 117: // ExpressionList
        yylhs.value.build< std::vector<std::shared_ptr<Expr>> > ();
        break;

      case 68: // ImportDeclList
        yylhs.value.build< std::vector<std::shared_ptr<ImportDecl>> > ();
        break;

      case 105: // MapEntryList
        yylhs.value.build< std::vector<std::shared_ptr<MapEntry>> > ();
        break;

      case 74: // ParamDeclList
        yylhs.value.build< std::vector<std::shared_ptr<ParamDecl>> > ();
        break;

      case 83: // StatementList
        yylhs.value.build< std::vector<std::shared_ptr<Stmt>> > ();
        break;

      case 77: // TypeReprList
        yylhs.value.build< std::vector<std::shared_ptr<TypeRepr>> > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 200 "src/Parser/Parser.y" // lalr1.cc:859
    { driver.ast.translationUnit = std::make_shared<TranslationUnitDecl>(yylhs.location, std::vector<std::shared_ptr<Decl>>{}); }
#line 1148 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 201 "src/Parser/Parser.y" // lalr1.cc:859
    { driver.ast.translationUnit = std::make_shared<TranslationUnitDecl>(yylhs.location, yystack_[0].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1154 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 202 "src/Parser/Parser.y" // lalr1.cc:859
    { driver.ast.translationUnit = std::make_shared<TranslationUnitDecl>(yylhs.location, yystack_[0].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1160 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 206 "src/Parser/Parser.y" // lalr1.cc:859
    { }
#line 1166 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 210 "src/Parser/Parser.y" // lalr1.cc:859
    { }
#line 1172 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 211 "src/Parser/Parser.y" // lalr1.cc:859
    { }
#line 1178 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 215 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); }
#line 1184 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 216 "src/Parser/Parser.y" // lalr1.cc:859
    { yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); yylhs.value.as< std::vector<std::shared_ptr<Decl>> > () = std::move(yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1190 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 220 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[0].value.as< std::shared_ptr<ClassDecl> > (); }
#line 1196 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 221 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[0].value.as< std::shared_ptr<FuncDecl> > (); }
#line 1202 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 222 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[1].value.as< std::shared_ptr<VarDecl> > (); }
#line 1208 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 226 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<FuncDecl> > () = std::make_shared<FuncDecl>(yylhs.location, yystack_[2].value.as< std::shared_ptr<Identifier> > (), std::get<0>(yystack_[1].value.as< CallSignature > ()), std::get<1>(yystack_[1].value.as< CallSignature > ()), yystack_[0].value.as< std::shared_ptr<CompoundStmt> > ()); }
#line 1214 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 230 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<FuncLiteral> > () = std::make_shared<FuncLiteral>(yylhs.location, std::get<0>(yystack_[1].value.as< CallSignature > ()), std::get<1>(yystack_[1].value.as< CallSignature > ()), yystack_[0].value.as< std::shared_ptr<CompoundStmt> > ()); }
#line 1220 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 234 "src/Parser/Parser.y" // lalr1.cc:859
    { std::get<1>(yylhs.value.as< CallSignature > ()) = nullptr; }
#line 1226 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 235 "src/Parser/Parser.y" // lalr1.cc:859
    { std::get<1>(yylhs.value.as< CallSignature > ()) = yystack_[0].value.as< std::shared_ptr<TypeRepr> > (); }
#line 1232 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 236 "src/Parser/Parser.y" // lalr1.cc:859
    { std::get<0>(yylhs.value.as< CallSignature > ()) = yystack_[1].value.as< std::vector<std::shared_ptr<ParamDecl>> > (); std::get<1>(yylhs.value.as< CallSignature > ()) = nullptr; }
#line 1238 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 237 "src/Parser/Parser.y" // lalr1.cc:859
    { std::get<0>(yylhs.value.as< CallSignature > ()) = yystack_[3].value.as< std::vector<std::shared_ptr<ParamDecl>> > (); std::get<1>(yylhs.value.as< CallSignature > ()) = yystack_[0].value.as< std::shared_ptr<TypeRepr> > (); }
#line 1244 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 241 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<ParamDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<ParamDecl> > ()); }
#line 1250 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 242 "src/Parser/Parser.y" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<ParamDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<ParamDecl> > ()); yylhs.value.as< std::vector<std::shared_ptr<ParamDecl>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<ParamDecl>> > ()); }
#line 1256 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 246 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParamDecl> > () = std::make_shared<ParamDecl>(yylhs.location, yystack_[0].value.as< std::shared_ptr<Identifier> > ()); }
#line 1262 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 247 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParamDecl> > () = std::make_shared<ParamDecl>(yylhs.location, yystack_[2].value.as< std::shared_ptr<Identifier> > (), yystack_[0].value.as< std::shared_ptr<TypeRepr> > ()); }
#line 1268 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 251 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<TypeRepr> > () = std::make_shared<SimpleIdentTypeRepr>(yylhs.location, yystack_[0].value.as< std::shared_ptr<Identifier> > ()); }
#line 1274 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 252 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<TypeRepr> > () = std::make_shared<GenericIdentTypeRepr>(yylhs.location, yystack_[3].value.as< std::shared_ptr<Identifier> > (), yystack_[1].value.as< std::vector<std::shared_ptr<TypeRepr>> > ()); }
#line 1280 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 253 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<TypeRepr> > () = std::make_shared<OptionalTypeRepr>(yylhs.location, yystack_[1].value.as< std::shared_ptr<TypeRepr> > ()); }
#line 1286 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 257 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<TypeRepr>> > ().push_back(yystack_[0].value.as< std::shared_ptr<TypeRepr> > ()); }
#line 1292 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 258 "src/Parser/Parser.y" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<TypeRepr>> > ().push_back(yystack_[0].value.as< std::shared_ptr<TypeRepr> > ()); yylhs.value.as< std::vector<std::shared_ptr<TypeRepr>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<TypeRepr>> > ()); }
#line 1298 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 262 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ClassDecl> > () = std::make_shared<ClassDecl>(yylhs.location, yystack_[2].value.as< std::shared_ptr<Identifier> > (), std::vector<std::shared_ptr<Decl>>{}); }
#line 1304 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 263 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ClassDecl> > () = std::make_shared<ClassDecl>(yylhs.location, yystack_[3].value.as< std::shared_ptr<Identifier> > (), yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1310 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 267 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); }
#line 1316 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 268 "src/Parser/Parser.y" // lalr1.cc:859
    { yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); yylhs.value.as< std::vector<std::shared_ptr<Decl>> > () = std::move(yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1322 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 272 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[0].value.as< std::shared_ptr<FuncDecl> > (); }
#line 1328 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 273 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[1].value.as< std::shared_ptr<VarDecl> > (); }
#line 1334 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 277 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<CompoundStmt> > (); }
#line 1340 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 278 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = std::make_shared<ExprStmt>(yylhs.location, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1346 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 279 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ReturnStmt> > (); }
#line 1352 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 280 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = std::make_shared<DeclStmt>(yylhs.location, yystack_[1].value.as< std::shared_ptr<VarDecl> > ()); }
#line 1358 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 281 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = std::make_shared<DeclStmt>(yylhs.location, yystack_[1].value.as< std::shared_ptr<DecompositionDecl> > ()); }
#line 1364 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 282 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<IfStmt> > (); }
#line 1370 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 283 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<WhileStmt> > (); }
#line 1376 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 284 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ForStmt> > (); }
#line 1382 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 285 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ForEachStmt> > (); }
#line 1388 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 286 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<DeferStmt> > (); }
#line 1394 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 290 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CompoundStmt> > () = std::make_shared<CompoundStmt>(yylhs.location, std::vector<std::shared_ptr<Stmt>>{}); }
#line 1400 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 291 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CompoundStmt> > () = std::make_shared<CompoundStmt>(yylhs.location, yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ()); }
#line 1406 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 295 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Stmt>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1412 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 296 "src/Parser/Parser.y" // lalr1.cc:859
    { yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Stmt> > ()); yylhs.value.as< std::vector<std::shared_ptr<Stmt>> > () = std::move(yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ()); }
#line 1418 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 300 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ReturnStmt> > () = std::make_shared<ReturnStmt>(yylhs.location); }
#line 1424 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 301 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ReturnStmt> > () = std::make_shared<ReturnStmt>(yylhs.location, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1430 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 305 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IfStmt> > () = std::make_shared<IfStmt>(yylhs.location, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1436 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 306 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IfStmt> > () = std::make_shared<IfStmt>(yylhs.location, yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Stmt> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1442 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 310 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<WhileStmt> > () = std::make_shared<WhileStmt>(yylhs.location, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1448 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 314 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ForStmt> > () = std::make_shared<ForStmt>(yylhs.location, yystack_[5].value.as< std::shared_ptr<Stmt> > (), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1454 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 318 "src/Parser/Parser.y" // lalr1.cc:859
    { }
#line 1460 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 319 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = std::make_shared<ExprStmt>(yylhs.location, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1466 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 320 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = std::make_shared<DeclStmt>(yylhs.location, yystack_[1].value.as< std::shared_ptr<VarDecl> > ()); }
#line 1472 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 324 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ForEachStmt> > () = std::make_shared<ForEachStmt>(yylhs.location, yystack_[4].value.as< std::shared_ptr<Decl> > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1478 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 328 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = std::make_shared<NamedDecl>(yylhs.location, yystack_[0].value.as< std::shared_ptr<Identifier> > ()); }
#line 1484 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 329 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = std::make_shared<VarDecl>(yylhs.location, yystack_[0].value.as< std::shared_ptr<Identifier> > (), yystack_[1].value.as< VarDeclSpecifier > (), nullptr, nullptr); }
#line 1490 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 330 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = std::make_shared<DecompositionDecl>(yylhs.location, yystack_[3].value.as< VarDeclSpecifier > (), yystack_[1].value.as< std::vector<std::shared_ptr<BindingDecl>> > ()); }
#line 1496 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 334 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<DeferStmt> > () = std::make_shared<DeferStmt>(yylhs.location, yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1502 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 338 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VarDecl> > () = std::make_shared<VarDecl>(yylhs.location, yystack_[0].value.as< std::shared_ptr<Identifier> > (), yystack_[1].value.as< VarDeclSpecifier > (), nullptr, nullptr); }
#line 1508 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 339 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VarDecl> > () = std::make_shared<VarDecl>(yylhs.location, yystack_[2].value.as< std::shared_ptr<Identifier> > (), yystack_[3].value.as< VarDeclSpecifier > (), nullptr, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1514 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 340 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VarDecl> > () = std::make_shared<VarDecl>(yylhs.location, yystack_[2].value.as< std::shared_ptr<Identifier> > (), yystack_[3].value.as< VarDeclSpecifier > (), yystack_[0].value.as< std::shared_ptr<TypeRepr> > (), nullptr); }
#line 1520 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 341 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VarDecl> > () = std::make_shared<VarDecl>(yylhs.location, yystack_[4].value.as< std::shared_ptr<Identifier> > (), yystack_[5].value.as< VarDeclSpecifier > (), yystack_[2].value.as< std::shared_ptr<TypeRepr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1526 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 345 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< VarDeclSpecifier > () = VarDeclSpecifier::Let; }
#line 1532 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 346 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< VarDeclSpecifier > () = VarDeclSpecifier::Var; }
#line 1538 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 347 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< VarDeclSpecifier > () = VarDeclSpecifier::Const; }
#line 1544 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 351 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<DecompositionDecl> > () = std::make_shared<DecompositionDecl>(yylhs.location, yystack_[5].value.as< VarDeclSpecifier > (), yystack_[3].value.as< std::vector<std::shared_ptr<BindingDecl>> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1550 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 355 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<BindingDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<BindingDecl> > ()); }
#line 1556 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 356 "src/Parser/Parser.y" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<BindingDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<BindingDecl> > ()); yylhs.value.as< std::vector<std::shared_ptr<BindingDecl>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<BindingDecl>> > ()); }
#line 1562 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 360 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BindingDecl> > () = std::make_shared<BindingDecl>(yylhs.location, yystack_[0].value.as< std::shared_ptr<Identifier> > ()); }
#line 1568 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 364 "src/Parser/Parser.y" // lalr1.cc:859
    { }
#line 1574 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 365 "src/Parser/Parser.y" // lalr1.cc:859
    { }
#line 1580 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 369 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<IntegerLiteral> > (); }
#line 1586 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 370 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<DoubleLiteral> > (); }
#line 1592 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 371 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BoolLiteral> > (); }
#line 1598 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 372 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<StringLiteral> > (); }
#line 1604 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 376 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<Expr> > (); }
#line 1610 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 377 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<NullLiteral> > (); }
#line 1616 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 378 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = std::make_shared<IdentifierExpr>(yylhs.location, yystack_[0].value.as< std::shared_ptr<Identifier> > ()); }
#line 1622 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 379 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<ParenExpr> > (); }
#line 1628 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 380 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<ArrayLiteral> > (); }
#line 1634 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 381 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<MapLiteral> > (); }
#line 1640 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 382 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<CallExpr> > (); }
#line 1646 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 383 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<MemberExpr> > (); }
#line 1652 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 384 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<SubscriptExpr> > (); }
#line 1658 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 385 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<NullConditionalOperator> > (); }
#line 1664 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 389 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParenExpr> > () = std::make_shared<ParenExpr>(yylhs.location, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1670 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 393 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullLiteral> > () = std::make_shared<NullLiteral>(yylhs.location); }
#line 1676 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 397 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ArrayLiteral> > () = std::make_shared<ArrayLiteral>(yylhs.location, std::vector<std::shared_ptr<Expr>>{}); }
#line 1682 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 398 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ArrayLiteral> > () = std::make_shared<ArrayLiteral>(yylhs.location, yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1688 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 402 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapLiteral> > () = std::make_shared<MapLiteral>(yylhs.location, std::vector<std::shared_ptr<MapEntry>>{}); }
#line 1694 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 403 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapLiteral> > () = std::make_shared<MapLiteral>(yylhs.location, yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ()); }
#line 1700 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 407 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapEntry> > () = std::make_shared<MapEntry>(yylhs.location, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1706 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 411 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<MapEntry>> > ().push_back(yystack_[0].value.as< std::shared_ptr<MapEntry> > ()); }
#line 1712 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 412 "src/Parser/Parser.y" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ().push_back(yystack_[0].value.as< std::shared_ptr<MapEntry> > ()); yylhs.value.as< std::vector<std::shared_ptr<MapEntry>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ()); }
#line 1718 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 416 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MemberExpr> > () = std::make_shared<MemberExpr>(yylhs.location, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Identifier> > ()); }
#line 1724 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 420 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<SubscriptExpr> > () = std::make_shared<SubscriptExpr>(yylhs.location, yystack_[3].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1730 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 424 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CallExpr> > () = std::make_shared<CallExpr>(yylhs.location, yystack_[2].value.as< std::shared_ptr<Expr> > (), std::vector<std::shared_ptr<Expr>>{}); }
#line 1736 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 425 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CallExpr> > () = std::make_shared<CallExpr>(yylhs.location, yystack_[3].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1742 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 429 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullConditionalOperator> > () = std::make_shared<NullConditionalOperator>(yylhs.location, yystack_[3].value.as< std::shared_ptr<Expr> > (), std::make_shared<MemberExpr>(yylhs.location, yystack_[3].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Identifier> > ())); }
#line 1748 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 430 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullConditionalOperator> > () = std::make_shared<NullConditionalOperator>(yylhs.location, yystack_[4].value.as< std::shared_ptr<Expr> > (), std::make_shared<SubscriptExpr>(yylhs.location, yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::shared_ptr<Expr> > ())); }
#line 1754 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 431 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullConditionalOperator> > () = std::make_shared<NullConditionalOperator>(yylhs.location, yystack_[3].value.as< std::shared_ptr<Expr> > (), std::make_shared<CallExpr>(yylhs.location, yystack_[3].value.as< std::shared_ptr<Expr> > (), std::vector<std::shared_ptr<Expr>>{})); }
#line 1760 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 432 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullConditionalOperator> > () = std::make_shared<NullConditionalOperator>(yylhs.location, yystack_[4].value.as< std::shared_ptr<Expr> > (), std::make_shared<CallExpr>(yylhs.location, yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::vector<std::shared_ptr<Expr>> > ())); }
#line 1766 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 436 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryExpr> > () = std::make_shared<UnaryExpr>(yylhs.location, yystack_[1].value.as< UnaryExprKind > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1772 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 437 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryExpr> > () = std::make_shared<UnaryExpr>(yylhs.location, UnaryExprKind::PostInc, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1778 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 438 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryExpr> > () = std::make_shared<UnaryExpr>(yylhs.location, UnaryExprKind::PostDec, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1784 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 442 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< UnaryExprKind > () = UnaryExprKind::PreInc; }
#line 1790 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 443 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< UnaryExprKind > () = UnaryExprKind::PreDec; }
#line 1796 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 444 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< UnaryExprKind > () = UnaryExprKind::Plus; }
#line 1802 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 445 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< UnaryExprKind > () = UnaryExprKind::Minus; }
#line 1808 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 446 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< UnaryExprKind > () = UnaryExprKind::LogicalNot; }
#line 1814 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 450 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryExpr> > () = std::make_shared<BinaryExpr>(yylhs.location, yystack_[1].value.as< BinaryExprKind > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1820 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 454 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::Add; }
#line 1826 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 455 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::Subtract; }
#line 1832 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 456 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::Multiply; }
#line 1838 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 457 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::Divide; }
#line 1844 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 458 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::Mod; }
#line 1850 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 459 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::Equal; }
#line 1856 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 460 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::NotEqual; }
#line 1862 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 461 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::LogicalAnd; }
#line 1868 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 462 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::LogicalOr; }
#line 1874 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 463 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::GreaterThan; }
#line 1880 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 464 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::GreaterThanOrEqual; }
#line 1886 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 465 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::LessThan; }
#line 1892 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 466 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::LessThanOrEqual; }
#line 1898 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 467 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::NullCoalescing; }
#line 1904 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 471 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ConditionalOperator> > () = std::make_shared<ConditionalOperator>(yylhs.location, yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1910 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 475 "src/Parser/Parser.y" // lalr1.cc:859
    { }
#line 1916 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 479 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<AssignExpr> > () = std::make_shared<AssignExpr>(yylhs.location, AssignExprKind::Assign, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1922 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 483 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Expr>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1928 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 484 "src/Parser/Parser.y" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Expr> > ()); yylhs.value.as< std::vector<std::shared_ptr<Expr>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1934 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 488 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<Expr> > (); }
#line 1940 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 489 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<AssignExpr> > (); }
#line 1946 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 490 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BinaryExpr> > (); }
#line 1952 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 491 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<UnaryExpr> > (); }
#line 1958 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 492 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<ConditionalOperator> > (); }
#line 1964 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 493 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<FuncLiteral> > (); }
#line 1970 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;


#line 1974 "src/Parser/Parser.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -105;

  const signed char Parser::yytable_ninf_ = -63;

  const short int
  Parser::yypact_[] =
  {
      17,   -37,  -105,  -105,  -105,   -22,   -17,    30,  -105,    17,
     118,  -105,  -105,  -105,    19,   -14,    43,    47,    25,  -105,
    -105,   118,  -105,  -105,    22,   -13,    53,    37,    35,   436,
      40,    62,    59,    -9,  -105,   161,  -105,  -105,  -105,    79,
    -105,    70,  -105,  -105,  -105,  -105,  -105,  -105,   436,   296,
      43,  -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,   117,
    -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,    -7,
    -105,  -105,  -105,   795,    80,     7,    40,    40,    68,    65,
    -105,   331,    99,   102,   111,   251,  -105,  -105,   206,  -105,
    -105,  -105,  -105,  -105,  -105,   112,     3,   123,   463,  -105,
    -105,  -105,   497,  -105,   109,  -105,   124,   129,   521,    53,
    -105,  -105,   366,   436,   110,   100,   436,    66,   436,  -105,
    -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,
    -105,  -105,  -105,   436,    40,   436,  -105,   134,   134,    40,
    -105,  -105,   543,   436,   436,    56,  -105,  -105,  -105,  -105,
     119,  -105,  -105,  -105,  -105,   436,   140,   436,   141,   436,
    -105,  -105,     1,   795,   565,  -105,   401,   436,   120,   599,
     100,   795,   816,   134,    49,   795,   134,  -105,   621,   645,
    -105,   131,   436,   132,   149,    10,   669,  -105,   107,  -105,
    -105,   521,  -105,   795,  -105,   795,  -105,   436,  -105,  -105,
     115,   691,  -105,   436,  -105,    40,   251,   251,   725,   436,
    -105,   119,     6,  -105,   179,   119,  -105,  -105,   816,   134,
     139,  -105,   436,   747,   128,   436,  -105,   251,   771,   251,
    -105,   795,  -105,   251,  -105,  -105
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       2,     0,    66,    67,    68,     0,     0,     0,     6,     0,
       3,     8,    11,    10,     0,     0,     0,     0,     0,     1,
       7,     4,     9,    12,    62,     0,     0,     0,     0,     0,
       0,    15,    21,     0,    19,     0,    13,    28,    32,     0,
      30,     0,     5,   112,   111,   109,   110,   113,     0,     0,
       0,    90,    81,    75,    76,    77,    78,   139,    79,   134,
      82,    80,    83,    84,    86,    87,    85,    88,   137,     0,
     136,   138,   135,    63,    23,    64,     0,     0,    17,     0,
      44,     0,     0,     0,     0,     0,    46,    34,     0,    36,
      39,    40,    41,    42,    43,     0,     0,     0,     0,    29,
      31,    33,     0,    91,     0,    96,    73,    73,   132,     0,
     107,   108,     0,     0,     0,   130,     0,   106,     0,   116,
     115,   117,   118,   119,   122,   123,   120,   121,   127,   125,
     126,   124,   128,     0,     0,     0,    25,    16,    22,     0,
      20,    48,     0,     0,     0,     0,    61,    45,    47,    37,
       0,    38,    35,    89,    93,    74,     0,    74,     0,     0,
      14,   100,     0,   132,     0,    98,     0,     0,     0,     0,
       0,   131,   114,    26,     0,    65,    18,    49,     0,     0,
      54,    81,     0,     0,     0,     0,     0,    72,     0,    70,
      97,     0,    94,   133,    92,    95,   101,     0,    99,   104,
       0,     0,   102,     0,    24,     0,     0,     0,     0,     0,
      56,     0,    59,    55,     0,     0,   105,   103,   129,    27,
      50,    52,     0,     0,     0,     0,    71,     0,     0,     0,
      60,    69,    51,     0,    57,    53
  };

  const short int
  Parser::yypgoto_[] =
  {
    -105,  -105,   155,  -105,   175,    33,    -6,  -105,   135,  -105,
     108,   -70,  -105,  -105,  -105,   152,   -84,   -23,  -105,  -105,
    -105,  -105,  -105,  -105,  -105,  -105,  -105,     2,     5,  -105,
     -19,   -21,    88,  -105,   136,  -105,  -105,  -105,  -105,    42,
    -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,
    -105,  -105,  -104,   -29
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     7,     8,     9,    10,    11,    12,    57,    26,    33,
      34,    75,   174,    13,    39,    40,    86,    87,    88,    89,
      90,    91,    92,   182,    93,   183,    94,    95,    96,    97,
     188,   189,   156,    58,    59,    60,    61,    62,    63,   105,
     106,    64,    65,    66,    67,    68,    69,    70,   133,    71,
     116,    72,   107,    98
  };

  const short int
  Parser::yytable_[] =
  {
      73,   146,    14,    36,   148,    15,   137,   138,   162,    29,
     135,    14,    14,    31,    15,    15,    16,    78,    48,   102,
     108,    38,    49,    14,    79,    29,    15,   196,   150,    41,
      19,    17,    15,    38,   197,   211,    18,    30,   -62,    24,
      32,    41,   136,    22,    15,    51,    52,    53,    54,    55,
      56,    23,   142,    30,    22,     1,    24,     2,     3,     4,
      43,    44,   200,   212,   173,    37,     5,     6,    25,   176,
      45,    46,    47,   204,    27,     1,    28,     2,     3,     4,
      35,    48,   205,   163,   164,    49,   160,   169,   180,   171,
      77,   112,    42,    74,    50,   113,     2,     3,     4,    76,
     114,   170,   101,   134,   172,   139,   175,    99,    51,   181,
      53,    54,    55,    56,   178,   179,   186,     1,    32,     2,
       3,     4,   220,   221,   143,   166,   191,   144,   193,   167,
     195,   110,   111,   214,   168,   219,   145,   163,   201,   154,
     215,   216,   112,   232,   149,   234,   113,   184,   197,   235,
     185,   114,   115,   208,   230,   151,     1,   155,     2,     3,
       4,   215,   157,   165,    20,    43,    44,     5,   193,   136,
     192,   194,   187,   202,   218,    45,    46,    47,   -58,   209,
     223,   210,   225,   227,    21,   109,    48,   140,    35,    80,
      49,   100,   224,   228,   226,   158,   231,   190,     0,    50,
      81,     2,     3,     4,    82,   117,    83,    84,     0,    85,
      43,    44,     0,    51,    52,    53,    54,    55,    56,     0,
      45,    46,    47,     0,     0,     0,     0,     0,     0,     0,
       0,    48,     0,    35,   147,    49,     0,     0,     0,     0,
       0,     0,     0,     0,    50,    81,     2,     3,     4,    82,
       0,    83,    84,     0,    85,    43,    44,     0,    51,    52,
      53,    54,    55,    56,     0,    45,    46,    47,     0,     0,
       0,     0,     0,     0,     0,     0,    48,     0,    35,     0,
      49,     0,     0,     0,     0,     0,     0,     0,     0,    50,
      81,     2,     3,     4,    82,     0,    83,    84,     0,    85,
      43,    44,     0,    51,    52,    53,    54,    55,    56,     0,
      45,    46,    47,     0,     0,     0,     0,     0,     0,     0,
       0,    48,     0,     0,     0,    49,   103,   104,     0,     0,
       0,     0,     0,     0,    50,    43,    44,     0,     0,     0,
       0,     0,     0,     0,     0,    45,    46,    47,    51,    52,
      53,    54,    55,    56,     0,     0,    48,     0,     0,     0,
      49,     0,     0,   141,     0,     0,     0,     0,     0,    50,
      43,    44,     0,     0,     0,     0,     0,     0,     0,     0,
      45,    46,    47,    51,    52,    53,    54,    55,    56,     0,
       0,    48,   161,     0,     0,    49,     0,     0,     0,     0,
       0,     0,     0,     0,    50,    43,    44,     0,     0,     0,
       0,     0,     0,     0,     0,    45,    46,    47,    51,    52,
      53,    54,    55,    56,     0,     0,    48,   199,     0,     0,
      49,     0,     0,     0,     0,     0,     0,     0,     0,    50,
      43,    44,     0,     0,     0,     0,     0,     0,     0,     0,
      45,    46,    47,    51,    52,    53,    54,    55,    56,     0,
       0,    48,     0,     0,     0,    49,   118,   119,   120,   121,
     122,   123,     0,     0,    50,     0,     0,     0,     0,     0,
     124,   125,   126,   127,   128,   129,   130,   131,    51,    52,
      53,    54,    55,    56,     0,   152,     0,     0,     0,   132,
     118,   119,   120,   121,   122,   123,     0,     0,     0,     0,
       0,     0,     0,     0,   124,   125,   126,   127,   128,   129,
     130,   131,     0,   153,   118,   119,   120,   121,   122,   123,
       0,     0,     0,   132,     0,     0,     0,     0,   124,   125,
     126,   127,   128,   129,   130,   131,   118,   119,   120,   121,
     122,   123,   159,     0,     0,     0,     0,   132,     0,     0,
     124,   125,   126,   127,   128,   129,   130,   131,   118,   119,
     120,   121,   122,   123,     0,   177,     0,     0,     0,   132,
       0,     0,   124,   125,   126,   127,   128,   129,   130,   131,
       0,     0,     0,     0,     0,   198,     0,     0,     0,     0,
       0,   132,   118,   119,   120,   121,   122,   123,     0,     0,
       0,     0,     0,     0,     0,     0,   124,   125,   126,   127,
     128,   129,   130,   131,   118,   119,   120,   121,   122,   123,
     203,     0,     0,     0,     0,   132,     0,     0,   124,   125,
     126,   127,   128,   129,   130,   131,     0,   206,   118,   119,
     120,   121,   122,   123,     0,     0,     0,   132,     0,     0,
       0,     0,   124,   125,   126,   127,   128,   129,   130,   131,
       0,   207,   118,   119,   120,   121,   122,   123,     0,     0,
       0,   132,     0,     0,     0,     0,   124,   125,   126,   127,
     128,   129,   130,   131,   118,   119,   120,   121,   122,   123,
       0,   213,     0,     0,     0,   132,     0,     0,   124,   125,
     126,   127,   128,   129,   130,   131,     0,     0,     0,     0,
       0,   217,     0,     0,     0,     0,     0,   132,   118,   119,
     120,   121,   122,   123,     0,     0,     0,     0,     0,     0,
       0,     0,   124,   125,   126,   127,   128,   129,   130,   131,
     118,   119,   120,   121,   122,   123,     0,   222,     0,     0,
       0,   132,     0,     0,   124,   125,   126,   127,   128,   129,
     130,   131,     0,   229,   118,   119,   120,   121,   122,   123,
       0,     0,     0,   132,     0,     0,     0,     0,   124,   125,
     126,   127,   128,   129,   130,   131,     0,   233,   118,   119,
     120,   121,   122,   123,     0,     0,     0,   132,     0,     0,
       0,     0,   124,   125,   126,   127,   128,   129,   130,   131,
     119,   120,   121,   122,   123,     0,     0,     0,     0,     0,
       0,   132,     0,   124,   125,   126,   127,   128,   129,   130,
     131,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   132
  };

  const short int
  Parser::yycheck_[] =
  {
      29,    85,     0,    26,    88,     0,    76,    77,   112,     3,
       3,     9,    10,    26,     9,    10,    53,    26,    25,    48,
      49,    27,    29,    21,    33,     3,    21,    26,    25,    27,
       0,    53,    27,    39,    33,    25,    53,    31,    32,    53,
      53,    39,    35,    10,    39,    52,    53,    54,    55,    56,
      57,    32,    81,    31,    21,    38,    53,    40,    41,    42,
       4,     5,   166,    53,   134,    28,    49,    50,    25,   139,
      14,    15,    16,    24,    27,    38,    51,    40,    41,    42,
      27,    25,    33,   112,   113,    29,   109,   116,    32,   118,
      31,    25,    57,    53,    38,    29,    40,    41,    42,    37,
      34,    35,    32,    23,   133,    37,   135,    28,    52,    53,
      54,    55,    56,    57,   143,   144,   145,    38,    53,    40,
      41,    42,   206,   207,    25,    25,   155,    25,   157,    29,
     159,    14,    15,    26,    34,   205,    25,   166,   167,    30,
      33,    26,    25,   227,    32,   229,    29,   145,    33,   233,
     145,    34,    35,   182,    26,    32,    38,    33,    40,    41,
      42,    33,    33,    53,     9,     4,     5,    49,   197,    35,
      30,    30,    53,    53,   203,    14,    15,    16,    47,    47,
     209,    32,     3,    44,     9,    50,    25,    79,    27,    28,
      29,    39,   211,   222,   215,   107,   225,   155,    -1,    38,
      39,    40,    41,    42,    43,    69,    45,    46,    -1,    48,
       4,     5,    -1,    52,    53,    54,    55,    56,    57,    -1,
      14,    15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    25,    -1,    27,    28,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      -1,    45,    46,    -1,    48,     4,     5,    -1,    52,    53,
      54,    55,    56,    57,    -1,    14,    15,    16,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    43,    -1,    45,    46,    -1,    48,
       4,     5,    -1,    52,    53,    54,    55,    56,    57,    -1,
      14,    15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    25,    -1,    -1,    -1,    29,    30,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    38,     4,     5,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    14,    15,    16,    52,    53,
      54,    55,    56,    57,    -1,    -1,    25,    -1,    -1,    -1,
      29,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    38,
       4,     5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      14,    15,    16,    52,    53,    54,    55,    56,    57,    -1,
      -1,    25,    26,    -1,    -1,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,     4,     5,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    14,    15,    16,    52,    53,
      54,    55,    56,    57,    -1,    -1,    25,    26,    -1,    -1,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
       4,     5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      14,    15,    16,    52,    53,    54,    55,    56,    57,    -1,
      -1,    25,    -1,    -1,    -1,    29,     3,     4,     5,     6,
       7,     8,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    52,    53,
      54,    55,    56,    57,    -1,    32,    -1,    -1,    -1,    36,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    -1,    26,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,     3,     4,     5,     6,
       7,     8,    31,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,     3,     4,
       5,     6,     7,     8,    -1,    32,    -1,    -1,    -1,    36,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,
      -1,    36,     3,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,     3,     4,     5,     6,     7,     8,
      31,    -1,    -1,    -1,    -1,    36,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    -1,    26,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    36,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,     3,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,     3,     4,     5,     6,     7,     8,
      -1,    32,    -1,    -1,    -1,    36,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    -1,    -1,    -1,    -1,    36,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
       3,     4,     5,     6,     7,     8,    -1,    32,    -1,    -1,
      -1,    36,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    -1,    26,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    -1,    26,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    36,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,    38,    40,    41,    42,    49,    50,    66,    67,    68,
      69,    70,    71,    78,    92,    93,    53,    53,    53,     0,
      67,    69,    70,    32,    53,    25,    73,    27,    51,     3,
      31,    26,    53,    74,    75,    27,    82,    28,    71,    79,
      80,    92,    57,     4,     5,    14,    15,    16,    25,    29,
      38,    52,    53,    54,    55,    56,    57,    72,    98,    99,
     100,   101,   102,   103,   106,   107,   108,   109,   110,   111,
     112,   114,   116,   118,    53,    76,    37,    31,    26,    33,
      28,    39,    43,    45,    46,    48,    81,    82,    83,    84,
      85,    86,    87,    89,    91,    92,    93,    94,   118,    28,
      80,    32,   118,    30,    31,   104,   105,   117,   118,    73,
      14,    15,    25,    29,    34,    35,   115,    99,     3,     4,
       5,     6,     7,     8,    17,    18,    19,    20,    21,    22,
      23,    24,    36,   113,    23,     3,    35,    76,    76,    37,
      75,    32,   118,    25,    25,    25,    81,    28,    81,    32,
      25,    32,    32,    26,    30,    33,    97,    33,    97,    31,
      82,    26,   117,   118,   118,    53,    25,    29,    34,   118,
      35,   118,   118,    76,    77,   118,    76,    32,   118,   118,
      32,    53,    88,    90,    92,    93,   118,    53,    95,    96,
     104,   118,    30,   118,    30,   118,    26,    33,    30,    26,
     117,   118,    53,    31,    24,    33,    26,    26,   118,    47,
      32,    25,    53,    32,    26,    33,    26,    30,   118,    76,
      81,    81,    32,   118,    95,     3,    96,    44,   118,    26,
      26,   118,    81,    26,    81,    81
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    65,    66,    66,    66,    67,    68,    68,    69,    69,
      70,    70,    70,    71,    72,    73,    73,    73,    73,    74,
      74,    75,    75,    76,    76,    76,    77,    77,    78,    78,
      79,    79,    80,    80,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    82,    82,    83,    83,    84,    84,
      85,    85,    86,    87,    88,    88,    88,    89,    90,    90,
      90,    91,    92,    92,    92,    92,    93,    93,    93,    94,
      95,    95,    96,    97,    97,    98,    98,    98,    98,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,   100,
     101,   102,   102,   103,   103,   104,   105,   105,   106,   107,
     108,   108,   109,   109,   109,   109,   110,   110,   110,   111,
     111,   111,   111,   111,   112,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   114,
     115,   116,   117,   117,   118,   118,   118,   118,   118,   118
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     0,     1,     2,     4,     1,     2,     1,     2,
       1,     1,     2,     4,     3,     2,     4,     3,     5,     1,
       3,     1,     3,     1,     4,     2,     1,     3,     4,     5,
       1,     2,     1,     2,     1,     2,     1,     2,     2,     1,
       1,     1,     1,     1,     2,     3,     1,     2,     2,     3,
       5,     7,     5,     8,     1,     2,     2,     7,     1,     2,
       4,     2,     2,     4,     4,     6,     1,     1,     1,     6,
       1,     3,     1,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     2,     4,     3,     4,     3,     1,     3,     3,     4,
       3,     4,     4,     5,     4,     5,     2,     2,     2,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"=\"", "\"-\"", "\"+\"",
  "\"*\"", "\"/\"", "\"%\"", "\"-=\"", "\"+=\"", "\"*=\"", "\"/=\"",
  "\"%=\"", "\"++\"", "\"--\"", "\"!\"", "\"&&\"", "\"||\"", "\"==\"",
  "\"!=\"", "\"<=\"", "\">=\"", "\"<\"", "\">\"", "\"(\"", "\")\"",
  "\"{\"", "\"}\"", "\"[\"", "\"]\"", "\":\"", "\";\"", "\",\"", "\".\"",
  "\"?\"", "\"??\"", "\"->\"", "\"func\"", "\"return\"", "\"let\"",
  "\"var\"", "\"const\"", "\"if\"", "\"else\"", "\"while\"", "\"for\"",
  "\"in\"", "\"defer\"", "\"class\"", "\"import\"", "\"from\"", "\"null\"",
  "\"identifier\"", "\"integer_literal\"", "\"double_literal\"",
  "\"bool_literal\"", "\"string_literal\"", "\"conditional_expression\"",
  "\"binary_op\"", "\"unary_plus\"", "\"unary_minus\"",
  "\"ternary_question\"", "\"grouping\"", "\"then\"", "$accept",
  "TranslationUnitDecl", "ImportDecl", "ImportDeclList",
  "TopLevelDeclarationList", "TopLevelDeclaration", "FuncDecl",
  "FuncLiteral", "CallSignature", "ParamDeclList", "ParamDecl", "TypeRepr",
  "TypeReprList", "ClassDecl", "ClassMemberDeclList", "ClassMemberDecl",
  "Statement", "CompoundStmt", "StatementList", "ReturnStmt", "IfStmt",
  "WhileStmt", "ForStmt", "ForInitStmt", "ForEachStmt", "ForEachInitDecl",
  "DeferStmt", "VarDecl", "VarDeclSpecifier", "DecompositionDecl",
  "BindingDeclList", "BindingDecl", "comma_opt", "Literal", "PrimaryExpr",
  "ParenExpr", "NullLiteral", "ArrayLiteral", "MapLiteral", "MapEntry",
  "MapEntryList", "MemberExpr", "SubscriptExpr", "CallExpr",
  "NullConditionalOperator", "UnaryExpr", "unary_op", "BinaryExpr",
  "binary_op", "ConditionalOperator", "ternary_question", "AssignExpr",
  "ExpressionList", "Expression", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   200,   200,   201,   202,   206,   210,   211,   215,   216,
     220,   221,   222,   226,   230,   234,   235,   236,   237,   241,
     242,   246,   247,   251,   252,   253,   257,   258,   262,   263,
     267,   268,   272,   273,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   290,   291,   295,   296,   300,   301,
     305,   306,   310,   314,   318,   319,   320,   324,   328,   329,
     330,   334,   338,   339,   340,   341,   345,   346,   347,   351,
     355,   356,   360,   364,   365,   369,   370,   371,   372,   376,
     377,   378,   379,   380,   381,   382,   383,   384,   385,   389,
     393,   397,   398,   402,   403,   407,   411,   412,   416,   420,
     424,   425,   429,   430,   431,   432,   436,   437,   438,   442,
     443,   444,   445,   446,   450,   454,   455,   456,   457,   458,
     459,   460,   461,   462,   463,   464,   465,   466,   467,   471,
     475,   479,   483,   484,   488,   489,   490,   491,   492,   493
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 6 "src/Parser/Parser.y" // lalr1.cc:1167
} // elma
#line 2648 "src/Parser/Parser.cpp" // lalr1.cc:1167
#line 496 "src/Parser/Parser.y" // lalr1.cc:1168


namespace elma {

void Parser::error(const location_type& loc, const std::string& what)
{
    driver.error(loc, what);
}

} // namespace elma
