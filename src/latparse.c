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
#line 1 "latparse.y"			/* yacc.c:339  */

/*
The MIT License (MIT)

Copyright (c) 2015 - 2016. Latino

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

#ifdef __linux
#include <libintl.h>
#define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#endif

int yyerror(struct YYLTYPE *yylloc_param, void *scanner, struct ast **root,
			const char *s);
int yylex(YYSTYPE * yylval_param, YYLTYPE * yylloc_param, yyscan_t yyscanner);

#line 114 "latparse.c"			/* yacc.c:339  */

#ifndef YY_NULLPTR
#if defined __cplusplus && 201103L <= __cplusplus
#define YY_NULLPTR nullptr
#else
#define YY_NULLPTR 0
#endif
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
#undef YYERROR_VERBOSE
#define YYERROR_VERBOSE 1
#else
#define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "latparse.h".  */
#ifndef YY_YY_LATPARSE_H_INCLUDED
#define YY_YY_LATPARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
#define YYTOKENTYPE
enum yytokentype {
	VERDADERO = 258,
	FALSO = 259,
	NULO = 260,
	NUMERICO = 261,
	CADENA = 262,
	IDENTIFICADOR = 263,
	SI = 264,
	O_SI = 265,
	FIN = 266,
	SINO = 267,
	MIENTRAS = 268,
	REPETIR = 269,
	ROMPER = 270,
	CONTINUAR = 271,
	HASTA = 272,
	FUNCION = 273,
	DESDE = 274,
	KBOOL = 275,
	RETORNO = 276,
	ELEGIR = 277,
	CASO = 278,
	DEFECTO = 279,
	ATRIBUTO = 280,
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
#define VERDADERO 258
#define FALSO 259
#define NULO 260
#define NUMERICO 261
#define CADENA 262
#define IDENTIFICADOR 263
#define SI 264
#define O_SI 265
#define FIN 266
#define SINO 267
#define MIENTRAS 268
#define REPETIR 269
#define ROMPER 270
#define CONTINUAR 271
#define HASTA 272
#define FUNCION 273
#define DESDE 274
#define KBOOL 275
#define RETORNO 276
#define ELEGIR 277
#define CASO 278
#define DEFECTO 279
#define ATRIBUTO 280
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
struct YYLTYPE {
	int first_line;
	int first_column;
	int last_line;
	int last_column;
};
#define YYLTYPE_IS_DECLARED 1
#define YYLTYPE_IS_TRIVIAL 1
#endif

int yyparse(ast ** root, void *scanner);

#endif /* !YY_YY_LATPARSE_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 261 "latparse.c"			/* yacc.c:358  */

#ifdef short
#undef short
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
#ifdef __SIZE_TYPE__
#define YYSIZE_T __SIZE_TYPE__
#elif defined size_t
#define YYSIZE_T size_t
#elif ! defined YYSIZE_T
#include <stddef.h>				/* INFRINGES ON USER NAME SPACE */
#define YYSIZE_T size_t
#else
#define YYSIZE_T unsigned int
#endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
#if defined YYENABLE_NLS && YYENABLE_NLS
#if ENABLE_NLS
#include <libintl.h>			/* INFRINGES ON USER NAME SPACE */
#define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#endif
#endif
#ifndef YY_
#define YY_(Msgid) Msgid
#endif
#endif

#ifndef YY_ATTRIBUTE
#if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#define YY_ATTRIBUTE(Spec) __attribute__(Spec)
#else
#define YY_ATTRIBUTE(Spec)		/* empty */
#endif
#endif

#ifndef YY_ATTRIBUTE_PURE
#define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
#define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
#if defined _MSC_VER && 1200 <= _MSC_VER
#define _Noreturn __declspec (noreturn)
#else
#define _Noreturn YY_ATTRIBUTE ((__noreturn__))
#endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
#define YYUSE(E) ((void) (E))
#else
#define YYUSE(E)				/* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
#define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
#define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
#define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
#define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
#define YY_INITIAL_VALUE(Value)	/* Nothing. */
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

#ifdef YYSTACK_USE_ALLOCA
#if YYSTACK_USE_ALLOCA
#ifdef __GNUC__
#define YYSTACK_ALLOC __builtin_alloca
#elif defined __BUILTIN_VA_ARG_INCR
#include <alloca.h>				/* INFRINGES ON USER NAME SPACE */
#elif defined _AIX
#define YYSTACK_ALLOC __alloca
#elif defined _MSC_VER
#include <malloc.h>				/* INFRINGES ON USER NAME SPACE */
#define alloca _alloca
#else
#define YYSTACK_ALLOC alloca
#if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#include <stdlib.h>				/* INFRINGES ON USER NAME SPACE */
	  /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#endif
#endif
#endif
#endif

#ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#ifndef YYSTACK_ALLOC_MAXIMUM
	/* The OS might guarantee only one guard page at the bottom of the stack,
	   and a page size can be as small as 4096 bytes.  So we cannot safely
	   invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
	   to allow for a few compiler-allocated temporary stack slots.  */
#define YYSTACK_ALLOC_MAXIMUM 4032	/* reasonable circa 2006 */
#endif
#else
#define YYSTACK_ALLOC YYMALLOC
#define YYSTACK_FREE YYFREE
#ifndef YYSTACK_ALLOC_MAXIMUM
#define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#endif
#if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#include <stdlib.h>				/* INFRINGES ON USER NAME SPACE */
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#endif
#ifndef YYMALLOC
#define YYMALLOC malloc
#if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc(YYSIZE_T);			/* INFRINGES ON USER NAME SPACE */
#endif
#endif
#ifndef YYFREE
#define YYFREE free
#if ! defined free && ! defined EXIT_SUCCESS
void free(void *);				/* INFRINGES ON USER NAME SPACE */
#endif
#endif
#endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc {
	yytype_int16 yyss_alloc;
	YYSTYPE yyvs_alloc;
	YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
#define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
#define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

#define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
#define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
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
#ifndef YYCOPY
#if defined __GNUC__ && 1 < __GNUC__
#define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#else
#define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#endif
#endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  64
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   654

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  110
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  203

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   299

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] = {
	0, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 51, 2, 2, 2, 50, 2, 2,
	54, 55, 48, 46, 59, 47, 2, 49, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 53, 58,
	2, 45, 2, 52, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 56, 2, 57, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 60, 2, 61, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 1, 2, 3, 4,
	5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
	25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
	35, 36, 37, 38, 39, 40, 41, 42, 43, 44
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] = {
	0, 138, 138, 139, 143, 144, 145, 146, 150, 154,
	161, 165, 169, 176, 180, 187, 188, 189, 190, 194,
	195, 196, 200, 204, 208, 212, 216, 220, 221, 222,
	223, 224, 225, 226, 227, 228, 229, 230, 231, 232,
	233, 234, 235, 236, 240, 243, 247, 252, 257, 261,
	262, 263, 264, 265, 266, 267, 271, 272, 276, 277,
	281, 282, 286, 289, 296, 297, 298, 299, 300, 301,
	302, 303, 304, 305, 309, 312, 315, 322, 329, 335,
	337, 339, 341, 347, 348, 352, 355, 358, 364, 366,
	368, 374, 378, 384, 390, 394, 395, 396, 400, 401,
	402, 406, 410, 411, 412, 416, 420, 421, 422, 426,
	427
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] = {
	"$end", "error", "$undefined", "VERDADERO", "FALSO", "NULO", "NUMERICO",
	"CADENA", "IDENTIFICADOR", "SI", "O_SI", "FIN", "SINO", "MIENTRAS",
	"REPETIR", "ROMPER", "CONTINUAR", "HASTA", "FUNCION", "DESDE", "KBOOL",
	"RETORNO", "ELEGIR", "CASO", "DEFECTO", "ATRIBUTO", "MAYOR_QUE",
	"MENOR_QUE", "MAYOR_IGUAL", "MENOR_IGUAL", "IGUAL_LOGICO", "DIFERENTE",
	"Y_LOGICO", "O_LOGICO", "INCREMENTO", "DECREMENTO", "CONCATENAR",
	"CONCATENAR_IGUAL", "MAS_IGUAL", "MENOS_IGUAL", "POR_IGUAL",
	"ENTRE_IGUAL", "MODULO_IGUAL", "REGEX", "GLOBAL", "'='", "'+'", "'-'",
	"'*'", "'/'", "'%'", "'!'", "'?'", "':'", "'('", "')'", "'['", "']'",
	"';'", "','", "'{'", "'}'", "$accept", "constant_expression",
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

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] = {
	0, 256, 257, 258, 259, 260, 261, 262, 263, 264,
	265, 266, 267, 268, 269, 270, 271, 272, 273, 274,
	275, 276, 277, 278, 279, 280, 281, 282, 283, 284,
	285, 286, 287, 288, 289, 290, 291, 292, 293, 294,
	295, 296, 297, 298, 299, 61, 43, 45, 42, 47,
	37, 33, 63, 58, 40, 41, 91, 93, 59, 44,
	123, 125
};
#endif

