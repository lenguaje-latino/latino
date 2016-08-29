/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parse.y" /* yacc.c:339  */

/* bison -y -oparse.c parse.y */
#define YYERROR_VERBOSE 1
#define YYDEBUG 1
#define YYENABLE_NLS 1
#define YYLEX_PARAM &yylval, &yylloc

#include <stddef.h>

#include "latino.h"
#include "ast.h"
#include "lex.h"

#ifdef __linux
#include <libintl.h>
#define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#endif

int yyerror(struct YYLTYPE *yylloc_param, void *scanner, struct ast **root, const char *s);
int yylex (YYSTYPE * yylval_param,YYLTYPE * yylloc_param ,yyscan_t yyscanner);


#line 89 "parse.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parse.h".  */
#ifndef YY_YY_PARSE_H_INCLUDED
# define YY_YY_PARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    VERDADERO = 258,
    FALSO = 259,
    ENTERO = 260,
    LITERAL = 261,
    _DECIMAL = 262,
    CADENA = 263,
    IDENTIFICADOR = 264,
    CONSTANTE = 265,
    SI = 266,
    FIN = 267,
    SINO = 268,
    MIENTRAS = 269,
    HACER = 270,
    ROMPER = 271,
    CONTINUAR = 272,
    CUANDO = 273,
    FUNCION = 274,
    DESDE = 275,
    KBOOL = 276,
    RETORNO = 277,
    INCLUIR = 278,
    ELEGIR = 279,
    CASO = 280,
    DEFECTO = 281,
    MAYOR_QUE = 282,
    MENOR_QUE = 283,
    MAYOR_IGUAL = 284,
    MENOR_IGUAL = 285,
    IGUAL_LOGICO = 286,
    DIFERENTE = 287,
    Y_LOGICO = 288,
    O_LOGICO = 289,
    INCREMENTO = 290,
    DECREMENTO = 291,
    CONCATENAR = 292,
    CONCATENAR_IGUAL = 293
  };
#endif
/* Tokens.  */
#define VERDADERO 258
#define FALSO 259
#define ENTERO 260
#define LITERAL 261
#define _DECIMAL 262
#define CADENA 263
#define IDENTIFICADOR 264
#define CONSTANTE 265
#define SI 266
#define FIN 267
#define SINO 268
#define MIENTRAS 269
#define HACER 270
#define ROMPER 271
#define CONTINUAR 272
#define CUANDO 273
#define FUNCION 274
#define DESDE 275
#define KBOOL 276
#define RETORNO 277
#define INCLUIR 278
#define ELEGIR 279
#define CASO 280
#define DEFECTO 281
#define MAYOR_QUE 282
#define MENOR_QUE 283
#define MAYOR_IGUAL 284
#define MENOR_IGUAL 285
#define IGUAL_LOGICO 286
#define DIFERENTE 287
#define Y_LOGICO 288
#define O_LOGICO 289
#define INCREMENTO 290
#define DECREMENTO 291
#define CONCATENAR 292
#define CONCATENAR_IGUAL 293

/* Value type.  */

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (ast **root, void *scanner);

