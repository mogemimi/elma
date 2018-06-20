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
      case 109: // binary_op
        value.move< BinaryExprKind > (that.value);
        break;

      case 69: // CallSignature
        value.move< CallSignature > (that.value);
        break;

      case 107: // unary_op
        value.move< UnaryExprKind > (that.value);
        break;

      case 89: // VarDeclSpecifier
        value.move< VarDeclSpecifier > (that.value);
        break;

      case 98: // ArrayLiteral
        value.move< std::shared_ptr<ArrayLiteral> > (that.value);
        break;

      case 112: // AssignExpr
        value.move< std::shared_ptr<AssignExpr> > (that.value);
        break;

      case 108: // BinaryExpr
        value.move< std::shared_ptr<BinaryExpr> > (that.value);
        break;

      case 92: // BindingDecl
        value.move< std::shared_ptr<BindingDecl> > (that.value);
        break;

      case 54: // "bool_literal"
        value.move< std::shared_ptr<BoolLiteral> > (that.value);
        break;

      case 104: // CallExpr
        value.move< std::shared_ptr<CallExpr> > (that.value);
        break;

      case 74: // ClassDecl
        value.move< std::shared_ptr<ClassDecl> > (that.value);
        break;

      case 78: // CompoundStmt
        value.move< std::shared_ptr<CompoundStmt> > (that.value);
        break;

      case 110: // ConditionalOperator
        value.move< std::shared_ptr<ConditionalOperator> > (that.value);
        break;

      case 66: // TopLevelDeclaration
      case 76: // ClassMemberDecl
      case 86: // ForEachInitDecl
        value.move< std::shared_ptr<Decl> > (that.value);
        break;

      case 90: // DecompositionDecl
        value.move< std::shared_ptr<DecompositionDecl> > (that.value);
        break;

      case 87: // DeferStmt
        value.move< std::shared_ptr<DeferStmt> > (that.value);
        break;

      case 53: // "double_literal"
        value.move< std::shared_ptr<DoubleLiteral> > (that.value);
        break;

      case 94: // Literal
      case 95: // PrimaryExpr
      case 114: // Expression
        value.move< std::shared_ptr<Expr> > (that.value);
        break;

      case 85: // ForEachStmt
        value.move< std::shared_ptr<ForEachStmt> > (that.value);
        break;

      case 83: // ForStmt
        value.move< std::shared_ptr<ForStmt> > (that.value);
        break;

      case 67: // FuncDecl
        value.move< std::shared_ptr<FuncDecl> > (that.value);
        break;

      case 68: // FuncLiteral
        value.move< std::shared_ptr<FuncLiteral> > (that.value);
        break;

      case 51: // "identifier"
        value.move< std::shared_ptr<Identifier> > (that.value);
        break;

      case 81: // IfStmt
        value.move< std::shared_ptr<IfStmt> > (that.value);
        break;

      case 52: // "integer_literal"
        value.move< std::shared_ptr<IntegerLiteral> > (that.value);
        break;

      case 100: // MapEntry
        value.move< std::shared_ptr<MapEntry> > (that.value);
        break;

      case 99: // MapLiteral
        value.move< std::shared_ptr<MapLiteral> > (that.value);
        break;

      case 102: // MemberExpr
        value.move< std::shared_ptr<MemberExpr> > (that.value);
        break;

      case 105: // NullConditionalOperator
        value.move< std::shared_ptr<NullConditionalOperator> > (that.value);
        break;

      case 97: // NullLiteral
        value.move< std::shared_ptr<NullLiteral> > (that.value);
        break;

      case 71: // ParamDecl
        value.move< std::shared_ptr<ParamDecl> > (that.value);
        break;

      case 96: // ParenExpr
        value.move< std::shared_ptr<ParenExpr> > (that.value);
        break;

      case 80: // ReturnStmt
        value.move< std::shared_ptr<ReturnStmt> > (that.value);
        break;

      case 77: // Statement
      case 84: // ForInitStmt
        value.move< std::shared_ptr<Stmt> > (that.value);
        break;

      case 55: // "string_literal"
        value.move< std::shared_ptr<StringLiteral> > (that.value);
        break;

      case 103: // SubscriptExpr
        value.move< std::shared_ptr<SubscriptExpr> > (that.value);
        break;

      case 64: // TranslationUnitDecl
        value.move< std::shared_ptr<TranslationUnitDecl> > (that.value);
        break;

      case 72: // TypeRepr
        value.move< std::shared_ptr<TypeRepr> > (that.value);
        break;

      case 106: // UnaryExpr
        value.move< std::shared_ptr<UnaryExpr> > (that.value);
        break;

      case 88: // VarDecl
        value.move< std::shared_ptr<VarDecl> > (that.value);
        break;

      case 82: // WhileStmt
        value.move< std::shared_ptr<WhileStmt> > (that.value);
        break;

      case 91: // BindingDeclList
        value.move< std::vector<std::shared_ptr<BindingDecl>> > (that.value);
        break;

      case 65: // TopLevelDeclarationList
      case 75: // ClassMemberDeclList
        value.move< std::vector<std::shared_ptr<Decl>> > (that.value);
        break;

      case 113: // ExpressionList
        value.move< std::vector<std::shared_ptr<Expr>> > (that.value);
        break;

      case 101: // MapEntryList
        value.move< std::vector<std::shared_ptr<MapEntry>> > (that.value);
        break;

      case 70: // ParamDeclList
        value.move< std::vector<std::shared_ptr<ParamDecl>> > (that.value);
        break;

      case 79: // StatementList
        value.move< std::vector<std::shared_ptr<Stmt>> > (that.value);
        break;

      case 73: // TypeReprList
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
      case 109: // binary_op
        value.copy< BinaryExprKind > (that.value);
        break;

      case 69: // CallSignature
        value.copy< CallSignature > (that.value);
        break;

      case 107: // unary_op
        value.copy< UnaryExprKind > (that.value);
        break;

      case 89: // VarDeclSpecifier
        value.copy< VarDeclSpecifier > (that.value);
        break;

      case 98: // ArrayLiteral
        value.copy< std::shared_ptr<ArrayLiteral> > (that.value);
        break;

      case 112: // AssignExpr
        value.copy< std::shared_ptr<AssignExpr> > (that.value);
        break;

      case 108: // BinaryExpr
        value.copy< std::shared_ptr<BinaryExpr> > (that.value);
        break;

      case 92: // BindingDecl
        value.copy< std::shared_ptr<BindingDecl> > (that.value);
        break;

      case 54: // "bool_literal"
        value.copy< std::shared_ptr<BoolLiteral> > (that.value);
        break;

      case 104: // CallExpr
        value.copy< std::shared_ptr<CallExpr> > (that.value);
        break;

      case 74: // ClassDecl
        value.copy< std::shared_ptr<ClassDecl> > (that.value);
        break;

      case 78: // CompoundStmt
        value.copy< std::shared_ptr<CompoundStmt> > (that.value);
        break;

      case 110: // ConditionalOperator
        value.copy< std::shared_ptr<ConditionalOperator> > (that.value);
        break;

      case 66: // TopLevelDeclaration
      case 76: // ClassMemberDecl
      case 86: // ForEachInitDecl
        value.copy< std::shared_ptr<Decl> > (that.value);
        break;

      case 90: // DecompositionDecl
        value.copy< std::shared_ptr<DecompositionDecl> > (that.value);
        break;

      case 87: // DeferStmt
        value.copy< std::shared_ptr<DeferStmt> > (that.value);
        break;

      case 53: // "double_literal"
        value.copy< std::shared_ptr<DoubleLiteral> > (that.value);
        break;

      case 94: // Literal
      case 95: // PrimaryExpr
      case 114: // Expression
        value.copy< std::shared_ptr<Expr> > (that.value);
        break;

      case 85: // ForEachStmt
        value.copy< std::shared_ptr<ForEachStmt> > (that.value);
        break;

      case 83: // ForStmt
        value.copy< std::shared_ptr<ForStmt> > (that.value);
        break;

      case 67: // FuncDecl
        value.copy< std::shared_ptr<FuncDecl> > (that.value);
        break;

      case 68: // FuncLiteral
        value.copy< std::shared_ptr<FuncLiteral> > (that.value);
        break;

      case 51: // "identifier"
        value.copy< std::shared_ptr<Identifier> > (that.value);
        break;

      case 81: // IfStmt
        value.copy< std::shared_ptr<IfStmt> > (that.value);
        break;

      case 52: // "integer_literal"
        value.copy< std::shared_ptr<IntegerLiteral> > (that.value);
        break;

      case 100: // MapEntry
        value.copy< std::shared_ptr<MapEntry> > (that.value);
        break;

      case 99: // MapLiteral
        value.copy< std::shared_ptr<MapLiteral> > (that.value);
        break;

      case 102: // MemberExpr
        value.copy< std::shared_ptr<MemberExpr> > (that.value);
        break;

      case 105: // NullConditionalOperator
        value.copy< std::shared_ptr<NullConditionalOperator> > (that.value);
        break;

      case 97: // NullLiteral
        value.copy< std::shared_ptr<NullLiteral> > (that.value);
        break;

      case 71: // ParamDecl
        value.copy< std::shared_ptr<ParamDecl> > (that.value);
        break;

      case 96: // ParenExpr
        value.copy< std::shared_ptr<ParenExpr> > (that.value);
        break;

      case 80: // ReturnStmt
        value.copy< std::shared_ptr<ReturnStmt> > (that.value);
        break;

      case 77: // Statement
      case 84: // ForInitStmt
        value.copy< std::shared_ptr<Stmt> > (that.value);
        break;

      case 55: // "string_literal"
        value.copy< std::shared_ptr<StringLiteral> > (that.value);
        break;

      case 103: // SubscriptExpr
        value.copy< std::shared_ptr<SubscriptExpr> > (that.value);
        break;

      case 64: // TranslationUnitDecl
        value.copy< std::shared_ptr<TranslationUnitDecl> > (that.value);
        break;

      case 72: // TypeRepr
        value.copy< std::shared_ptr<TypeRepr> > (that.value);
        break;

      case 106: // UnaryExpr
        value.copy< std::shared_ptr<UnaryExpr> > (that.value);
        break;

      case 88: // VarDecl
        value.copy< std::shared_ptr<VarDecl> > (that.value);
        break;

      case 82: // WhileStmt
        value.copy< std::shared_ptr<WhileStmt> > (that.value);
        break;

      case 91: // BindingDeclList
        value.copy< std::vector<std::shared_ptr<BindingDecl>> > (that.value);
        break;

      case 65: // TopLevelDeclarationList
      case 75: // ClassMemberDeclList
        value.copy< std::vector<std::shared_ptr<Decl>> > (that.value);
        break;

      case 113: // ExpressionList
        value.copy< std::vector<std::shared_ptr<Expr>> > (that.value);
        break;

      case 101: // MapEntryList
        value.copy< std::vector<std::shared_ptr<MapEntry>> > (that.value);
        break;

      case 70: // ParamDeclList
        value.copy< std::vector<std::shared_ptr<ParamDecl>> > (that.value);
        break;

      case 79: // StatementList
        value.copy< std::vector<std::shared_ptr<Stmt>> > (that.value);
        break;

      case 73: // TypeReprList
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