#define YYPACT_NINF -151

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-151)))

#define YYTABLE_NINF -59

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] = {
	79, 279, -151, 30, 30, 279, -2, -45, 30, 30,
	-1, 26, -151, 260, -151, 397, -151, -151, -151, -151,
	-151, -151, -151, -151, -151, -151, -151, -151, -151, -151,
	-4, -22, 30, 30, 30, 30, 30, 30, -151, -151,
	-151, -151, -151, -151, -151, -151, -151, -151, -151, 209,
	3, -151, -151, -151, -151, 209, 36, 10, 57, 579,
	471, 420, -151, -151, -151, -151, 59, -151, -151, 30,
	30, 30, 30, 30, 30, 30, 30, 30, 60, -151,
	-151, -151, 441, 579, -37, 496, -36, -151, 30, 30,
	30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
	30, 30, 30, 19, 30, 64, 30, 60, 24, 33,
	25, 72, 20, -151, -151, 579, 579, 579, 579, 579,
	579, -151, 552, 281, 34, 339, -151, -51, -151, -151,
	30, 30, 30, -151, 56, 56, 56, 56, 56, 56,
	331, 331, 604, 56, 46, 46, -151, -151, -151, 30,
	-151, 279, 51, -151, 371, -151, 579, -41, 30, 32,
	279, -151, -151, 30, 30, -151, 54, 279, 83, 579,
	579, -151, 209, 105, -151, -151, -151, 279, 306, 279,
	-151, 524, -151, 30, 106, -151, 44, -151, 107, 57,
	-151, 30, 579, -151, 279, 109, -151, 65, 579, -151,
	279, 110, -151
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] = {
	0, 0, 58, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 45, 0, 73, 0, 59, 50, 49, 51,
	52, 53, 54, 55, 48, 5, 6, 7, 2, 3,
	4, 0, 0, 0, 0, 0, 102, 106, 28, 29,
	30, 31, 32, 33, 34, 35, 36, 37, 38, 0,
	42, 43, 39, 40, 41, 0, 0, 0, 0, 91,
	0, 0, 62, 63, 1, 46, 0, 56, 57, 0,
	0, 0, 0, 0, 0, 0, 95, 0, 98, 9,
	8, 22, 0, 103, 0, 0, 0, 107, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 98, 0, 0,
	0, 0, 75, 76, 60, 67, 68, 69, 70, 71,
	72, 65, 64, 96, 0, 0, 99, 0, 27, 101,
	0, 0, 109, 105, 15, 16, 17, 18, 20, 19,
	23, 24, 26, 21, 14, 13, 10, 11, 12, 0,
	79, 0, 0, 83, 0, 88, 89, 0, 0, 0,
	0, 82, 74, 0, 95, 94, 61, 0, 0, 104,
	110, 108, 0, 0, 81, 84, 61, 0, 0, 0,
	78, 0, 97, 0, 0, 100, 85, 80, 0, 0,
	77, 0, 66, 93, 0, 87, 92, 0, 25, 86,
	0, 0, 90
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] = {
	-151, 13, -151, -151, -151, -151, -151, -151, -151, -151,
	-151, -151, -151, 38, -151, 14, -151, -151, 0, -151,
	-151, -7, 12, -151, -151, -151, -61, -150, -151, -151,
	131, -151, 11, -21, 39, -151, -151, -151, -151, 15
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] = {
	-1, 38, 39, 40, 41, 42, 43, 44, 45, 46,
	47, 121, 48, 85, 11, 12, 13, 14, 50, 16,
	17, 18, 111, 112, 113, 19, 152, 153, 20, 21,
	22, 51, 52, 124, 127, 53, 84, 54, 86, 87
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] = {
	15, 15, 175, 62, 167, 15, 57, 2, 168, 58,
	61, 23, 23, 15, 177, 24, 23, 6, 168, 56,
	129, -58, 130, 132, 23, 133, 64, 65, 66, 149,
	150, 151, 78, 25, 26, 27, 28, 29, 30, 28,
	29, 49, 55, 109, 110, 175, 59, 60, 31, 15,
	-58, 108, -58, 106, 149, 15, 194, 76, 61, 104,
	23, 149, 174, 103, 107, 2, 23, 114, 126, 105,
	79, 80, 81, 82, 83, 155, 32, 33, 160, -44,
	1, 34, 158, 161, 35, 179, 36, 2, 3, 165,
	37, 185, 4, 5, 100, 101, 102, 6, 7, 183,
	8, 9, 98, 99, 100, 101, 102, 115, 116, 117,
	118, 119, 120, 122, 123, 125, 187, 193, 196, 149,
	200, 202, 159, 10, 162, 195, 134, 135, 136, 137,
	138, 139, 140, 141, 142, 143, 144, 145, 146, 147,
	148, 63, 154, 182, 156, 0, 157, 171, 0, 0,
	0, 15, 0, 0, 0, 0, 0, 0, 0, 0,
	15, 0, 23, 0, 0, 173, 0, 15, 169, 170,
	0, 23, 15, 0, 180, 0, 0, 15, 23, 15,
	0, 184, 197, 23, 0, 0, 186, 172, 23, 61,
	23, 188, 0, 190, 15, 0, 178, 0, 0, 0,
	15, 181, 123, 0, 0, 23, 0, 0, 199, 0,
	1, 23, 0, 0, 201, 0, 0, 2, 3, 0,
	0, 192, 4, 5, 0, 0, 0, 6, 7, 198,
	8, 9, 0, 0, 0, 88, 89, 90, 91, 92,
	93, 94, 95, 0, 0, 96, 0, 0, 0, 0,
	0, 0, 97, 10, 0, 98, 99, 100, 101, 102,
	-47, 1, 0, 0, 0, 0, 0, 0, 2, 3,
	-47, -47, -47, 4, 5, 0, 0, -47, 6, 7,
	1, 8, 9, -47, -47, 0, 0, 2, 3, 0,
	0, 0, 4, 5, 0, 0, 0, 6, 7, 0,
	8, 9, 0, 0, 10, 0, 0, 88, 89, 90,
	91, 92, 93, 94, 95, 0, 0, 96, 0, 0,
	0, 0, 0, 10, 97, 0, 0, 98, 99, 100,
	101, 102, 88, 89, 90, 91, 92, 93, 94, 95,
	164, 0, 96, 0, 0, 0, 0, 0, 0, 97,
	0, 0, 98, 99, 100, 101, 102, 88, 89, 90,
	91, 92, 93, 0, 189, 88, 89, 90, 91, 92,
	93, 94, 95, 0, 97, 96, 0, 98, 99, 100,
	101, 102, 97, 0, 0, 98, 99, 100, 101, 102,
	0, 0, 0, 0, 0, 0, 166, 88, 89, 90,
	91, 92, 93, 94, 95, 0, 0, 96, 0, 0,
	0, 0, 0, 0, 97, 0, 0, 98, 99, 100,
	101, 102, 66, 0, 0, 0, 0, 0, 176, 0,
	0, 67, 68, 0, 69, 70, 71, 72, 73, 74,
	0, 0, 75, 0, 0, 66, 0, 0, 0, 0,
	0, 76, 0, 77, 67, 68, 0, 69, 70, 71,
	72, 73, 74, 0, 0, 75, 0, 88, 89, 90,
	91, 92, 93, 94, 95, 0, 77, 96, 0, 0,
	0, 0, 0, 0, 97, 0, 0, 98, 99, 100,
	101, 102, 0, 0, 109, 110, 128, 88, 89, 90,
	91, 92, 93, 94, 95, 0, 0, 96, 0, 0,
	0, 0, 0, 0, 97, 0, 0, 98, 99, 100,
	101, 102, 88, 89, 90, 91, 92, 93, 94, 95,
	0, 0, 96, 0, 0, 0, 0, 0, 0, 97,
	0, 0, 98, 99, 100, 101, 102, 0, 0, 131,
	88, 89, 90, 91, 92, 93, 94, 95, 0, 0,
	96, 0, 0, 0, 0, 0, 0, 97, 0, 0,
	98, 99, 100, 101, 102, 0, 0, 191, 88, 89,
	90, 91, 92, 93, 94, 95, 0, 0, 96, 0,
	0, 0, 0, 0, 0, 97, 0, 0, 98, 99,
	100, 101, 102, 0, 163, 88, 89, 90, 91, 92,
	93, 94, 95, 0, 0, 96, 0, 0, 0, 0,
	0, 0, 97, 0, 0, 98, 99, 100, 101, 102,
	88, 89, 90, 91, 92, 93, 94, 95, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 97, 0, 0,
	98, 99, 100, 101, 102
};

