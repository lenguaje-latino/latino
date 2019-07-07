/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "latparse.y" /* yacc.c:339  */


/*
The MIT License (MIT)

Copyright (c) Latino - Lenguaje de Programacion

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/* bison -y -oparse.c parse.y */
#define YYERROR_VERBOSE 1
#define YYDEBUG 1
#define YYENABLE_NLS 1
#define YYLEX_PARAM &yylval, &yylloc

#include <stddef.h>

#include "latino.h"
#include "latast.h"
#include "latlex.h"

#ifndef LAT_ERROR_FMT
#define LAT_ERROR_FMT "%s:%d:%d: %s\n"
#endif

#ifdef __linux
#include <libintl.h>
#define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#endif

int yyerror(struct YYLTYPE *yylloc_param, void *scanner, struct ast **root, const char *s);
int yylex (YYSTYPE * yylval_param,YYLTYPE * yylloc_param ,yyscan_t yyscanner);


#line 114 "latparse.c" /* yacc.c:339  */

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
   by #include "latparse.h".  */
#ifndef YY_YY_LATPARSE_H_INCLUDED
# define YY_YY_LATPARSE_H_INCLUDED
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
    NUMERICO = 258,
    CADENA = 259,
    IDENTIFICADOR = 260,
    VAR_ARGS = 261,
    SI = 262,
    O_SI = 263,
    FIN = 264,
    SINO = 265,
    MIENTRAS = 266,
    REPETIR = 267,
    ROMPER = 268,
    CONTINUAR = 269,
    HASTA = 270,
    FUNCION = 271,
    DESDE = 272,
    RETORNO = 273,
    ELEGIR = 274,
    CASO = 275,
    DEFECTO = 276,
    ATRIBUTO = 277,
    VERDADERO = 278,
    FALSO = 279,
    NULO = 280,
    MAYOR_QUE = 281,
    MENOR_QUE = 282,
    MAYOR_IGUAL = 283,
    MENOR_IGUAL = 284,
    IGUAL_LOGICO = 285,
    DIFERENTE = 286,
    Y_LOGICO = 287,
    O_LOGICO = 288,
    INCREMENTO = 289,
    DECREMENTO = 290,
    CONCATENAR = 291,
    CONCATENAR_IGUAL = 292,
    MAS_IGUAL = 293,
    MENOS_IGUAL = 294,
    POR_IGUAL = 295,
    ENTRE_IGUAL = 296,
    MODULO_IGUAL = 297,
    REGEX = 298,
    GLOBAL = 299
  };
#endif
/* Tokens.  */
#define NUMERICO 258
#define CADENA 259
#define IDENTIFICADOR 260
#define VAR_ARGS 261
#define SI 262
#define O_SI 263
#define FIN 264
#define SINO 265
#define MIENTRAS 266
#define REPETIR 267
#define ROMPER 268
#define CONTINUAR 269
#define HASTA 270
#define FUNCION 271
#define DESDE 272
#define RETORNO 273
#define ELEGIR 274
#define CASO 275
#define DEFECTO 276
#define ATRIBUTO 277
#define VERDADERO 278
#define FALSO 279
#define NULO 280
#define MAYOR_QUE 281
#define MENOR_QUE 282
#define MAYOR_IGUAL 283
#define MENOR_IGUAL 284
#define IGUAL_LOGICO 285
#define DIFERENTE 286
#define Y_LOGICO 287
#define O_LOGICO 288
#define INCREMENTO 289
#define DECREMENTO 290
#define CONCATENAR 291
#define CONCATENAR_IGUAL 292
#define MAS_IGUAL 293
#define MENOS_IGUAL 294
#define POR_IGUAL 295
#define ENTRE_IGUAL 296
#define MODULO_IGUAL 297
#define REGEX 298
#define GLOBAL 299

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