#line 816 "src/Parser/Parser.cpp" // lalr1.cc:745

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
      case 109: // binary_op
        yylhs.value.build< BinaryExprKind > ();
        break;

      case 69: // CallSignature
        yylhs.value.build< CallSignature > ();
        break;

      case 107: // unary_op
        yylhs.value.build< UnaryExprKind > ();
        break;

      case 89: // VarDeclSpecifier
        yylhs.value.build< VarDeclSpecifier > ();
        break;

      case 98: // ArrayLiteral
        yylhs.value.build< std::shared_ptr<ArrayLiteral> > ();
        break;

      case 112: // AssignExpr
        yylhs.value.build< std::shared_ptr<AssignExpr> > ();
        break;

      case 108: // BinaryExpr
        yylhs.value.build< std::shared_ptr<BinaryExpr> > ();
        break;

      case 92: // BindingDecl
        yylhs.value.build< std::shared_ptr<BindingDecl> > ();
        break;

      case 54: // "bool_literal"
        yylhs.value.build< std::shared_ptr<BoolLiteral> > ();
        break;

      case 104: // CallExpr
        yylhs.value.build< std::shared_ptr<CallExpr> > ();
        break;

      case 74: // ClassDecl
        yylhs.value.build< std::shared_ptr<ClassDecl> > ();
        break;

      case 78: // CompoundStmt
        yylhs.value.build< std::shared_ptr<CompoundStmt> > ();
        break;

      case 110: // ConditionalOperator
        yylhs.value.build< std::shared_ptr<ConditionalOperator> > ();
        break;

      case 66: // TopLevelDeclaration
      case 76: // ClassMemberDecl
      case 86: // ForEachInitDecl
        yylhs.value.build< std::shared_ptr<Decl> > ();
        break;

      case 90: // DecompositionDecl
        yylhs.value.build< std::shared_ptr<DecompositionDecl> > ();
        break;

      case 87: // DeferStmt
        yylhs.value.build< std::shared_ptr<DeferStmt> > ();
        break;

      case 53: // "double_literal"
        yylhs.value.build< std::shared_ptr<DoubleLiteral> > ();
        break;

      case 94: // Literal
      case 95: // PrimaryExpr
      case 114: // Expression
        yylhs.value.build< std::shared_ptr<Expr> > ();
        break;

      case 85: // ForEachStmt
        yylhs.value.build< std::shared_ptr<ForEachStmt> > ();
        break;

      case 83: // ForStmt
        yylhs.value.build< std::shared_ptr<ForStmt> > ();
        break;

      case 67: // FuncDecl
        yylhs.value.build< std::shared_ptr<FuncDecl> > ();
        break;

      case 68: // FuncLiteral
        yylhs.value.build< std::shared_ptr<FuncLiteral> > ();
        break;

      case 51: // "identifier"
        yylhs.value.build< std::shared_ptr<Identifier> > ();
        break;

      case 81: // IfStmt
        yylhs.value.build< std::shared_ptr<IfStmt> > ();
        break;

      case 52: // "integer_literal"
        yylhs.value.build< std::shared_ptr<IntegerLiteral> > ();
        break;

      case 100: // MapEntry
        yylhs.value.build< std::shared_ptr<MapEntry> > ();
        break;

      case 99: // MapLiteral
        yylhs.value.build< std::shared_ptr<MapLiteral> > ();
        break;

      case 102: // MemberExpr
        yylhs.value.build< std::shared_ptr<MemberExpr> > ();
        break;

      case 105: // NullConditionalOperator
        yylhs.value.build< std::shared_ptr<NullConditionalOperator> > ();
        break;

      case 97: // NullLiteral
        yylhs.value.build< std::shared_ptr<NullLiteral> > ();
        break;

      case 71: // ParamDecl
        yylhs.value.build< std::shared_ptr<ParamDecl> > ();
        break;

      case 96: // ParenExpr
        yylhs.value.build< std::shared_ptr<ParenExpr> > ();
        break;

      case 80: // ReturnStmt
        yylhs.value.build< std::shared_ptr<ReturnStmt> > ();
        break;

      case 77: // Statement
      case 84: // ForInitStmt
        yylhs.value.build< std::shared_ptr<Stmt> > ();
        break;

      case 55: // "string_literal"
        yylhs.value.build< std::shared_ptr<StringLiteral> > ();
        break;

      case 103: // SubscriptExpr
        yylhs.value.build< std::shared_ptr<SubscriptExpr> > ();
        break;

      case 64: // TranslationUnitDecl
        yylhs.value.build< std::shared_ptr<TranslationUnitDecl> > ();
        break;

      case 72: // TypeRepr
        yylhs.value.build< std::shared_ptr<TypeRepr> > ();
        break;

      case 106: // UnaryExpr
        yylhs.value.build< std::shared_ptr<UnaryExpr> > ();
        break;

      case 88: // VarDecl
        yylhs.value.build< std::shared_ptr<VarDecl> > ();
        break;

      case 82: // WhileStmt
        yylhs.value.build< std::shared_ptr<WhileStmt> > ();
        break;

      case 91: // BindingDeclList
        yylhs.value.build< std::vector<std::shared_ptr<BindingDecl>> > ();
        break;

      case 65: // TopLevelDeclarationList
      case 75: // ClassMemberDeclList
        yylhs.value.build< std::vector<std::shared_ptr<Decl>> > ();
        break;

      case 113: // ExpressionList
        yylhs.value.build< std::vector<std::shared_ptr<Expr>> > ();
        break;

      case 101: // MapEntryList
        yylhs.value.build< std::vector<std::shared_ptr<MapEntry>> > ();
        break;

      case 70: // ParamDeclList
        yylhs.value.build< std::vector<std::shared_ptr<ParamDecl>> > ();
        break;

      case 79: // StatementList
        yylhs.value.build< std::vector<std::shared_ptr<Stmt>> > ();
        break;

      case 73: // TypeReprList
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
#line 196 "src/Parser/Parser.y" // lalr1.cc:859
    { driver.ast.translationUnit = std::make_shared<TranslationUnitDecl>(yylhs.location, std::vector<std::shared_ptr<Decl>>{}); }