static const yytype_int16 yycheck[] = {
	0, 1, 152, 10, 55, 5, 8, 8, 59, 54,
	10, 0, 1, 13, 55, 1, 5, 18, 59, 5,
	57, 25, 59, 59, 13, 61, 0, 13, 25, 10,
	11, 12, 54, 3, 4, 5, 6, 7, 8, 6,
	7, 3, 4, 23, 24, 195, 8, 9, 18, 49,
	54, 58, 56, 17, 10, 55, 12, 54, 58, 56,
	49, 10, 11, 49, 54, 8, 55, 8, 8, 55,
	32, 33, 34, 35, 36, 11, 46, 47, 53, 0,
	1, 51, 58, 11, 54, 53, 56, 8, 9, 55,
	60, 8, 13, 14, 48, 49, 50, 18, 19, 45,
	21, 22, 46, 47, 48, 49, 50, 69, 70, 71,
	72, 73, 74, 75, 76, 77, 11, 11, 11, 10,
	55, 11, 109, 44, 112, 186, 88, 89, 90, 91,
	92, 93, 94, 95, 96, 97, 98, 99, 100, 101,
	102, 10, 104, 164, 106, -1, 107, 132, -1, -1,
	-1, 151, -1, -1, -1, -1, -1, -1, -1, -1,
	160, -1, 151, -1, -1, 151, -1, 167, 130, 131,
	-1, 160, 172, -1, 160, -1, -1, 177, 167, 179,
	-1, 167, 189, 172, -1, -1, 172, 149, 177, 189,
	179, 177, -1, 179, 194, -1, 158, -1, -1, -1,
	200, 163, 164, -1, -1, 194, -1, -1, 194, -1,
	1, 200, -1, -1, 200, -1, -1, 8, 9, -1,
	-1, 183, 13, 14, -1, -1, -1, 18, 19, 191,
	21, 22, -1, -1, -1, 26, 27, 28, 29, 30,
	31, 32, 33, -1, -1, 36, -1, -1, -1, -1,
	-1, -1, 43, 44, -1, 46, 47, 48, 49, 50,
	0, 1, -1, -1, -1, -1, -1, -1, 8, 9,
	10, 11, 12, 13, 14, -1, -1, 17, 18, 19,
	1, 21, 22, 23, 24, -1, -1, 8, 9, -1,
	-1, -1, 13, 14, -1, -1, -1, 18, 19, -1,
	21, 22, -1, -1, 44, -1, -1, 26, 27, 28,
	29, 30, 31, 32, 33, -1, -1, 36, -1, -1,
	-1, -1, -1, 44, 43, -1, -1, 46, 47, 48,
	49, 50, 26, 27, 28, 29, 30, 31, 32, 33,
	59, -1, 36, -1, -1, -1, -1, -1, -1, 43,
	-1, -1, 46, 47, 48, 49, 50, 26, 27, 28,
	29, 30, 31, -1, 58, 26, 27, 28, 29, 30,
	31, 32, 33, -1, 43, 36, -1, 46, 47, 48,
	49, 50, 43, -1, -1, 46, 47, 48, 49, 50,
	-1, -1, -1, -1, -1, -1, 57, 26, 27, 28,
	29, 30, 31, 32, 33, -1, -1, 36, -1, -1,
	-1, -1, -1, -1, 43, -1, -1, 46, 47, 48,
	49, 50, 25, -1, -1, -1, -1, -1, 57, -1,
	-1, 34, 35, -1, 37, 38, 39, 40, 41, 42,
	-1, -1, 45, -1, -1, 25, -1, -1, -1, -1,
	-1, 54, -1, 56, 34, 35, -1, 37, 38, 39,
	40, 41, 42, -1, -1, 45, -1, 26, 27, 28,
	29, 30, 31, 32, 33, -1, 56, 36, -1, -1,
	-1, -1, -1, -1, 43, -1, -1, 46, 47, 48,
	49, 50, -1, -1, 23, 24, 55, 26, 27, 28,
	29, 30, 31, 32, 33, -1, -1, 36, -1, -1,
	-1, -1, -1, -1, 43, -1, -1, 46, 47, 48,
	49, 50, 26, 27, 28, 29, 30, 31, 32, 33,
	-1, -1, 36, -1, -1, -1, -1, -1, -1, 43,
	-1, -1, 46, 47, 48, 49, 50, -1, -1, 53,
	26, 27, 28, 29, 30, 31, 32, 33, -1, -1,
	36, -1, -1, -1, -1, -1, -1, 43, -1, -1,
	46, 47, 48, 49, 50, -1, -1, 53, 26, 27,
	28, 29, 30, 31, 32, 33, -1, -1, 36, -1,
	-1, -1, -1, -1, -1, 43, -1, -1, 46, 47,
	48, 49, 50, -1, 52, 26, 27, 28, 29, 30,
	31, 32, 33, -1, -1, 36, -1, -1, -1, -1,
	-1, -1, 43, -1, -1, 46, 47, 48, 49, 50,
	26, 27, 28, 29, 30, 31, 32, 33, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, 43, -1, -1,
	46, 47, 48, 49, 50
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] = {
	0, 1, 8, 9, 13, 14, 18, 19, 21, 22,
	44, 76, 77, 78, 79, 80, 81, 82, 83, 87,
	90, 91, 92, 94, 77, 3, 4, 5, 6, 7,
	8, 18, 46, 47, 51, 54, 56, 60, 63, 64,
	65, 66, 67, 68, 69, 70, 71, 72, 74, 75,
	80, 93, 94, 97, 99, 75, 77, 8, 54, 75,
	75, 80, 83, 92, 0, 77, 25, 34, 35, 37,
	38, 39, 40, 41, 42, 45, 54, 56, 54, 75,
	75, 75, 75, 75, 98, 75, 100, 101, 26, 27,
	28, 29, 30, 31, 32, 33, 36, 43, 46, 47,
	48, 49, 50, 77, 56, 77, 17, 54, 83, 23,
	24, 84, 85, 86, 8, 75, 75, 75, 75, 75,
	75, 73, 75, 75, 95, 75, 8, 96, 55, 57,
	59, 53, 59, 61, 75, 75, 75, 75, 75, 75,
	75, 75, 75, 75, 75, 75, 75, 75, 75, 10,
	11, 12, 88, 89, 75, 11, 75, 96, 58, 63,
	53, 11, 84, 52, 59, 55, 57, 55, 59, 75,
	75, 101, 75, 77, 11, 89, 57, 55, 75, 53,
	77, 75, 95, 45, 77, 8, 77, 11, 77, 58,
	77, 53, 75, 11, 12, 88, 11, 83, 75, 77,
	55, 77, 11
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] = {
	0, 62, 63, 63, 64, 64, 64, 64, 65, 65,
	66, 66, 66, 67, 67, 68, 68, 68, 68, 69,
	69, 69, 70, 71, 72, 73, 74, 75, 75, 75,
	75, 75, 75, 75, 75, 75, 75, 75, 75, 75,
	75, 75, 75, 75, 76, 76, 77, 77, 77, 78,
	78, 78, 78, 78, 78, 78, 79, 79, 80, 80,
	81, 81, 82, 82, 83, 83, 83, 83, 83, 83,
	83, 83, 83, 83, 84, 84, 84, 85, 86, 87,
	87, 87, 87, 88, 88, 89, 89, 89, 90, 90,
	90, 91, 92, 93, 94, 95, 95, 95, 96, 96,
	96, 97, 98, 98, 98, 99, 100, 100, 100, 101,
	101
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] = {
	0, 2, 1, 1, 1, 1, 1, 1, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 2, 3, 3, 5, 3, 3, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 0, 1, 2, 1, 2, 1,
	1, 1, 1, 1, 1, 1, 2, 2, 1, 1,
	3, 4, 2, 2, 3, 3, 6, 3, 3, 3,
	3, 3, 3, 1, 2, 1, 1, 4, 3, 4,
	6, 5, 4, 1, 2, 3, 5, 4, 4, 4,
	10, 2, 7, 6, 4, 0, 1, 3, 0, 1,
	3, 3, 0, 1, 3, 3, 0, 1, 3, 0,
	3
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
#define YYLLOC_DEFAULT(Current, Rhs, N)                                \
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

#ifndef YYFPRINTF
#include <stdio.h>				/* INFRINGES ON USER NAME SPACE */
#define YYFPRINTF fprintf
#endif

#define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
	static unsigned yy_location_print_(FILE * yyo, YYLTYPE const *const yylocp) 
{
	unsigned res = 0;
	int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
	if (0 <= yylocp->first_line) {
		res += YYFPRINTF(yyo, "%d", yylocp->first_line);
		if (0 <= yylocp->first_column)
			res += YYFPRINTF(yyo, ".%d", yylocp->first_column);
	}
	if (0 <= yylocp->last_line) {
		if (yylocp->first_line < yylocp->last_line) {
			res += YYFPRINTF(yyo, "-%d", yylocp->last_line);
			if (0 <= end_col)
				res += YYFPRINTF(yyo, ".%d", end_col);
		} else if (0 <= end_col && yylocp->first_column < end_col)
			res += YYFPRINTF(yyo, "-%d", end_col);
	}
	return res;
}

#define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

#else
#define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif
#endif

#define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
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
yy_symbol_value_print(FILE * yyoutput, int yytype,
					  YYSTYPE const *const yyvaluep,
					  YYLTYPE const *const yylocationp, ast ** root,
					  void *scanner) {
	FILE *yyo = yyoutput;
	YYUSE(yyo);
	YYUSE(yylocationp);
	YYUSE(root);
	YYUSE(scanner);
	if (!yyvaluep)
		return;
#ifdef YYPRINT
	if (yytype < YYNTOKENS)
		YYPRINT(yyoutput, yytoknum[yytype], *yyvaluep);
#endif
	YYUSE(yytype);
}

/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print(FILE * yyoutput, int yytype, YYSTYPE const *const yyvaluep,
				YYLTYPE const *const yylocationp, ast ** root, void *scanner) {
	YYFPRINTF(yyoutput, "%s %s (",
			  yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

	YY_LOCATION_PRINT(yyoutput, *yylocationp);
	YYFPRINTF(yyoutput, ": ");
	yy_symbol_value_print(yyoutput, yytype, yyvaluep, yylocationp, root,
						  scanner);
	YYFPRINTF(yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void yy_stack_print(yytype_int16 * yybottom, yytype_int16 * yytop) {
	YYFPRINTF(stderr, "Stack now");
	for (; yybottom <= yytop; yybottom++) {
		int yybot = *yybottom;
		YYFPRINTF(stderr, " %d", yybot);
	}
	YYFPRINTF(stderr, "\n");
}

#define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)

/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print(yytype_int16 * yyssp, YYSTYPE * yyvsp, YYLTYPE * yylsp,
				int yyrule, ast ** root, void *scanner) {
	unsigned long int yylno = yyrline[yyrule];
	int yynrhs = yyr2[yyrule];
	int yyi;
	YYFPRINTF(stderr, "Reducing stack by rule %d (line %lu):\n",
			  yyrule - 1, yylno);
	/* The symbols being reduced.  */
	for (yyi = 0; yyi < yynrhs; yyi++) {
		YYFPRINTF(stderr, "   $%d = ", yyi + 1);
		yy_symbol_print(stderr,
						yystos[yyssp[yyi + 1 - yynrhs]],
						&(yyvsp[(yyi + 1) - (yynrhs)])
						, &(yylsp[(yyi + 1) - (yynrhs)]), root, scanner);
		YYFPRINTF(stderr, "\n");
	}
}

#define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, root, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
#define YYDPRINTF(Args)
#define YY_SYMBOL_PRINT(Title, Type, Value, Location)
#define YY_STACK_PRINT(Bottom, Top)
#define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
#define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

#if YYERROR_VERBOSE

#ifndef yystrlen
#if defined __GLIBC__ && defined _STRING_H
#define yystrlen strlen
#else
/* Return the length of YYSTR.  */
static YYSIZE_T yystrlen(const char *yystr) {
	YYSIZE_T yylen;
	for (yylen = 0; yystr[yylen]; yylen++)
		continue;
	return yylen;
}
#endif
#endif

#ifndef yystpcpy
#if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#define yystpcpy stpcpy
#else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *yystpcpy(char *yydest, const char *yysrc) {
	char *yyd = yydest;
	const char *yys = yysrc;

	while ((*yyd++ = *yys++) != '\0')
		continue;

	return yyd - 1;
}
#endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T yytnamerr(char *yyres, const char *yystr) {
	if (*yystr == '"') {
		YYSIZE_T yyn = 0;
		char const *yyp = yystr;

		for (;;)
			switch (*++yyp) {
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
do_not_strip_quotes:;
	}

	if (!yyres)
		return yystrlen(yystr);

	return yystpcpy(yyres, yystr) - yyres;
}
#endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error(YYSIZE_T * yymsg_alloc, char **yymsg,
			   yytype_int16 * yyssp, int yytoken) {
	YYSIZE_T yysize0 = yytnamerr(YY_NULLPTR, yytname[yytoken]);
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
	if (yytoken != YYEMPTY) {
		int yyn = yypact[*yyssp];
		yyarg[yycount++] = yytname[yytoken];
		if (!yypact_value_is_default(yyn)) {
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
					&& !yytable_value_is_error(yytable[yyx + yyn])) {
					if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM) {
						yycount = 1;
						yysize = yysize0;
						break;
					}
					yyarg[yycount++] = yytname[yyx];
					{
						YYSIZE_T yysize1 = yysize + yytnamerr(YY_NULLPTR,
															  yytname[yyx]);
						if (!
							(yysize <= yysize1
							 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
							return 2;
						yysize = yysize1;
					}
				}
		}
	}

	switch (yycount) {
#define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
		YYCASE_(0, YY_("syntax error"));
		YYCASE_(1, YY_("syntax error, unexpected %s"));
		YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
		YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
		YYCASE_(4,
				YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
		YYCASE_(5,
				YY_
				("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
	}

	{
		YYSIZE_T yysize1 = yysize + yystrlen(yyformat);
		if (!(yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
			return 2;
		yysize = yysize1;
	}

	if (*yymsg_alloc < yysize) {
		*yymsg_alloc = 2 * yysize;
		if (!(yysize <= *yymsg_alloc && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
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
			if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount) {
				yyp += yytnamerr(yyp, yyarg[yyi++]);
				yyformat += 2;
			} else {
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
yydestruct(const char *yymsg, int yytype, YYSTYPE * yyvaluep,
		   YYLTYPE * yylocationp, ast ** root, void *scanner) {
	YYUSE(yyvaluep);
	YYUSE(yylocationp);
	YYUSE(root);
	YYUSE(scanner);
	if (!yymsg)
		yymsg = "Deleting";
	YY_SYMBOL_PRINT(yymsg, yytype, yyvaluep, yylocationp);

	YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN YYUSE(yytype);
YY_IGNORE_MAYBE_UNINITIALIZED_END}

/*----------.
| yyparse.  |
`----------*/

int yyparse(ast ** root, void *scanner) {
/* The lookahead symbol.  */
	int yychar;

/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
	YY_INITIAL_VALUE(static YYSTYPE yyval_default;
		)
	YYSTYPE yylval YY_INITIAL_VALUE( = yyval_default);

/* Location data for the lookahead symbol.  */
	static YYLTYPE yyloc_default
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
	= { 1, 1, 1, 1 }
#endif
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

	YYDPRINTF((stderr, "Starting parse\n"));

	yystate = 0;
	yyerrstatus = 0;
	yynerrs = 0;
	yychar = YYEMPTY;			/* Cause a token to be read.  */
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

	if (yyss + yystacksize - 1 <= yyssp) {
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
			yyoverflow(YY_("memory exhausted"),
					   &yyss1, yysize * sizeof(*yyssp),
					   &yyvs1, yysize * sizeof(*yyvsp),
					   &yyls1, yysize * sizeof(*yylsp), &yystacksize);

			yyls = yyls1;
			yyss = yyss1;
			yyvs = yyvs1;
		}
#else /* no yyoverflow */
#ifndef YYSTACK_RELOCATE
		goto yyexhaustedlab;
#else
		/* Extend the stack our own way.  */
		if (YYMAXDEPTH <= yystacksize)
			goto yyexhaustedlab;
		yystacksize *= 2;
		if (YYMAXDEPTH < yystacksize)
			yystacksize = YYMAXDEPTH;

		{
			yytype_int16 *yyss1 = yyss;
			union yyalloc *yyptr = (union yyalloc *)
				YYSTACK_ALLOC(YYSTACK_BYTES(yystacksize));
			if (!yyptr)
				goto yyexhaustedlab;
			YYSTACK_RELOCATE(yyss_alloc, yyss);
			YYSTACK_RELOCATE(yyvs_alloc, yyvs);
			YYSTACK_RELOCATE(yyls_alloc, yyls);
#undef YYSTACK_RELOCATE
			if (yyss1 != yyssa)
				YYSTACK_FREE(yyss1);
		}
#endif
#endif /* no yyoverflow */

		yyssp = yyss + yysize - 1;
		yyvsp = yyvs + yysize - 1;
		yylsp = yyls + yysize - 1;

		YYDPRINTF((stderr, "Stack size increased to %lu\n",
				   (unsigned long int)yystacksize));

		if (yyss + yystacksize - 1 <= yyssp)
			YYABORT;
	}

	YYDPRINTF((stderr, "Entering state %d\n", yystate));

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
	if (yypact_value_is_default(yyn))
		goto yydefault;

	/* Not known => get a lookahead token if don't already have one.  */

	/* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
	if (yychar == YYEMPTY) {
		YYDPRINTF((stderr, "Reading a token: "));
		yychar = yylex(&yylval, &yylloc, scanner);
	}

	if (yychar <= YYEOF) {
		yychar = yytoken = YYEOF;
		YYDPRINTF((stderr, "Now at end of input.\n"));
	} else {
		yytoken = YYTRANSLATE(yychar);
		YY_SYMBOL_PRINT("Next token is", yytoken, &yylval, &yylloc);
	}

	/* If the proper action on seeing token YYTOKEN is to reduce or to
	   detect an error, take that action.  */
	yyn += yytoken;
	if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
		goto yydefault;
	yyn = yytable[yyn];
	if (yyn <= 0) {
		if (yytable_value_is_error(yyn))
			goto yyerrlab;
		yyn = -yyn;
		goto yyreduce;
	}

	/* Count tokens shifted since error; after three, turn off error
	   status.  */
	if (yyerrstatus)
		yyerrstatus--;

	/* Shift the lookahead token.  */
	YY_SYMBOL_PRINT("Shifting", yytoken, &yylval, &yylloc);

	/* Discard the shifted token.  */
	yychar = YYEMPTY;

	yystate = yyn;
	YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN *++yyvsp = yylval;
	YY_IGNORE_MAYBE_UNINITIALIZED_END *++yylsp = yylloc;
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
	yyval = yyvsp[1 - yylen];

	/* Default location.  */
	YYLLOC_DEFAULT(yyloc, (yylsp - yylen), yylen);
	YY_REDUCE_PRINT(yyn);
	switch (yyn) {
	case 8:
#line 150 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_reducir_constantes(NODO_MENOS_UNARIO,
									   (yyvsp[0].node), NULL);
			if ((yyval.node) == NULL)
				YYABORT;
		}
#line 1694 "latparse.c"			/* yacc.c:1646  */
		break;

	case 9:
#line 154 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_reducir_constantes(NODO_MAS_UNARIO, (yyvsp[0].node), NULL);
			if ((yyval.node) == NULL)
				YYABORT;
		}
#line 1703 "latparse.c"			/* yacc.c:1646  */
		break;

	case 10:
#line 161 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_reducir_constantes(NODO_MULTIPLICACION,
									   (yyvsp[-2].node), (yyvsp[0].node));
			if ((yyval.node) == NULL)
				YYABORT;
		}
#line 1712 "latparse.c"			/* yacc.c:1646  */
		break;

	case 11:
#line 165 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_reducir_constantes(NODO_DIVISION,
									   (yyvsp[-2].node), (yyvsp[0].node));
			if ((yyval.node) == NULL)
				YYABORT;
		}
#line 1721 "latparse.c"			/* yacc.c:1646  */
		break;

	case 12:
#line 169 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_reducir_constantes(NODO_MODULO,
									   (yyvsp[-2].node), (yyvsp[0].node));
			if ((yyval.node) == NULL)
				YYABORT;
		}
#line 1730 "latparse.c"			/* yacc.c:1646  */
		break;

	case 13:
#line 176 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_reducir_constantes(NODO_RESTA, (yyvsp[-2].node),
									   (yyvsp[0].node));
			if ((yyval.node) == NULL)
				YYABORT;
		}
#line 1739 "latparse.c"			/* yacc.c:1646  */
		break;

	case 14:
#line 180 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_reducir_constantes(NODO_SUMA, (yyvsp[-2].node),
									   (yyvsp[0].node));
			if ((yyval.node) == NULL)
				YYABORT;
		}
