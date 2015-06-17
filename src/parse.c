
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "../src/parse.y"

#include "latino.h"
#include "structs.h"
#define YYERROR_VERBOSE 1


/* Line 189 of yacc.c  */
#line 80 "../src/parse.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     KEYWORD_TRUE = 258,
     KEYWORD_FALSE = 259,
     TOKEN_INT = 260,
     TOKEN_CHAR = 261,
     TOKEN_NUMBER = 262,
     TOKEN_STRING = 263,
     TOKEN_IDENTIFIER = 264,
     TOKEN_FUNC = 265,
     KEYWORD_IF = 266,
     KEYWORD_END = 267,
     KEYWORD_ELSE = 268,
     KEYWORD_WHILE = 269,
     KEYWORD_DO = 270,
     KEYWORD_SWITCH = 271,
     KEYWORD_CASE = 272,
     KEYWORD_BREAK = 273,
     KEYWORD_DEFAULT = 274,
     KEYWORD_WHEN = 275,
     KEYWORD_FUNCTION = 276,
     KEYWORD_FROM = 277,
     KEYWORD_TO = 278,
     KEYWORD_STEP = 279,
     KEYWORD_BOOL = 280,
     KEYWORD_RETURN = 281,
     OP_GT = 282,
     OP_LT = 283,
     OP_GE = 284,
     OP_LE = 285,
     OP_EQ = 286,
     OP_NEQ = 287,
     OP_AND = 288,
     OP_OR = 289,
     OP_NEG = 290,
     UNEG = 291,
     UMINUS = 292
   };
#endif
/* Tokens.  */
#define KEYWORD_TRUE 258
#define KEYWORD_FALSE 259
#define TOKEN_INT 260
#define TOKEN_CHAR 261
#define TOKEN_NUMBER 262
#define TOKEN_STRING 263
#define TOKEN_IDENTIFIER 264
#define TOKEN_FUNC 265
#define KEYWORD_IF 266
#define KEYWORD_END 267
#define KEYWORD_ELSE 268
#define KEYWORD_WHILE 269
#define KEYWORD_DO 270
#define KEYWORD_SWITCH 271
#define KEYWORD_CASE 272
#define KEYWORD_BREAK 273
#define KEYWORD_DEFAULT 274
#define KEYWORD_WHEN 275
#define KEYWORD_FUNCTION 276
#define KEYWORD_FROM 277
#define KEYWORD_TO 278
#define KEYWORD_STEP 279
#define KEYWORD_BOOL 280
#define KEYWORD_RETURN 281
#define OP_GT 282
#define OP_LT 283
#define OP_GE 284
#define OP_LE 285
#define OP_EQ 286
#define OP_NEQ 287
#define OP_AND 288
#define OP_OR 289
#define OP_NEG 290
#define UNEG 291
#define UMINUS 292




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 8 "../src/parse.y"

    int fn; /* which function */
    char *b; /* boolean type*/
    char *c; /* char type */
    int i;  /* int type */
    double d; /* double type */
    struct lat_string *str; /* string type */
    struct ast *a; /* astract syntax tree */
    struct symbol *s;   /* which symbol */
    struct symlist *sl; /* symbol list */



