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
    NUMERICO = 262,
    CADENA = 263,
    IDENTIFICADOR = 264,
    CONSTANTE = 265,
    SI = 266,
    FIN = 267,
    SINO = 268,
    MIENTRAS = 269,
    ROMPER = 270,
    CONTINUAR = 271,
    DESDE = 272,
    REPETIR = 273,
    HASTA = 274,
    POR = 275,
    EN = 276,
    FUNCION = 277,
    RETORNO = 278,
    INCLUIR = 279,
    ELEGIR = 280,
    CASO = 281,
    DEFECTO = 282,
    CLASE = 283,
    MAYOR_QUE = 284,
    MENOR_QUE = 285,
    MAYOR_IGUAL = 286,
    MENOR_IGUAL = 287,
    IGUAL_LOGICO = 288,
    DIFERENTE = 289,
    Y_LOGICO = 290,
    O_LOGICO = 291
  };
#endif
/* Tokens.  */
#define VERDADERO 258
#define FALSO 259
#define ENTERO 260
#define LITERAL 261
#define NUMERICO 262
#define CADENA 263
#define IDENTIFICADOR 264
#define CONSTANTE 265
#define SI 266
#define FIN 267
#define SINO 268
#define MIENTRAS 269
#define ROMPER 270
#define CONTINUAR 271
#define DESDE 272
#define REPETIR 273
#define HASTA 274
#define POR 275
#define EN 276
#define FUNCION 277
#define RETORNO 278
#define INCLUIR 279
#define ELEGIR 280
#define CASO 281
#define DEFECTO 282
#define CLASE 283
#define MAYOR_QUE 284
#define MENOR_QUE 285
#define MAYOR_IGUAL 286
#define MENOR_IGUAL 287
#define IGUAL_LOGICO 288
#define DIFERENTE 289
#define Y_LOGICO 290
#define O_LOGICO 291

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

#line 220 "parse.c" /* yacc.c:358  */

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
#define YYFINAL  66
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   421

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  106
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  196

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   291

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    43,     2,     2,     2,    42,     2,     2,
      46,    47,    40,    38,    51,    39,    48,    41,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    45,     2,
       2,    37,     2,    44,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    49,     2,    50,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    52,     2,    53,     2,     2,     2,     2,
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
      35,    36
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   105,   105,   106,   107,   108,   113,   114,   115,   116,
     120,   122,   127,   128,   129,   134,   135,   140,   141,   142,
     143,   148,   149,   153,   159,   164,   169,   174,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   193,   196,   201,   206,   211,   216,   217,   218,
     219,   220,   221,   222,   223,   227,   228,   232,   233,   237,
     241,   249,   253,   254,   258,   262,   263,   265,   266,   271,
     274,   277,   284,   291,   298,   301,   304,   311,   314,   317,
     320,   327,   328,   329,   334,   341,   345,   348,   349,   353,
     356,   357,   361,   366,   371,   374,   375,   380,   381,   385,
     388,   393,   394,   399,   400,   401,   402
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VERDADERO", "FALSO", "ENTERO",
  "LITERAL", "NUMERICO", "CADENA", "IDENTIFICADOR", "CONSTANTE", "SI",
  "FIN", "SINO", "MIENTRAS", "ROMPER", "CONTINUAR", "DESDE", "REPETIR",
  "HASTA", "POR", "EN", "FUNCION", "RETORNO", "INCLUIR", "ELEGIR", "CASO",
  "DEFECTO", "CLASE", "MAYOR_QUE", "MENOR_QUE", "MAYOR_IGUAL",
  "MENOR_IGUAL", "IGUAL_LOGICO", "DIFERENTE", "Y_LOGICO", "O_LOGICO",
  "'='", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "'?'", "':'", "'('",
  "')'", "'.'", "'['", "']'", "','", "'{'", "'}'", "$accept",
  "constant_expression", "primary_expression", "unary_expression",
  "multiplicative_expression", "additive_expression",
  "relational_expression", "equality_expression", "logical_not_expression",
  "logical_and_expression", "logical_or_expression", "ternary_expression",
  "expression", "program", "statement_list", "statement",
  "class_statements", "class_statement", "class_declaration",
  "include_declaration", "variable_access", "field_designator",
  "declaration", "labeled_statements", "labeled_statement_case",
  "labeled_statement_default", "selection_statement",
  "iteration_statement", "jump_statement", "function_definition",
  "function_call", "argument_expression_list", "identifier_list",
  "list_new", "dict_new", "list_items", "dict_items", "dict_item", "key",
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
     285,   286,   287,   288,   289,   290,   291,    61,    43,    45,
      42,    47,    37,    33,    63,    58,    40,    41,    46,    91,
      93,    44,   123,   125
};
# endif

