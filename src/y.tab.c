
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
#line 1 "src/parse.y"

int yystopparser=0;


/* Line 189 of yacc.c  */
#line 78 "src/y.tab.c"

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
     PRINCIPAL = 258,
     FIN = 259,
     NOMBRECAMPO = 260,
     ENTERO = 261,
     DECIMAL = 262,
     LOGICO = 263,
     CARACTER = 264,
     CADENA = 265,
     T_CADENA = 266,
     T_LOGICO = 267,
     T_ENTERO = 268,
     T_DECIMAL = 269,
     T_CARACTER = 270,
     ASIGNADOR = 271,
     SUMA = 272,
     RESTA = 273,
     MULTIP = 274,
     DIVISION = 275,
     MODULO = 276,
     AUMENTAR = 277,
     DISMINUIR = 278,
     SI = 279,
     MAYOR = 280,
     MENOR = 281,
     IGUAL = 282,
     MAYORIGUAL = 283,
     MENORIGUAL = 284,
     NOIGUAL = 285,
     DESDE = 286,
     HACER = 287,
     SALTO = 288,
     MIENTRAS = 289,
     SINO = 290,
     ELEGIR = 291,
     CASO = 292,
     HASTA = 293,
     CONTINUAR = 294,
     ROMPER = 295,
     CONSTANTE = 296,
     CUANDO = 297,
     DEFECTO = 298,
     FUNCION = 299,
     CLASE = 300,
     PROPIEDAD = 301,
     ESTA = 302,
     CONSTRUCTOR = 303,
     RETORNO = 304,
     NEGATIVO = 305,
     PAREN_IZQ = 306,
     PAREN_DER = 307
   };