/* Line 214 of yacc.c  */
#line 204 "../src/parse.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 216 "../src/parse.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   347

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNRULES -- Number of states.  */
#define YYNSTATES  128

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    41,     2,     2,
      44,    45,    39,    37,    47,    38,     2,    40,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    46,     2,
       2,    36,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    42,    43
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     7,    14,    23,    30,    37,    44,
      52,    59,    69,    77,    79,    81,    83,    86,    89,    92,
      94,    99,   103,   104,   107,   111,   115,   119,   123,   127,
     131,   135,   139,   142,   146,   150,   154,   158,   162,   166,
     169,   171,   173,   177,   182,   187,   189,   191,   193,   195,
     197,   199,   201,   203,   204,   206,   210,   211,   213
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      49,     0,    -1,    -1,    49,    50,    -1,    11,    44,    56,
      45,    55,    12,    -1,    11,    44,    56,    45,    55,    13,
      55,    12,    -1,    14,    44,    56,    45,    55,    12,    -1,
      15,    55,    20,    44,    56,    45,    -1,    16,    44,    59,
      45,    52,    12,    -1,    16,    44,    59,    45,    52,    54,
      12,    -1,    22,    56,    23,    56,    55,    12,    -1,    22,
      56,    23,    56,    24,    36,    59,    55,    12,    -1,    21,
       9,    44,    62,    45,    55,    12,    -1,    57,    -1,    58,
      -1,    51,    -1,    26,    56,    -1,    26,    58,    -1,    52,
      53,    -1,    53,    -1,    17,    60,    46,    55,    -1,    19,
      46,    55,    -1,    -1,    50,    55,    -1,    56,    27,    56,
      -1,    56,    28,    56,    -1,    56,    29,    56,    -1,    56,
      30,    56,    -1,    56,    32,    56,    -1,    56,    31,    56,
      -1,    56,    33,    56,    -1,    56,    34,    56,    -1,    35,
      56,    -1,    56,    37,    56,    -1,    56,    38,    56,    -1,
      56,    39,    56,    -1,    56,    40,    56,    -1,    56,    41,
      56,    -1,    44,    56,    45,    -1,    38,    56,    -1,    59,
      -1,    58,    -1,     9,    36,    56,    -1,     9,    44,    61,
      45,    -1,    10,    44,    61,    45,    -1,     9,    -1,     3,
      -1,     4,    -1,    60,    -1,     5,    -1,     7,    -1,     6,
      -1,     8,    -1,    -1,    56,    -1,    56,    47,    61,    -1,
      -1,     9,    -1,     9,    47,    62,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    78,    78,    79,    88,    90,    92,    94,    96,    98,
     100,   102,   104,   108,   109,   110,   113,   114,   118,   122,
     128,   135,   141,   142,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   170,   174,   175,   179,   180,   181,   182,   186,
     187,   188,   189,   192,   193,   194,   197,   198,   199
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KEYWORD_TRUE", "KEYWORD_FALSE",
  "TOKEN_INT", "TOKEN_CHAR", "TOKEN_NUMBER", "TOKEN_STRING",
  "TOKEN_IDENTIFIER", "TOKEN_FUNC", "KEYWORD_IF", "KEYWORD_END",
  "KEYWORD_ELSE", "KEYWORD_WHILE", "KEYWORD_DO", "KEYWORD_SWITCH",
  "KEYWORD_CASE", "KEYWORD_BREAK", "KEYWORD_DEFAULT", "KEYWORD_WHEN",
  "KEYWORD_FUNCTION", "KEYWORD_FROM", "KEYWORD_TO", "KEYWORD_STEP",
  "KEYWORD_BOOL", "KEYWORD_RETURN", "OP_GT", "OP_LT", "OP_GE", "OP_LE",
  "OP_EQ", "OP_NEQ", "OP_AND", "OP_OR", "OP_NEG", "'='", "'+'", "'-'",
  "'*'", "'/'", "'%'", "UNEG", "UMINUS", "'('", "')'", "':'", "','",
  "$accept", "program", "stmt", "jump_stmt", "cases", "case", "default",
  "list", "exp", "var", "callfunc", "value", "atom_value", "explist",
  "symlist", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,    61,    43,    45,    42,
      47,    37,   291,   292,    40,    41,    58,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    49,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    51,    51,    52,    52,
      53,    54,    55,    55,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    57,    58,    58,    59,    59,    59,    59,    60,
      60,    60,    60,    61,    61,    61,    62,    62,    62
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     6,     8,     6,     6,     6,     7,
       6,     9,     7,     1,     1,     1,     2,     2,     2,     1,
       4,     3,     0,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     3,     3,     3,     3,     3,     3,     2,
       1,     1,     3,     4,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     1,     3,     0,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,    22,     0,     0,
       0,     0,     3,    15,    13,    14,     0,    53,    53,     0,
       0,    22,     0,     0,     0,    46,    47,    49,    51,    50,
      52,    45,     0,     0,     0,     0,    41,    40,    48,    16,
      17,    42,    54,     0,     0,     0,     0,    23,     0,    45,
       0,    56,    32,    39,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    53,
      43,    44,    22,    22,     0,     0,    57,     0,    38,    22,
      24,    25,    26,    27,    29,    28,    30,    31,    33,    34,
      35,    36,    37,    55,     0,     0,     0,     0,     0,    19,
      56,    22,     0,     0,     4,    22,     6,     7,     0,     8,
       0,    18,     0,    58,     0,     0,    10,     0,    22,    22,
       9,    12,    22,     5,    20,    21,     0,    11
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    21,    13,    98,    99,   112,    22,    42,    14,
      36,    37,    38,    43,    77
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -40
static const yytype_int16 yypact[] =
{
     -40,    22,   -40,   -32,   -39,   -35,   -33,   275,   -23,    25,
      20,    20,   -40,   -40,   -40,   -40,    20,    20,    20,    20,
      20,   275,    19,   105,    -3,   -40,   -40,   -40,   -40,   -40,
     -40,     3,    20,    20,    20,   170,   -40,   -40,   -40,   276,
     291,   276,   149,     6,    15,   185,   204,   -40,    13,   -40,
      16,    47,    12,    12,   223,    20,    20,    20,    20,    20,
      20,    20,    20,    20,    20,    20,    20,    20,    20,    20,
     -40,   -40,   275,   275,    20,    45,    18,    21,   -40,   134,
     306,   306,   306,   306,   306,   306,   276,   276,   -26,   -26,
      12,    12,    12,   -40,    37,    51,   242,    11,    23,   -40,
      47,   275,    31,    56,   -40,   275,   -40,   -40,    24,   -40,
      27,   -40,    57,   -40,    62,   105,   -40,    63,   275,   275,
     -40,   -40,   275,   -40,   -40,   -40,    64,   -40
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -40,   -40,    76,   -40,   -40,   -19,   -40,   -20,    73,   -40,
      -1,   -21,   -17,   -15,   -18
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -42
static const yytype_int8 yytable[] =
{
      15,    47,    50,    44,    16,    18,    15,    62,    63,    19,
      40,    20,    17,    66,    67,    68,    27,    28,    29,    30,
      15,    23,     2,    25,    26,    27,    28,    29,    30,    31,
       4,     3,     4,     5,    24,   109,     6,     7,     8,    48,
      97,    51,   110,     9,    10,    62,    63,    17,    11,   104,
     105,    70,    94,    95,    93,    32,    76,    74,    33,   103,
      71,    75,    97,   106,    34,   100,   101,   115,   116,   120,
     118,    15,    15,   119,   121,   123,   127,    12,    15,   111,
     108,   114,   113,    35,    39,   117,     0,     0,     0,    41,
       0,     0,    45,    46,   122,     0,     0,     0,   124,   125,
      15,     0,   126,     0,    15,    52,    53,    54,    25,    26,
      27,    28,    29,    30,    49,     0,     0,    15,    15,     0,
       0,    15,     0,     0,     0,     0,     0,     0,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,     0,     3,     4,     5,     0,    96,     6,     7,
       8,     0,     0,     0,     0,     9,    10,     0,   102,     0,
      11,    56,    57,    58,    59,    60,    61,    62,    63,     0,
       0,    64,    65,    66,    67,    68,    56,    57,    58,    59,
      60,    61,    62,    63,     0,     0,    64,    65,    66,    67,
      68,     0,     0,    55,     0,     0,    69,    56,    57,    58,
      59,    60,    61,    62,    63,     0,     0,    64,    65,    66,
      67,    68,    56,    57,    58,    59,    60,    61,    62,    63,
       0,     0,    64,    65,    66,    67,    68,     0,     0,     0,
      72,    56,    57,    58,    59,    60,    61,    62,    63,     0,
       0,    64,    65,    66,    67,    68,     0,     0,     0,    73,
      56,    57,    58,    59,    60,    61,    62,    63,     0,     0,
      64,    65,    66,    67,    68,     0,     0,     0,    78,    56,
      57,    58,    59,    60,    61,    62,    63,     0,     0,    64,
      65,    66,    67,    68,     3,     4,     5,   107,     0,     6,
       7,     8,     0,     0,     0,     0,     9,    10,     0,     0,
       0,    11,     0,    56,    57,    58,    59,    60,    61,    62,
      63,     0,     0,    64,    65,    66,    67,    68,   -41,   -41,
     -41,   -41,   -41,   -41,   -41,   -41,     0,     0,   -41,   -41,
     -41,   -41,   -41,   -42,   -42,   -42,   -42,   -42,   -42,    62,
      63,     0,     0,    64,    65,    66,    67,    68
};

static const yytype_int8 yycheck[] =
{
       1,    21,    23,    18,    36,    44,     7,    33,    34,    44,
      11,    44,    44,    39,    40,    41,     5,     6,     7,     8,
      21,    44,     0,     3,     4,     5,     6,     7,     8,     9,
      10,     9,    10,    11,     9,    12,    14,    15,    16,    20,
      17,    44,    19,    21,    22,    33,    34,    44,    26,    12,
      13,    45,    72,    73,    69,    35,     9,    44,    38,    79,
      45,    45,    17,    12,    44,    47,    45,    36,    12,    12,
      46,    72,    73,    46,    12,    12,    12,     1,    79,    98,
      97,   101,   100,    10,    11,   105,    -1,    -1,    -1,    16,
      -1,    -1,    19,    20,   115,    -1,    -1,    -1,   118,   119,
     101,    -1,   122,    -1,   105,    32,    33,    34,     3,     4,
       5,     6,     7,     8,     9,    -1,    -1,   118,   119,    -1,
      -1,   122,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    -1,     9,    10,    11,    -1,    74,    14,    15,
      16,    -1,    -1,    -1,    -1,    21,    22,    -1,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      -1,    37,    38,    39,    40,    41,    27,    28,    29,    30,
      31,    32,    33,    34,    -1,    -1,    37,    38,    39,    40,
      41,    -1,    -1,    23,    -1,    -1,    47,    27,    28,    29,
      30,    31,    32,    33,    34,    -1,    -1,    37,    38,    39,
      40,    41,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,    -1,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      45,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      -1,    37,    38,    39,    40,    41,    -1,    -1,    -1,    45,
      27,    28,    29,    30,    31,    32,    33,    34,    -1,    -1,
      37,    38,    39,    40,    41,    -1,    -1,    -1,    45,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    -1,    37,
      38,    39,    40,    41,     9,    10,    11,    45,    -1,    14,
      15,    16,    -1,    -1,    -1,    -1,    21,    22,    -1,    -1,
      -1,    26,    -1,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    -1,    37,    38,    39,    40,    41,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    -1,    37,    38,
      39,    40,    41,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    -1,    37,    38,    39,    40,    41
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    49,     0,     9,    10,    11,    14,    15,    16,    21,
      22,    26,    50,    51,    57,    58,    36,    44,    44,    44,
      44,    50,    55,    44,     9,     3,     4,     5,     6,     7,
       8,     9,    35,    38,    44,    56,    58,    59,    60,    56,
      58,    56,    56,    61,    61,    56,    56,    55,    20,     9,
      59,    44,    56,    56,    56,    23,    27,    28,    29,    30,
      31,    32,    33,    34,    37,    38,    39,    40,    41,    47,
      45,    45,    45,    45,    44,    45,     9,    62,    45,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    61,    55,    55,    56,    17,    52,    53,
      47,    45,    24,    55,    12,    13,    12,    45,    60,    12,
      19,    53,    54,    62,    55,    36,    12,    55,    46,    46,
      12,    12,    59,    12,    55,    55,    55,    12
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:

/* Line 1455 of yacc.c  */
#line 79 "../src/parse.y"
    {
        if((yyvsp[(2) - (2)].a) != NULL) {
            eval((yyvsp[(2) - (2)].a));
            treefree((yyvsp[(2) - (2)].a));
        }
    }
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 88 "../src/parse.y"
    {
        (yyval.a) = newflow(NODE_IF, (yyvsp[(3) - (6)].a), (yyvsp[(5) - (6)].a), NULL); }
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 90 "../src/parse.y"
    {
        (yyval.a) = newflow(NODE_IF, (yyvsp[(3) - (8)].a), (yyvsp[(5) - (8)].a), (yyvsp[(7) - (8)].a)); }
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 92 "../src/parse.y"
    {
        (yyval.a) = newflow(NODE_WHILE, (yyvsp[(3) - (6)].a), (yyvsp[(5) - (6)].a), NULL); }
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 94 "../src/parse.y"
    {
        (yyval.a) = newflow(NODE_DO, (yyvsp[(5) - (6)].a), (yyvsp[(2) - (6)].a), NULL); }
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 96 "../src/parse.y"
    {
        (yyval.a) = newflow(NODE_SWITCH, (yyvsp[(3) - (6)].a), (yyvsp[(5) - (6)].a), NULL); }
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 98 "../src/parse.y"
    {
        (yyval.a) = newflow(NODE_SWITCH, (yyvsp[(3) - (7)].a), (yyvsp[(5) - (7)].a), (yyvsp[(6) - (7)].a)); }
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 100 "../src/parse.y"
    {
        (yyval.a) = newfor(NODE_FROM, (yyvsp[(2) - (6)].a), (yyvsp[(4) - (6)].a), (yyvsp[(5) - (6)].a), NULL); }
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 102 "../src/parse.y"
    {
        (yyval.a) = newfor(NODE_FROM, (yyvsp[(2) - (9)].a), (yyvsp[(4) - (9)].a), (yyvsp[(8) - (9)].a), (yyvsp[(7) - (9)].a)); }
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 104 "../src/parse.y"
    {
        dodef((yyvsp[(2) - (7)].s), (yyvsp[(4) - (7)].sl), (yyvsp[(6) - (7)].a));
        (yyval.a) = NULL;
    }
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 113 "../src/parse.y"
    { (yyval.a) = newast(NODE_RETURN, (yyvsp[(2) - (2)].a), NULL);}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 114 "../src/parse.y"
    { (yyval.a) = newast(NODE_RETURN, (yyvsp[(2) - (2)].a), NULL);}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 118 "../src/parse.y"
    {
        /*printf("parse cases\n");*/
        (yyval.a) = newflow(NODE_CASES, NULL, (yyvsp[(1) - (2)].a), (yyvsp[(2) - (2)].a));
     }
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 122 "../src/parse.y"
    {
            (yyval.a) = (yyvsp[(1) - (1)].a);
        }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 128 "../src/parse.y"
    {
        /*printf("parse simple case\n");*/
        (yyval.a) = newflow(NODE_CASE, NULL, (yyvsp[(2) - (4)].a), (yyvsp[(4) - (4)].a));
    }
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 135 "../src/parse.y"
    {
        /*printf("parse default\n");*/
        (yyval.a) = newflow(NODE_DEFAULT, NULL, (yyvsp[(3) - (3)].a), NULL);
    }
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 141 "../src/parse.y"
    { (yyval.a) = NULL; }
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 142 "../src/parse.y"
    {
        if ((yyvsp[(2) - (2)].a) == NULL)
            (yyval.a) = newast(NODE_BLOCK, (yyvsp[(1) - (2)].a), NULL);
        else
            (yyval.a) = newast(NODE_BLOCK, (yyvsp[(1) - (2)].a), (yyvsp[(2) - (2)].a));
    }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 150 "../src/parse.y"
    { (yyval.a) = newast(NODE_GT, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 151 "../src/parse.y"
    { (yyval.a) = newast(NODE_LT, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 152 "../src/parse.y"
    { (yyval.a) = newast(NODE_GE, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 153 "../src/parse.y"
    { (yyval.a) = newast(NODE_LE, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 154 "../src/parse.y"
    { (yyval.a) = newast(NODE_NEQ, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 155 "../src/parse.y"
    { (yyval.a) = newast(NODE_EQ, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 156 "../src/parse.y"
    { (yyval.a) = newast(NODE_AND, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 157 "../src/parse.y"
    { (yyval.a) = newast(NODE_OR, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 158 "../src/parse.y"
    { (yyval.a) = newast(NODE_NEG, (yyvsp[(2) - (2)].a), NULL); }
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 159 "../src/parse.y"
    { (yyval.a) = newast(NODE_ADD, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 160 "../src/parse.y"
    { (yyval.a) = newast(NODE_SUB, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 161 "../src/parse.y"
    { (yyval.a) = newast(NODE_MULT, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 162 "../src/parse.y"
    { (yyval.a) = newast(NODE_DIV, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 163 "../src/parse.y"
    { (yyval.a) = newast(NODE_MOD, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 164 "../src/parse.y"
    { (yyval.a) = (yyvsp[(2) - (3)].a); }
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 165 "../src/parse.y"
    { (yyval.a) = newast(NODE_UNARY_MINUS, (yyvsp[(2) - (2)].a), NULL); }
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 170 "../src/parse.y"
    { (yyval.a) = newasgn((yyvsp[(1) - (3)].s), (yyvsp[(3) - (3)].a)); }
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 174 "../src/parse.y"
    { (yyval.a) = newcall((yyvsp[(1) - (4)].s), (yyvsp[(3) - (4)].a)); }
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 175 "../src/parse.y"
    { (yyval.a) = newfunc((yyvsp[(1) - (4)].fn), (yyvsp[(3) - (4)].a)); }
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 179 "../src/parse.y"
    { (yyval.a) = newref((yyvsp[(1) - (1)].s)); }
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 180 "../src/parse.y"
    { (yyval.a) = newbool((yyvsp[(1) - (1)].b)); }
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 181 "../src/parse.y"
    { (yyval.a) = newbool((yyvsp[(1) - (1)].b)); }
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 182 "../src/parse.y"
    { (yyval.a) = (yyvsp[(1) - (1)].a); }
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 186 "../src/parse.y"
    { (yyval.a) = newint((yyvsp[(1) - (1)].i)); }
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 187 "../src/parse.y"
    { (yyval.a) = newnum((yyvsp[(1) - (1)].d)); }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 188 "../src/parse.y"
    { (yyval.a) = (yyvsp[(1) - (1)].c); }
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 189 "../src/parse.y"
    { (yyval.a) = (yyvsp[(1) - (1)].str); }
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 192 "../src/parse.y"
    { (yyval.a) = NULL; }
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 193 "../src/parse.y"
    { (yyval.a) = newast(NODE_LIST_SYMBOLS, (yyvsp[(1) - (1)].a), NULL); }
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 194 "../src/parse.y"
    { (yyval.a) = newast(NODE_LIST_SYMBOLS, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 197 "../src/parse.y"
    { (yyval.sl) = NULL; }
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 198 "../src/parse.y"
    { (yyval.sl) = newsymlist((yyvsp[(1) - (1)].s), NULL); }
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 199 "../src/parse.y"
    { (yyval.sl) = newsymlist((yyvsp[(1) - (3)].s), (yyvsp[(3) - (3)].sl)); }
    break;



/* Line 1455 of yacc.c  */
#line 1947 "../src/parse.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



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
		      yytoken, &yylval);
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 202 "../src/parse.y"


extern
void yyerror(char *s, ...)
{
    print_error("linea %i, %s", yylineno, s);
}