#endif /* !YY_YY_LATPARSE_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 261 "latparse.c" /* yacc.c:358  */

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
#define YYFINAL  71
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   742

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  118
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  214

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   299

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,     2,     2,    50,     2,     2,
      55,    56,    48,    46,    60,    47,     2,    49,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    54,    59,
       2,    45,     2,    53,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    57,     2,    58,    52,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    61,     2,    62,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   140,   140,   141,   145,   146,   147,   148,   152,   156,
     163,   167,   171,   175,   182,   186,   193,   194,   195,   196,
     200,   201,   202,   206,   210,   214,   218,   222,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   249,   252,
     256,   261,   266,   270,   271,   272,   273,   274,   275,   276,
     277,   281,   282,   286,   287,   288,   292,   293,   297,   300,
     306,   307,   309,   311,   313,   315,   317,   319,   320,   324,
     327,   330,   337,   344,   350,   352,   354,   356,   362,   363,
     367,   370,   373,   379,   381,   383,   389,   390,   394,   400,
     406,   410,   411,   412,   422,   423,   424,   425,   431,   435,
     439,   440,   441,   451,   455,   456,   457,   461,   462
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMERICO", "CADENA", "IDENTIFICADOR",
  "VAR_ARGS", "SI", "O_SI", "FIN", "SINO", "MIENTRAS", "REPETIR", "ROMPER",
  "CONTINUAR", "HASTA", "FUNCION", "DESDE", "RETORNO", "ELEGIR", "CASO",
  "DEFECTO", "ATRIBUTO", "VERDADERO", "FALSO", "NULO", "MAYOR_QUE",
  "MENOR_QUE", "MAYOR_IGUAL", "MENOR_IGUAL", "IGUAL_LOGICO", "DIFERENTE",
  "Y_LOGICO", "O_LOGICO", "INCREMENTO", "DECREMENTO", "CONCATENAR",
  "CONCATENAR_IGUAL", "MAS_IGUAL", "MENOS_IGUAL", "POR_IGUAL",
  "ENTRE_IGUAL", "MODULO_IGUAL", "REGEX", "GLOBAL", "'='", "'+'", "'-'",
  "'*'", "'/'", "'%'", "'!'", "'^'", "'?'", "':'", "'('", "')'", "'['",
  "']'", "';'", "','", "'{'", "'}'", "$accept", "constant_expression",
  "primary_expression", "unary_expression", "multiplicative_expression",
  "additive_expression", "relational_expression", "equality_expression",
  "logical_not_expression", "logical_and_expression",
  "logical_or_expression", "ternary_expression", "concat_expression",
  "expression", "program", "statement_list", "statement",
  "incdec_statement", "variable_access", "field_designator",
  "global_declaration", "declaration", "labeled_statements",
  "labeled_statement_case", "labeled_statement_default",
  "selection_statement", "osi_statements", "osi_statement",
  "iteration_statement", "jump_statement", "function_definition",
  "function_anonymous", "function_call", "argument_expression_list",
  "parameter_list", "list_new", "list_items", "dict_new", "dict_items",
  "dict_item", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,    61,    43,    45,    42,    47,
      37,    33,    94,    63,    58,    40,    41,    91,    93,    59,
      44,   123,   125
};
# endif

#define YYPACT_NINF -166

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-166)))

