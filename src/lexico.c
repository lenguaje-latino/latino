
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
#line 1 "lexico.y"

int yystopparser=0;


/* Line 189 of yacc.c  */
#line 78 "lexico.c"

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
     MULTIPLICACION = 274,
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
     RETORNO = 304
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 169 "lexico.c"

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
#define YYLAST   352

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  144
/* YYNRULES -- Number of states.  */
#define YYNSTATES  241

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      50,    51,     2,     2,    52,     2,    54,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    53,     2,
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
      45,    46,    47,    48,    49
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
     152,   154,   157,   161,   165,   169,   173,   177,   181,   185,
     189,   193,   195,   197,   199,   201,   203,   206,   208,   211,
     214,   217,   223,   229,   235,   241,   244,   247,   249,   251,
     253,   255,   257,   259,   261,   263,   266,   273,   280,   284,
     288,   292,   296,   298,   300,   302,   304,   306,   308,   310,
     312,   316,   323,   330,   333,   335,   340,   341,   346,   353,
     361,   365,   368,   370,   372,   374,   376,   379,   386,   393,
     396,   398,   406,   409,   411,   416,   423,   426,   428,   432,
     437,   444,   447,   450,   453
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      56,     0,    -1,    57,    98,   100,    -1,    57,    98,    -1,
      57,   100,    -1,   100,    98,    -1,    57,    -1,    98,    -1,
     100,    -1,     3,    50,    65,    51,    58,     4,    -1,    59,
      -1,    -1,    59,    60,    -1,    60,    -1,    61,    -1,    69,
      -1,    70,    -1,    82,    -1,    39,    -1,    40,    -1,    80,
      -1,   102,    -1,   104,    -1,    98,    -1,   105,    -1,   106,
      -1,     5,    50,    62,    51,    -1,    63,    -1,    -1,    64,
      52,    64,    -1,    64,    -1,    68,    -1,     5,    -1,    66,
      -1,    -1,    67,    52,    67,    -1,    67,    -1,    71,     5,
      16,    68,    -1,    71,     5,    -1,     8,    -1,     6,    -1,
       7,    -1,     9,    -1,    10,    -1,    71,     5,    -1,    71,
       5,    72,    -1,     5,    72,    -1,    41,    71,     5,    16,
      68,    -1,    41,     5,    16,    68,    -1,    12,    -1,    13,
      -1,    14,    -1,    15,    -1,    11,    -1,    16,    73,    -1,
      16,    68,    -1,    16,     5,    -1,    74,    -1,    61,    -1,
      80,    -1,    75,    -1,    75,    77,    -1,    68,    76,    68,
      -1,    68,    76,     5,    -1,     5,    76,    68,    -1,     5,
      76,     5,    -1,    68,    76,    79,    -1,    79,    76,    68,
      -1,     5,    76,    79,    -1,    79,    76,     5,    -1,    79,
      76,    79,    -1,    17,    -1,    18,    -1,    19,    -1,    20,
      -1,    21,    -1,    77,    78,    -1,    78,    -1,    76,    68,
      -1,    76,     5,    -1,    76,    79,    -1,    50,    68,    76,
      68,    51,    -1,    50,    68,    76,     5,    51,    -1,    50,
       5,    76,    68,    51,    -1,    50,     5,    76,     5,    51,
      -1,     5,    81,    -1,    81,     5,    -1,    22,    -1,    23,
      -1,    83,    -1,    88,    -1,    92,    -1,    96,    -1,    97,
      -1,    84,    -1,    84,    87,    -1,    24,    50,    85,    51,
      58,     4,    -1,    24,    50,    85,    51,    58,    87,    -1,
      68,    86,    68,    -1,    68,    86,     5,    -1,     5,    86,
      68,    -1,     5,    86,     5,    -1,     5,    -1,     8,    -1,
      25,    -1,    26,    -1,    27,    -1,    28,    -1,    29,    -1,
      30,    -1,    35,    58,     4,    -1,    36,    50,     5,    51,
      89,     4,    -1,    36,    50,     5,    51,    89,    91,    -1,
      89,    90,    -1,    90,    -1,    37,    68,    53,    58,    -1,
      -1,    43,    53,    58,     4,    -1,    31,    93,    38,    94,
      58,     4,    -1,    31,    93,    38,    93,    95,    58,     4,
      -1,    71,     5,    72,    -1,     5,    72,    -1,     5,    -1,
      68,    -1,     5,    -1,    68,    -1,    33,    72,    -1,    34,
      50,    85,    51,    58,     4,    -1,    32,    58,    42,    50,
      85,    51,    -1,    98,    99,    -1,    99,    -1,    44,     5,
      50,    65,    51,    58,     4,    -1,   100,   101,    -1,   101,
      -1,    45,     5,    58,     4,    -1,    45,     5,    53,     5,
      58,     4,    -1,   102,   103,    -1,   103,    -1,    46,    71,
       5,    -1,    47,    54,     5,    72,    -1,    48,    50,    65,
      51,    58,     4,    -1,    49,    68,    -1,    49,     5,    -1,
      49,    73,    -1,    49,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    15,    15,    15,    15,    15,    15,    15,    15,    17,
      19,    19,    21,    21,    23,    23,    23,    23,    23,    23,
      23,    23,    23,    23,    23,    23,    25,    27,    27,    29,
      29,    31,    31,    33,    33,    35,    35,    37,    37,    39,
      39,    39,    39,    39,    41,    41,    41,    43,    43,    45,
      45,    45,    45,    45,    47,    47,    47,    49,    49,    49,
      51,    51,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    55,    55,    55,    55,    55,    57,    57,    59,    59,
      59,    61,    61,    61,    61,    63,    63,    65,    65,    67,
      67,    67,    67,    67,    69,    69,    71,    71,    73,    73,
      73,    73,    73,    73,    75,    75,    75,    75,    75,    75,
      77,    79,    79,    81,    81,    83,    83,    85,    87,    87,
      89,    89,    89,    89,    91,    91,    93,    95,    97,    99,
      99,   101,   103,   103,   105,   105,   107,   107,   109,   111,
     113,   115,   115,   115,   115
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
  "RESTA", "MULTIPLICACION", "DIVISION", "MODULO", "AUMENTAR", "DISMINUIR",
  "SI", "MAYOR", "MENOR", "IGUAL", "MAYORIGUAL", "MENORIGUAL", "NOIGUAL",
  "DESDE", "HACER", "SALTO", "MIENTRAS", "SINO", "ELEGIR", "CASO", "HASTA",
  "CONTINUAR", "ROMPER", "CONSTANTE", "CUANDO", "DEFECTO", "FUNCION",
  "CLASE", "PROPIEDAD", "ESTA", "CONSTRUCTOR", "RETORNO", "'('", "')'",
  "','", "':'", "'.'", "$accept", "programa", "principal", "lineascodigo",
  "lineacodigo", "linea", "invocarmetodo", "parametrosenvio", "parenvio",
  "penvio", "parametrosrecibe", "parecibe", "precibe", "valor",
  "crearvariable", "crearconstante", "tipodato", "asignarvalor",
  "operasignacion", "aritmetico", "oprcomun", "tipoopr", "oprcomplemento",
  "oprcom", "oprcompuesto", "incredismivariable", "incdis",
  "buclecondicion", "condicionif", "condicionsi", "condicion",
  "condicional", "condicionno", "condicionswitch", "casos", "uncaso",
  "elegirotro", "buclefor", "iniciafor", "finfor", "inc", "buclewhile",
  "bucledo", "funciones", "func", "clases", "clas", "propiedades", "prop",
  "asignaProp", "ctor", "regresar", 0
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
      40,    41,    44,    58,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    56,    56,    56,    56,    56,    56,    57,
      58,    58,    59,    59,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    61,    62,    62,    63,
      63,    64,    64,    65,    65,    66,    66,    67,    67,    68,
      68,    68,    68,    68,    69,    69,    69,    70,    70,    71,
      71,    71,    71,    71,    72,    72,    72,    73,    73,    73,
      74,    74,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    76,    76,    76,    76,    76,    77,    77,    78,    78,
      78,    79,    79,    79,    79,    80,    80,    81,    81,    82,
      82,    82,    82,    82,    83,    83,    84,    84,    85,    85,
      85,    85,    85,    85,    86,    86,    86,    86,    86,    86,
      87,    88,    88,    89,    89,    90,    90,    91,    92,    92,
      93,    93,    93,    93,    94,    94,    95,    96,    97,    98,
      98,    99,   100,   100,   101,   101,   102,   102,   103,   104,
     105,   106,   106,   106,   106
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
       1,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     1,     1,     1,     2,     1,     2,     2,
       2,     5,     5,     5,     5,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     6,     6,     3,     3,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     6,     6,     2,     1,     4,     0,     4,     6,     7,
       3,     2,     1,     1,     1,     1,     2,     6,     6,     2,
       1,     7,     2,     1,     4,     6,     2,     1,     3,     4,
       6,     2,     2,     2,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     6,     7,   130,     8,   133,
      34,     0,    11,     1,     3,     4,   129,     5,   132,    53,
      49,    50,    51,    52,     0,    33,    36,     0,    34,     0,
      87,    88,     0,     0,    11,     0,     0,    18,    19,     0,
       0,     0,     0,   144,     0,     0,    10,    13,    14,    15,
      16,     0,    20,     0,    17,    89,    94,    90,    91,    92,
      93,    23,    21,   137,    22,    24,    25,     2,    11,     0,
      38,     0,     0,    28,    46,    85,     0,   122,    40,    41,
      39,    42,    43,   123,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    34,   142,     0,    58,   141,   143,    57,
      60,     0,    59,    11,   134,    12,    44,    86,    11,    95,
     136,     0,    35,     0,    11,    56,    55,    54,    32,     0,
      27,    30,    31,   102,    39,     0,     0,   121,     0,     0,
       0,     0,     0,     0,     0,   138,     0,     0,    71,    72,
      73,    74,    75,     0,     0,     0,     0,     0,    61,    77,
       0,     0,    45,     0,     9,    37,     0,    26,     0,   104,
     105,   106,   107,   108,   109,     0,     0,    11,   120,   124,
     125,     0,    11,     0,    11,   116,    48,     0,   139,    11,
      65,    64,    68,     0,     0,    63,    62,    66,    79,    78,
      80,    76,    69,    67,    70,   135,   110,   131,    29,   101,
     100,    99,    98,     0,     0,    11,     0,     0,     0,     0,
       0,   114,    47,     0,     0,     0,     0,     0,    96,    97,
     126,     0,   118,   128,   127,     0,   111,     0,   113,   112,
     140,    84,    83,    82,    81,   119,    11,    11,   115,     0,
     117
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,    45,    46,    47,    48,   119,   120,   121,
      24,    25,    26,   125,    49,    50,    51,   127,    98,    99,
     100,   143,   148,   149,   101,    52,    53,    54,    55,    56,
     126,   165,   109,    57,   210,   211,   229,    58,    85,   172,
     205,    59,    60,    61,     7,     8,     9,    62,    63,    64,
      65,    66
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -84
static const yytype_int16 yypact[] =
{
      40,   -27,    17,    22,    31,    -9,    -6,   -84,    -9,   -84,
     117,   -13,   143,   -84,    -9,     1,   -84,    -6,   -84,   -84,
     -84,   -84,   -84,   -84,    -4,   -84,    13,    70,   117,    -5,
     -84,   -84,    27,   284,   239,    29,    33,   -84,   -84,    92,
     117,    35,    42,    45,    89,    95,   239,   -84,   -84,   -84,
     -84,   104,   -84,   105,   -84,   -84,    76,   -84,   -84,   -84,
     -84,    -6,    67,   -84,   -84,   -84,   -84,     1,   239,   117,
     107,    69,   199,   154,   -84,   -84,   306,   108,   -84,   -84,
     -84,   -84,   -84,   -84,   120,    98,    84,   306,   132,   123,
     136,   137,   138,   117,   219,   312,   -84,   180,   -84,   -84,
     180,   180,   -84,   239,   -84,   -84,   108,   -84,   239,   -84,
     -84,   140,   -84,   210,   239,   219,   180,   -84,   -84,    96,
     -84,    97,   -84,   298,    99,   298,   100,   -84,   108,   295,
     118,   119,   121,   210,   153,   -84,   108,   122,   -84,   -84,
     -84,   -84,   -84,    51,   180,   180,   205,   218,   180,   -84,
     224,   176,   -84,   177,   -84,   -84,   181,   -84,   154,   -84,
     -84,   -84,   -84,   -84,   -84,   324,   330,   239,   -84,    -3,
     155,   160,   239,   306,   239,   149,   -84,   210,   -84,   239,
     -84,   -84,   -84,   336,   342,   -84,   -84,   -84,   -84,   -84,
     -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,
     -84,   -84,   -84,     5,   108,   239,   190,   144,   231,   210,
      44,   -84,   -84,   241,   192,   195,   196,   197,   -84,   -84,
     -84,   252,   -84,   -84,   -84,   204,   -84,   206,   -84,   -84,
     -84,   -84,   -84,   -84,   -84,   -84,   239,   239,   -84,   254,
     -84
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -84,   -84,   -84,   -34,   -84,   214,   -33,   -84,   -84,   106,
     -22,   -84,   198,   -31,   -84,   -84,    -7,   -28,   193,   -84,
     -84,   -72,   -84,   124,   -29,   -23,   -24,   -84,   -84,   -84,
     -83,   141,    73,   -84,   -84,    71,   -84,   -84,   148,   -84,
     -84,   -84,   -84,    88,     2,    10,    -1,   -84,   220,   -84,
     -84,   -84
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -124
static const yytype_int16 yytable[] =
{
      86,    74,    83,    27,   131,    75,    71,    18,    16,   218,
      96,    72,    97,    72,    18,    15,    16,    30,    31,    16,
     102,    27,    11,    10,    67,   146,    84,    12,   147,   150,
    -122,    13,    90,    91,   111,     2,     3,    28,     2,    96,
     108,   116,   122,     1,   146,    73,     3,    68,   226,   102,
      94,    78,    79,    80,    81,    82,   180,    78,    79,    80,
      81,    82,    27,    16,   145,    69,    18,    30,    31,   151,
      75,   137,   183,   184,   153,    70,   147,    76,   152,    87,
     156,   209,   155,    88,     2,     3,    27,   227,     6,    92,
     207,    75,    93,    14,   103,    95,    17,    89,   170,   104,
     168,    95,   176,    19,    20,    21,    22,    23,   178,   106,
     107,   108,   181,    40,   182,   186,   189,   187,   190,   193,
     114,   194,    84,   113,    72,   128,   130,   122,    19,    20,
      21,    22,    23,   203,   200,   202,   129,   132,   206,   133,
     208,   134,   135,   136,   154,   213,   212,   157,    29,   158,
    -103,   167,   215,   217,    19,    20,    21,    22,    23,   118,
      78,    79,    80,    81,    82,    30,    31,    32,   173,   177,
     174,   221,   175,   179,    33,    34,   220,    35,   225,    36,
     195,   196,    37,    38,    39,   197,   209,     2,  -123,    40,
      41,    42,    43,   204,   222,   223,    44,   138,   139,   140,
     141,   142,   238,   239,   115,    78,    79,    80,    81,    82,
     185,    78,    79,    80,    81,    82,    78,    79,    80,    81,
      82,    30,    31,   188,    78,    79,    80,    81,    82,   192,
      78,    79,    80,    81,    82,   224,   138,   139,   140,   141,
     142,    30,    31,   231,    29,   230,   232,   233,   234,    95,
      19,    20,    21,    22,    23,    95,   235,   236,   240,   237,
     105,    30,    31,    32,   198,   117,   166,   112,    95,    73,
      33,    34,   191,    35,    95,    36,   219,   171,    37,    38,
      39,   228,   110,     2,     0,    40,    41,    42,    43,    77,
      78,    79,    80,    81,    82,    19,    20,    21,    22,    23,
     169,    78,    79,    80,    81,    82,    19,    20,    21,    22,
      23,   123,    78,    79,   124,    81,    82,   144,    78,    79,
      80,    81,    82,   159,   160,   161,   162,   163,   164,   199,
      78,    79,    80,    81,    82,   201,    78,    79,    80,    81,
      82,   214,    78,    79,    80,    81,    82,   216,    78,    79,
      80,    81,    82
};

static const yytype_int16 yycheck[] =
{
      34,    29,    33,    10,    87,    29,    28,     8,     6,     4,
      43,    16,    43,    16,    15,     5,    14,    22,    23,    17,
      43,    28,     5,    50,    14,    97,    33,     5,   100,   101,
      33,     0,    39,    40,    68,    44,    45,    50,    44,    72,
      35,    72,    73,     3,   116,    50,    45,    51,     4,    72,
       5,     6,     7,     8,     9,    10,     5,     6,     7,     8,
       9,    10,    69,    61,    95,    52,    67,    22,    23,   103,
      94,    93,   144,   145,   108,     5,   148,    50,   106,    50,
     114,    37,   113,    50,    44,    45,    93,    43,     0,    54,
     173,   115,    50,     5,     5,    50,     8,     5,   129,     4,
     128,    50,   133,    11,    12,    13,    14,    15,   136,     5,
       5,    35,   143,    46,   143,   146,   147,   146,   147,   150,
      51,   150,   129,    16,    16,     5,    42,   158,    11,    12,
      13,    14,    15,   167,   165,   166,    38,     5,   172,    16,
     174,     5,     5,     5,     4,   179,   177,    51,     5,    52,
      51,    51,   183,   184,    11,    12,    13,    14,    15,     5,
       6,     7,     8,     9,    10,    22,    23,    24,    50,    16,
      51,   205,    51,    51,    31,    32,   204,    34,   209,    36,
       4,     4,    39,    40,    41,     4,    37,    44,    33,    46,
      47,    48,    49,    33,     4,    51,    53,    17,    18,    19,
      20,    21,   236,   237,     5,     6,     7,     8,     9,    10,
       5,     6,     7,     8,     9,    10,     6,     7,     8,     9,
      10,    22,    23,     5,     6,     7,     8,     9,    10,     5,
       6,     7,     8,     9,    10,     4,    17,    18,    19,    20,
      21,    22,    23,    51,     5,     4,    51,    51,    51,    50,
      11,    12,    13,    14,    15,    50,     4,    53,     4,    53,
      46,    22,    23,    24,   158,    72,   125,    69,    50,    50,
      31,    32,   148,    34,    50,    36,   203,   129,    39,    40,
      41,   210,    62,    44,    -1,    46,    47,    48,    49,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,     5,     6,     7,     8,     9,    10,     5,     6,     7,
       8,     9,    10,    25,    26,    27,    28,    29,    30,     5,
       6,     7,     8,     9,    10,     5,     6,     7,     8,     9,
      10,     5,     6,     7,     8,     9,    10,     5,     6,     7,
       8,     9,    10
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    44,    45,    56,    57,    98,    99,   100,   101,
      50,     5,     5,     0,    98,   100,    99,    98,   101,    11,
      12,    13,    14,    15,    65,    66,    67,    71,    50,     5,
      22,    23,    24,    31,    32,    34,    36,    39,    40,    41,
      46,    47,    48,    49,    53,    58,    59,    60,    61,    69,
      70,    71,    80,    81,    82,    83,    84,    88,    92,    96,
      97,    98,   102,   103,   104,   105,   106,   100,    51,    52,
       5,    65,    16,    50,    72,    81,    50,     5,     6,     7,
       8,     9,    10,    68,    71,    93,    58,    50,    50,     5,
      71,    71,    54,    50,     5,    50,    61,    68,    73,    74,
      75,    79,    80,     5,     4,    60,     5,     5,    35,    87,
     103,    58,    67,    16,    51,     5,    68,    73,     5,    62,
      63,    64,    68,     5,     8,    68,    85,    72,     5,    38,
      42,    85,     5,    16,     5,     5,     5,    65,    17,    18,
      19,    20,    21,    76,     5,    68,    76,    76,    77,    78,
      76,    58,    72,    58,     4,    68,    58,    51,    52,    25,
      26,    27,    28,    29,    30,    86,    86,    51,    72,     5,
      68,    93,    94,    50,    51,    51,    68,    16,    72,    51,
       5,    68,    79,    76,    76,     5,    68,    79,     5,    68,
      79,    78,     5,    68,    79,     4,     4,     4,    64,     5,
      68,     5,    68,    58,    33,    95,    58,    85,    58,    37,
      89,    90,    68,    58,     5,    68,     5,    68,     4,    87,
      72,    58,     4,    51,     4,    68,     4,    43,    90,    91,
       4,    51,    51,    51,    51,     4,    53,    53,    58,    58,
       4
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
#line 1626 "lexico.c"
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