#endif /* !YY_YY_PARSE_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 224 "parse.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
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


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  68
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   416

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  103
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  194

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,     2,     2,    44,     2,     2,
      48,    49,    42,    40,    53,    41,     2,    43,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    47,    52,
       2,    39,     2,    46,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    50,     2,    51,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    54,     2,    55,     2,     2,     2,     2,
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
      35,    36,    37,    38
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   104,   104,   105,   106,   107,   111,   112,   113,   114,
     118,   119,   123,   124,   125,   129,   130,   134,   135,   136,
     137,   141,   142,   146,   150,   154,   158,   162,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   185,   188,   192,   197,   202,   206,
     207,   208,   209,   210,   211,   212,   216,   217,   220,   221,
     225,   226,   227,   228,   229,   230,   231,   235,   238,   241,
     248,   255,   261,   263,   265,   271,   273,   275,   281,   285,
     291,   294,   295,   296,   300,   301,   302,   306,   310,   311,
     312,   316,   320,   321,   325,   328,   333,   334,   338,   339,
     340,   341,   342,   343
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VERDADERO", "FALSO", "ENTERO",
  "LITERAL", "_DECIMAL", "CADENA", "IDENTIFICADOR", "CONSTANTE", "SI",
  "FIN", "SINO", "MIENTRAS", "HACER", "ROMPER", "CONTINUAR", "CUANDO",
  "FUNCION", "DESDE", "KBOOL", "RETORNO", "INCLUIR", "ELEGIR", "CASO",
  "DEFECTO", "MAYOR_QUE", "MENOR_QUE", "MAYOR_IGUAL", "MENOR_IGUAL",
  "IGUAL_LOGICO", "DIFERENTE", "Y_LOGICO", "O_LOGICO", "INCREMENTO",
  "DECREMENTO", "CONCATENAR", "CONCATENAR_IGUAL", "'='", "'+'", "'-'",
  "'*'", "'/'", "'%'", "'!'", "'?'", "':'", "'('", "')'", "'['", "']'",
  "';'", "','", "'{'", "'}'", "$accept", "constant_expression",
  "primary_expression", "unary_expression", "multiplicative_expression",
  "additive_expression", "relational_expression", "equality_expression",
  "logical_not_expression", "logical_and_expression",
  "logical_or_expression", "ternary_expression", "concat_expression",
  "expression", "program", "statement_list", "statement",
  "incdec_statement", "include_declaration", "declaration",
  "labeled_statements", "labeled_statement_case",
  "labeled_statement_default", "selection_statement",
  "iteration_statement", "jump_statement", "function_definition",
  "function_call", "argument_expression_list", "identifier_list",
  "list_new", "list_items", "dict_new", "dict_items", "dict_item", "key",
  "list_get_item", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,    61,
      43,    45,    42,    47,    37,    33,    63,    58,    40,    41,
      91,    93,    59,    44,   123,   125
};
# endif

#define YYPACT_NINF -62

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-62)))