#endif
/* Tokens.  */
#define PRINCIPAL 258
#define FIN 259
#define NOMBRECAMPO 260
#define ENTERO 261
#define DECIMAL 262
#define LOGICO 263
#define CARACTER 264
#define CADENA 265
#define T_CADENA 266
#define T_LOGICO 267
#define T_ENTERO 268
#define T_DECIMAL 269
#define T_CARACTER 270
#define ASIGNADOR 271
#define SUMA 272
#define RESTA 273
#define MULTIP 274
#define DIVISION 275
#define MODULO 276
#define AUMENTAR 277
#define DISMINUIR 278
#define SI 279
#define MAYOR 280
#define MENOR 281
#define IGUAL 282
#define MAYORIGUAL 283
#define MENORIGUAL 284
#define NOIGUAL 285
#define DESDE 286
#define HACER 287
#define SALTO 288
#define MIENTRAS 289
#define SINO 290
#define ELEGIR 291
#define CASO 292
#define HASTA 293
#define CONTINUAR 294
#define ROMPER 295
#define CONSTANTE 296
#define CUANDO 297
#define DEFECTO 298
#define FUNCION 299
#define CLASE 300
#define PROPIEDAD 301
#define ESTA 302
#define CONSTRUCTOR 303
#define RETORNO 304
#define NEGATIVO 305
#define PAREN_IZQ 306
#define PAREN_DER 307




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 224 "src/y.tab.c"

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
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   339

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  132
/* YYNRULES -- Number of states.  */
#define YYNSTATES  228

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   307

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    53,     2,    55,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    54,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    10,    13,    16,    18,    20,    22,
      29,    31,    32,    35,    37,    39,    41,    43,    45,    47,
      49,    51,    53,    55,    57,    59,    61,    66,    68,    69,
      73,    75,    77,    79,    81,    82,    86,    88,    93,    96,
      98,   100,   102,   104,   106,   109,   113,   116,   122,   127,
     129,   131,   133,   135,   137,   140,   143,   146,   148,   150,
     152,   154,   158,   162,   166,   170,   174,   178,   182,   186,
     190,   194,   196,   198,   202,   204,   207,   210,   212,   214,
     216,   218,   220,   222,   224,   226,   229,   236,   243,   247,
     251,   255,   259,   261,   263,   265,   267,   269,   271,   273,
     275,   279,   286,   293,   296,   298,   303,   304,   309,   316,
     324,   328,   331,   333,   335,   337,   339,   342,   349,   356,
     359,   361,   369,   372,   374,   379,   386,   389,   391,   395,
     400,   407,   410
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      57,     0,    -1,    58,    95,    97,    -1,    58,    95,    -1,
      58,    97,    -1,    97,    95,    -1,    58,    -1,    95,    -1,
      97,    -1,     3,    51,    66,    52,    59,     4,    -1,    60,
      -1,    -1,    60,    61,    -1,    61,    -1,    62,    -1,    70,
      -1,    71,    -1,    79,    -1,    39,    -1,    40,    -1,    77,
      -1,    99,    -1,   101,    -1,    95,    -1,   102,    -1,   103,
      -1,     5,    51,    63,    52,    -1,    64,    -1,    -1,    65,
      53,    65,    -1,    65,    -1,    69,    -1,     5,    -1,    67,
      -1,    -1,    68,    53,    68,    -1,    68,    -1,    72,     5,
      16,    69,    -1,    72,     5,    -1,     8,    -1,     6,    -1,
       7,    -1,     9,    -1,    10,    -1,    72,     5,    -1,    72,
       5,    73,    -1,     5,    73,    -1,    41,    72,     5,    16,
      69,    -1,    41,     5,    16,    69,    -1,    12,    -1,    13,
      -1,    14,    -1,    15,    -1,    11,    -1,    16,    74,    -1,
      16,    69,    -1,    16,     5,    -1,    75,    -1,    62,    -1,
      77,    -1,    76,    -1,    76,    17,    76,    -1,    76,    18,
      76,    -1,    76,    19,    76,    -1,    76,    20,    76,    -1,
      76,    21,    76,    -1,    75,    17,    76,    -1,    75,    18,
      76,    -1,    75,    19,    76,    -1,    75,    20,    76,    -1,
      75,    21,    76,    -1,    69,    -1,     5,    -1,    51,    75,
      52,    -1,    62,    -1,     5,    78,    -1,    78,     5,    -1,
      22,    -1,    23,    -1,    80,    -1,    85,    -1,    89,    -1,
      93,    -1,    94,    -1,    81,    -1,    81,    84,    -1,    24,
      51,    82,    52,    59,     4,    -1,    24,    51,    82,    52,
      59,    84,    -1,    69,    83,    69,    -1,    69,    83,     5,
      -1,     5,    83,    69,    -1,     5,    83,     5,    -1,     5,
      -1,     8,    -1,    25,    -1,    26,    -1,    27,    -1,    28,
      -1,    29,    -1,    30,    -1,    35,    59,     4,    -1,    36,
      51,     5,    52,    86,     4,    -1,    36,    51,     5,    52,
      86,    88,    -1,    86,    87,    -1,    87,    -1,    37,    69,
      54,    59,    -1,    -1,    43,    54,    59,     4,    -1,    31,
      90,    38,    91,    59,     4,    -1,    31,    90,    38,    90,
      92,    59,     4,    -1,    72,     5,    73,    -1,     5,    73,
      -1,     5,    -1,    69,    -1,     5,    -1,    69,    -1,    33,
      73,    -1,    34,    51,    82,    52,    59,     4,    -1,    32,
      59,    42,    51,    82,    52,    -1,    95,    96,    -1,    96,
      -1,    44,     5,    51,    66,    52,    59,     4,    -1,    97,
      98,    -1,    98,    -1,    45,     5,    59,     4,    -1,    45,
       5,    54,     5,    59,     4,    -1,    99,   100,    -1,   100,
      -1,    46,    72,     5,    -1,    47,    55,     5,    73,    -1,
      48,    51,    66,    52,    59,     4,    -1,    49,    74,    -1,
      49,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    30,    30,    31,    32,    33,    34,    35,    36,    40,
      43,    44,    48,    49,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    68,    72,    73,    77,
      78,    82,    83,    86,    87,    91,    92,    96,    97,   101,
     102,   103,   104,   105,   108,   109,   110,   114,   115,   119,
     120,   121,   122,   123,   127,   128,   129,   133,   134,   135,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   153,   154,   155,   156,   160,   161,   165,   166,   170,
     171,   172,   173,   174,   178,   179,   183,   184,   188,   189,
     190,   191,   192,   193,   197,   198,   199,   200,   201,   202,
     206,   210,   211,   215,   216,   220,   221,   225,   229,   230,
     234,   235,   236,   237,   241,   242,   246,   250,   254,   258,
     259,   263,   267,   268,   272,   273,   277,   278,   282,   286,
     290,   294,   295
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PRINCIPAL", "FIN", "NOMBRECAMPO",
  "ENTERO", "DECIMAL", "LOGICO", "CARACTER", "CADENA", "T_CADENA",
  "T_LOGICO", "T_ENTERO", "T_DECIMAL", "T_CARACTER", "ASIGNADOR", "SUMA",
  "RESTA", "MULTIP", "DIVISION", "MODULO", "AUMENTAR", "DISMINUIR", "SI",
  "MAYOR", "MENOR", "IGUAL", "MAYORIGUAL", "MENORIGUAL", "NOIGUAL",
  "DESDE", "HACER", "SALTO", "MIENTRAS", "SINO", "ELEGIR", "CASO", "HASTA",
  "CONTINUAR", "ROMPER", "CONSTANTE", "CUANDO", "DEFECTO", "FUNCION",
  "CLASE", "PROPIEDAD", "ESTA", "CONSTRUCTOR", "RETORNO", "NEGATIVO",
  "PAREN_IZQ", "PAREN_DER", "','", "':'", "'.'", "$accept", "programa",
  "principal", "lineascodigo", "lineacodigo", "linea", "invocarmetodo",
  "parametrosenvio", "parenvio", "penvio", "parametrosrecibe", "parecibe",
  "precibe", "valor", "crearvariable", "crearconstante", "tipodato",
  "asignarvalor", "operasignacion", "expresion", "primary",
  "incredismivariable", "incdis", "buclecondicion", "condicionif",
  "condicionsi", "condicion", "condicional", "condicionno",
  "condicionswitch", "casos", "uncaso", "elegirotro", "buclefor",
  "iniciafor", "finfor", "inc", "buclewhile", "bucledo", "funciones",
  "func", "clases", "clas", "propiedades", "prop", "asignaProp", "ctor",
  "regresar", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,    44,    58,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    57,    57,    57,    57,    57,    57,    58,
      59,    59,    60,    60,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    62,    63,    63,    64,
      64,    65,    65,    66,    66,    67,    67,    68,    68,    69,
      69,    69,    69,    69,    70,    70,    70,    71,    71,    72,
      72,    72,    72,    72,    73,    73,    73,    74,    74,    74,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    76,    76,    76,    76,    77,    77,    78,    78,    79,
      79,    79,    79,    79,    80,    80,    81,    81,    82,    82,
      82,    82,    82,    82,    83,    83,    83,    83,    83,    83,
      84,    85,    85,    86,    86,    87,    87,    88,    89,    89,
      90,    90,    90,    90,    91,    91,    92,    93,    94,    95,
      95,    96,    97,    97,    98,    98,    99,    99,   100,   101,
     102,   103,   103
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     2,     2,     1,     1,     1,     6,
       1,     0,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     1,     0,     3,
       1,     1,     1,     1,     0,     3,     1,     4,     2,     1,
       1,     1,     1,     1,     2,     3,     2,     5,     4,     1,
       1,     1,     1,     1,     2,     2,     2,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     3,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     6,     6,     3,     3,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     6,     6,     2,     1,     4,     0,     4,     6,     7,
       3,     2,     1,     1,     1,     1,     2,     6,     6,     2,
       1,     7,     2,     1,     4,     6,     2,     1,     3,     4,
       6,     2,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     6,     7,   120,     8,   123,
      34,     0,    11,     1,     3,     4,   119,     5,   122,    53,
      49,    50,    51,    52,     0,    33,    36,     0,    34,     0,
      77,    78,     0,     0,    11,     0,     0,    18,    19,     0,
       0,     0,     0,   132,     0,     0,    10,    13,    14,    15,
      16,     0,    20,     0,    17,    79,    84,    80,    81,    82,
      83,    23,    21,   127,    22,    24,    25,     2,    11,     0,
      38,     0,     0,    28,    46,    75,     0,   112,    40,    41,
      39,    42,    43,   113,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    34,    72,     0,    58,    71,   131,    57,
      60,    59,    11,   124,    12,    44,    76,    11,    85,   126,
       0,    35,     0,    11,    56,    55,    54,    32,     0,    27,
      30,    31,    92,    39,     0,     0,   111,     0,     0,     0,
       0,     0,     0,     0,   128,     0,     0,    72,    74,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    45,     0,     9,    37,     0,    26,     0,    94,    95,
      96,    97,    98,    99,     0,     0,    11,   110,   114,   115,
       0,    11,     0,    11,   106,    48,     0,   129,    11,    73,
      66,    67,    68,    69,    70,    61,    62,    63,    64,    65,
     125,   100,   121,    29,    91,    90,    89,    88,     0,     0,
      11,     0,     0,     0,     0,     0,   104,    47,     0,    86,
      87,   116,     0,   108,   118,   117,     0,   101,     0,   103,
     102,   130,   109,    11,    11,   105,     0,   107
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,    45,    46,    47,    48,   118,   119,   120,
      24,    25,    26,    97,    49,    50,    51,   126,    98,    99,
     100,    52,    53,    54,    55,    56,   125,   164,   108,    57,
     205,   206,   220,    58,    85,   171,   200,    59,    60,    61,
       7,     8,     9,    62,    63,    64,    65,    66
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -83
static const yytype_int16 yypact[] =
{
       9,   -41,    39,    55,    23,   -29,    17,   -83,   -29,   -83,
     116,   -38,   138,   -83,   -29,    22,   -83,    17,   -83,   -83,
     -83,   -83,   -83,   -83,    24,   -83,    12,    69,   116,     6,
     -83,   -83,    27,   262,   210,    31,    33,   -83,   -83,    91,
     116,    30,    36,   188,    83,    87,   210,   -83,   -83,   -83,
     -83,    88,   -83,    89,   -83,   -83,    60,   -83,   -83,   -83,
     -83,    17,    52,   -83,   -83,   -83,   -83,    22,   210,   116,
      84,    66,   194,   149,   -83,   -83,   221,   103,   -83,   -83,
     -83,   -83,   -83,   -83,   115,    85,    80,   221,   119,   109,
     130,   131,   133,   116,     8,    41,   272,   -83,   -83,   307,
     313,   -83,   210,   -83,   -83,   103,   -83,   210,   -83,   -83,
     136,   -83,   199,   210,   243,   318,   -83,   -83,    90,   -83,
      93,   -83,   280,    95,   280,    96,   -83,   103,   273,   112,
     113,   123,   199,   148,   -83,   103,   124,   117,   -83,    18,
      41,    41,    41,    41,    41,    41,    41,    41,    41,    41,
     163,   -83,   176,   -83,   -83,   177,   -83,   149,   -83,   -83,
     -83,   -83,   -83,   -83,   306,   312,   210,   -83,    -8,   150,
     158,   210,   221,   210,   151,   -83,   199,   -83,   210,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,    20,   103,
     210,   208,   161,   214,   199,    15,   -83,   -83,   215,   -83,
     -83,   -83,   216,   -83,   -83,   -83,   160,   -83,   181,   -83,
     -83,   -83,   -83,   210,   210,   -83,   232,   -83
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -83,   -83,   -83,   -34,   -83,   191,   -32,   -83,   -83,    81,
     -22,   -83,   171,   -31,   -83,   -83,    -7,   -28,   175,   153,
     155,     0,   -25,   -83,   -83,   -83,   -82,   128,    45,   -83,
     -83,    48,   -83,   -83,   127,   -83,   -83,   -83,   -83,    75,
       3,    13,    -1,   -83,   261,   -83,   -83,   -83
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -114
static const yytype_int16 yytable[] =
{
      86,    74,    83,    27,    75,   130,    71,    18,    72,    16,
      10,    96,     1,    28,    18,     2,     3,    16,    15,   217,
      16,    27,    72,    13,   209,  -112,    84,    67,    30,    31,
      30,    31,    90,    91,   110,   140,   141,   142,   143,   144,
      96,   115,   121,   101,    11,   124,   137,    78,    79,    80,
      81,    82,   204,     2,     3,   107,   124,    73,   218,    73,
      12,     2,    27,   138,    16,    69,    18,     3,   150,    75,
     179,   136,   101,   152,    70,     6,    68,   151,    76,   155,
      14,   154,    87,    17,    88,    92,    27,    93,   102,    75,
     202,   103,    95,   105,   106,   107,    89,   169,    40,   167,
     112,   175,    19,    20,    21,    22,    23,   177,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   113,    72,
     127,    84,   129,   128,   131,   132,   121,    19,    20,    21,
      22,    23,   198,   195,   197,   133,   134,   201,   135,   203,
     153,   124,   156,    29,   208,   207,   157,   -93,   166,    19,
      20,    21,    22,    23,   117,    78,    79,    80,    81,    82,
      30,    31,    32,   172,   176,   173,   212,   190,    73,    33,
      34,   211,    35,   216,    36,   174,   178,    37,    38,    39,
     191,   192,     2,  -113,    40,    41,    42,    43,   204,   225,
     226,   199,    44,    94,    78,    79,    80,    81,    82,   114,
      78,    79,    80,    81,    82,    78,    79,    80,    81,    82,
      30,    31,   213,   214,   223,    29,    30,    31,   215,   221,
     222,    19,    20,    21,    22,    23,   122,    78,    79,   123,
      81,    82,    30,    31,    32,   224,   227,   104,   193,    95,
     111,    33,    34,   210,    35,    95,    36,   116,   139,    37,
      38,    39,   165,   219,     2,   170,    40,    41,    42,    43,
     -72,   -72,   -72,   -72,   -72,    30,    31,    77,    78,    79,
      80,    81,    82,    19,    20,    21,    22,    23,   168,    78,
      79,    80,    81,    82,    19,    20,    21,    22,    23,   -74,
     -74,   -74,   -74,   -74,    73,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   158,   159,   160,   161,   162,
     163,   194,    78,    79,    80,    81,    82,   196,    78,    79,
      80,    81,    82,   109,   140,   141,   142,   143,   144,     0,
     145,   146,   147,   148,   149,   -71,   -71,   -71,   -71,   -71
};

static const yytype_int16 yycheck[] =
{
      34,    29,    33,    10,    29,    87,    28,     8,    16,     6,
      51,    43,     3,    51,    15,    44,    45,    14,     5,     4,
      17,    28,    16,     0,     4,    33,    33,    14,    22,    23,
      22,    23,    39,    40,    68,    17,    18,    19,    20,    21,
      72,    72,    73,    43,     5,    76,     5,     6,     7,     8,
       9,    10,    37,    44,    45,    35,    87,    51,    43,    51,
       5,    44,    69,    95,    61,    53,    67,    45,   102,    94,
      52,    93,    72,   107,     5,     0,    52,   105,    51,   113,
       5,   112,    51,     8,    51,    55,    93,    51,     5,   114,
     172,     4,    51,     5,     5,    35,     5,   128,    46,   127,
      16,   132,    11,    12,    13,    14,    15,   135,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,    52,    16,
       5,   128,    42,    38,     5,    16,   157,    11,    12,    13,
      14,    15,   166,   164,   165,     5,     5,   171,     5,   173,
       4,   172,    52,     5,   178,   176,    53,    52,    52,    11,
      12,    13,    14,    15,     5,     6,     7,     8,     9,    10,
      22,    23,    24,    51,    16,    52,   200,     4,    51,    31,
      32,   199,    34,   204,    36,    52,    52,    39,    40,    41,
       4,     4,    44,    33,    46,    47,    48,    49,    37,   223,
     224,    33,    54,     5,     6,     7,     8,     9,    10,     5,
       6,     7,     8,     9,    10,     6,     7,     8,     9,    10,
      22,    23,     4,    52,    54,     5,    22,    23,     4,     4,
       4,    11,    12,    13,    14,    15,     5,     6,     7,     8,
       9,    10,    22,    23,    24,    54,     4,    46,   157,    51,
      69,    31,    32,   198,    34,    51,    36,    72,    95,    39,
      40,    41,   124,   205,    44,   128,    46,    47,    48,    49,
      17,    18,    19,    20,    21,    22,    23,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    17,
      18,    19,    20,    21,    51,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,    25,    26,    27,    28,    29,
      30,     5,     6,     7,     8,     9,    10,     5,     6,     7,
       8,     9,    10,    62,    17,    18,    19,    20,    21,    -1,
      17,    18,    19,    20,    21,    17,    18,    19,    20,    21
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    44,    45,    57,    58,    95,    96,    97,    98,
      51,     5,     5,     0,    95,    97,    96,    95,    98,    11,
      12,    13,    14,    15,    66,    67,    68,    72,    51,     5,
      22,    23,    24,    31,    32,    34,    36,    39,    40,    41,
      46,    47,    48,    49,    54,    59,    60,    61,    62,    70,
      71,    72,    77,    78,    79,    80,    81,    85,    89,    93,
      94,    95,    99,   100,   101,   102,   103,    97,    52,    53,
       5,    66,    16,    51,    73,    78,    51,     5,     6,     7,
       8,     9,    10,    69,    72,    90,    59,    51,    51,     5,
      72,    72,    55,    51,     5,    51,    62,    69,    74,    75,
      76,    77,     5,     4,    61,     5,     5,    35,    84,   100,
      59,    68,    16,    52,     5,    69,    74,     5,    63,    64,
      65,    69,     5,     8,    69,    82,    73,     5,    38,    42,
      82,     5,    16,     5,     5,     5,    66,     5,    62,    75,
      17,    18,    19,    20,    21,    17,    18,    19,    20,    21,
      59,    73,    59,     4,    69,    59,    52,    53,    25,    26,
      27,    28,    29,    30,    83,    83,    52,    73,     5,    69,
      90,    91,    51,    52,    52,    69,    16,    73,    52,    52,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
       4,     4,     4,    65,     5,    69,     5,    69,    59,    33,
      92,    59,    82,    59,    37,    86,    87,    69,    59,     4,
      84,    73,    59,     4,    52,     4,    69,     4,    43,    87,
      88,     4,     4,    54,    54,    59,    59,     4
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
      

/* Line 1455 of yacc.c  */
#line 1661 "src/y.tab.c"
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
#line 298 "src/parse.y"