#line 1124 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 197 "src/Parser/Parser.y" // lalr1.cc:859
    { driver.ast.translationUnit = std::make_shared<TranslationUnitDecl>(yylhs.location, yystack_[0].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1130 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 201 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); }
#line 1136 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 202 "src/Parser/Parser.y" // lalr1.cc:859
    { yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); yylhs.value.as< std::vector<std::shared_ptr<Decl>> > () = std::move(yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1142 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 206 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[0].value.as< std::shared_ptr<ClassDecl> > (); }
#line 1148 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 207 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[0].value.as< std::shared_ptr<FuncDecl> > (); }
#line 1154 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 211 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<FuncDecl> > () = std::make_shared<FuncDecl>(yylhs.location, yystack_[2].value.as< std::shared_ptr<Identifier> > (), std::get<0>(yystack_[1].value.as< CallSignature > ()), std::get<1>(yystack_[1].value.as< CallSignature > ()), yystack_[0].value.as< std::shared_ptr<CompoundStmt> > ()); }
#line 1160 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 215 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<FuncLiteral> > () = std::make_shared<FuncLiteral>(yylhs.location, std::get<0>(yystack_[1].value.as< CallSignature > ()), std::get<1>(yystack_[1].value.as< CallSignature > ()), yystack_[0].value.as< std::shared_ptr<CompoundStmt> > ()); }
#line 1166 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 219 "src/Parser/Parser.y" // lalr1.cc:859
    { std::get<1>(yylhs.value.as< CallSignature > ()) = nullptr; }
#line 1172 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 220 "src/Parser/Parser.y" // lalr1.cc:859
    { std::get<1>(yylhs.value.as< CallSignature > ()) = yystack_[0].value.as< std::shared_ptr<TypeRepr> > (); }
#line 1178 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 221 "src/Parser/Parser.y" // lalr1.cc:859
    { std::get<0>(yylhs.value.as< CallSignature > ()) = yystack_[1].value.as< std::vector<std::shared_ptr<ParamDecl>> > (); std::get<1>(yylhs.value.as< CallSignature > ()) = nullptr; }
#line 1184 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 222 "src/Parser/Parser.y" // lalr1.cc:859
    { std::get<0>(yylhs.value.as< CallSignature > ()) = yystack_[3].value.as< std::vector<std::shared_ptr<ParamDecl>> > (); std::get<1>(yylhs.value.as< CallSignature > ()) = yystack_[0].value.as< std::shared_ptr<TypeRepr> > (); }