#define YYPACT_NINF -107

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-107)))

#define YYTABLE_NINF -63

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     258,   276,  -107,    94,    94,  -107,  -107,   276,    28,    45,
      94,    16,    94,    55,    68,  -107,   229,  -107,  -107,   -29,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,  -107,  -107,  -107,    23,  -107,    94,    94,    94,    94,
      94,    19,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,  -107,   186,   -16,  -107,  -107,  -107,  -107,   186,    60,
      84,    75,   357,    98,   310,     4,  -107,  -107,    94,    94,
     113,     9,    47,   385,   385,   385,   291,    78,    73,  -107,
    -107,    71,    74,    81,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    63,   116,    94,
       1,   121,    87,    53,    86,   123,    51,  -107,   127,   126,
       2,    -9,  -107,  -107,  -107,   341,   277,    92,  -107,    91,
      95,    97,    99,   101,   102,  -107,    94,  -107,  -107,    19,
      94,  -107,  -107,  -107,  -107,  -107,  -107,    12,    12,   371,
     371,   385,   385,   385,  -107,   276,  -107,   357,   276,   276,
      93,   108,  -107,   103,   276,  -107,  -107,     2,  -107,  -107,
      94,    94,  -107,   105,   119,  -107,  -107,  -107,  -107,  -107,
    -107,   357,   149,   153,   154,   121,   276,   276,  -107,   156,
     324,  -107,    94,    94,  -107,  -107,  -107,  -107,   160,  -107,
    -107,    94,   357,   357,  -107,   357
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    62,     0,     0,    82,    83,     0,     0,     0,
       0,     0,     0,     0,     0,    43,     0,    54,    47,     0,
      63,    48,    49,    50,    51,    52,    53,    46,     8,     9,
       2,     4,     3,     5,     6,     7,     0,     0,     0,     0,
      94,    99,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,     0,     0,    38,    39,    41,    40,     0,     0,
       0,     0,    81,     0,     0,     0,     1,    44,     0,    86,
       0,     0,     0,    11,    10,    23,     0,    96,     0,   101,
     102,     0,    98,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    89,     0,     0,     0,     0,    69,    71,     0,     0,
      56,     0,    57,    58,    66,    65,    88,     0,    64,     0,
       0,     0,     0,     0,     0,    27,    94,    92,    93,    99,
       0,    17,    18,    19,    20,    22,    21,    24,    25,    16,
      15,    12,    13,    14,    74,     0,    77,    78,     0,     0,
      91,     0,    61,     0,     0,    76,    70,     0,    59,    55,
       0,    86,    85,     0,     0,   105,   104,   103,   106,    95,
      97,   100,     0,     0,     0,    89,     0,     0,    73,     0,
       0,    87,     0,     0,    75,    80,    79,    90,     0,    72,
      60,     0,    67,    68,    84,    26
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -107,    70,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,  -107,    -3,  -107,    22,  -107,  -106,  -107,  -107,  -107,
       5,  -107,   -63,    69,  -107,  -107,  -107,  -107,  -107,   -62,
      15,    13,     3,    77,  -107,    57,    56,  -107,  -107,  -107
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,   114,    77,    14,    15,    16,   109,   110,    17,    18,
      53,    20,    21,   105,   106,   107,    22,    23,    24,    25,
      54,   117,   151,    55,    56,    78,    81,    82,    83,    57
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      52,    58,   112,   113,   159,    19,    19,    62,    68,    64,
     148,     2,    19,     2,   119,    26,    26,    69,   120,    70,
      71,    19,    26,    27,     9,    79,     9,    80,    68,    59,
      69,    26,    70,    73,    74,    75,    76,    60,    67,    70,
      71,    84,    85,    86,    87,    88,    89,   112,   113,   108,
      40,   179,   121,   122,    61,   123,   124,    19,    30,    31,
      32,    33,    63,    19,    65,   115,   116,    26,    66,   -62,
     111,   -62,    72,    26,    97,   144,   145,   103,   104,    99,
      98,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   112,   113,   147,    28,    29,    30,
      31,    32,    33,    34,    35,   100,   102,    84,    85,    86,
      87,    88,    89,    90,    91,   111,    92,    93,    94,    95,
      96,   101,   118,   127,   128,   129,   130,   171,   146,   126,
     150,   154,    36,    37,   152,   155,   157,    38,   158,   162,
      39,   163,   182,    40,   175,   164,    41,   165,   177,   166,
      19,   167,   168,    19,    19,   176,   183,   180,   116,    19,
      26,   184,   111,    26,    26,   185,   186,   172,   190,    26,
     173,   174,   194,   153,   181,   156,   178,   149,   187,   192,
     193,    19,    19,   169,     0,   170,     0,     1,   195,     0,
       0,    26,    26,     0,     0,     2,     0,     3,   188,   189,
       4,     5,     6,     0,     7,     0,     8,     0,     9,    10,
      11,    12,     0,     0,    13,    84,    85,    86,    87,    88,
      89,    90,    91,     0,    92,    93,    94,    95,    96,   -45,
       1,     0,     0,     0,     0,     0,     0,     0,     2,     0,
       3,   -45,   -45,     4,     5,     6,     0,     7,   -45,     8,
       0,     9,    10,    11,    12,   -45,   -45,    13,   -42,     1,
       0,     0,     0,     0,     0,     0,     0,     2,     0,     3,
       0,     0,     4,     5,     6,     0,     7,     1,     8,     0,
       9,    10,    11,    12,     0,     2,    13,     3,     0,     0,
       4,     5,     6,     0,     7,     0,     8,     0,     9,    10,
      11,    12,     0,     0,    13,     0,    84,    85,    86,    87,
      88,    89,    90,    91,     0,    92,    93,    94,    95,    96,
      84,    85,    86,    87,    88,    89,    90,    91,   161,    92,
      93,    94,    95,    96,     0,     0,   103,   104,   125,    84,
      85,    86,    87,    88,    89,    90,    91,     0,    92,    93,
      94,    95,    96,    84,    85,    86,    87,    88,    89,    90,
      91,     0,    92,    93,    94,    95,    96,     0,     0,   191,
      84,    85,    86,    87,    88,    89,    90,    91,     0,    92,
      93,    94,    95,    96,     0,   160,    84,    85,    86,    87,
      88,    89,    90,    91,     0,    92,    93,    94,    95,    96,
      84,    85,    86,    87,    88,    89,    90,    91,     0,     0,
       0,    94,    95,    96,    84,    85,    86,    87,    88,    89,
      90,    91
};