#define YYTABLE_NINF -106

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     116,   140,   -48,  -166,   346,   346,   140,    13,   -21,   346,
     346,    15,    48,  -166,    94,  -166,    33,  -166,  -166,  -166,
    -166,  -166,  -166,  -166,   131,   -41,  -166,  -166,  -166,     1,
    -166,     2,  -166,  -166,  -166,   346,   346,   346,   346,   346,
     346,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,
    -166,  -166,  -166,   246,  -166,    27,  -166,    85,  -166,  -166,
     246,    62,     4,    45,   402,  -166,   472,   343,  -166,  -166,
    -166,  -166,  -166,    78,  -166,  -166,   346,   346,   346,   346,
     346,   346,   346,   346,   346,   346,    75,    81,    44,    44,
      44,   600,   437,    31,   631,   -55,  -166,   346,   346,   346,
     346,   346,   346,   346,   346,   346,   346,   346,   346,   346,
     346,   346,   346,   346,    56,   346,    84,   346,    81,    49,
     346,   121,    64,   117,   109,  -166,  -166,   689,   689,   689,
     689,   689,   689,   689,   402,    87,   534,  -166,  -166,  -166,
    -166,   -19,  -166,   346,  -166,   346,   346,  -166,   307,   307,
     307,   307,   307,   307,   274,   274,   689,   307,   -24,   -24,
      44,    44,    44,    91,   660,   346,  -166,   140,   128,  -166,
     567,  -166,   689,   -13,   346,  -166,    77,   140,  -166,  -166,
    -166,   103,   140,  -166,   689,  -166,   346,   246,   141,  -166,
    -166,  -166,   140,   500,   140,  -166,   346,   146,   689,     5,
    -166,   153,   403,  -166,   689,  -166,   140,   155,  -166,    93,
    -166,   140,   165,  -166
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    63,   106,     0,     0,     0,     0,     0,   101,
       0,   104,     0,    49,     0,    60,     0,    64,    54,    53,
      55,    56,    57,    58,    59,     0,    52,     2,     3,     4,
      47,     0,     5,     6,     7,     0,     0,     0,     0,   110,
     114,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    45,    39,     0,    46,    43,    44,    40,    41,    42,
       0,     0,     0,   104,    96,    97,     0,     0,    68,    69,
      65,     1,    50,     0,    61,    62,     0,     0,     0,     0,
       0,     0,     0,   101,     0,   101,     0,   104,     9,     8,
      23,     0,   111,     0,     0,     0,   115,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   104,     0,
     101,     0,     0,     0,    80,    81,    66,    71,    72,    73,
      74,    75,    76,    70,   102,     0,     0,    77,   107,   108,
     105,     0,    28,   110,   109,     0,   117,   113,    16,    17,
      18,    19,    21,    20,    24,    25,    27,    22,    15,    14,
      11,    12,    13,    10,     0,     0,    84,     0,     0,    88,
       0,    93,    94,     0,     0,   103,     0,     0,    87,    79,
     100,    67,     0,   112,   118,   116,     0,     0,     0,    86,
      89,    67,     0,     0,     0,    83,     0,     0,    26,    90,
      85,     0,   104,    82,    78,    99,     0,    92,    98,     0,
      91,     0,     0,    95
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -166,    43,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,
    -166,  -166,  -166,   231,  -166,    38,   -27,    32,     0,  -166,
    -166,    -9,    54,  -166,  -166,  -166,   -20,  -165,  -166,  -166,
     169,  -166,    16,   -75,   -78,  -166,    46,  -166,  -166,    35
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,   134,    12,    13,    14,    54,    55,    17,
      18,    19,   123,   124,   125,    20,   168,   169,    21,    22,
      23,    56,    57,    65,    25,    58,    93,    59,    95,    96
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      16,    16,    68,   190,    85,   146,    16,   147,   135,   141,
     137,    67,  -105,   165,    16,   206,    24,    24,    62,    86,
       2,     3,    24,   -63,   109,   110,   111,    70,   112,   113,
      24,     7,    15,    15,    63,   -63,   -63,   182,    15,    26,
     173,    86,   190,   192,    61,   175,    15,    86,    71,    73,
       2,     3,    72,    16,   119,    73,   -63,    87,   -63,   118,
      16,    74,    75,    67,   165,   166,   167,    74,    75,    24,
      76,    77,    78,    79,    80,    81,    24,   117,    82,    70,
     138,   139,    83,   126,   115,    15,   140,     3,    83,   144,
      84,   114,    15,   171,   -51,     1,   112,   113,   116,     2,
       3,     4,   -51,   -51,   -51,     5,     6,   -65,   174,   -51,
       7,     8,     9,    10,   -51,   -51,   -48,     1,   177,   -65,
     -65,     2,     3,     4,    27,    28,   178,     5,     6,   121,
     122,   194,     7,     8,     9,    10,   165,   189,    11,  -104,
     -65,     1,   -65,   180,   113,     2,     3,     4,   196,   211,
     200,     5,     6,   -65,  -104,   205,     7,     8,     9,    10,
      11,  -104,   208,   165,   176,   -65,   -65,    16,   -65,   -65,
     -65,   -65,   -65,   -65,   213,   209,  -104,    16,   179,   207,
      69,   185,    16,    24,    11,  -104,   -65,    16,   -65,   183,
       0,     0,    16,    24,    16,     0,     0,     0,    24,    15,
    -104,     0,    16,    24,     0,   188,    16,     0,    24,    15,
      24,    16,     0,     0,    15,   195,     0,     0,    24,    15,
     197,     0,    24,     0,    15,   199,    15,    24,     0,     0,
     201,     0,   203,     0,    15,    53,    60,     0,    15,     0,
      64,    66,     0,    15,   210,     0,     0,     1,     0,   212,
       0,     2,     3,     4,     0,     0,     0,     5,     6,     0,
       0,     0,     7,     8,     9,    10,    88,    89,    90,    91,
      92,    94,    97,    98,    99,   100,   101,   102,   103,   104,
       0,     0,   105,     0,     0,     0,     0,     0,     0,   106,
      11,  -104,   107,   108,   109,   110,   111,     0,   112,   113,
      97,    98,    99,   100,   101,   102,  -104,   127,   128,   129,
     130,   131,   132,   133,     0,   136,     0,   106,     0,     0,
     107,   108,   109,   110,   111,     0,   112,   113,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,     0,   170,     0,   172,    27,
      28,    29,    30,   107,   108,   109,   110,   111,     0,   112,
     113,     0,    31,     0,     0,    73,     0,     0,     0,    32,
      33,    34,     0,     0,    92,     0,   184,    94,     0,     0,
      76,    77,    78,    79,    80,    81,     0,     0,    82,     0,
       0,     0,    35,    36,     0,     0,   187,    37,    83,     0,
      84,    38,     0,    39,     0,   193,     0,    40,     2,     3,
       4,     0,     0,     0,     5,     6,     0,   198,     0,     7,
       8,     9,    10,     0,     0,     0,     0,   204,    97,    98,
      99,   100,   101,   102,   103,   104,     0,     0,   105,     0,
       0,     0,     0,     0,     0,   106,     0,    11,   107,   108,
     109,   110,   111,     0,   112,   113,     0,     0,     0,     0,
       0,     0,   120,    97,    98,    99,   100,   101,   102,   103,
     104,     0,     0,   105,     0,     0,     0,     0,     0,     0,
     106,     0,     0,   107,   108,   109,   110,   111,     0,   112,
     113,     0,   121,   122,     0,     0,     0,   143,    97,    98,
      99,   100,   101,   102,   103,   104,     0,     0,   105,     0,
       0,     0,     0,     0,     0,   106,     0,     0,   107,   108,
     109,   110,   111,     0,   112,   113,    97,    98,    99,   100,
     101,   102,   103,   104,     0,     0,   105,     0,     0,     0,
       0,     0,     0,   106,     0,     0,   107,   108,   109,   110,
     111,     0,   112,   113,     0,     0,     0,     0,     0,   202,
      97,    98,    99,   100,   101,   102,   103,   104,     0,     0,
     105,     0,     0,     0,     0,     0,     0,   106,     0,     0,
     107,   108,   109,   110,   111,     0,   112,   113,     0,     0,
       0,     0,   181,    97,    98,    99,   100,   101,   102,   103,
     104,     0,     0,   105,     0,     0,     0,     0,     0,     0,
     106,     0,     0,   107,   108,   109,   110,   111,     0,   112,
     113,     0,     0,     0,     0,   191,    97,    98,    99,   100,
     101,   102,   103,   104,     0,     0,   105,     0,     0,     0,
       0,     0,     0,   106,     0,     0,   107,   108,   109,   110,
     111,     0,   112,   113,     0,     0,   142,    97,    98,    99,
     100,   101,   102,   103,   104,     0,     0,   105,     0,     0,
       0,     0,     0,     0,   106,     0,     0,   107,   108,   109,
     110,   111,     0,   112,   113,   145,    97,    98,    99,   100,
     101,   102,   103,   104,     0,     0,   105,     0,     0,     0,
       0,     0,     0,   106,     0,     0,   107,   108,   109,   110,
     111,     0,   112,   113,   186,    97,    98,    99,   100,   101,
     102,   103,   104,     0,     0,   105,     0,     0,     0,     0,
       0,     0,   106,     0,     0,   107,   108,   109,   110,   111,
       0,   112,   113
};