#line 1190 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 226 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<ParamDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<ParamDecl> > ()); }
#line 1196 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 227 "src/Parser/Parser.y" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<ParamDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<ParamDecl> > ()); yylhs.value.as< std::vector<std::shared_ptr<ParamDecl>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<ParamDecl>> > ()); }
#line 1202 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 231 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParamDecl> > () = std::make_shared<ParamDecl>(yylhs.location, yystack_[0].value.as< std::shared_ptr<Identifier> > ()); }
#line 1208 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 232 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParamDecl> > () = std::make_shared<ParamDecl>(yylhs.location, yystack_[2].value.as< std::shared_ptr<Identifier> > (), yystack_[0].value.as< std::shared_ptr<TypeRepr> > ()); }
#line 1214 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 236 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<TypeRepr> > () = std::make_shared<SimpleIdentTypeRepr>(yylhs.location, yystack_[0].value.as< std::shared_ptr<Identifier> > ()); }
#line 1220 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 237 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<TypeRepr> > () = std::make_shared<GenericIdentTypeRepr>(yylhs.location, yystack_[3].value.as< std::shared_ptr<Identifier> > (), yystack_[1].value.as< std::vector<std::shared_ptr<TypeRepr>> > ()); }
#line 1226 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 238 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<TypeRepr> > () = std::make_shared<OptionalTypeRepr>(yylhs.location, yystack_[1].value.as< std::shared_ptr<TypeRepr> > ()); }
#line 1232 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 242 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<TypeRepr>> > ().push_back(yystack_[0].value.as< std::shared_ptr<TypeRepr> > ()); }
#line 1238 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 243 "src/Parser/Parser.y" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<TypeRepr>> > ().push_back(yystack_[0].value.as< std::shared_ptr<TypeRepr> > ()); yylhs.value.as< std::vector<std::shared_ptr<TypeRepr>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<TypeRepr>> > ()); }
#line 1244 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 247 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ClassDecl> > () = std::make_shared<ClassDecl>(yylhs.location, yystack_[2].value.as< std::shared_ptr<Identifier> > (), std::vector<std::shared_ptr<Decl>>{}); }
#line 1250 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 248 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ClassDecl> > () = std::make_shared<ClassDecl>(yylhs.location, yystack_[3].value.as< std::shared_ptr<Identifier> > (), yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1256 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 252 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); }
#line 1262 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 253 "src/Parser/Parser.y" // lalr1.cc:859
    { yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); yylhs.value.as< std::vector<std::shared_ptr<Decl>> > () = std::move(yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1268 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 257 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[0].value.as< std::shared_ptr<FuncDecl> > (); }
#line 1274 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 258 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[1].value.as< std::shared_ptr<VarDecl> > (); }
#line 1280 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 262 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<CompoundStmt> > (); }
#line 1286 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 263 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = std::make_shared<ExprStmt>(yylhs.location, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1292 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 264 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ReturnStmt> > (); }
#line 1298 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 265 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = std::make_shared<DeclStmt>(yylhs.location, yystack_[1].value.as< std::shared_ptr<VarDecl> > ()); }
#line 1304 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 266 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = std::make_shared<DeclStmt>(yylhs.location, yystack_[1].value.as< std::shared_ptr<DecompositionDecl> > ()); }
#line 1310 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 267 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<IfStmt> > (); }
#line 1316 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 268 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<WhileStmt> > (); }
#line 1322 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 269 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ForStmt> > (); }
#line 1328 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 270 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ForEachStmt> > (); }
#line 1334 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 271 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<DeferStmt> > (); }
#line 1340 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 275 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CompoundStmt> > () = std::make_shared<CompoundStmt>(yylhs.location, std::vector<std::shared_ptr<Stmt>>{}); }
#line 1346 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 276 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CompoundStmt> > () = std::make_shared<CompoundStmt>(yylhs.location, yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ()); }
#line 1352 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 280 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Stmt>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1358 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 281 "src/Parser/Parser.y" // lalr1.cc:859
    { yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Stmt> > ()); yylhs.value.as< std::vector<std::shared_ptr<Stmt>> > () = std::move(yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ()); }
#line 1364 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 285 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ReturnStmt> > () = std::make_shared<ReturnStmt>(yylhs.location); }
#line 1370 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 286 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ReturnStmt> > () = std::make_shared<ReturnStmt>(yylhs.location, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1376 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 290 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IfStmt> > () = std::make_shared<IfStmt>(yylhs.location, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1382 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 291 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IfStmt> > () = std::make_shared<IfStmt>(yylhs.location, yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Stmt> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1388 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 295 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<WhileStmt> > () = std::make_shared<WhileStmt>(yylhs.location, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1394 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 299 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ForStmt> > () = std::make_shared<ForStmt>(yylhs.location, yystack_[5].value.as< std::shared_ptr<Stmt> > (), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1400 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 303 "src/Parser/Parser.y" // lalr1.cc:859
    { }
#line 1406 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 304 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = std::make_shared<ExprStmt>(yylhs.location, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1412 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 305 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = std::make_shared<DeclStmt>(yylhs.location, yystack_[1].value.as< std::shared_ptr<VarDecl> > ()); }
#line 1418 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 309 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ForEachStmt> > () = std::make_shared<ForEachStmt>(yylhs.location, yystack_[4].value.as< std::shared_ptr<Decl> > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1424 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 313 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = std::make_shared<NamedDecl>(yylhs.location, yystack_[0].value.as< std::shared_ptr<Identifier> > ()); }
#line 1430 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 314 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = std::make_shared<VarDecl>(yylhs.location, yystack_[0].value.as< std::shared_ptr<Identifier> > (), yystack_[1].value.as< VarDeclSpecifier > (), nullptr, nullptr); }
#line 1436 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 315 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = std::make_shared<DecompositionDecl>(yylhs.location, yystack_[3].value.as< VarDeclSpecifier > (), yystack_[1].value.as< std::vector<std::shared_ptr<BindingDecl>> > ()); }
#line 1442 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 319 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<DeferStmt> > () = std::make_shared<DeferStmt>(yylhs.location, yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1448 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 323 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VarDecl> > () = std::make_shared<VarDecl>(yylhs.location, yystack_[0].value.as< std::shared_ptr<Identifier> > (), yystack_[1].value.as< VarDeclSpecifier > (), nullptr, nullptr); }
#line 1454 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 324 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VarDecl> > () = std::make_shared<VarDecl>(yylhs.location, yystack_[2].value.as< std::shared_ptr<Identifier> > (), yystack_[3].value.as< VarDeclSpecifier > (), nullptr, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1460 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 325 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VarDecl> > () = std::make_shared<VarDecl>(yylhs.location, yystack_[2].value.as< std::shared_ptr<Identifier> > (), yystack_[3].value.as< VarDeclSpecifier > (), yystack_[0].value.as< std::shared_ptr<TypeRepr> > (), nullptr); }
#line 1466 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 326 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VarDecl> > () = std::make_shared<VarDecl>(yylhs.location, yystack_[4].value.as< std::shared_ptr<Identifier> > (), yystack_[5].value.as< VarDeclSpecifier > (), yystack_[2].value.as< std::shared_ptr<TypeRepr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1472 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 330 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< VarDeclSpecifier > () = VarDeclSpecifier::Let; }
#line 1478 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 331 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< VarDeclSpecifier > () = VarDeclSpecifier::Var; }
#line 1484 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 332 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< VarDeclSpecifier > () = VarDeclSpecifier::Const; }
#line 1490 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 336 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<DecompositionDecl> > () = std::make_shared<DecompositionDecl>(yylhs.location, yystack_[5].value.as< VarDeclSpecifier > (), yystack_[3].value.as< std::vector<std::shared_ptr<BindingDecl>> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1496 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 340 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<BindingDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<BindingDecl> > ()); }
#line 1502 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 341 "src/Parser/Parser.y" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<BindingDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<BindingDecl> > ()); yylhs.value.as< std::vector<std::shared_ptr<BindingDecl>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<BindingDecl>> > ()); }
#line 1508 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 345 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BindingDecl> > () = std::make_shared<BindingDecl>(yylhs.location, yystack_[0].value.as< std::shared_ptr<Identifier> > ()); }
#line 1514 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 349 "src/Parser/Parser.y" // lalr1.cc:859
    { }