#line 1748 "latparse.c"			/* yacc.c:1646  */
		break;

	case 15:
#line 187 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo(NODO_MAYOR_QUE, (yyvsp[-2].node), (yyvsp[0].node));
		}
#line 1754 "latparse.c"			/* yacc.c:1646  */
		break;

	case 16:
#line 188 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo(NODO_MENOR_QUE, (yyvsp[-2].node), (yyvsp[0].node));
		}
#line 1760 "latparse.c"			/* yacc.c:1646  */
		break;

	case 17:
#line 189 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo(NODO_MAYOR_IGUAL, (yyvsp[-2].node), (yyvsp[0].node));
		}
#line 1766 "latparse.c"			/* yacc.c:1646  */
		break;

	case 18:
#line 190 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo(NODO_MENOR_IGUAL, (yyvsp[-2].node), (yyvsp[0].node));
		}
#line 1772 "latparse.c"			/* yacc.c:1646  */
		break;

	case 19:
#line 194 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo(NODO_DESIGUALDAD, (yyvsp[-2].node), (yyvsp[0].node));
		}
#line 1778 "latparse.c"			/* yacc.c:1646  */
		break;

	case 20:
#line 195 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo(NODO_IGUALDAD, (yyvsp[-2].node), (yyvsp[0].node));
		}