static const yytype_int16 yycheck[] =
{
       0,     1,    11,   168,    45,    60,     6,    62,    83,    87,
      85,    11,    60,     8,    14,    10,     0,     1,     5,    60,
       5,     6,     6,    22,    48,    49,    50,    11,    52,    53,
      14,    16,     0,     1,    55,    34,    35,    56,     6,     1,
     118,    60,   207,    56,     6,   120,    14,    60,     0,    22,
       5,     6,    14,    53,    63,    22,    55,    55,    57,    55,
      60,    34,    35,    63,     8,     9,    10,    34,    35,    53,
      37,    38,    39,    40,    41,    42,    60,    15,    45,    63,
       5,     6,    55,     5,    57,    53,     5,     6,    55,    58,
      57,    53,    60,     9,     0,     1,    52,    53,    60,     5,
       6,     7,     8,     9,    10,    11,    12,    22,    59,    15,
      16,    17,    18,    19,    20,    21,     0,     1,    54,    34,
      35,     5,     6,     7,     3,     4,     9,    11,    12,    20,
      21,    54,    16,    17,    18,    19,     8,     9,    44,    45,
      55,     1,    57,    56,    53,     5,     6,     7,    45,    56,
       9,    11,    12,    22,    60,     9,    16,    17,    18,    19,
      44,    45,     9,     8,   121,    34,    35,   167,    37,    38,
      39,    40,    41,    42,     9,   202,    60,   177,   124,   199,
      11,   146,   182,   167,    44,    45,    55,   187,    57,   143,
      -1,    -1,   192,   177,   194,    -1,    -1,    -1,   182,   167,
      60,    -1,   202,   187,    -1,   167,   206,    -1,   192,   177,
     194,   211,    -1,    -1,   182,   177,    -1,    -1,   202,   187,
     182,    -1,   206,    -1,   192,   187,   194,   211,    -1,    -1,
     192,    -1,   194,    -1,   202,     4,     5,    -1,   206,    -1,
       9,    10,    -1,   211,   206,    -1,    -1,     1,    -1,   211,
      -1,     5,     6,     7,    -1,    -1,    -1,    11,    12,    -1,
      -1,    -1,    16,    17,    18,    19,    35,    36,    37,    38,
      39,    40,    26,    27,    28,    29,    30,    31,    32,    33,
      -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    47,    48,    49,    50,    -1,    52,    53,
      26,    27,    28,    29,    30,    31,    60,    76,    77,    78,
      79,    80,    81,    82,    -1,    84,    -1,    43,    -1,    -1,
      46,    47,    48,    49,    50,    -1,    52,    53,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,    -1,   115,    -1,   117,     3,
       4,     5,     6,    46,    47,    48,    49,    50,    -1,    52,
      53,    -1,    16,    -1,    -1,    22,    -1,    -1,    -1,    23,
      24,    25,    -1,    -1,   143,    -1,   145,   146,    -1,    -1,
      37,    38,    39,    40,    41,    42,    -1,    -1,    45,    -1,
      -1,    -1,    46,    47,    -1,    -1,   165,    51,    55,    -1,
      57,    55,    -1,    57,    -1,   174,    -1,    61,     5,     6,
       7,    -1,    -1,    -1,    11,    12,    -1,   186,    -1,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,   196,    26,    27,
      28,    29,    30,    31,    32,    33,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    -1,    44,    46,    47,
      48,    49,    50,    -1,    52,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    26,    27,    28,    29,    30,    31,    32,
      33,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    -1,    -1,    46,    47,    48,    49,    50,    -1,    52,
      53,    -1,    20,    21,    -1,    -1,    -1,    60,    26,    27,
      28,    29,    30,    31,    32,    33,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    -1,    -1,    46,    47,
      48,    49,    50,    -1,    52,    53,    26,    27,    28,    29,
      30,    31,    32,    33,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    46,    47,    48,    49,
      50,    -1,    52,    53,    -1,    -1,    -1,    -1,    -1,    59,
      26,    27,    28,    29,    30,    31,    32,    33,    -1,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    -1,
      46,    47,    48,    49,    50,    -1,    52,    53,    -1,    -1,
      -1,    -1,    58,    26,    27,    28,    29,    30,    31,    32,
      33,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    -1,    -1,    46,    47,    48,    49,    50,    -1,    52,
      53,    -1,    -1,    -1,    -1,    58,    26,    27,    28,    29,
      30,    31,    32,    33,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    46,    47,    48,    49,
      50,    -1,    52,    53,    -1,    -1,    56,    26,    27,    28,
      29,    30,    31,    32,    33,    -1,    -1,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    -1,    -1,    46,    47,    48,
      49,    50,    -1,    52,    53,    54,    26,    27,    28,    29,
      30,    31,    32,    33,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    46,    47,    48,    49,
      50,    -1,    52,    53,    54,    26,    27,    28,    29,    30,
      31,    32,    33,    -1,    -1,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    -1,    -1,    46,    47,    48,    49,    50,
      -1,    52,    53
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     5,     6,     7,    11,    12,    16,    17,    18,
      19,    44,    77,    78,    79,    80,    81,    82,    83,    84,
      88,    91,    92,    93,    95,    97,    78,     3,     4,     5,
       6,    16,    23,    24,    25,    46,    47,    51,    55,    57,
      61,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    80,    81,    94,    95,    98,   100,
      76,    78,     5,    55,    76,    96,    76,    81,    84,    93,
      95,     0,    78,    22,    34,    35,    37,    38,    39,    40,
      41,    42,    45,    55,    57,    45,    60,    55,    76,    76,
      76,    76,    76,    99,    76,   101,   102,    26,    27,    28,
      29,    30,    31,    32,    33,    36,    43,    46,    47,    48,
      49,    50,    52,    53,    78,    57,    78,    15,    55,    84,
      60,    20,    21,    85,    86,    87,     5,    76,    76,    76,
      76,    76,    76,    76,    76,    96,    76,    96,     5,     6,
       5,    97,    56,    60,    58,    54,    60,    62,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,     8,     9,    10,    89,    90,
      76,     9,    76,    97,    59,    96,    64,    54,     9,    85,
      56,    58,    56,    99,    76,   102,    54,    76,    78,     9,
      90,    58,    56,    76,    54,    78,    45,    78,    76,    78,
       9,    78,    59,    78,    76,     9,    10,    89,     9,    79,
      78,    56,    78,     9
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    63,    64,    64,    65,    65,    65,    65,    66,    66,
      67,    67,    67,    67,    68,    68,    69,    69,    69,    69,
      70,    70,    70,    71,    72,    73,    74,    75,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    77,    77,
      78,    78,    78,    79,    79,    79,    79,    79,    79,    79,
      79,    80,    80,    81,    81,    81,    82,    82,    83,    83,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    85,
      85,    85,    86,    87,    88,    88,    88,    88,    89,    89,
      90,    90,    90,    91,    91,    91,    92,    92,    93,    94,
      95,    96,    96,    96,    97,    97,    97,    97,    97,    98,
      99,    99,    99,   100,   101,   101,   101,   102,   102
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     3,     5,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     1,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     1,     1,     1,     3,     4,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     6,     2,
       1,     1,     4,     3,     4,     6,     5,     4,     1,     2,
       3,     5,     4,     4,     4,    10,     2,     2,     7,     6,
       4,     0,     1,     3,     0,     1,     1,     3,     3,     3,
       0,     1,     3,     3,     0,     1,     3,     0,     3
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
        case 5:
#line 146 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_logico(1, (yylsp[0]).first_line, (yylsp[0]).first_column);}
#line 1712 "latparse.c" /* yacc.c:1646  */
    break;

  case 6:
#line 147 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_logico(0, (yylsp[0]).first_line, (yylsp[0]).first_column);}
#line 1718 "latparse.c" /* yacc.c:1646  */
    break;

  case 7:
#line 148 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nulo(NULL, (yylsp[0]).first_line, (yylsp[0]).first_column);}
#line 1724 "latparse.c" /* yacc.c:1646  */
    break;

  case 8:
#line 152 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_nodo(NODO_MENOS_UNARIO, (yyvsp[0].node), NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        if((yyval.node) == NULL) YYABORT;
    }