#line 1520 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 350 "src/Parser/Parser.y" // lalr1.cc:859
    { }
#line 1526 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 354 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<IntegerLiteral> > (); }
#line 1532 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 355 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<DoubleLiteral> > (); }
#line 1538 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 356 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BoolLiteral> > (); }
#line 1544 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 357 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<StringLiteral> > (); }
#line 1550 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 361 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<Expr> > (); }
#line 1556 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 362 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<NullLiteral> > (); }
#line 1562 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 363 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = std::make_shared<IdentifierExpr>(yylhs.location, yystack_[0].value.as< std::shared_ptr<Identifier> > ()); }
#line 1568 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 364 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<ParenExpr> > (); }
#line 1574 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 365 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<ArrayLiteral> > (); }
#line 1580 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 366 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<MapLiteral> > (); }
#line 1586 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 367 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<CallExpr> > (); }
#line 1592 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 368 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<MemberExpr> > (); }
#line 1598 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 369 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<SubscriptExpr> > (); }
#line 1604 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 370 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<NullConditionalOperator> > (); }
#line 1610 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 374 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParenExpr> > () = std::make_shared<ParenExpr>(yylhs.location, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1616 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 378 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullLiteral> > () = std::make_shared<NullLiteral>(yylhs.location); }
#line 1622 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 382 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ArrayLiteral> > () = std::make_shared<ArrayLiteral>(yylhs.location, std::vector<std::shared_ptr<Expr>>{}); }
#line 1628 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 383 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ArrayLiteral> > () = std::make_shared<ArrayLiteral>(yylhs.location, yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1634 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 387 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapLiteral> > () = std::make_shared<MapLiteral>(yylhs.location, std::vector<std::shared_ptr<MapEntry>>{}); }
#line 1640 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 388 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapLiteral> > () = std::make_shared<MapLiteral>(yylhs.location, yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ()); }
#line 1646 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 392 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapEntry> > () = std::make_shared<MapEntry>(yylhs.location, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1652 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 396 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<MapEntry>> > ().push_back(yystack_[0].value.as< std::shared_ptr<MapEntry> > ()); }
#line 1658 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 397 "src/Parser/Parser.y" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ().push_back(yystack_[0].value.as< std::shared_ptr<MapEntry> > ()); yylhs.value.as< std::vector<std::shared_ptr<MapEntry>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ()); }
#line 1664 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 401 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MemberExpr> > () = std::make_shared<MemberExpr>(yylhs.location, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Identifier> > ()); }
#line 1670 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 405 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<SubscriptExpr> > () = std::make_shared<SubscriptExpr>(yylhs.location, yystack_[3].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1676 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 409 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CallExpr> > () = std::make_shared<CallExpr>(yylhs.location, yystack_[2].value.as< std::shared_ptr<Expr> > (), std::vector<std::shared_ptr<Expr>>{}); }
#line 1682 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 410 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CallExpr> > () = std::make_shared<CallExpr>(yylhs.location, yystack_[3].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1688 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 414 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullConditionalOperator> > () = std::make_shared<NullConditionalOperator>(yylhs.location, yystack_[3].value.as< std::shared_ptr<Expr> > (), std::make_shared<MemberExpr>(yylhs.location, yystack_[3].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Identifier> > ())); }
#line 1694 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 415 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullConditionalOperator> > () = std::make_shared<NullConditionalOperator>(yylhs.location, yystack_[4].value.as< std::shared_ptr<Expr> > (), std::make_shared<SubscriptExpr>(yylhs.location, yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::shared_ptr<Expr> > ())); }
#line 1700 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 416 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullConditionalOperator> > () = std::make_shared<NullConditionalOperator>(yylhs.location, yystack_[3].value.as< std::shared_ptr<Expr> > (), std::make_shared<CallExpr>(yylhs.location, yystack_[3].value.as< std::shared_ptr<Expr> > (), std::vector<std::shared_ptr<Expr>>{})); }
#line 1706 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 417 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullConditionalOperator> > () = std::make_shared<NullConditionalOperator>(yylhs.location, yystack_[4].value.as< std::shared_ptr<Expr> > (), std::make_shared<CallExpr>(yylhs.location, yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::vector<std::shared_ptr<Expr>> > ())); }
#line 1712 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 421 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryExpr> > () = std::make_shared<UnaryExpr>(yylhs.location, yystack_[1].value.as< UnaryExprKind > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1718 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 422 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryExpr> > () = std::make_shared<UnaryExpr>(yylhs.location, UnaryExprKind::PostInc, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1724 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 423 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryExpr> > () = std::make_shared<UnaryExpr>(yylhs.location, UnaryExprKind::PostDec, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1730 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 427 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< UnaryExprKind > () = UnaryExprKind::PreInc; }
#line 1736 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 428 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< UnaryExprKind > () = UnaryExprKind::PreDec; }
#line 1742 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 429 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< UnaryExprKind > () = UnaryExprKind::Plus; }
#line 1748 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 430 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< UnaryExprKind > () = UnaryExprKind::Minus; }
#line 1754 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 431 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< UnaryExprKind > () = UnaryExprKind::LogicalNot; }
#line 1760 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 435 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryExpr> > () = std::make_shared<BinaryExpr>(yylhs.location, yystack_[1].value.as< BinaryExprKind > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1766 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 439 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::Add; }
#line 1772 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 440 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::Subtract; }
#line 1778 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 441 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::Multiply; }
#line 1784 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 442 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::Divide; }
#line 1790 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 443 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::Mod; }
#line 1796 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 444 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::Equal; }
#line 1802 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 445 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::NotEqual; }
#line 1808 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 446 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::LogicalAnd; }
#line 1814 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 447 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::LogicalOr; }
#line 1820 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 448 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::GreaterThan; }
#line 1826 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 449 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::GreaterThanOrEqual; }
#line 1832 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 450 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::LessThan; }
#line 1838 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 451 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::LessThanOrEqual; }
#line 1844 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 452 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< BinaryExprKind > () = BinaryExprKind::NullCoalescing; }
#line 1850 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 456 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ConditionalOperator> > () = std::make_shared<ConditionalOperator>(yylhs.location, yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1856 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 460 "src/Parser/Parser.y" // lalr1.cc:859
    { }