#line 1784 "latparse.c"			/* yacc.c:1646  */
		break;

	case 21:
#line 196 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo(NODO_REGEX, (yyvsp[-2].node), (yyvsp[0].node));
		}
#line 1790 "latparse.c"			/* yacc.c:1646  */
		break;

	case 22:
#line 200 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) = ast_nuevo(NODO_NO, (yyvsp[0].node), NULL);
		}
#line 1796 "latparse.c"			/* yacc.c:1646  */
		break;

	case 23:
#line 204 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) = ast_nuevo(NODO_Y, (yyvsp[-2].node), (yyvsp[0].node));
		}
#line 1802 "latparse.c"			/* yacc.c:1646  */
		break;

	case 24:
#line 208 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) = ast_nuevo(NODO_O, (yyvsp[-2].node), (yyvsp[0].node));
		}
#line 1808 "latparse.c"			/* yacc.c:1646  */
		break;

	case 25:
#line 212 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo_si((yyvsp[-4].node), (yyvsp[-2].node),
							 (yyvsp[0].node));
		}
#line 1814 "latparse.c"			/* yacc.c:1646  */
		break;

	case 26:
#line 216 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo(NODO_CONCATENAR, (yyvsp[-2].node), (yyvsp[0].node));
		}
#line 1820 "latparse.c"			/* yacc.c:1646  */
		break;

	case 27:
#line 220 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) = (yyvsp[-1].node);
		}
#line 1826 "latparse.c"			/* yacc.c:1646  */
		break;

	case 44:
#line 240 "latparse.y"			/* yacc.c:1646  */
		{						/* empty */
			*root = NULL;
		}
#line 1834 "latparse.c"			/* yacc.c:1646  */
		break;

	case 45:
#line 243 "latparse.y"			/* yacc.c:1646  */
		{
			*root = (yyvsp[0].node);
		}
#line 1840 "latparse.c"			/* yacc.c:1646  */
		break;

	case 46:
#line 247 "latparse.y"			/* yacc.c:1646  */
		{
			if ((yyvsp[0].node)) {
				(yyval.node) =
					ast_nuevo(NODO_BLOQUE, (yyvsp[-1].node), (yyvsp[0].node));
			}
		}
#line 1850 "latparse.c"			/* yacc.c:1646  */
		break;

	case 47:
#line 252 "latparse.y"			/* yacc.c:1646  */
		{
			if ((yyvsp[0].node)) {
				(yyval.node) = ast_nuevo(NODO_BLOQUE, (yyvsp[0].node), NULL);
			}
		}
#line 1860 "latparse.c"			/* yacc.c:1646  */
		break;

	case 48:
#line 257 "latparse.y"			/* yacc.c:1646  */
		{
			yyerrok;
			yyclearin;
		}
#line 1866 "latparse.c"			/* yacc.c:1646  */
		break;

	case 56:
#line 271 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) = ast_nuevo(NODO_INC, (yyvsp[-1].node), NULL);
		}
#line 1872 "latparse.c"			/* yacc.c:1646  */
		break;

	case 57:
#line 272 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) = ast_nuevo(NODO_DEC, (yyvsp[-1].node), NULL);
		}
#line 1878 "latparse.c"			/* yacc.c:1646  */
		break;

	case 60:
#line 281 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo(NODO_ATRIBUTO, (yyvsp[-2].node), (yyvsp[0].node));
		}
#line 1884 "latparse.c"			/* yacc.c:1646  */
		break;

	case 61:
#line 282 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo(NODO_LISTA_OBTENER_ELEMENTO,
						  (yyvsp[-1].node), (yyvsp[-3].node));
		}
#line 1890 "latparse.c"			/* yacc.c:1646  */
		break;

	case 62:
#line 286 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) = ast_nuevo(NODO_GLOBAL, (yyvsp[0].node), NULL);
		}
#line 1898 "latparse.c"			/* yacc.c:1646  */
		break;

	case 63:
#line 289 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) = ast_nuevo(NODO_GLOBAL, (yyvsp[0].node), NULL);
		}
#line 1906 "latparse.c"			/* yacc.c:1646  */
		break;

	case 64:
#line 296 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo_asignacion((yyvsp[0].node), (yyvsp[-2].node));
		}
#line 1912 "latparse.c"			/* yacc.c:1646  */
		break;

	case 65:
#line 297 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo_asignacion((yyvsp[0].node), (yyvsp[-2].node));
		}
#line 1918 "latparse.c"			/* yacc.c:1646  */
		break;

	case 66:
#line 298 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo_asignacion_lista_elem((yyvsp[0].node),
												(yyvsp[-5].node),
												(yyvsp[-3].node));
		}
#line 1924 "latparse.c"			/* yacc.c:1646  */
		break;

	case 67:
#line 299 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo_asignacion((ast_nuevo
									  (NODO_CONCATENAR,
									   (yyvsp[-2].node),
									   (yyvsp[0].node))), (yyvsp[-2].node));
		}
#line 1930 "latparse.c"			/* yacc.c:1646  */
		break;

	case 68:
#line 300 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo_asignacion((ast_nuevo
									  (NODO_SUMA, (yyvsp[-2].node),
									   (yyvsp[0].node))), (yyvsp[-2].node));
		}
#line 1936 "latparse.c"			/* yacc.c:1646  */
		break;

	case 69:
#line 301 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo_asignacion((ast_nuevo
									  (NODO_RESTA, (yyvsp[-2].node),
									   (yyvsp[0].node))), (yyvsp[-2].node));
		}
#line 1942 "latparse.c"			/* yacc.c:1646  */
		break;

	case 70:
#line 302 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo_asignacion((ast_nuevo
									  (NODO_MULTIPLICACION,
									   (yyvsp[-2].node),
									   (yyvsp[0].node))), (yyvsp[-2].node));
		}
#line 1948 "latparse.c"			/* yacc.c:1646  */
		break;

	case 71:
#line 303 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo_asignacion((ast_nuevo
									  (NODO_DIVISION,
									   (yyvsp[-2].node),
									   (yyvsp[0].node))), (yyvsp[-2].node));
		}
#line 1954 "latparse.c"			/* yacc.c:1646  */
		break;

	case 72:
#line 304 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo_asignacion((ast_nuevo
									  (NODO_MODULO,
									   (yyvsp[-2].node),
									   (yyvsp[0].node))), (yyvsp[-2].node));
		}
#line 1960 "latparse.c"			/* yacc.c:1646  */
		break;

	case 74:
#line 309 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo(NODO_CASOS, (yyvsp[-1].node), (yyvsp[0].node));
		}
#line 1968 "latparse.c"			/* yacc.c:1646  */
		break;

	case 75:
#line 312 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) = ast_nuevo(NODO_CASOS, (yyvsp[0].node), NULL);
		}
#line 1976 "latparse.c"			/* yacc.c:1646  */
		break;

	case 76:
#line 315 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) = ast_nuevo(NODO_CASOS, (yyvsp[0].node), NULL);
		}
#line 1984 "latparse.c"			/* yacc.c:1646  */
		break;

	case 77:
#line 322 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo(NODO_CASO, (yyvsp[-2].node), (yyvsp[0].node));
		}
#line 1992 "latparse.c"			/* yacc.c:1646  */
		break;

	case 78:
#line 329 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) = ast_nuevo(NODO_DEFECTO, NULL, (yyvsp[0].node));
		}
#line 2000 "latparse.c"			/* yacc.c:1646  */
		break;

	case 79:
#line 335 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo_si((yyvsp[-2].node), (yyvsp[-1].node), NULL);
		}
#line 2007 "latparse.c"			/* yacc.c:1646  */
		break;

	case 80:
#line 337 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo_si((yyvsp[-4].node), (yyvsp[-3].node),
							 (yyvsp[-1].node));
		}
#line 2014 "latparse.c"			/* yacc.c:1646  */
		break;

	case 81:
#line 339 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo_si((yyvsp[-3].node), (yyvsp[-2].node),
							 (yyvsp[-1].node));
		}
#line 2021 "latparse.c"			/* yacc.c:1646  */
		break;

	case 82:
#line 341 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo(NODO_ELEGIR, (yyvsp[-2].node), (yyvsp[-1].node));
		}
#line 2029 "latparse.c"			/* yacc.c:1646  */
		break;

	case 85:
#line 352 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo_si((yyvsp[-1].node), (yyvsp[0].node), NULL);
		}
#line 2037 "latparse.c"			/* yacc.c:1646  */
		break;

	case 86:
#line 355 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo_si((yyvsp[-3].node), (yyvsp[-2].node),
							 (yyvsp[0].node));
		}
#line 2045 "latparse.c"			/* yacc.c:1646  */
		break;

	case 87:
#line 358 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo_si((yyvsp[-2].node), (yyvsp[-1].node),
							 (yyvsp[0].node));
		}
#line 2053 "latparse.c"			/* yacc.c:1646  */
		break;

	case 88:
#line 364 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo_mientras((yyvsp[-2].node), (yyvsp[-1].node));
		}
#line 2060 "latparse.c"			/* yacc.c:1646  */
		break;

	case 89:
#line 366 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) = ast_nuevo_hacer((yyvsp[0].node), (yyvsp[-2].node));
		}
#line 2067 "latparse.c"			/* yacc.c:1646  */
		break;

	case 90:
#line 369 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo_desde((yyvsp[-7].node), (yyvsp[-5].node),
								(yyvsp[-3].node), (yyvsp[-1].node));
		}
#line 2074 "latparse.c"			/* yacc.c:1646  */
		break;

	case 91:
#line 374 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) = ast_nuevo(NODO_RETORNO, (yyvsp[0].node), NULL);
		}
#line 2080 "latparse.c"			/* yacc.c:1646  */
		break;

	case 92:
#line 378 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo_funcion((yyvsp[-5].node),
								  (yyvsp[-3].node), (yyvsp[-1].node));
		}
#line 2088 "latparse.c"			/* yacc.c:1646  */
		break;

	case 93:
#line 384 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo_funcion(ast_nuevo_identificador
								  ("anonima",
								   (yylsp[-5]).first_line,
								   (yylsp[-5]).first_column, false),
								  (yyvsp[-3].node), (yyvsp[-1].node));
		}
#line 2096 "latparse.c"			/* yacc.c:1646  */
		break;

	case 94:
#line 390 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo(NODO_FUNCION_LLAMADA, (yyvsp[-3].node),
						  (yyvsp[-1].node));
		}
#line 2102 "latparse.c"			/* yacc.c:1646  */
		break;

	case 95:
#line 394 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) = NULL;
		}
#line 2108 "latparse.c"			/* yacc.c:1646  */
		break;

	case 96:
#line 395 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo(NODO_FUNCION_ARGUMENTOS, (yyvsp[0].node), NULL);
		}
#line 2114 "latparse.c"			/* yacc.c:1646  */
		break;

	case 97:
#line 396 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo(NODO_FUNCION_ARGUMENTOS, (yyvsp[-2].node),
						  (yyvsp[0].node));
		}
#line 2120 "latparse.c"			/* yacc.c:1646  */
		break;

	case 98:
#line 400 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) = NULL;
		}
#line 2126 "latparse.c"			/* yacc.c:1646  */
		break;

	case 99:
#line 401 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo(NODO_FUNCION_PARAMETROS, (yyvsp[0].node), NULL);
		}
#line 2132 "latparse.c"			/* yacc.c:1646  */
		break;

	case 100:
#line 402 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo(NODO_FUNCION_PARAMETROS, (yyvsp[0].node),
						  (yyvsp[-2].node));
		}
#line 2138 "latparse.c"			/* yacc.c:1646  */
		break;

	case 101:
#line 406 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) = ast_nuevo(NODO_LISTA, (yyvsp[-1].node), NULL);
		}
#line 2144 "latparse.c"			/* yacc.c:1646  */
		break;

	case 102:
#line 410 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) = NULL;
		}
#line 2150 "latparse.c"			/* yacc.c:1646  */
		break;

	case 103:
#line 411 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo(NODO_LISTA_AGREGAR_ELEMENTO, (yyvsp[0].node), NULL);
		}
#line 2156 "latparse.c"			/* yacc.c:1646  */
		break;

	case 104:
#line 412 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo(NODO_LISTA_AGREGAR_ELEMENTO,
						  (yyvsp[0].node), (yyvsp[-2].node));
		}
#line 2162 "latparse.c"			/* yacc.c:1646  */
		break;

	case 105:
#line 416 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) = ast_nuevo(NODO_DICCIONARIO, (yyvsp[-1].node), NULL);
		}
#line 2168 "latparse.c"			/* yacc.c:1646  */
		break;

	case 106:
#line 420 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) = NULL;
		}
#line 2174 "latparse.c"			/* yacc.c:1646  */
		break;

	case 107:
#line 421 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo(NODO_DICC_AGREGAR_ELEMENTO, (yyvsp[0].node), NULL);
		}
#line 2180 "latparse.c"			/* yacc.c:1646  */
		break;

	case 108:
#line 422 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo(NODO_DICC_AGREGAR_ELEMENTO,
						  (yyvsp[0].node), (yyvsp[-2].node));
		}
#line 2186 "latparse.c"			/* yacc.c:1646  */
		break;

	case 109:
#line 426 "latparse.y"			/* yacc.c:1646  */
		{						/* empty */
			(yyval.node) = NULL;
		}
#line 2192 "latparse.c"			/* yacc.c:1646  */
		break;

	case 110:
#line 427 "latparse.y"			/* yacc.c:1646  */
		{
			(yyval.node) =
				ast_nuevo(NODO_DICC_ELEMENTO, (yyvsp[-2].node),
						  (yyvsp[0].node));
		}
#line 2198 "latparse.c"			/* yacc.c:1646  */
		break;

#line 2202 "latparse.c"			/* yacc.c:1646  */
	default:
		break;
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
	YY_SYMBOL_PRINT("-> $$ =", yyr1[yyn], &yyval, &yyloc);

	YYPOPSTACK(yylen);
	yylen = 0;
	YY_STACK_PRINT(yyss, yyssp);

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
	yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE(yychar);

	/* If not already recovering from an error, report this error.  */
	if (!yyerrstatus) {
		++yynerrs;
#if ! YYERROR_VERBOSE
		yyerror(&yylloc, root, scanner, YY_("syntax error"));
#else
#define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
		{
			char const *yymsgp = YY_("syntax error");
			int yysyntax_error_status;
			yysyntax_error_status = YYSYNTAX_ERROR;
			if (yysyntax_error_status == 0)
				yymsgp = yymsg;
			else if (yysyntax_error_status == 1) {
				if (yymsg != yymsgbuf)
					YYSTACK_FREE(yymsg);
				yymsg = (char *)YYSTACK_ALLOC(yymsg_alloc);
				if (!yymsg) {
					yymsg = yymsgbuf;
					yymsg_alloc = sizeof yymsgbuf;
					yysyntax_error_status = 2;
				} else {
					yysyntax_error_status = YYSYNTAX_ERROR;
					yymsgp = yymsg;
				}
			}
			yyerror(&yylloc, root, scanner, yymsgp);
			if (yysyntax_error_status == 2)
				goto yyexhaustedlab;
		}
#undef YYSYNTAX_ERROR
#endif
	}

	yyerror_range[1] = yylloc;

	if (yyerrstatus == 3) {
		/* If just tried and failed to reuse lookahead token after an
		   error, discard it.  */

		if (yychar <= YYEOF) {
			/* Return failure if at end of input.  */
			if (yychar == YYEOF)
				YYABORT;
		} else {
			yydestruct("Error: discarding",
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
	if ( /*CONSTCOND*/ 0)
		goto yyerrorlab;

	yyerror_range[1] = yylsp[1 - yylen];
	/* Do not reclaim the symbols of the rule whose action triggered
	   this YYERROR.  */
	YYPOPSTACK(yylen);
	yylen = 0;
	YY_STACK_PRINT(yyss, yyssp);
	yystate = *yyssp;
	goto yyerrlab1;

/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
	yyerrstatus = 3;			/* Each real token shifted decrements this.  */

	for (;;) {
		yyn = yypact[yystate];
		if (!yypact_value_is_default(yyn)) {
			yyn += YYTERROR;
			if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR) {
				yyn = yytable[yyn];
				if (0 < yyn)
					break;
			}
		}

		/* Pop the current state because it cannot handle the error token.  */
		if (yyssp == yyss)
			YYABORT;

		yyerror_range[1] = *yylsp;
		yydestruct("Error: popping",
				   yystos[yystate], yyvsp, yylsp, root, scanner);
		YYPOPSTACK(1);
		yystate = *yyssp;
		YY_STACK_PRINT(yyss, yyssp);
	}

	YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN *++yyvsp = yylval;
	YY_IGNORE_MAYBE_UNINITIALIZED_END yyerror_range[2] = yylloc;
	/* Using YYLLOC is tempting, but would change the location of
	   the lookahead.  YYLOC is available though.  */
	YYLLOC_DEFAULT(yyloc, yyerror_range, 2);
	*++yylsp = yyloc;

	/* Shift the error token.  */
	YY_SYMBOL_PRINT("Shifting", yystos[yyn], yyvsp, yylsp);

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
	yyerror(&yylloc, root, scanner, YY_("memory exhausted"));
	yyresult = 2;
	/* Fall through.  */
#endif

yyreturn:
	if (yychar != YYEMPTY) {
		/* Make sure we have latest lookahead translation.  See comments at
		   user semantic actions for why this is necessary.  */
		yytoken = YYTRANSLATE(yychar);
		yydestruct("Cleanup: discarding lookahead",
				   yytoken, &yylval, &yylloc, root, scanner);
	}
	/* Do not reclaim the symbols of the rule whose action triggered
	   this YYABORT or YYACCEPT.  */
	YYPOPSTACK(yylen);
	YY_STACK_PRINT(yyss, yyssp);
	while (yyssp != yyss) {
		yydestruct("Cleanup: popping",
				   yystos[*yyssp], yyvsp, yylsp, root, scanner);
		YYPOPSTACK(1);
	}
#ifndef yyoverflow
	if (yyss != yyssa)
		YYSTACK_FREE(yyss);
#endif
#if YYERROR_VERBOSE
	if (yymsg != yymsgbuf)
		YYSTACK_FREE(yymsg);
#endif
	return yyresult;
}

#line 430 "latparse.y"			/* yacc.c:1906  */

//se define para analisis sintactico (bison)
int yyerror(struct YYLTYPE *yylloc_param, void *scanner, struct ast **root,
			const char *s) {
	if (!parse_silent) {
		lat_error("Linea %d, %d: %s", yylloc_param->first_line,
				  yylloc_param->first_column, s);
	}
	return 0;
}