#line 1733 "latparse.c" /* yacc.c:1646  */
    break;

  case 9:
#line 156 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_nodo(NODO_MAS_UNARIO, (yyvsp[0].node), NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        if((yyval.node) == NULL) YYABORT;
    }
#line 1742 "latparse.c" /* yacc.c:1646  */
    break;

  case 10:
#line 163 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_nodo(NODO_POTENCIA, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        if((yyval.node) == NULL) YYABORT;
    }
#line 1751 "latparse.c" /* yacc.c:1646  */
    break;

  case 11:
#line 167 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_nodo(NODO_MULTIPLICACION, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        if((yyval.node) == NULL) YYABORT;
    }
#line 1760 "latparse.c" /* yacc.c:1646  */
    break;

  case 12:
#line 171 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_nodo(NODO_DIVISION, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        if((yyval.node) == NULL) YYABORT;
    }
#line 1769 "latparse.c" /* yacc.c:1646  */
    break;

  case 13:
#line 175 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_nodo(NODO_MODULO, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        if((yyval.node) == NULL) YYABORT;
    }
#line 1778 "latparse.c" /* yacc.c:1646  */
    break;

  case 14:
#line 182 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_nodo(NODO_RESTA, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        if((yyval.node) == NULL) YYABORT;
    }
#line 1787 "latparse.c" /* yacc.c:1646  */
    break;

  case 15:
#line 186 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_nodo(NODO_SUMA, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        if((yyval.node) == NULL) YYABORT;
    }
#line 1796 "latparse.c" /* yacc.c:1646  */
    break;

  case 16:
#line 193 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_MAYOR_QUE, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1802 "latparse.c" /* yacc.c:1646  */
    break;

  case 17:
#line 194 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_MENOR_QUE, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1808 "latparse.c" /* yacc.c:1646  */
    break;

  case 18:
#line 195 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_MAYOR_IGUAL, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1814 "latparse.c" /* yacc.c:1646  */
    break;

  case 19:
#line 196 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_MENOR_IGUAL, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1820 "latparse.c" /* yacc.c:1646  */
    break;

  case 20:
#line 200 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_DESIGUALDAD, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1826 "latparse.c" /* yacc.c:1646  */
    break;

  case 21:
#line 201 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_IGUALDAD, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1832 "latparse.c" /* yacc.c:1646  */
    break;

  case 22:
#line 202 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_REGEX, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1838 "latparse.c" /* yacc.c:1646  */
    break;

  case 23:
#line 206 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_NO, (yyvsp[0].node), NULL, (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 1844 "latparse.c" /* yacc.c:1646  */
    break;

  case 24:
#line 210 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_Y, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1850 "latparse.c" /* yacc.c:1646  */
    break;

  case 25:
#line 214 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_O, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1856 "latparse.c" /* yacc.c:1646  */
    break;

  case 26:
#line 218 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_si((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1862 "latparse.c" /* yacc.c:1646  */
    break;

  case 27:
#line 222 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_CONCATENAR, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1868 "latparse.c" /* yacc.c:1646  */
    break;

  case 28:
#line 226 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1874 "latparse.c" /* yacc.c:1646  */
    break;

  case 47:
#line 245 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_LOAD_VAR_ARGS , NULL, NULL, 0, 0); }
#line 1880 "latparse.c" /* yacc.c:1646  */
    break;

  case 48:
#line 249 "latparse.y" /* yacc.c:1646  */
    { /* empty */
        *root = NULL;
    }
#line 1888 "latparse.c" /* yacc.c:1646  */
    break;

  case 49:
#line 252 "latparse.y" /* yacc.c:1646  */
    { *root = (yyvsp[0].node); }
#line 1894 "latparse.c" /* yacc.c:1646  */
    break;

  case 50:
#line 256 "latparse.y" /* yacc.c:1646  */
    {
        if((yyvsp[0].node)){
            (yyval.node) = latA_nodo(NODO_BLOQUE, (yyvsp[-1].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
        }
    }
#line 1904 "latparse.c" /* yacc.c:1646  */
    break;

  case 51:
#line 261 "latparse.y" /* yacc.c:1646  */
    {
        if((yyvsp[0].node)){
          (yyval.node) = latA_nodo(NODO_BLOQUE, (yyvsp[0].node), NULL, (yylsp[0]).first_line, (yylsp[0]).first_column);
        }
    }
#line 1914 "latparse.c" /* yacc.c:1646  */
    break;

  case 52:
#line 266 "latparse.y" /* yacc.c:1646  */
    { yyerrok; yyclearin;}
#line 1920 "latparse.c" /* yacc.c:1646  */
    break;

  case 61:
#line 281 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_INC, (yyvsp[-1].node), NULL, (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 1926 "latparse.c" /* yacc.c:1646  */
    break;

  case 62:
#line 282 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_DEC, (yyvsp[-1].node), NULL, (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 1932 "latparse.c" /* yacc.c:1646  */
    break;

  case 66:
#line 292 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_ATRIBUTO, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 1938 "latparse.c" /* yacc.c:1646  */
    break;

  case 67:
#line 293 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_LISTA_OBTENER_ELEMENTO, (yyvsp[-1].node), (yyvsp[-3].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1944 "latparse.c" /* yacc.c:1646  */
    break;

  case 68:
#line 297 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_nodo(NODO_GLOBAL, (yyvsp[0].node), NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
    }
#line 1952 "latparse.c" /* yacc.c:1646  */
    break;

  case 69:
#line 300 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_nodo(NODO_GLOBAL, (yyvsp[0].node), NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
    }
#line 1960 "latparse.c" /* yacc.c:1646  */
    break;

  case 70:
#line 306 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_asign((yyvsp[0].node), (yyvsp[-2].node)); }
#line 1966 "latparse.c" /* yacc.c:1646  */
    break;

  case 71:
#line 307 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_asign(
        (latA_nodo(NODO_CONCATENAR, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column)), (yyvsp[-2].node)); }
#line 1973 "latparse.c" /* yacc.c:1646  */
    break;

  case 72:
#line 309 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_asign(
        (latA_nodo(NODO_SUMA, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column)), (yyvsp[-2].node)); }
#line 1980 "latparse.c" /* yacc.c:1646  */
    break;

  case 73:
#line 311 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_asign(
        (latA_nodo(NODO_RESTA, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column)), (yyvsp[-2].node)); }
#line 1987 "latparse.c" /* yacc.c:1646  */
    break;

  case 74:
#line 313 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_asign(
        (latA_nodo(NODO_MULTIPLICACION, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column)), (yyvsp[-2].node)); }
#line 1994 "latparse.c" /* yacc.c:1646  */
    break;

  case 75:
#line 315 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_asign(
        (latA_nodo(NODO_DIVISION, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column)), (yyvsp[-2].node)); }
#line 2001 "latparse.c" /* yacc.c:1646  */
    break;

  case 76:
#line 317 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_asign(
        (latA_nodo(NODO_MODULO, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column)), (yyvsp[-2].node)); }
#line 2008 "latparse.c" /* yacc.c:1646  */
    break;

  case 77:
#line 319 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_asign((yyvsp[0].node), (yyvsp[-2].node)); }
#line 2014 "latparse.c" /* yacc.c:1646  */
    break;

  case 78:
#line 320 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_asign_le((yyvsp[0].node), (yyvsp[-5].node), (yyvsp[-3].node)); }
#line 2020 "latparse.c" /* yacc.c:1646  */
    break;

  case 79:
#line 324 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_nodo(NODO_CASOS, (yyvsp[-1].node), (yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
    }
#line 2028 "latparse.c" /* yacc.c:1646  */
    break;

  case 80:
#line 327 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_nodo(NODO_CASOS, (yyvsp[0].node), NULL, (yylsp[0]).first_line, (yylsp[0]).first_column);
    }
#line 2036 "latparse.c" /* yacc.c:1646  */
    break;

  case 81:
#line 330 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_nodo(NODO_CASOS, (yyvsp[0].node), NULL, (yylsp[0]).first_line, (yylsp[0]).first_column);
    }
#line 2044 "latparse.c" /* yacc.c:1646  */
    break;

  case 82:
#line 337 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_nodo(NODO_CASO, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-3]).first_line, (yylsp[-3]).first_column);
    }
#line 2052 "latparse.c" /* yacc.c:1646  */
    break;

  case 83:
#line 344 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_nodo(NODO_DEFECTO, NULL, (yyvsp[0].node), (yylsp[-2]).first_line, (yylsp[-2]).first_column);
    }
#line 2060 "latparse.c" /* yacc.c:1646  */
    break;

  case 84:
#line 350 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_si((yyvsp[-2].node), (yyvsp[-1].node), NULL); }
#line 2067 "latparse.c" /* yacc.c:1646  */
    break;

  case 85:
#line 352 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_si((yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2074 "latparse.c" /* yacc.c:1646  */
    break;

  case 86:
#line 354 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_si((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 2081 "latparse.c" /* yacc.c:1646  */
    break;

  case 87:
#line 356 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_nodo(NODO_ELEGIR, (yyvsp[-2].node), (yyvsp[-1].node), (yylsp[-3]).first_line, (yylsp[-3]).first_column);
    }
#line 2089 "latparse.c" /* yacc.c:1646  */
    break;

  case 90:
#line 367 "latparse.y" /* yacc.c:1646  */
    {
          (yyval.node) = latA_si((yyvsp[-1].node), (yyvsp[0].node), NULL);
    }
#line 2097 "latparse.c" /* yacc.c:1646  */
    break;

  case 91:
#line 370 "latparse.y" /* yacc.c:1646  */
    {
          (yyval.node) = latA_si((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2105 "latparse.c" /* yacc.c:1646  */
    break;

  case 92:
#line 373 "latparse.y" /* yacc.c:1646  */
    {
          (yyval.node) = latA_si((yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2113 "latparse.c" /* yacc.c:1646  */
    break;

  case 93:
#line 379 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_mientras((yyvsp[-2].node), (yyvsp[-1].node)); }
#line 2120 "latparse.c" /* yacc.c:1646  */
    break;

  case 94:
#line 381 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_hacer((yyvsp[0].node), (yyvsp[-2].node)); }
#line 2127 "latparse.c" /* yacc.c:1646  */
    break;

  case 95:
#line 384 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_desde((yyvsp[-7].node), (yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2134 "latparse.c" /* yacc.c:1646  */
    break;

  case 96:
#line 389 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_RETORNO, (yyvsp[0].node), NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 2140 "latparse.c" /* yacc.c:1646  */
    break;

  case 97:
#line 390 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_RETORNO, (yyvsp[0].node), NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 2146 "latparse.c" /* yacc.c:1646  */
    break;

  case 98:
#line 394 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_funcion((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node), (yylsp[-5]).first_line, (yylsp[-5]).first_column);
    }
#line 2154 "latparse.c" /* yacc.c:1646  */
    break;

  case 99:
#line 400 "latparse.y" /* yacc.c:1646  */
    {
        (yyval.node) = latA_funcion(latA_var("anonima", (yylsp[-5]).first_line, (yylsp[-5]).first_column, false), (yyvsp[-3].node), (yyvsp[-1].node), (yylsp[-5]).first_line, (yylsp[-5]).first_column);
    }
#line 2162 "latparse.c" /* yacc.c:1646  */
    break;

  case 100:
#line 406 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_FUNCION_LLAMADA, (yyvsp[-3].node), (yyvsp[-1].node), (yylsp[-3]).first_line, (yylsp[-3]).first_column); }
#line 2168 "latparse.c" /* yacc.c:1646  */
    break;

  case 101:
#line 410 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = NULL; }
#line 2174 "latparse.c" /* yacc.c:1646  */
    break;

  case 102:
#line 411 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_FUNCION_ARGUMENTOS, (yyvsp[0].node), NULL, (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 2180 "latparse.c" /* yacc.c:1646  */
    break;

  case 103:
#line 412 "latparse.y" /* yacc.c:1646  */
    {
        if((yyvsp[-2].node)->tipo == NODO_VAR_ARGS){
            printf(LAT_ERROR_FMT, filename, (yylsp[-2]).first_line, (yylsp[-2]).first_column, "Parametro VAR_ARGS (...) debe de ser el ultimo parametro");
            YYABORT;
        }
        (yyval.node) = latA_nodo(NODO_FUNCION_ARGUMENTOS, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-2]).first_line, (yylsp[-2]).first_column);
    }
#line 2192 "latparse.c" /* yacc.c:1646  */
    break;

  case 104:
#line 422 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = NULL; }
#line 2198 "latparse.c" /* yacc.c:1646  */
    break;

  case 105:
#line 423 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_FUNCION_PARAMETROS, (yyvsp[0].node), NULL, (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 2204 "latparse.c" /* yacc.c:1646  */
    break;

  case 106:
#line 424 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_FUNCION_PARAMETROS, (yyvsp[0].node), NULL, 0, 0); }
#line 2210 "latparse.c" /* yacc.c:1646  */
    break;

  case 107:
#line 425 "latparse.y" /* yacc.c:1646  */
    {
        if((yyvsp[-2].node)->izq->tipo == NODO_VAR_ARGS){
            printf(LAT_ERROR_FMT, (yylsp[0]).file_name, (yylsp[0]).first_line, (yylsp[0]).first_column, "Parametro VAR_ARGS (...) debe de ser el ultimo parametro");
            YYABORT;
        }
        (yyval.node) = latA_nodo(NODO_FUNCION_PARAMETROS, (yyvsp[0].node), (yyvsp[-2].node), (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 2221 "latparse.c" /* yacc.c:1646  */
    break;

  case 108:
#line 431 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_FUNCION_PARAMETROS, (yyvsp[0].node), (yyvsp[-2].node), 0, 0); }
#line 2227 "latparse.c" /* yacc.c:1646  */
    break;

  case 109:
#line 435 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_LISTA, (yyvsp[-1].node), NULL, (yylsp[-2]).first_line, (yylsp[-2]).first_column); }
#line 2233 "latparse.c" /* yacc.c:1646  */
    break;

  case 110:
#line 439 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = NULL; }
#line 2239 "latparse.c" /* yacc.c:1646  */
    break;

  case 111:
#line 440 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_LISTA_AGREGAR_ELEMENTO, (yyvsp[0].node), NULL, (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 2245 "latparse.c" /* yacc.c:1646  */
    break;

  case 112:
#line 441 "latparse.y" /* yacc.c:1646  */
    {
        if((yyvsp[-2].node)->tipo == NODO_LOAD_VAR_ARGS){
            printf(LAT_ERROR_FMT, filename, (yylsp[-2]).first_line, (yylsp[-2]).first_column, "Parametro VAR_ARGS (...) debe de ser el ultimo parametro");
            YYABORT;
        }
        (yyval.node) = latA_nodo(NODO_LISTA_AGREGAR_ELEMENTO, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[0]).first_line, (yylsp[0]).first_column);
    }
#line 2257 "latparse.c" /* yacc.c:1646  */
    break;

  case 113:
#line 451 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_DICCIONARIO, (yyvsp[-1].node), NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 2263 "latparse.c" /* yacc.c:1646  */
    break;

  case 114:
#line 455 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = NULL; }
#line 2269 "latparse.c" /* yacc.c:1646  */
    break;

  case 115:
#line 456 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_DICC_AGREGAR_ELEMENTO, (yyvsp[0].node), NULL, (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 2275 "latparse.c" /* yacc.c:1646  */
    break;

  case 116:
#line 457 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_DICC_AGREGAR_ELEMENTO, (yyvsp[0].node), (yyvsp[-2].node), (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 2281 "latparse.c" /* yacc.c:1646  */
    break;

  case 117:
#line 461 "latparse.y" /* yacc.c:1646  */
    { /* empty */ (yyval.node) = NULL; }
#line 2287 "latparse.c" /* yacc.c:1646  */
    break;

  case 118:
#line 462 "latparse.y" /* yacc.c:1646  */
    { (yyval.node) = latA_nodo(NODO_DICC_ELEMENTO, (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-2]).first_line, (yylsp[-2]).first_column); }
#line 2293 "latparse.c" /* yacc.c:1646  */
    break;


#line 2297 "latparse.c" /* yacc.c:1646  */
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
#line 465 "latparse.y" /* yacc.c:1906  */


//se define para analisis sintactico (bison)
int yyerror(struct YYLTYPE *yylloc_param, void *scanner, struct ast **root,
const char *s) {
  if(!parse_silent){
      fprintf(stderr, LAT_ERROR_FMT, yylloc_param->file_name,
        yylloc_param->first_line, yylloc_param->first_column,  s);
  }
  return 0;
}
