
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
     INCREMENTO = 288,
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
     PUBLICA = 302,
     PRIVADA = 303,
     PROTEGIDA = 304,
     ESTA = 305
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
#line 170 "lexico.c"

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
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   358

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  134
/* YYNRULES -- Number of states.  */
#define YYNSTATES  229

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      51,    52,     2,     2,    53,     2,    55,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    10,    13,    16,    18,    20,    22,
      29,    31,    32,    35,    37,    39,    41,    43,    45,    47,
      49,    51,    53,    55,    57,    62,    64,    65,    69,    71,
      73,    75,    77,    78,    82,    84,    87,    88,    90,    92,
      94,    96,    98,   101,   105,   108,   114,   119,   121,   123,
     125,   127,   129,   132,   135,   138,   140,   142,   144,   146,
     149,   153,   157,   161,   165,   167,   169,   171,   173,   175,
     178,   180,   183,   186,   189,   192,   194,   196,   198,   200,
     202,   204,   206,   208,   211,   218,   225,   229,   233,   237,
     241,   243,   245,   247,   249,   251,   253,   255,   257,   261,
     268,   275,   278,   280,   285,   286,   291,   298,   306,   310,
     313,   315,   317,   319,   321,   324,   331,   338,   341,   343,
     351,   360,   363,   365,   370,   377,   383,   391,   394,   396,
     401,   403,   405,   407,   408
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      57,     0,    -1,    58,    98,   100,    -1,    58,    98,    -1,
      58,   100,    -1,   100,    98,    -1,    58,    -1,    98,    -1,
     100,    -1,     3,    51,    66,    52,    59,     4,    -1,    60,
      -1,    -1,    60,    61,    -1,    61,    -1,    62,    -1,    70,
      -1,    71,    -1,    82,    -1,    39,    -1,    40,    -1,    80,
      -1,   102,    -1,   105,    -1,    98,    -1,     5,    51,    63,
      52,    -1,    64,    -1,    -1,    65,    53,    65,    -1,    65,
      -1,    69,    -1,     5,    -1,    67,    -1,    -1,    68,    53,
      68,    -1,    68,    -1,    72,     5,    -1,    -1,     8,    -1,
       6,    -1,     7,    -1,     9,    -1,    10,    -1,    72,     5,
      -1,    72,     5,    73,    -1,     5,    73,    -1,    41,    72,
       5,    16,    69,    -1,    41,     5,    16,    69,    -1,    12,
      -1,    13,    -1,    14,    -1,    15,    -1,    11,    -1,    16,
      74,    -1,    16,    69,    -1,    16,     5,    -1,    75,    -1,
      62,    -1,    80,    -1,    76,    -1,    76,    78,    -1,    69,
      77,    69,    -1,    69,    77,     5,    -1,     5,    77,    69,
      -1,     5,    77,     5,    -1,    17,    -1,    18,    -1,    19,
      -1,    20,    -1,    21,    -1,    78,    79,    -1,    79,    -1,
      77,    69,    -1,    77,     5,    -1,     5,    81,    -1,    81,
       5,    -1,    22,    -1,    23,    -1,    83,    -1,    88,    -1,
      92,    -1,    96,    -1,    97,    -1,    84,    -1,    84,    87,
      -1,    24,    51,    85,    52,    59,     4,    -1,    24,    51,
      85,    52,    59,    87,    -1,    69,    86,    69,    -1,    69,
      86,     5,    -1,     5,    86,    69,    -1,     5,    86,     5,
      -1,     5,    -1,     8,    -1,    25,    -1,    26,    -1,    27,
      -1,    28,    -1,    29,    -1,    30,    -1,    35,    59,     4,
      -1,    36,    51,     5,    52,    89,     4,    -1,    36,    51,
       5,    52,    89,    91,    -1,    89,    90,    -1,    90,    -1,
      37,    69,    54,    59,    -1,    -1,    43,    54,    59,     4,
      -1,    31,    93,    38,    94,    59,     4,    -1,    31,    93,
      38,    93,    95,    59,     4,    -1,    72,     5,    73,    -1,
       5,    73,    -1,     5,    -1,    69,    -1,     5,    -1,    69,
      -1,    33,    73,    -1,    34,    51,    85,    52,    59,     4,
      -1,    32,    59,    42,    51,    85,    52,    -1,    98,    99,
      -1,    99,    -1,    44,     5,    51,    66,    52,    59,     4,
      -1,   104,    44,     5,    51,    66,    52,    59,     4,    -1,
     100,   101,    -1,   101,    -1,    45,     5,    59,     4,    -1,
      45,     5,    54,     5,    59,     4,    -1,   104,    45,     5,
      59,     4,    -1,   104,    45,     5,    54,     5,    59,     4,
      -1,   102,   103,    -1,   103,    -1,   104,    46,    72,     5,
      -1,    47,    -1,    48,    -1,    49,    -1,    -1,    50,    55,
       5,    73,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    11,    11,    11,    11,    11,    11,    11,    11,    13,
      15,    15,    17,    17,    19,    19,    19,    19,    19,    19,
      19,    19,    19,    19,    21,    23,    23,    25,    25,    27,
      27,    29,    29,    31,    31,    33,    33,    35,    35,    35,
      35,    35,    37,    37,    37,    39,    39,    41,    41,    41,
      41,    41,    43,    43,    43,    45,    45,    45,    47,    47,
      49,    49,    49,    49,    51,    51,    51,    51,    51,    53,
      53,    55,    55,    57,    57,    59,    59,    61,    61,    61,
      61,    61,    63,    63,    65,    65,    67,    67,    67,    67,
      67,    67,    69,    69,    69,    69,    69,    69,    71,    73,
      73,    75,    75,    77,    77,    79,    81,    81,    83,    83,
      83,    83,    85,    85,    87,    89,    91,    93,    93,    95,
      95,    97,    97,    99,    99,    99,    99,   101,   101,   103,
     105,   105,   105,   105,   107
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
  "DESDE", "HACER", "INCREMENTO", "MIENTRAS", "SINO", "ELEGIR", "CASO",
  "HASTA", "CONTINUAR", "ROMPER", "CONSTANTE", "CUANDO", "DEFECTO",
  "FUNCION", "CLASE", "PROPIEDAD", "PUBLICA", "PRIVADA", "PROTEGIDA",
  "ESTA", "'('", "')'", "','", "':'", "'.'", "$accept", "programa",
  "principal", "lineascodigo", "lineacodigo", "linea", "invocarmetodo",
  "parametrosenvio", "parenvio", "penvio", "parametrosrecibe", "parecibe",
  "precibe", "valor", "crearvariable", "crearconstante", "tipodato",
  "asignarvalor", "operasignacion", "aritmetico", "oprcomun", "tipoopr",
  "oprcomplemento", "oprcom", "incredismivariable", "incdis",
  "buclecondicion", "condicionif", "condicionsi", "condicion",
  "condicional", "condicionno", "condicionswitch", "casos", "uncaso",
  "elegirotro", "buclefor", "iniciafor", "finfor", "inc", "buclewhile",
  "bucledo", "funciones", "func", "clases", "clas", "propiedades", "prop",
  "ambito", "asignaProp", 0
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
     305,    40,    41,    44,    58,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    57,    57,    57,    57,    57,    57,    58,
      59,    59,    60,    60,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    62,    63,    63,    64,    64,    65,
      65,    66,    66,    67,    67,    68,    68,    69,    69,    69,
      69,    69,    70,    70,    70,    71,    71,    72,    72,    72,
      72,    72,    73,    73,    73,    74,    74,    74,    75,    75,
      76,    76,    76,    76,    77,    77,    77,    77,    77,    78,
      78,    79,    79,    80,    80,    81,    81,    82,    82,    82,
      82,    82,    83,    83,    84,    84,    85,    85,    85,    85,
      85,    85,    86,    86,    86,    86,    86,    86,    87,    88,
      88,    89,    89,    90,    90,    91,    92,    92,    93,    93,
      93,    93,    94,    94,    95,    96,    97,    98,    98,    99,
      99,   100,   100,   101,   101,   101,   101,   102,   102,   103,
     104,   104,   104,   104,   105
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     2,     2,     1,     1,     1,     6,
       1,     0,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     1,     0,     3,     1,     1,
       1,     1,     0,     3,     1,     2,     0,     1,     1,     1,
       1,     1,     2,     3,     2,     5,     4,     1,     1,     1,
       1,     1,     2,     2,     2,     1,     1,     1,     1,     2,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     2,
       1,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     6,     6,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     6,
       6,     2,     1,     4,     0,     4,     6,     7,     3,     2,
       1,     1,     1,     1,     2,     6,     6,     2,     1,     7,
       8,     2,     1,     4,     6,     5,     7,     2,     1,     4,
       1,     1,     1,     0,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,   130,   131,   132,     0,     6,     7,
     118,     8,   122,     0,    32,     0,    11,     1,     3,     4,
     117,     0,     5,   121,     0,     0,    51,    47,    48,    49,
      50,     0,    31,    34,     0,    32,     0,    75,    76,     0,
       0,    11,     0,     0,    18,    19,     0,     0,     0,     0,
      10,    13,    14,    15,    16,     0,    20,     0,    17,    77,
      82,    78,    79,    80,    81,    23,    21,   128,     0,    22,
       2,     0,     0,    11,    11,    36,    35,     0,     0,    26,
      44,    73,     0,   110,    38,    39,    37,    40,    41,   111,
       0,     0,     0,     0,     0,     0,     0,     0,    11,   123,
      12,    42,    74,    11,    83,   127,     0,     0,    32,     0,
       0,     0,    33,    11,    54,    56,    53,    52,    55,    58,
      57,    30,     0,    25,    28,    29,    90,    37,     0,     0,
     109,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      43,     0,     0,     0,    11,   125,     9,     0,    64,    65,
      66,    67,    68,     0,     0,     0,    59,    70,    24,     0,
      92,    93,    94,    95,    96,    97,     0,     0,    11,   108,
     112,   113,     0,    11,     0,    11,   104,    46,     0,   134,
     124,    98,   129,    11,     0,   119,    63,    62,    61,    60,
      72,    71,    69,    27,    89,    88,    87,    86,     0,     0,
      11,     0,     0,     0,     0,     0,   102,    45,     0,   126,
      84,    85,   114,     0,   106,   116,   115,     0,    99,     0,
     101,   100,   120,   107,    11,    11,   103,     0,   105
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     7,     8,    49,    50,    51,    52,   122,   123,   124,
      31,    32,    33,   128,    53,    54,    55,   130,   117,   118,
     119,   155,   156,   157,    56,    57,    58,    59,    60,   129,
     166,   104,    61,   205,   206,   221,    62,    91,   173,   200,
      63,    64,    65,    10,    11,    12,    66,    67,    68,    69
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -93
static const yytype_int16 yypact[] =
{
       7,   -40,    21,    31,   -93,   -93,   -93,    37,    75,    36,
     -93,    75,   -93,   -14,    33,   -39,   141,   -93,    75,    48,
     -93,   -23,    36,   -93,    55,    59,   -93,   -93,   -93,   -93,
     -93,    15,   -93,    20,    63,    33,    12,   -93,   -93,    26,
     286,   233,    57,    61,   -93,   -93,   136,    58,   109,   114,
     233,   -93,   -93,   -93,   -93,   120,   -93,   121,   -93,   -93,
      95,   -93,   -93,   -93,   -93,    36,    53,   -93,    30,   -93,
      48,    86,    85,   187,   233,   302,   -93,    81,    82,   198,
     -93,   -93,   207,   122,   -93,   -93,   -93,   -93,   -93,   -93,
     132,   101,   102,   207,   138,   129,   152,   153,   233,   -93,
     -93,   122,   -93,   233,   -93,   -93,   115,   302,    33,   155,
     158,   164,   -93,   233,   267,   -93,   327,   -93,   -93,   327,
     -93,   -93,   117,   -93,   118,   -93,   224,   124,   224,   126,
     -93,   122,   297,   119,   127,   134,   343,   177,   122,   170,
     -93,   190,   191,   145,   233,   -93,   -93,   216,   -93,   -93,
     -93,   -93,   -93,   253,   314,   320,   327,   -93,   -93,   198,
     -93,   -93,   -93,   -93,   -93,   -93,   326,   332,   233,   -93,
       9,   189,   192,   233,   207,   233,   193,   -93,   343,   -93,
     -93,   -93,   -93,   233,   220,   -93,   -93,   -93,   -93,   -93,
     -93,   -93,   -93,   -93,   -93,   -93,   -93,   -93,     4,   122,
     233,   225,   180,   235,   343,    16,   -93,   -93,   236,   -93,
     -93,   -93,   -93,   238,   -93,   -93,   -93,   212,   -93,   214,
     -93,   -93,   -93,   -93,   233,   233,   -93,   239,   -93
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -93,   -93,   -93,   -41,   -93,   221,   197,   -93,   -93,   111,
     -29,   -93,   201,   -38,   -93,   -93,     3,   -32,   -93,   -93,
     -93,    -7,   -93,   199,   200,   -33,   -93,   -93,   -93,   -92,
     215,   156,   -93,   -93,   151,   -93,   -93,   226,   -93,   -93,
     -93,   -93,    50,     0,    11,    -4,   -93,   291,     5,   -93
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -134
static const yytype_int16 yytable[] =
{
      92,   134,    89,    81,    80,    13,    77,    23,   210,    20,
       1,    14,    35,    13,    21,    23,    13,    34,    20,    19,
     218,    24,    20,    13,    71,    78,    15,    21,    78,    70,
      24,    25,   110,   111,    37,    38,    16,    17,    34,   103,
     116,   125,  -110,    90,    26,    27,    28,    29,    30,    96,
       9,     2,     3,   204,     4,     5,     6,   139,    18,   219,
      72,    22,   141,    79,    73,    20,    23,    74,    76,   140,
      21,   106,   147,    75,    24,    71,   107,    82,    34,   143,
       2,    81,   202,     4,     5,     6,   -36,   114,    84,    85,
      86,    87,    88,     3,   171,     4,     5,     6,   177,   169,
       4,     5,     6,   184,    37,    38,   179,   153,    93,   154,
     142,    34,    94,    97,    98,   187,   189,   191,    99,     2,
       3,   125,     4,     5,     6,   101,   102,   198,   195,   197,
     103,    25,   201,   113,   203,    90,   108,   131,    78,   132,
     207,    95,   208,   135,   133,   136,    36,    26,    27,    28,
      29,    30,    26,    27,    28,    29,    30,   137,   138,   213,
     144,   107,   145,    37,    38,    39,   217,   212,   146,   158,
     174,   159,    40,    41,   180,    42,   -91,    43,   168,   175,
      44,    45,    46,   226,   227,     2,   176,  -133,     4,     5,
       6,    47,    36,   178,   181,    48,   182,   183,    26,    27,
      28,    29,    30,   121,    84,    85,    86,    87,    88,    37,
      38,    39,   126,    84,    85,   127,    87,    88,    40,    41,
     185,    42,  -111,    43,   209,   199,    44,    45,    46,   214,
     204,     2,   215,  -133,     4,     5,     6,    47,    36,   216,
     222,   109,   223,   228,    26,    27,    28,    29,    30,   160,
     161,   162,   163,   164,   165,    37,    38,    39,   186,    84,
      85,    86,    87,    88,    40,    41,   224,    42,   225,    43,
     193,   100,    44,    45,    46,   115,   112,     2,   120,  -133,
       4,     5,     6,    47,   148,   149,   150,   151,   152,    37,
      38,    83,    84,    85,    86,    87,    88,    26,    27,    28,
      29,    30,   170,    84,    85,    86,    87,    88,    26,    27,
      28,    29,    30,    26,    27,    28,    29,    30,    79,   188,
      84,    85,    86,    87,    88,   190,    84,    85,    86,    87,
      88,   194,    84,    85,    86,    87,    88,   196,    84,    85,
      86,    87,    88,   167,   148,   149,   150,   151,   152,    84,
      85,    86,    87,    88,   211,   192,   220,   105,   172
};

static const yytype_uint8 yycheck[] =
{
      41,    93,    40,    36,    36,     0,    35,    11,     4,     9,
       3,    51,    51,     8,     9,    19,    11,    14,    18,     8,
       4,    44,    22,    18,    19,    16,     5,    22,    16,    18,
      44,    45,    73,    74,    22,    23,     5,     0,    35,    35,
      78,    79,    33,    40,    11,    12,    13,    14,    15,    46,
       0,    44,    45,    37,    47,    48,    49,    98,     8,    43,
       5,    11,   103,    51,     5,    65,    70,    52,     5,   101,
      65,    66,   113,    53,    44,    70,    46,    51,    75,   108,
      44,   114,   174,    47,    48,    49,    53,     5,     6,     7,
       8,     9,    10,    45,   132,    47,    48,    49,   136,   131,
      47,    48,    49,   144,    22,    23,   138,   114,    51,   116,
     107,   108,    51,    55,     5,   153,   154,   155,     4,    44,
      45,   159,    47,    48,    49,     5,     5,   168,   166,   167,
      35,    45,   173,    52,   175,   132,    51,     5,    16,    38,
     178,     5,   183,     5,    42,    16,     5,    11,    12,    13,
      14,    15,    11,    12,    13,    14,    15,     5,     5,   200,
       5,    46,     4,    22,    23,    24,   204,   199,     4,    52,
      51,    53,    31,    32,     4,    34,    52,    36,    52,    52,
      39,    40,    41,   224,   225,    44,    52,    46,    47,    48,
      49,    50,     5,    16,     4,    54,     5,    52,    11,    12,
      13,    14,    15,     5,     6,     7,     8,     9,    10,    22,
      23,    24,     5,     6,     7,     8,     9,    10,    31,    32,
       4,    34,    33,    36,     4,    33,    39,    40,    41,     4,
      37,    44,    52,    46,    47,    48,    49,    50,     5,     4,
       4,    54,     4,     4,    11,    12,    13,    14,    15,    25,
      26,    27,    28,    29,    30,    22,    23,    24,     5,     6,
       7,     8,     9,    10,    31,    32,    54,    34,    54,    36,
     159,    50,    39,    40,    41,    78,    75,    44,    78,    46,
      47,    48,    49,    50,    17,    18,    19,    20,    21,    22,
      23,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    11,    12,    13,    14,    15,    51,     5,
       6,     7,     8,     9,    10,     5,     6,     7,     8,     9,
      10,     5,     6,     7,     8,     9,    10,     5,     6,     7,
       8,     9,    10,   128,    17,    18,    19,    20,    21,     6,
       7,     8,     9,    10,   198,   156,   205,    66,   132
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    44,    45,    47,    48,    49,    57,    58,    98,
      99,   100,   101,   104,    51,     5,     5,     0,    98,   100,
      99,   104,    98,   101,    44,    45,    11,    12,    13,    14,
      15,    66,    67,    68,    72,    51,     5,    22,    23,    24,
      31,    32,    34,    36,    39,    40,    41,    50,    54,    59,
      60,    61,    62,    70,    71,    72,    80,    81,    82,    83,
      84,    88,    92,    96,    97,    98,   102,   103,   104,   105,
     100,   104,     5,     5,    52,    53,     5,    66,    16,    51,
      73,    81,    51,     5,     6,     7,     8,     9,    10,    69,
      72,    93,    59,    51,    51,     5,    72,    55,     5,     4,
      61,     5,     5,    35,    87,   103,   104,    46,    51,    54,
      59,    59,    68,    52,     5,    62,    69,    74,    75,    76,
      80,     5,    63,    64,    65,    69,     5,     8,    69,    85,
      73,     5,    38,    42,    85,     5,    16,     5,     5,    59,
      73,    59,    72,    66,     5,     4,     4,    59,    17,    18,
      19,    20,    21,    77,    77,    77,    78,    79,    52,    53,
      25,    26,    27,    28,    29,    30,    86,    86,    52,    73,
       5,    69,    93,    94,    51,    52,    52,    69,    16,    73,
       4,     4,     5,    52,    59,     4,     5,    69,     5,    69,
       5,    69,    79,    65,     5,    69,     5,    69,    59,    33,
      95,    59,    85,    59,    37,    89,    90,    69,    59,     4,
       4,    87,    73,    59,     4,    52,     4,    69,     4,    43,
      90,    91,     4,     4,    54,    54,    59,    59,     4
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
#line 1611 "lexico.c"
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