#line 1862 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 464 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<AssignExpr> > () = std::make_shared<AssignExpr>(yylhs.location, AssignExprKind::Assign, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1868 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 468 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Expr>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1874 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 469 "src/Parser/Parser.y" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Expr> > ()); yylhs.value.as< std::vector<std::shared_ptr<Expr>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1880 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 473 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<Expr> > (); }
#line 1886 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 474 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<AssignExpr> > (); }
#line 1892 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 475 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BinaryExpr> > (); }
#line 1898 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 476 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<UnaryExpr> > (); }
#line 1904 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 477 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<ConditionalOperator> > (); }
#line 1910 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 478 "src/Parser/Parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<FuncLiteral> > (); }
#line 1916 "src/Parser/Parser.cpp" // lalr1.cc:859
    break;


#line 1920 "src/Parser/Parser.cpp" // lalr1.cc:859
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


  const signed char Parser::yypact_ninf_ = -111;

  const signed char Parser::yytable_ninf_ = -58;

  const short int
  Parser::yypact_[] =
  {
     -25,   -23,   -22,    30,   -25,  -111,  -111,  -111,     6,    25,
    -111,  -111,    -4,    29,   112,     7,    27,   -15,  -111,   175,
    -111,  -111,  -111,  -111,  -111,  -111,   196,  -111,    72,    67,
      69,    69,    85,    74,  -111,  -111,  -111,  -111,  -111,   144,
    -111,   285,     6,   337,    81,   101,   102,   279,  -111,  -111,
    -111,  -111,  -111,  -111,  -111,  -111,  -111,   227,  -111,  -111,
    -111,  -111,  -111,  -111,    97,   -18,   100,  -111,    99,  -111,
    -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,    14,  -111,
    -111,  -111,   428,  -111,  -111,  -111,    17,   108,   104,   104,
      69,  -111,    79,  -111,   105,  -111,   103,   109,   450,    29,
    -111,   472,   144,   144,    21,  -111,  -111,  -111,  -111,    90,
    -111,  -111,  -111,   345,   144,    94,    -2,   144,    20,   144,
    -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,
    -111,  -111,  -111,  -111,  -111,   144,   144,    69,    69,  -111,
     104,  -111,  -111,   144,   116,   144,   117,   144,  -111,  -111,
     494,   518,  -111,   110,   144,   114,   119,   -17,   542,  -111,
      44,  -111,  -111,    55,   724,   564,  -111,   389,   144,   111,
     598,    -2,   724,   240,   724,     3,   104,    18,  -111,   450,
    -111,   724,  -111,   724,   279,   279,   620,   144,  -111,    90,
       9,  -111,   152,    90,  -111,   144,  -111,  -111,    83,   642,
    -111,   144,   144,  -111,    69,   120,  -111,   144,   676,    84,
     144,  -111,  -111,  -111,   240,   724,   104,   279,   700,   279,
    -111,   724,  -111,   279,  -111,  -111
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       2,     0,     0,     0,     3,     4,     7,     6,     0,     0,
       1,     5,     0,     0,     0,    10,    16,     0,    14,     0,
       8,    23,    61,    62,    63,    27,     0,    25,     0,     0,
       0,     0,    12,     0,   107,   106,   104,   105,   108,     0,
      39,     0,     0,     0,     0,     0,     0,     0,    85,    76,
      70,    71,    72,    73,   134,    41,    29,     0,    31,    34,
      35,    36,    37,    38,     0,     0,     0,    74,   129,    77,
      75,    78,    79,    81,    82,    80,    83,   132,     0,   131,
     133,   130,     0,    24,    26,    28,    57,    18,    11,    17,
       0,    15,     0,    86,     0,    91,    68,    68,   127,     0,
      43,     0,     0,     0,     0,    56,    40,    42,    32,     0,
      33,   102,   103,     0,     0,     0,   125,     0,   101,     0,
     111,   110,   112,   113,   114,   117,   118,   115,   116,   122,
     120,   121,   119,    30,   123,     0,     0,     0,     0,    20,
      13,    84,    88,    69,     0,    69,     0,     0,     9,    44,
       0,     0,    49,    76,     0,     0,     0,     0,     0,    67,
       0,    65,    95,     0,   127,     0,    93,     0,     0,     0,
       0,     0,   126,   109,    58,    59,    21,     0,    92,     0,
      89,   128,    87,    90,     0,     0,     0,     0,    51,     0,
      54,    50,     0,     0,    96,     0,    94,    99,     0,     0,
      97,     0,     0,    19,     0,    45,    47,     0,     0,     0,
       0,    66,   100,    98,   124,    60,    22,     0,     0,     0,
      55,    64,    46,     0,    52,    48
  };

  const short int
  Parser::yypgoto_[] =
  {
    -111,  -111,  -111,   161,    -5,  -111,   124,  -111,   123,   -30,
    -111,  -111,  -111,   141,   -47,    -8,  -111,  -111,  -111,  -111,
    -111,  -111,  -111,  -111,  -111,   -12,   -10,  -111,   -21,    -9,
      78,  -111,   107,  -111,  -111,  -111,  -111,    38,  -111,  -111,
    -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,
    -110,   -24
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,     5,     6,    54,    13,    17,    18,    88,
     177,     7,    26,    27,    55,    56,    57,    58,    59,    60,
      61,   154,    62,   155,    63,    64,    65,    66,   160,   161,
     144,    67,    68,    69,    70,    71,    72,    95,    96,    73,
      74,    75,    76,    77,    78,    79,   135,    80,   117,    81,
      97,    82
  };

  const short int
  Parser::yytable_[] =
  {
     105,    89,    28,   163,    29,    20,   202,   109,   189,    25,
     107,    32,   136,     1,    28,    92,    29,    98,    33,   101,
     136,    25,    15,   167,     2,    34,    35,   168,     8,     9,
      10,    12,   169,    86,   190,    36,    37,    38,   139,    39,
     137,   -57,   203,    41,    30,   113,    39,    16,   137,   114,
      41,   204,    14,   152,   115,   171,    19,   198,    31,    42,
     140,    22,    23,    24,    48,    49,    50,    51,    52,    53,
     192,    48,   153,    50,    51,    52,    53,   193,   150,   151,
     158,   194,   119,   120,   121,   122,   123,   124,   195,   164,
     165,   148,   156,   170,   157,   172,   125,   126,   127,   128,
     129,   130,   131,   132,    85,   141,   102,   175,   176,   212,
     220,   173,   174,   111,   112,   134,   195,   193,    86,   179,
      87,   181,    90,   183,   113,    16,   103,   104,   114,   108,
     186,   138,   110,   115,   116,   142,   143,   205,   206,   139,
      21,   159,   145,   164,   199,   166,   180,   182,    34,    35,
       1,   188,    22,    23,    24,   210,    91,   -53,    36,    37,
      38,   187,   200,   208,   217,    11,    99,    84,   209,    39,
     222,   181,   224,    41,   216,   146,   225,   214,   215,    34,
      35,   178,    42,   218,   211,   118,   221,     0,     0,    36,
      37,    38,     0,     0,    48,    49,    50,    51,    52,    53,
      39,     0,    19,    40,    41,     0,     0,     0,     0,     0,
       0,     0,     0,    42,    43,    22,    23,    24,    44,     0,
      45,    46,     0,    47,    83,    48,    49,    50,    51,    52,
      53,    34,    35,     0,     1,     0,    22,    23,    24,     0,
       0,    36,    37,    38,   120,   121,   122,   123,   124,     0,
       0,     0,    39,     0,    19,   106,    41,   125,   126,   127,
     128,   129,   130,   131,   132,    42,    43,    22,    23,    24,
      44,     0,    45,    46,     0,    47,   134,    48,    49,    50,
      51,    52,    53,    34,    35,     0,     0,     0,     0,    34,
      35,     0,     0,    36,    37,    38,     0,     0,     0,    36,
      37,    38,     0,     0,    39,     0,    19,     0,    41,     0,
      39,     0,     0,     0,    41,    93,    94,    42,    43,    22,
      23,    24,    44,    42,    45,    46,     0,    47,     0,    48,
      49,    50,    51,    52,    53,    48,    49,    50,    51,    52,
      53,    34,    35,     0,     0,     0,     0,     0,     0,    34,
      35,    36,    37,    38,     0,     0,     0,     0,     0,    36,
      37,    38,    39,     0,     0,     0,    41,     0,     0,   100,
      39,   162,     0,     0,    41,    42,     0,     0,     0,     0,
       0,     0,     0,    42,     0,     0,     0,    48,    49,    50,
      51,    52,    53,    34,    35,    48,    49,    50,    51,    52,
      53,     0,     0,    36,    37,    38,     0,     0,     0,     0,
       0,     0,     0,     0,    39,   197,     0,     0,    41,     0,
       0,     0,     0,     0,     0,     0,     0,    42,     0,     0,
       0,   119,   120,   121,   122,   123,   124,     0,     0,    48,
      49,    50,    51,    52,    53,   125,   126,   127,   128,   129,
     130,   131,   132,   119,   120,   121,   122,   123,   124,     0,
     133,     0,     0,     0,   134,     0,     0,   125,   126,   127,
     128,   129,   130,   131,   132,   119,   120,   121,   122,   123,
     124,   147,     0,     0,     0,     0,   134,     0,     0,   125,
     126,   127,   128,   129,   130,   131,   132,   119,   120,   121,
     122,   123,   124,     0,   149,     0,     0,     0,   134,     0,
       0,   125,   126,   127,   128,   129,   130,   131,   132,     0,
     184,   119,   120,   121,   122,   123,   124,     0,     0,     0,
     134,     0,     0,     0,     0,   125,   126,   127,   128,   129,
     130,   131,   132,     0,   185,   119,   120,   121,   122,   123,
     124,     0,     0,     0,   134,     0,     0,     0,     0,   125,
     126,   127,   128,   129,   130,   131,   132,   119,   120,   121,
     122,   123,   124,     0,   191,     0,     0,     0,   134,     0,
       0,   125,   126,   127,   128,   129,   130,   131,   132,     0,
       0,     0,     0,     0,   196,     0,     0,     0,     0,     0,
     134,   119,   120,   121,   122,   123,   124,     0,     0,     0,
       0,     0,     0,     0,     0,   125,   126,   127,   128,   129,
     130,   131,   132,   119,   120,   121,   122,   123,   124,   201,
       0,     0,     0,     0,   134,     0,     0,   125,   126,   127,
     128,   129,   130,   131,   132,   119,   120,   121,   122,   123,
     124,     0,   207,     0,     0,     0,   134,     0,     0,   125,
     126,   127,   128,   129,   130,   131,   132,     0,     0,     0,
       0,     0,   213,     0,     0,     0,     0,     0,   134,   119,
     120,   121,   122,   123,   124,     0,     0,     0,     0,     0,
       0,     0,     0,   125,   126,   127,   128,   129,   130,   131,
     132,     0,   219,   119,   120,   121,   122,   123,   124,     0,
       0,     0,   134,     0,     0,     0,     0,   125,   126,   127,
     128,   129,   130,   131,   132,     0,   223,   119,   120,   121,
     122,   123,   124,     0,     0,     0,   134,     0,     0,     0,
       0,   125,   126,   127,   128,   129,   130,   131,   132,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     134
  };

  const short int
  Parser::yycheck_[] =
  {
      47,    31,    14,   113,    14,    13,     3,    25,    25,    14,
      57,    26,     3,    38,    26,    39,    26,    41,    33,    43,
       3,    26,    26,    25,    49,     4,     5,    29,    51,    51,
       0,    25,    34,    51,    51,    14,    15,    16,    35,    25,
      31,    32,    24,    29,    37,    25,    25,    51,    31,    29,
      29,    33,    27,    32,    34,    35,    27,   167,    31,    38,
      90,    40,    41,    42,    50,    51,    52,    53,    54,    55,
      26,    50,    51,    52,    53,    54,    55,    33,   102,   103,
     104,    26,     3,     4,     5,     6,     7,     8,    33,   113,
     114,    99,   104,   117,   104,   119,    17,    18,    19,    20,
      21,    22,    23,    24,    32,    26,    25,   137,   138,    26,
      26,   135,   136,    14,    15,    36,    33,    33,    51,   143,
      51,   145,    37,   147,    25,    51,    25,    25,    29,    32,
     154,    23,    32,    34,    35,    30,    33,   184,   185,    35,
      28,    51,    33,   167,   168,    51,    30,    30,     4,     5,
      38,    32,    40,    41,    42,     3,    33,    47,    14,    15,
      16,    47,    51,   187,    44,     4,    42,    26,   189,    25,
     217,   195,   219,    29,   204,    97,   223,   201,   202,     4,
       5,   143,    38,   207,   193,    78,   210,    -1,    -1,    14,
      15,    16,    -1,    -1,    50,    51,    52,    53,    54,    55,
      25,    -1,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    39,    40,    41,    42,    43,    -1,
      45,    46,    -1,    48,    28,    50,    51,    52,    53,    54,
      55,     4,     5,    -1,    38,    -1,    40,    41,    42,    -1,
      -1,    14,    15,    16,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    25,    -1,    27,    28,    29,    17,    18,    19,
      20,    21,    22,    23,    24,    38,    39,    40,    41,    42,
      43,    -1,    45,    46,    -1,    48,    36,    50,    51,    52,
      53,    54,    55,     4,     5,    -1,    -1,    -1,    -1,     4,
       5,    -1,    -1,    14,    15,    16,    -1,    -1,    -1,    14,
      15,    16,    -1,    -1,    25,    -1,    27,    -1,    29,    -1,
      25,    -1,    -1,    -1,    29,    30,    31,    38,    39,    40,
      41,    42,    43,    38,    45,    46,    -1,    48,    -1,    50,
      51,    52,    53,    54,    55,    50,    51,    52,    53,    54,
      55,     4,     5,    -1,    -1,    -1,    -1,    -1,    -1,     4,
       5,    14,    15,    16,    -1,    -1,    -1,    -1,    -1,    14,
      15,    16,    25,    -1,    -1,    -1,    29,    -1,    -1,    32,
      25,    26,    -1,    -1,    29,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,     4,     5,    50,    51,    52,    53,    54,
      55,    -1,    -1,    14,    15,    16,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    25,    26,    -1,    -1,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,    -1,    -1,    50,
      51,    52,    53,    54,    55,    17,    18,    19,    20,    21,
      22,    23,    24,     3,     4,     5,     6,     7,     8,    -1,
      32,    -1,    -1,    -1,    36,    -1,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,     3,     4,     5,     6,     7,
       8,    31,    -1,    -1,    -1,    -1,    36,    -1,    -1,    17,
      18,    19,    20,    21,    22,    23,    24,     3,     4,     5,
       6,     7,     8,    -1,    32,    -1,    -1,    -1,    36,    -1,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    -1,
      26,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,
      22,    23,    24,    -1,    26,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    17,
      18,    19,    20,    21,    22,    23,    24,     3,     4,     5,
       6,     7,     8,    -1,    32,    -1,    -1,    -1,    36,    -1,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      36,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,
      22,    23,    24,     3,     4,     5,     6,     7,     8,    31,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,     3,     4,     5,     6,     7,
       8,    -1,    32,    -1,    -1,    -1,    36,    -1,    -1,    17,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    36,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    26,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    36,    -1,    -1,    -1,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    -1,    26,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,    38,    49,    64,    65,    66,    67,    74,    51,    51,
       0,    66,    25,    69,    27,    26,    51,    70,    71,    27,
      78,    28,    40,    41,    42,    67,    75,    76,    88,    89,
      37,    31,    26,    33,     4,     5,    14,    15,    16,    25,
      28,    29,    38,    39,    43,    45,    46,    48,    50,    51,
      52,    53,    54,    55,    68,    77,    78,    79,    80,    81,
      82,    83,    85,    87,    88,    89,    90,    94,    95,    96,
      97,    98,    99,   102,   103,   104,   105,   106,   107,   108,
     110,   112,   114,    28,    76,    32,    51,    51,    72,    72,
      37,    71,   114,    30,    31,   100,   101,   113,   114,    69,
      32,   114,    25,    25,    25,    77,    28,    77,    32,    25,
      32,    14,    15,    25,    29,    34,    35,   111,    95,     3,
       4,     5,     6,     7,     8,    17,    18,    19,    20,    21,
      22,    23,    24,    32,    36,   109,     3,    31,    23,    35,
      72,    26,    30,    33,    93,    33,    93,    31,    78,    32,
     114,   114,    32,    51,    84,    86,    88,    89,   114,    51,
      91,    92,    26,   113,   114,   114,    51,    25,    29,    34,
     114,    35,   114,   114,   114,    72,    72,    73,   100,   114,
      30,   114,    30,   114,    26,    26,   114,    47,    32,    25,
      51,    32,    26,    33,    26,    33,    30,    26,   113,   114,
      51,    31,     3,    24,    33,    77,    77,    32,   114,    91,
       3,    92,    26,    30,   114,   114,    72,    44,   114,    26,
      26,   114,    77,    26,    77,    77
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    63,    64,    64,    65,    65,    66,    66,    67,    68,
      69,    69,    69,    69,    70,    70,    71,    71,    72,    72,
      72,    73,    73,    74,    74,    75,    75,    76,    76,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    78,
      78,    79,    79,    80,    80,    81,    81,    82,    83,    84,
      84,    84,    85,    86,    86,    86,    87,    88,    88,    88,
      88,    89,    89,    89,    90,    91,    91,    92,    93,    93,
      94,    94,    94,    94,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    96,    97,    98,    98,    99,    99,
     100,   101,   101,   102,   103,   104,   104,   105,   105,   105,
     105,   106,   106,   106,   107,   107,   107,   107,   107,   108,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   110,   111,   112,   113,   113,   114,
     114,   114,   114,   114,   114
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     0,     1,     1,     2,     1,     1,     4,     3,
       2,     4,     3,     5,     1,     3,     1,     3,     1,     4,
       2,     1,     3,     4,     5,     1,     2,     1,     2,     1,
       2,     1,     2,     2,     1,     1,     1,     1,     1,     2,
       3,     1,     2,     2,     3,     5,     7,     5,     8,     1,
       2,     2,     7,     1,     2,     4,     2,     2,     4,     4,
       6,     1,     1,     1,     6,     1,     3,     1,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     2,     4,     3,     4,
       3,     1,     3,     3,     4,     3,     4,     4,     5,     4,
       5,     2,     2,     2,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     1,     3,     1,     3,     1,
       1,     1,     1,     1,     1
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
  "\"in\"", "\"defer\"", "\"class\"", "\"null\"", "\"identifier\"",
  "\"integer_literal\"", "\"double_literal\"", "\"bool_literal\"",
  "\"string_literal\"", "\"conditional_expression\"", "\"binary_op\"",
  "\"unary_plus\"", "\"unary_minus\"", "\"ternary_question\"",
  "\"grouping\"", "\"then\"", "$accept", "TranslationUnitDecl",
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
       0,   196,   196,   197,   201,   202,   206,   207,   211,   215,
     219,   220,   221,   222,   226,   227,   231,   232,   236,   237,
     238,   242,   243,   247,   248,   252,   253,   257,   258,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   275,
     276,   280,   281,   285,   286,   290,   291,   295,   299,   303,
     304,   305,   309,   313,   314,   315,   319,   323,   324,   325,
     326,   330,   331,   332,   336,   340,   341,   345,   349,   350,
     354,   355,   356,   357,   361,   362,   363,   364,   365,   366,
     367,   368,   369,   370,   374,   378,   382,   383,   387,   388,
     392,   396,   397,   401,   405,   409,   410,   414,   415,   416,
     417,   421,   422,   423,   427,   428,   429,   430,   431,   435,
     439,   440,   441,   442,   443,   444,   445,   446,   447,   448,
     449,   450,   451,   452,   456,   460,   464,   468,   469,   473,
     474,   475,   476,   477,   478
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
#line 2572 "src/Parser/Parser.cpp" // lalr1.cc:1167
#line 481 "src/Parser/Parser.y" // lalr1.cc:1168


namespace elma {

void Parser::error(const location_type& loc, const std::string& what)
{
    driver.error(loc, what);
}

} // namespace elma