#define YYTABLE_NINF -48

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     260,   276,   101,   -29,    18,    18,   276,     4,   -28,    18,
      12,    18,    80,   -62,    64,   -62,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,   -62,   -62,   -62,    18,    18,    18,    -1,
      18,   -62,   -62,   -62,   -62,   -62,   -62,   -31,   -62,    18,
      18,    18,    18,    18,    61,   -62,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,   -62,   -62,   -62,   179,   -62,   -62,   -62,
     -62,   179,    63,    37,    26,   358,   106,   320,   -62,   -62,
     358,   -62,   338,    88,    44,    60,    75,   358,    86,   376,
     376,   376,   274,   197,    76,   -62,   -62,    41,    82,    95,
      18,    18,    18,    18,    18,    18,    18,    18,    18,    18,
      18,    18,    18,    18,    39,   121,    18,   134,   126,    92,
      96,    97,    24,   103,   140,    45,   -62,    18,    18,   -62,
     114,   115,   104,   107,   109,   112,   -62,    18,   -62,   -62,
      61,    18,   -62,   -62,   -62,   -62,   -62,   -62,   384,   384,
      11,    11,    11,   376,   376,   376,   -62,   276,   -62,   358,
     -62,   -44,    18,   -62,   -62,   119,   276,   -62,   -62,   297,
     -62,    18,    18,   -62,   128,   131,   -62,   -62,   -62,   358,
     161,   276,   168,   215,   276,   -62,    18,   358,   358,    18,
      18,   -62,   166,   -62,    26,   -62,   358,   358,   358,   -62,
     130,   276,   169,   -62
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    45,     0,    66,    49,    50,    51,    52,
      53,    54,    55,    48,    56,    57,     0,     0,    81,     0,
       0,     8,     9,     2,     4,     3,     5,     6,     7,     0,
       0,     0,     0,    88,    94,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,     0,    40,    41,    43,
      42,     0,     0,     0,     0,    78,     0,     0,     1,    46,
      65,    61,    60,    83,     0,     0,     0,    62,     0,    11,
      10,    23,     0,    90,     0,    96,    97,     0,    93,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    84,     0,     0,
       0,     0,     0,     0,     0,    68,    69,     0,    81,    80,
       0,     0,     0,     0,     0,     0,    28,    88,    87,    91,
      94,     0,    17,    18,    19,    20,    22,    21,    24,    25,
      27,    16,    15,    12,    13,    14,    72,     0,    75,    76,
      85,     0,     0,    59,    58,     0,     0,    74,    67,     0,
      82,     0,     0,   100,    99,    98,   103,    89,    92,    95,
       0,     0,     0,     0,     0,    71,     0,    63,    64,     0,
       0,    73,     0,    86,     0,    70,    26,   101,   102,    79,
       0,     0,     0,    77
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -62,    70,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,     7,   -62,     1,   -62,   -62,   -62,   -61,
      69,   -62,   -62,   -62,   -62,   -62,   -62,     0,    67,   -62,
     -62,    68,   -62,    66,   -62,   -62,   -62
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    71,    55,    73,    12,    13,    14,    15,    16,    17,
     114,   115,   116,    18,    19,    20,    21,    57,    74,   151,
      58,    84,    59,    87,    88,    89,    60
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      22,    22,    23,   109,    75,   171,    22,    62,    76,   172,
      30,    56,    61,    63,    22,    69,    65,    28,    67,    78,
      64,    31,    32,    33,    34,    35,    36,    37,    38,    33,
      34,    35,    36,    70,    72,   108,     3,    77,    90,    91,
      92,    93,    94,    95,    96,    97,    79,    80,    81,    82,
      83,   146,   147,   101,   102,   103,    22,   104,    39,    40,
      66,    22,   105,    41,   -47,     1,    42,    85,    43,    86,
     112,   113,    44,     2,     3,     4,   -47,   -47,     5,     6,
      68,   106,   -47,     7,     8,   107,     9,    10,    11,   -47,
     -47,   122,   123,   119,   124,   125,   129,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   120,   110,   149,   111,    90,    91,    92,    93,    94,
      95,    96,    97,   190,   159,    98,   121,   128,    99,   100,
     101,   102,   103,   148,    83,   130,    24,    25,   169,    26,
      27,   118,   131,   150,   152,   153,   154,    22,   170,    28,
     156,    29,   157,   161,   162,   163,    22,   175,   164,   173,
     165,    24,    25,   166,    26,    27,   174,   179,   177,   178,
     180,    22,   182,   181,    22,   185,    29,   183,   189,   191,
       1,   193,   155,   186,   158,   160,   187,   188,     2,     3,
       4,    22,   192,     5,     6,   167,   168,     0,     7,     8,
       0,     9,    10,    11,     0,     0,    90,    91,    92,    93,
      94,    95,    96,    97,     0,     0,    98,     0,     0,    99,
     100,   101,   102,   103,    90,    91,    92,    93,    94,    95,
      96,    97,     0,     0,    98,     0,     0,    99,   100,   101,
     102,   103,    90,    91,    92,    93,    94,    95,    96,    97,
     127,     0,    98,     0,     0,    99,   100,   101,   102,   103,
     -44,     1,     0,     0,     0,     0,     0,   184,     0,     2,
       3,     4,     0,     0,     5,     6,     0,     1,     0,     7,
       8,     0,     9,    10,    11,     2,     3,     4,     0,     0,
       5,     6,     0,     0,     0,     7,     8,     0,     9,    10,
      11,    90,    91,    92,    93,    94,    95,    96,    97,     0,
       0,    98,     0,     0,    99,   100,   101,   102,   103,     0,
       0,     0,     0,   126,    90,    91,    92,    93,    94,    95,
      96,    97,     0,     0,    98,     0,     0,    99,   100,   101,
     102,   103,     0,     0,   176,   112,   113,    90,    91,    92,
      93,    94,    95,    96,    97,     0,     0,    98,     0,     0,
      99,   100,   101,   102,   103,    90,    91,    92,    93,    94,
      95,    96,    97,     0,     0,    98,     0,     0,    99,   100,
     101,   102,   103,     0,   117,    90,    91,    92,    93,    94,
      95,    96,    97,     0,     0,    98,     0,     0,    99,   100,
     101,   102,   103,    90,    91,    92,    93,    94,    95,    96,
      97,    90,    91,    92,    93,    94,    95
};