static const yytype_int16 yycheck[] =
{
       3,     4,    65,    65,   110,     0,     1,    10,    37,    12,
       9,     9,     7,     9,     5,     0,     1,    46,     9,    48,
      49,    16,     7,     1,    22,     6,    22,     8,    37,     7,
      46,    16,    48,    36,    37,    38,    39,     9,    16,    48,
      49,    29,    30,    31,    32,    33,    34,   110,   110,    45,
      49,   157,     5,     6,     9,     8,     9,    52,     5,     6,
       7,     8,    46,    58,     9,    68,    69,    52,     0,    46,
      65,    48,    49,    58,    52,    12,    13,    26,    27,    19,
      58,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,   157,   157,    99,     3,     4,     5,
       6,     7,     8,     9,    10,    21,     8,    29,    30,    31,
      32,    33,    34,    35,    36,   110,    38,    39,    40,    41,
      42,    46,     9,    50,    53,    51,    45,   130,    12,    51,
       9,    45,    38,    39,    47,    12,     9,    43,    12,    47,
      46,    50,    37,    49,    51,    50,    52,    50,    45,    50,
     145,    50,    50,   148,   149,    47,    37,   160,   161,   154,
     145,    12,   157,   148,   149,    12,    12,   145,    12,   154,
     148,   149,    12,   103,   161,   106,   154,   100,   175,   182,
     183,   176,   177,   126,    -1,   129,    -1,     1,   191,    -1,
      -1,   176,   177,    -1,    -1,     9,    -1,    11,   176,   177,
      14,    15,    16,    -1,    18,    -1,    20,    -1,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    38,    39,    40,    41,    42,     0,
       1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    -1,
      11,    12,    13,    14,    15,    16,    -1,    18,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    28,     0,     1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    -1,    11,
      -1,    -1,    14,    15,    16,    -1,    18,     1,    20,    -1,
      22,    23,    24,    25,    -1,     9,    28,    11,    -1,    -1,
      14,    15,    16,    -1,    18,    -1,    20,    -1,    22,    23,
      24,    25,    -1,    -1,    28,    -1,    29,    30,    31,    32,
      33,    34,    35,    36,    -1,    38,    39,    40,    41,    42,
      29,    30,    31,    32,    33,    34,    35,    36,    51,    38,
      39,    40,    41,    42,    -1,    -1,    26,    27,    47,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    38,    39,
      40,    41,    42,    29,    30,    31,    32,    33,    34,    35,
      36,    -1,    38,    39,    40,    41,    42,    -1,    -1,    45,
      29,    30,    31,    32,    33,    34,    35,    36,    -1,    38,
      39,    40,    41,    42,    -1,    44,    29,    30,    31,    32,
      33,    34,    35,    36,    -1,    38,    39,    40,    41,    42,
      29,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      -1,    40,    41,    42,    29,    30,    31,    32,    33,    34,
      35,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     9,    11,    14,    15,    16,    18,    20,    22,
      23,    24,    25,    28,    67,    68,    69,    72,    73,    74,
      75,    76,    80,    81,    82,    83,    84,    68,     3,     4,
       5,     6,     7,     8,     9,    10,    38,    39,    43,    46,
      49,    52,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    66,    74,    84,    87,    88,    93,    66,    68,
       9,     9,    66,    46,    66,     9,     0,    68,    37,    46,
      48,    49,    49,    66,    66,    66,    66,    66,    89,     6,
       8,    90,    91,    92,    29,    30,    31,    32,    33,    34,
      35,    36,    38,    39,    40,    41,    42,    68,    68,    19,
      21,    46,     8,    26,    27,    77,    78,    79,    45,    70,
      71,    74,    76,    83,    65,    66,    66,    85,     9,     5,
       9,     5,     6,     8,     9,    47,    51,    50,    53,    51,
      45,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    12,    13,    12,    66,     9,    87,
       9,    86,    47,    55,    45,    12,    77,     9,    12,    70,
      44,    51,    47,    50,    50,    50,    50,    50,    50,    89,
      90,    66,    68,    68,    68,    51,    47,    45,    68,    70,
      66,    85,    37,    37,    12,    12,    12,    86,    68,    68,
      12,    45,    66,    66,    12,    66
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    55,    55,    55,    56,    56,    56,    56,
      57,    57,    58,    58,    58,    59,    59,    60,    60,    60,
      60,    61,    61,    62,    63,    64,    65,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    67,    67,    68,    68,    68,    69,    69,    69,
      69,    69,    69,    69,    69,    70,    70,    71,    71,    72,
      72,    73,    74,    74,    75,    76,    76,    76,    76,    77,
      77,    77,    78,    79,    80,    80,    80,    81,    81,    81,
      81,    82,    82,    82,    83,    84,    85,    85,    85,    86,
      86,    86,    87,    88,    89,    89,    89,    90,    90,    91,
      91,    92,    92,    93,    93,    93,    93
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     3,     5,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     2,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     4,
       6,     4,     1,     1,     3,     3,     3,     6,     6,     1,
       2,     1,     4,     3,     4,     6,     4,     4,     4,     6,
       6,     2,     1,     1,     7,     4,     0,     3,     1,     0,
       3,     1,     3,     3,     0,     3,     1,     3,     1,     0,
       3,     1,     1,     4,     4,     4,     4
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
#line 121 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo_op("-", (yyvsp[0].nodo), NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1595 "parse.c" /* yacc.c:1646  */
    break;

  case 11:
#line 122 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo_op("+", (yyvsp[0].nodo), NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1601 "parse.c" /* yacc.c:1646  */
    break;

  case 12:
#line 127 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo_op("*", (yyvsp[-2].nodo), (yyvsp[0].nodo), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1607 "parse.c" /* yacc.c:1646  */
    break;

  case 13:
#line 128 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo_op("/", (yyvsp[-2].nodo), (yyvsp[0].nodo), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1613 "parse.c" /* yacc.c:1646  */
    break;

  case 14:
#line 129 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo_op("%", (yyvsp[-2].nodo), (yyvsp[0].nodo), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1619 "parse.c" /* yacc.c:1646  */
    break;

  case 15:
#line 134 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo_op("-", (yyvsp[-2].nodo), (yyvsp[0].nodo), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1625 "parse.c" /* yacc.c:1646  */
    break;

  case 16:
#line 135 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo_op("+", (yyvsp[-2].nodo), (yyvsp[0].nodo), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1631 "parse.c" /* yacc.c:1646  */
    break;

  case 17:
#line 140 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo_op(">", (yyvsp[-2].nodo), (yyvsp[0].nodo), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1637 "parse.c" /* yacc.c:1646  */
    break;

  case 18:
#line 141 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo_op("<", (yyvsp[-2].nodo), (yyvsp[0].nodo), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1643 "parse.c" /* yacc.c:1646  */
    break;

  case 19:
#line 142 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo_op(">=", (yyvsp[-2].nodo), (yyvsp[0].nodo), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1649 "parse.c" /* yacc.c:1646  */
    break;

  case 20:
#line 143 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo_op("<=", (yyvsp[-2].nodo), (yyvsp[0].nodo), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1655 "parse.c" /* yacc.c:1646  */
    break;

  case 21:
#line 148 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo_op("!=", (yyvsp[-2].nodo), (yyvsp[0].nodo), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1661 "parse.c" /* yacc.c:1646  */
    break;

  case 22:
#line 149 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo_op("==", (yyvsp[-2].nodo), (yyvsp[0].nodo), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1667 "parse.c" /* yacc.c:1646  */
    break;

  case 23:
#line 154 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo_op("!", (yyvsp[0].nodo), NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1673 "parse.c" /* yacc.c:1646  */
    break;

  case 24:
#line 159 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo_op("&&", (yyvsp[-2].nodo), (yyvsp[0].nodo), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1679 "parse.c" /* yacc.c:1646  */
    break;

  case 25:
#line 164 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo_op("||", (yyvsp[-2].nodo), (yyvsp[0].nodo), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1685 "parse.c" /* yacc.c:1646  */
    break;

  case 26:
#line 169 "parse.y" /* yacc.c:1646  */
    {
    (yyval.nodo) = nodo_nuevo_si((yyvsp[-4].nodo), (yyvsp[-2].nodo), (yyvsp[0].nodo), (yylsp[-4]).first_line, (yylsp[-4]).first_column);
}
#line 1693 "parse.c" /* yacc.c:1646  */
    break;

  case 27:
#line 175 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = (yyvsp[-1].nodo); }
#line 1699 "parse.c" /* yacc.c:1646  */
    break;

  case 42:
#line 193 "parse.y" /* yacc.c:1646  */
    { /* empty */
    *root = NULL;
}
#line 1707 "parse.c" /* yacc.c:1646  */
    break;

  case 43:
#line 196 "parse.y" /* yacc.c:1646  */
    { *root = (yyvsp[0].nodo); }
#line 1713 "parse.c" /* yacc.c:1646  */
    break;

  case 44:
#line 201 "parse.y" /* yacc.c:1646  */
    {
    if((yyvsp[0].nodo)) {
        (yyval.nodo) = nodo_nuevo(NODO_BLOQUE, (yyvsp[-1].nodo), (yyvsp[0].nodo), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
    }
}
#line 1723 "parse.c" /* yacc.c:1646  */
    break;

  case 45:
#line 206 "parse.y" /* yacc.c:1646  */
    {
    if((yyvsp[0].nodo)) {
        (yyval.nodo) = nodo_nuevo(NODO_BLOQUE, (yyvsp[0].nodo), NULL, (yylsp[0]).first_line, (yylsp[0]).first_column);
    }
}
#line 1733 "parse.c" /* yacc.c:1646  */
    break;

  case 46:
#line 211 "parse.y" /* yacc.c:1646  */
    { yyerrok; yyclearin; }
#line 1739 "parse.c" /* yacc.c:1646  */
    break;

  case 59:
#line 237 "parse.y" /* yacc.c:1646  */
    {
    (yyval.nodo) = NULL;
    printf("creando clase...\n");
}
#line 1748 "parse.c" /* yacc.c:1646  */
    break;

  case 60:
#line 241 "parse.y" /* yacc.c:1646  */
    {
    (yyval.nodo) = NULL;
    printf("creando clase hija...\n");
}
#line 1757 "parse.c" /* yacc.c:1646  */
    break;

  case 61:
#line 249 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo_incluir((yyvsp[-1].nodo), (yylsp[-3]).first_line, (yylsp[-3]).first_column); }
#line 1763 "parse.c" /* yacc.c:1646  */
    break;

  case 64:
#line 258 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = NULL; }
#line 1769 "parse.c" /* yacc.c:1646  */
    break;

  case 65:
#line 262 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo_asignacion((yyvsp[-2].nodo), (yyvsp[0].nodo), (yylsp[-2]).first_line, (yylsp[-2]).first_column); }
#line 1775 "parse.c" /* yacc.c:1646  */
    break;

  case 66:
#line 263 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo_asignacion((yyvsp[-2].nodo), (yyvsp[0].nodo), (yylsp[-2]).first_line, (yylsp[-2]).first_column); }
#line 1781 "parse.c" /* yacc.c:1646  */
    break;

  case 67:
#line 265 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo_asignacion_lista_elem((yyvsp[-5].nodo), (yyvsp[-3].nodo), (yyvsp[0].nodo), (yylsp[-5]).first_line, (yylsp[-5]).first_column); }
#line 1787 "parse.c" /* yacc.c:1646  */
    break;

  case 68:
#line 266 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo_asignacion_lista_elem((yyvsp[-5].nodo), (yyvsp[-3].nodo), (yyvsp[0].nodo), (yylsp[-5]).first_line, (yylsp[-5]).first_column); }
#line 1793 "parse.c" /* yacc.c:1646  */
    break;

  case 69:
#line 271 "parse.y" /* yacc.c:1646  */
    {
    (yyval.nodo) = nodo_nuevo(NODO_CASOS, (yyvsp[0].nodo), NULL, (yylsp[0]).first_line, (yylsp[0]).first_column);
}
#line 1801 "parse.c" /* yacc.c:1646  */
    break;

  case 70:
#line 274 "parse.y" /* yacc.c:1646  */
    {
    (yyval.nodo) = nodo_nuevo(NODO_CASOS, (yyvsp[-1].nodo), (yyvsp[0].nodo), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
}
#line 1809 "parse.c" /* yacc.c:1646  */
    break;

  case 71:
#line 277 "parse.y" /* yacc.c:1646  */
    {
    (yyval.nodo) = nodo_nuevo(NODO_CASOS, (yyvsp[0].nodo), NULL, (yylsp[0]).first_line, (yylsp[0]).first_column);
}
#line 1817 "parse.c" /* yacc.c:1646  */
    break;

  case 72:
#line 284 "parse.y" /* yacc.c:1646  */
    {
    (yyval.nodo) = nodo_nuevo(NODO_CASO, (yyvsp[-2].nodo), (yyvsp[0].nodo), (yylsp[-3]).first_line, (yylsp[-3]).first_column);
}
#line 1825 "parse.c" /* yacc.c:1646  */
    break;

  case 73:
#line 291 "parse.y" /* yacc.c:1646  */
    {
    (yyval.nodo) = nodo_nuevo(NODO_DEFECTO, NULL, (yyvsp[0].nodo), (yylsp[-2]).first_line, (yylsp[-2]).first_column);
}
#line 1833 "parse.c" /* yacc.c:1646  */
    break;

  case 74:
#line 298 "parse.y" /* yacc.c:1646  */
    {
    (yyval.nodo) = nodo_nuevo_si((yyvsp[-2].nodo), (yyvsp[-1].nodo), NULL, (yylsp[-3]).first_line, (yylsp[-3]).first_column);
}
#line 1841 "parse.c" /* yacc.c:1646  */
    break;

  case 75:
#line 301 "parse.y" /* yacc.c:1646  */
    {
    (yyval.nodo) = nodo_nuevo_si((yyvsp[-4].nodo), (yyvsp[-3].nodo), (yyvsp[-1].nodo), (yylsp[-5]).first_line, (yylsp[-5]).first_column);
}
#line 1849 "parse.c" /* yacc.c:1646  */
    break;

  case 76:
#line 304 "parse.y" /* yacc.c:1646  */
    {
    (yyval.nodo) = nodo_nuevo(NODO_ELEGIR, (yyvsp[-2].nodo), (yyvsp[-1].nodo), (yylsp[-3]).first_line, (yylsp[-3]).first_column);
}
#line 1857 "parse.c" /* yacc.c:1646  */
    break;

  case 77:
#line 311 "parse.y" /* yacc.c:1646  */
    {
    (yyval.nodo) = nodo_nuevo_mientras((yyvsp[-2].nodo), (yyvsp[-1].nodo), (yylsp[-3]).first_line, (yylsp[-3]).first_column);
}
#line 1865 "parse.c" /* yacc.c:1646  */
    break;

  case 78:
#line 314 "parse.y" /* yacc.c:1646  */
    {
    (yyval.nodo) = nodo_nuevo_repetir((yyvsp[-2].nodo), (yyvsp[0].nodo), (yylsp[-3]).first_line, (yylsp[-3]).first_column);
}
#line 1873 "parse.c" /* yacc.c:1646  */
    break;

  case 79:
#line 317 "parse.y" /* yacc.c:1646  */
    {
    (yyval.nodo) = nodo_nuevo_por((yyvsp[-4].nodo), (yyvsp[-2].nodo), (yyvsp[-1].nodo), (yylsp[-5]).first_line, (yylsp[-5]).first_column);
}
#line 1881 "parse.c" /* yacc.c:1646  */
    break;

  case 80:
#line 320 "parse.y" /* yacc.c:1646  */
    {
    (yyval.nodo) = nodo_nuevo_por((yyvsp[-4].nodo), (yyvsp[-2].nodo), (yyvsp[-1].nodo), (yylsp[-5]).first_line, (yylsp[-5]).first_column);
}
#line 1889 "parse.c" /* yacc.c:1646  */
    break;

  case 81:
#line 327 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo(NODO_RETORNO, (yyvsp[0].nodo), NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1895 "parse.c" /* yacc.c:1646  */
    break;

  case 82:
#line 328 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo(NODO_ROMPER, NULL, NULL, (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 1901 "parse.c" /* yacc.c:1646  */
    break;

  case 83:
#line 329 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo(NODO_CONTINUAR, NULL, NULL, (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 1907 "parse.c" /* yacc.c:1646  */
    break;

  case 84:
#line 334 "parse.y" /* yacc.c:1646  */
    {
    (yyval.nodo) = nodo_nuevo_funcion((yyvsp[-5].nodo), (yyvsp[-3].nodo), (yyvsp[-1].nodo), (yylsp[-6]).first_line, (yylsp[-6]).first_column);
}
#line 1915 "parse.c" /* yacc.c:1646  */
    break;

  case 85:
#line 341 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo(NODO_FUNCION_LLAMADA, (yyvsp[-3].nodo), (yyvsp[-1].nodo), (yylsp[-3]).first_line, (yylsp[-3]).first_column); }
#line 1921 "parse.c" /* yacc.c:1646  */
    break;

  case 86:
#line 345 "parse.y" /* yacc.c:1646  */
    { /* empty */
    (yyval.nodo) = NULL;
}
#line 1929 "parse.c" /* yacc.c:1646  */
    break;

  case 87:
#line 348 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo(NODO_FUNCION_ARGUMENTOS, (yyvsp[-2].nodo), (yyvsp[0].nodo), (yylsp[-2]).first_line, (yylsp[-2]).first_column); }
#line 1935 "parse.c" /* yacc.c:1646  */
    break;

  case 88:
#line 349 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo(NODO_FUNCION_ARGUMENTOS, (yyvsp[0].nodo), NULL, (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 1941 "parse.c" /* yacc.c:1646  */
    break;

  case 89:
#line 353 "parse.y" /* yacc.c:1646  */
    { /* empty */
    (yyval.nodo) = NULL;
}
#line 1949 "parse.c" /* yacc.c:1646  */
    break;

  case 90:
#line 356 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo(NODO_FUNCION_PARAMETROS, (yyvsp[-2].nodo), (yyvsp[0].nodo), (yylsp[-2]).first_line, (yylsp[-2]).first_column); }
#line 1955 "parse.c" /* yacc.c:1646  */
    break;

  case 91:
#line 357 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo(NODO_FUNCION_PARAMETROS, (yyvsp[0].nodo), NULL, (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 1961 "parse.c" /* yacc.c:1646  */
    break;

  case 92:
#line 362 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo(NODO_LISTA, (yyvsp[-1].nodo), NULL, (yylsp[-2]).first_line, (yylsp[-2]).first_column); }
#line 1967 "parse.c" /* yacc.c:1646  */
    break;

  case 93:
#line 367 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo(NODO_DICCIONARIO, (yyvsp[-1].nodo), NULL, (yylsp[-2]).first_line, (yylsp[-2]).first_column); }
#line 1973 "parse.c" /* yacc.c:1646  */
    break;

  case 94:
#line 371 "parse.y" /* yacc.c:1646  */
    { /* empty */
    (yyval.nodo) = NULL;
}
#line 1981 "parse.c" /* yacc.c:1646  */
    break;

  case 95:
#line 374 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo(NODO_LISTA_AGREGAR_ELEMENTO, (yyvsp[-2].nodo), (yyvsp[0].nodo), (yylsp[-2]).first_line, (yylsp[-2]).first_column); }
#line 1987 "parse.c" /* yacc.c:1646  */
    break;

  case 96:
#line 375 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo(NODO_LISTA_AGREGAR_ELEMENTO, (yyvsp[0].nodo), NULL, (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 1993 "parse.c" /* yacc.c:1646  */
    break;

  case 97:
#line 380 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo(NODO_DICC_AGREGAR_ELEMENTO, (yyvsp[-2].nodo), (yyvsp[0].nodo), (yylsp[-2]).first_line, (yylsp[-2]).first_column); }
#line 1999 "parse.c" /* yacc.c:1646  */
    break;

  case 98:
#line 381 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo(NODO_DICC_AGREGAR_ELEMENTO, (yyvsp[0].nodo), NULL, (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 2005 "parse.c" /* yacc.c:1646  */
    break;

  case 99:
#line 385 "parse.y" /* yacc.c:1646  */
    { /* empty */
    (yyval.nodo) = NULL;
}
#line 2013 "parse.c" /* yacc.c:1646  */
    break;

  case 100:
#line 388 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo(NODO_DICC_ELEMENTO, (yyvsp[-2].nodo), (yyvsp[0].nodo), (yylsp[-2]).first_line, (yylsp[-2]).first_column); }
#line 2019 "parse.c" /* yacc.c:1646  */
    break;

  case 103:
#line 399 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo(NODO_DICC_OBTENER_ELEMENTO, (yyvsp[-3].nodo), (yyvsp[-1].nodo), (yylsp[-3]).first_line, (yylsp[-3]).first_column); }
#line 2025 "parse.c" /* yacc.c:1646  */
    break;

  case 104:
#line 400 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo(NODO_DICC_OBTENER_ELEMENTO, (yyvsp[-3].nodo), (yyvsp[-1].nodo), (yylsp[-3]).first_line, (yylsp[-3]).first_column); }
#line 2031 "parse.c" /* yacc.c:1646  */
    break;

  case 105:
#line 401 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo(NODO_LISTA_OBTENER_ELEMENTO, (yyvsp[-3].nodo), (yyvsp[-1].nodo), (yylsp[-3]).first_line, (yylsp[-3]).first_column); }
#line 2037 "parse.c" /* yacc.c:1646  */
    break;

  case 106:
#line 402 "parse.y" /* yacc.c:1646  */
    { (yyval.nodo) = nodo_nuevo(NODO_LISTA_OBTENER_ELEMENTO, (yyvsp[-3].nodo), (yyvsp[-1].nodo), (yylsp[-3]).first_line, (yylsp[-3]).first_column); }
#line 2043 "parse.c" /* yacc.c:1646  */
    break;


#line 2047 "parse.c" /* yacc.c:1646  */
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
#line 405 "parse.y" /* yacc.c:1906  */


//se define para analisis sintactico (bison)
int yyerror(struct YYLTYPE *yylloc_param, void *scanner, struct ast **root,
            const char *s) {
    if(!analisis_silencioso) {
        error("linea %i, %i: %s", yylloc_param->first_line, yylloc_param->first_column, s);
    }
    return 0;
}