static const yytype_int16 yycheck[] =
{
       0,     1,     1,    64,     5,    49,     6,     6,     9,    53,
      39,     4,     5,     9,    14,    14,     9,    48,    11,    50,
      48,     3,     4,     5,     6,     7,     8,     9,    10,     5,
       6,     7,     8,    26,    27,     9,    10,    30,    27,    28,
      29,    30,    31,    32,    33,    34,    39,    40,    41,    42,
      43,    12,    13,    42,    43,    44,    56,    56,    40,    41,
      48,    61,    61,    45,     0,     1,    48,     6,    50,     8,
      25,    26,    54,     9,    10,    11,    12,    13,    14,    15,
       0,    18,    18,    19,    20,    48,    22,    23,    24,    25,
      26,     5,     6,    49,     8,     9,    55,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,    51,     6,   106,     8,    27,    28,    29,    30,    31,
      32,    33,    34,   184,   117,    37,    51,    51,    40,    41,
      42,    43,    44,    12,   127,    53,    35,    36,   131,    38,
      39,    53,    47,     9,    52,    49,    49,   147,   147,    48,
      47,    50,    12,    39,    39,    51,   156,   156,    51,   152,
      51,    35,    36,    51,    38,    39,    47,    39,   161,   162,
      39,   171,   171,    12,   174,   174,    50,     9,    12,    49,
       1,    12,   112,   176,   115,   118,   179,   180,     9,    10,
      11,   191,   191,    14,    15,   127,   130,    -1,    19,    20,
      -1,    22,    23,    24,    -1,    -1,    27,    28,    29,    30,
      31,    32,    33,    34,    -1,    -1,    37,    -1,    -1,    40,
      41,    42,    43,    44,    27,    28,    29,    30,    31,    32,
      33,    34,    -1,    -1,    37,    -1,    -1,    40,    41,    42,
      43,    44,    27,    28,    29,    30,    31,    32,    33,    34,
      53,    -1,    37,    -1,    -1,    40,    41,    42,    43,    44,
       0,     1,    -1,    -1,    -1,    -1,    -1,    52,    -1,     9,
      10,    11,    -1,    -1,    14,    15,    -1,     1,    -1,    19,
      20,    -1,    22,    23,    24,     9,    10,    11,    -1,    -1,
      14,    15,    -1,    -1,    -1,    19,    20,    -1,    22,    23,
      24,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      -1,    37,    -1,    -1,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    49,    27,    28,    29,    30,    31,    32,
      33,    34,    -1,    -1,    37,    -1,    -1,    40,    41,    42,
      43,    44,    -1,    -1,    47,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    -1,    -1,    37,    -1,    -1,
      40,    41,    42,    43,    44,    27,    28,    29,    30,    31,
      32,    33,    34,    -1,    -1,    37,    -1,    -1,    40,    41,
      42,    43,    44,    -1,    46,    27,    28,    29,    30,    31,
      32,    33,    34,    -1,    -1,    37,    -1,    -1,    40,    41,
      42,    43,    44,    27,    28,    29,    30,    31,    32,    33,
      34,    27,    28,    29,    30,    31,    32
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     9,    10,    11,    14,    15,    19,    20,    22,
      23,    24,    70,    71,    72,    73,    74,    75,    79,    80,
      81,    82,    83,    71,    35,    36,    38,    39,    48,    50,
      39,     3,     4,     5,     6,     7,     8,     9,    10,    40,
      41,    45,    48,    50,    54,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    68,    69,    83,    86,    88,
      92,    69,    71,     9,    48,    69,    48,    69,     0,    71,
      69,    67,    69,    69,    84,     5,     9,    69,    50,    69,
      69,    69,    69,    69,    87,     6,     8,    89,    90,    91,
      27,    28,    29,    30,    31,    32,    33,    34,    37,    40,
      41,    42,    43,    44,    71,    71,    18,    48,     9,    75,
       6,     8,    25,    26,    76,    77,    78,    46,    53,    49,
      51,    51,     5,     6,     8,     9,    49,    53,    51,    55,
      53,    47,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    12,    13,    12,    69,
       9,    85,    52,    49,    49,    57,    47,    12,    76,    69,
      84,    39,    39,    51,    51,    51,    51,    87,    89,    69,
      71,    49,    53,    69,    47,    71,    47,    69,    69,    39,
      39,    12,    71,     9,    52,    71,    69,    69,    69,    12,
      75,    49,    71,    12
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    57,    57,    57,    58,    58,    58,    58,
      59,    59,    60,    60,    60,    61,    61,    62,    62,    62,
      62,    63,    63,    64,    65,    66,    67,    68,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    70,    70,    71,    71,    71,    72,
      72,    72,    72,    72,    72,    72,    73,    73,    74,    74,
      75,    75,    75,    75,    75,    75,    75,    76,    76,    76,
      77,    78,    79,    79,    79,    80,    80,    80,    81,    82,
      83,    84,    84,    84,    85,    85,    85,    86,    87,    87,
      87,    88,    89,    89,    90,    90,    91,    91,    92,    92,
      92,    92,    92,    92
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     3,     5,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     1,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     4,     4,
       3,     3,     3,     6,     6,     3,     1,     2,     1,     1,
       4,     3,     4,     6,     4,     4,     4,    10,     2,     7,
       4,     0,     3,     1,     0,     1,     3,     3,     0,     3,
       1,     3,     3,     1,     0,     3,     1,     1,     4,     4,
       4,     6,     6,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (&yylloc, root, scanner, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, root, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, ast **root, void *scanner)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (root);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, ast **root, void *scanner)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, root, scanner);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, ast **root, void *scanner)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , root, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, root, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, ast **root, void *scanner)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (root);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (ast **root, void *scanner)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 10:
#line 118 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_MENOS_UNARIO, (yyvsp[0].node), NULL); }
#line 1597 "parse.c" /* yacc.c:1646  */
    break;

  case 11:
#line 119 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_MAS_UNARIO, (yyvsp[0].node), NULL); }
#line 1603 "parse.c" /* yacc.c:1646  */
    break;

  case 12:
#line 123 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_MULTIPLICACION, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1609 "parse.c" /* yacc.c:1646  */
    break;

  case 13:
#line 124 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_DIVISION, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1615 "parse.c" /* yacc.c:1646  */
    break;

  case 14:
#line 125 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_MODULO, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1621 "parse.c" /* yacc.c:1646  */
    break;

  case 15:
#line 129 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_RESTA, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1627 "parse.c" /* yacc.c:1646  */
    break;

  case 16:
#line 130 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_SUMA, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1633 "parse.c" /* yacc.c:1646  */
    break;

  case 17:
#line 134 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_MAYOR_QUE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1639 "parse.c" /* yacc.c:1646  */
    break;

  case 18:
#line 135 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_MENOR_QUE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1645 "parse.c" /* yacc.c:1646  */
    break;

  case 19:
#line 136 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_MAYOR_IGUAL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1651 "parse.c" /* yacc.c:1646  */
    break;

  case 20:
#line 137 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_MENOR_IGUAL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1657 "parse.c" /* yacc.c:1646  */
    break;

  case 21:
#line 141 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_DESIGUALDAD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1663 "parse.c" /* yacc.c:1646  */
    break;

  case 22:
#line 142 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_IGUALDAD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1669 "parse.c" /* yacc.c:1646  */
    break;

  case 23:
#line 146 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_NEGACION, (yyvsp[0].node), NULL); }
#line 1675 "parse.c" /* yacc.c:1646  */
    break;

  case 24:
#line 150 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_Y, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1681 "parse.c" /* yacc.c:1646  */
    break;

  case 25:
#line 154 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_O, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1687 "parse.c" /* yacc.c:1646  */
    break;

  case 26:
#line 158 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo_si((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1693 "parse.c" /* yacc.c:1646  */
    break;

  case 27:
#line 162 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_CONCATENAR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1699 "parse.c" /* yacc.c:1646  */
    break;

  case 28:
#line 166 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1705 "parse.c" /* yacc.c:1646  */
    break;

  case 44:
#line 185 "parse.y" /* yacc.c:1646  */
    { /* empty */
        *root = NULL;
    }
#line 1713 "parse.c" /* yacc.c:1646  */
    break;

  case 45:
#line 188 "parse.y" /* yacc.c:1646  */
    { *root = (yyvsp[0].node); }
#line 1719 "parse.c" /* yacc.c:1646  */
    break;

  case 46:
#line 192 "parse.y" /* yacc.c:1646  */
    {
        if((yyvsp[0].node)){
            (yyval.node) = nodo_nuevo(NODO_BLOQUE, (yyvsp[-1].node), (yyvsp[0].node));
        }
    }
#line 1729 "parse.c" /* yacc.c:1646  */
    break;

  case 47:
#line 197 "parse.y" /* yacc.c:1646  */
    {
        if((yyvsp[0].node)){
          (yyval.node) = nodo_nuevo(NODO_BLOQUE, (yyvsp[0].node), NULL);
        }
    }
#line 1739 "parse.c" /* yacc.c:1646  */
    break;

  case 48:
#line 202 "parse.y" /* yacc.c:1646  */
    { yyerrok; yyclearin; }
#line 1745 "parse.c" /* yacc.c:1646  */
    break;

  case 56:
#line 216 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo_asignacion(nodo_nuevo(NODO_INCREMENTO, (yyvsp[-1].node), NULL), (yyvsp[-1].node)); }
#line 1751 "parse.c" /* yacc.c:1646  */
    break;

  case 57:
#line 217 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo_asignacion(nodo_nuevo(NODO_DECREMENTO, (yyvsp[-1].node), NULL), (yyvsp[-1].node)); }
#line 1757 "parse.c" /* yacc.c:1646  */
    break;

  case 58:
#line 220 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo_incluir((yyvsp[-1].node)); }
#line 1763 "parse.c" /* yacc.c:1646  */
    break;

  case 59:
#line 221 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo_incluir((yyvsp[-1].node)); }
#line 1769 "parse.c" /* yacc.c:1646  */
    break;

  case 60:
#line 225 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo_asignacion((yyvsp[0].node), (yyvsp[-2].node)); }
#line 1775 "parse.c" /* yacc.c:1646  */
    break;

  case 61:
#line 226 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo_asignacion((yyvsp[0].node), (yyvsp[-2].node)); }
#line 1781 "parse.c" /* yacc.c:1646  */
    break;

  case 62:
#line 227 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo_asignacion((yyvsp[0].node), (yyvsp[-2].node)); }
#line 1787 "parse.c" /* yacc.c:1646  */
    break;

  case 63:
#line 228 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo_asignacion_lista_elem((yyvsp[0].node), (yyvsp[-5].node), (yyvsp[-3].node)); }
#line 1793 "parse.c" /* yacc.c:1646  */
    break;

  case 64:
#line 229 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo_asignacion_lista_elem((yyvsp[0].node), (yyvsp[-5].node), (yyvsp[-3].node)); }
#line 1799 "parse.c" /* yacc.c:1646  */
    break;

  case 65:
#line 230 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo_asignacion((nodo_nuevo(NODO_CONCATENAR, (yyvsp[-2].node), (yyvsp[0].node))), (yyvsp[-2].node)); }
#line 1805 "parse.c" /* yacc.c:1646  */
    break;

  case 67:
#line 235 "parse.y" /* yacc.c:1646  */
    {
        (yyval.node) = nodo_nuevo(NODO_CASOS, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1813 "parse.c" /* yacc.c:1646  */
    break;

  case 68:
#line 238 "parse.y" /* yacc.c:1646  */
    {
        (yyval.node) = nodo_nuevo(NODO_CASOS, (yyvsp[0].node), NULL);
    }
#line 1821 "parse.c" /* yacc.c:1646  */
    break;

  case 69:
#line 241 "parse.y" /* yacc.c:1646  */
    {
        (yyval.node) = nodo_nuevo(NODO_CASOS, (yyvsp[0].node), NULL);
    }
#line 1829 "parse.c" /* yacc.c:1646  */
    break;

  case 70:
#line 248 "parse.y" /* yacc.c:1646  */
    {
        (yyval.node) = nodo_nuevo(NODO_CASO, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1837 "parse.c" /* yacc.c:1646  */
    break;

  case 71:
#line 255 "parse.y" /* yacc.c:1646  */
    {
        (yyval.node) = nodo_nuevo(NODO_DEFECTO, NULL, (yyvsp[0].node));
    }
#line 1845 "parse.c" /* yacc.c:1646  */
    break;

  case 72:
#line 261 "parse.y" /* yacc.c:1646  */
    {
        (yyval.node) = nodo_nuevo_si((yyvsp[-2].node), (yyvsp[-1].node), NULL); }
#line 1852 "parse.c" /* yacc.c:1646  */
    break;

  case 73:
#line 263 "parse.y" /* yacc.c:1646  */
    {
        (yyval.node) = nodo_nuevo_si((yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 1859 "parse.c" /* yacc.c:1646  */
    break;

  case 74:
#line 265 "parse.y" /* yacc.c:1646  */
    {
        (yyval.node) = nodo_nuevo(NODO_ELEGIR, (yyvsp[-2].node), (yyvsp[-1].node));
    }
#line 1867 "parse.c" /* yacc.c:1646  */
    break;

  case 75:
#line 271 "parse.y" /* yacc.c:1646  */
    {
        (yyval.node) = nodo_nuevo_mientras((yyvsp[-2].node), (yyvsp[-1].node)); }
#line 1874 "parse.c" /* yacc.c:1646  */
    break;

  case 76:
#line 273 "parse.y" /* yacc.c:1646  */
    {
        (yyval.node) = nodo_nuevo_hacer((yyvsp[0].node), (yyvsp[-2].node)); }
#line 1881 "parse.c" /* yacc.c:1646  */
    break;

  case 77:
#line 276 "parse.y" /* yacc.c:1646  */
    {
        (yyval.node) = nodo_nuevo_desde((yyvsp[-7].node), (yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 1888 "parse.c" /* yacc.c:1646  */
    break;

  case 78:
#line 281 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_RETORNO, (yyvsp[0].node), NULL); }
#line 1894 "parse.c" /* yacc.c:1646  */
    break;

  case 79:
#line 285 "parse.y" /* yacc.c:1646  */
    {
        (yyval.node) = nodo_nuevo_funcion((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 1902 "parse.c" /* yacc.c:1646  */
    break;

  case 80:
#line 291 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_FUNCION_LLAMADA, (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 1908 "parse.c" /* yacc.c:1646  */
    break;

  case 81:
#line 294 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = NULL; }
#line 1914 "parse.c" /* yacc.c:1646  */
    break;

  case 82:
#line 295 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_FUNCION_ARGUMENTOS, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1920 "parse.c" /* yacc.c:1646  */
    break;

  case 83:
#line 296 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_FUNCION_ARGUMENTOS, (yyvsp[0].node), NULL); }
#line 1926 "parse.c" /* yacc.c:1646  */
    break;

  case 84:
#line 300 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = NULL; }
#line 1932 "parse.c" /* yacc.c:1646  */
    break;

  case 85:
#line 301 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_LISTA_PARAMETROS, (yyvsp[0].node), NULL); }
#line 1938 "parse.c" /* yacc.c:1646  */
    break;

  case 86:
#line 302 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_LISTA_PARAMETROS, (yyvsp[0].node), (yyvsp[-2].node)); }
#line 1944 "parse.c" /* yacc.c:1646  */
    break;

  case 87:
#line 306 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_LISTA, (yyvsp[-1].node), NULL); }
#line 1950 "parse.c" /* yacc.c:1646  */
    break;

  case 88:
#line 310 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = NULL; }
#line 1956 "parse.c" /* yacc.c:1646  */
    break;

  case 89:
#line 311 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_LISTA_AGREGAR_ELEMENTO, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1962 "parse.c" /* yacc.c:1646  */
    break;

  case 90:
#line 312 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_LISTA_AGREGAR_ELEMENTO, (yyvsp[0].node), NULL); }
#line 1968 "parse.c" /* yacc.c:1646  */
    break;

  case 91:
#line 316 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_DICCIONARIO, (yyvsp[-1].node), NULL); }
#line 1974 "parse.c" /* yacc.c:1646  */
    break;

  case 92:
#line 320 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_DICC_AGREGAR_ELEMENTO, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1980 "parse.c" /* yacc.c:1646  */
    break;

  case 93:
#line 321 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_DICC_AGREGAR_ELEMENTO, (yyvsp[0].node), NULL); }
#line 1986 "parse.c" /* yacc.c:1646  */
    break;

  case 94:
#line 325 "parse.y" /* yacc.c:1646  */
    { /* empty */
        (yyval.node) = NULL;
    }
#line 1994 "parse.c" /* yacc.c:1646  */
    break;

  case 95:
#line 328 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_DICC_ELEMENTO, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2000 "parse.c" /* yacc.c:1646  */
    break;

  case 98:
#line 338 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_DICC_OBTENER_ELEMENTO, (yyvsp[-1].node), (yyvsp[-3].node)); }
#line 2006 "parse.c" /* yacc.c:1646  */
    break;

  case 99:
#line 339 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_DICC_OBTENER_ELEMENTO, (yyvsp[-1].node), (yyvsp[-3].node)); }
#line 2012 "parse.c" /* yacc.c:1646  */
    break;

  case 100:
#line 340 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_LISTA_OBTENER_ELEMENTO, (yyvsp[-1].node), (yyvsp[-3].node)); }
#line 2018 "parse.c" /* yacc.c:1646  */
    break;

  case 101:
#line 341 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo_asignacion_dicc_elem((yyvsp[0].node), (yyvsp[-5].node), (yyvsp[-3].node)); }
#line 2024 "parse.c" /* yacc.c:1646  */
    break;

  case 102:
#line 342 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo_asignacion_dicc_elem((yyvsp[0].node), (yyvsp[-5].node), (yyvsp[-3].node)); }
#line 2030 "parse.c" /* yacc.c:1646  */
    break;

  case 103:
#line 343 "parse.y" /* yacc.c:1646  */
    { (yyval.node) = nodo_nuevo(NODO_LISTA_OBTENER_ELEMENTO, (yyvsp[-1].node), (yyvsp[-3].node)); }
#line 2036 "parse.c" /* yacc.c:1646  */
    break;


#line 2040 "parse.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, root, scanner, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, root, scanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, root, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, root, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, root, scanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, root, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, root, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 346 "parse.y" /* yacc.c:1906  */


//se define para analisis sintactico (bison)
int yyerror(struct YYLTYPE *yylloc_param, void *scanner, struct ast **root,
            const char *s) {
  if(!parse_silent){
      lat_error("Linea %d, %d: %s", yylloc_param->first_line, yylloc_param->first_column,  s);
  }
  return 0;
}
