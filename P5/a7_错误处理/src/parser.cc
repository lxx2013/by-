/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     num_tok = 258,
     var_tok = 259,
     eol_tok = 260,
     err_tok = 261,
     const_tok = 262,
     int_tok = 263,
     void_tok = 264,
     if_tok = 265,
     else_tok = 266,
     while_tok = 267,
     RelOp = 268,
     zg = 269
   };
#endif
/* Tokens.  */
#define num_tok 258
#define var_tok 259
#define eol_tok 260
#define err_tok 261
#define const_tok 262
#define int_tok 263
#define void_tok 264
#define if_tok 265
#define else_tok 266
#define while_tok 267
#define RelOp 268
#define zg 269




/* Copy the first part of user declarations.  */
#line 1 "config/parser.y"

#include <stdio.h>
#include <string>
#include <vector>
#define DEBUG
#include "node.hh"
#include "util.hh"
#include "global.hh"
extern int yylex ();
extern void yyerror (const char *msg);
InputNode *root;
//flag
int error_flag;         // 0: common state(could generate new node) 1: don't generate new node;
int error_debug_flag;   // when encounter error:{ 0 : common state(delete all_node and set error_flag 1);
                        //                        1 : just generate modified Node;
                        //                            /* this flag is set by 'input' at the begin of parser */ }
// all_node
std::vector<Node*>all_node;
void delete_all_node( )
{
    Node* it;
    int i;
    int len = all_node.size();
    //printf("all_node.size() = %d\n",len);
    for(i = len-1 ; i>=0 ;i--)
    {  
        it = all_node[i];
        delete it;
        all_node.pop_back();
    }
    root = NULL;
    //printf("all_node.size() = %lu\n",all_node.size());
}
//show_line //
std::string line_str;
void show_line(int line,char* filename)
{
    line_str = "";
    line_str+="./bin/sed.sh '";
    char temp[10];
    sprintf(temp,"%d",line);
    line_str+=temp;
    line_str+="p' ";
    line_str+=filename;
    line_str+=".temp.c";
    system(line_str.c_str());
}
void print_blank(int column)
{
    int i=0;
    for(i=0;i<column-1;i++)
        line(" ");
    line("^\n");
};
//**********//


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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 59 "config/parser.y"
{
    int  num;
    std::string *var;
    Node *node;
}
/* Line 193 of yacc.c.  */
#line 187 "src/parser.cc"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 212 "src/parser.cc"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   223

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNRULES -- Number of states.  */
#define YYNSTATES  125

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   269

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    21,     2,     2,
      16,    15,    19,    18,    27,    17,     2,    20,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    26,
       2,    14,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    28,     2,    29,    22,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    24,     2,    25,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    12,    13,    23
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     7,     9,    11,    17,    22,    27,
      30,    34,    36,    39,    41,    43,    46,    51,    55,    59,
      61,    69,    76,    82,    87,    93,    98,   100,   104,   106,
     108,   113,   117,   119,   123,   127,   129,   137,   146,   150,
     152,   156,   158,   162,   164,   166,   170,   174,   176,   180,
     184,   188,   192,   196,   199,   202,   205,   207,   210,   213,
     215,   218,   220
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      31,     0,    -1,    -1,    31,    32,    -1,    39,    -1,    33,
      -1,     9,     4,    16,    15,    34,    -1,     9,     4,    15,
      34,    -1,     9,     4,    16,    34,    -1,    24,    25,    -1,
      24,    35,    25,    -1,    36,    -1,    35,    36,    -1,    39,
      -1,    37,    -1,    48,    26,    -1,     4,    16,    15,    26,
      -1,     4,    15,    26,    -1,     4,    16,    26,    -1,    34,
      -1,    10,    16,    38,    15,    37,    11,    37,    -1,    10,
      16,    38,    37,    11,    37,    -1,    10,    16,    38,    15,
      37,    -1,    10,    16,    38,    37,    -1,    12,    16,    38,
      15,    37,    -1,    12,    16,    38,    37,    -1,    26,    -1,
      49,    13,    49,    -1,    40,    -1,    44,    -1,     7,     8,
      41,    26,    -1,     7,    41,    26,    -1,    42,    -1,    41,
      27,    42,    -1,     4,    14,    49,    -1,    43,    -1,     4,
      28,    29,    14,    24,    47,    25,    -1,     4,    28,    49,
      29,    14,    24,    47,    25,    -1,     8,    45,    26,    -1,
      46,    -1,    45,    27,    46,    -1,    51,    -1,     4,    14,
      49,    -1,    43,    -1,    49,    -1,    47,    27,    49,    -1,
      51,    14,    49,    -1,     3,    -1,    49,    18,    49,    -1,
      49,    17,    49,    -1,    49,    19,    49,    -1,    49,    20,
      49,    -1,    49,    21,    49,    -1,    17,    49,    -1,    18,
      49,    -1,    50,    15,    -1,    50,    -1,    49,    15,    -1,
      49,    49,    -1,    51,    -1,    16,    49,    -1,     4,    -1,
       4,    28,    49,    29,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    85,    85,    93,   104,   109,   114,   124,   143,   163,
     173,   192,   203,   216,   220,   225,   229,   239,   259,   278,
     283,   293,   315,   325,   347,   356,   376,   386,   399,   403,
     409,   418,   431,   441,   453,   462,   467,   477,   489,   500,
     510,   523,   528,   537,   543,   553,   566,   577,   586,   596,
     606,   616,   626,   636,   646,   656,   664,   683,   702,   721,
     727,   732,   742
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "num_tok", "var_tok", "eol_tok",
  "err_tok", "const_tok", "int_tok", "void_tok", "if_tok", "else_tok",
  "while_tok", "RelOp", "'='", "')'", "'('", "'-'", "'+'", "'*'", "'/'",
  "'%'", "'^'", "zg", "'{'", "'}'", "';'", "','", "'['", "']'", "$accept",
  "input", "CompUnit", "FuncDef", "Block", "BlockItemH", "BlockItem",
  "Stmt", "Cond", "Decl", "ConstDecl", "ConstDefH", "ConstDef", "ArrayDef",
  "VarDecl", "VarDefH", "VarDef", "ExpH", "asgn", "exp", "ExpL", "LVal", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,    61,    41,    40,    45,    43,    42,
      47,    37,    94,   269,   123,   125,    59,    44,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    30,    31,    31,    32,    32,    33,    33,    33,    34,
      34,    35,    35,    36,    36,    37,    37,    37,    37,    37,
      37,    37,    37,    37,    37,    37,    37,    38,    39,    39,
      40,    40,    41,    41,    42,    42,    43,    43,    44,    45,
      45,    46,    46,    46,    47,    47,    48,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      50,    51,    51
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     5,     4,     4,     2,
       3,     1,     2,     1,     1,     2,     4,     3,     3,     1,
       7,     6,     5,     4,     5,     4,     1,     3,     1,     1,
       4,     3,     1,     3,     3,     1,     7,     8,     3,     1,
       3,     1,     3,     1,     1,     3,     3,     1,     3,     3,
       3,     3,     3,     2,     2,     2,     1,     2,     2,     1,
       2,     1,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     3,     5,     4,    28,
      29,     0,     0,     0,    32,    35,    61,    43,     0,    39,
      41,     0,     0,     0,     0,    31,     0,     0,     0,    38,
       0,     0,     0,    47,    61,     0,     0,     0,    34,    56,
      59,     0,     0,    30,    33,    42,     0,    40,     0,     7,
       0,     8,     0,    60,    53,    54,    57,     0,     0,     0,
       0,     0,    58,    55,     0,     0,    62,    61,     0,     0,
       9,    26,    19,     0,    11,    14,    13,     0,     0,     6,
       0,    49,    48,    50,    51,    52,     0,     0,     0,     0,
       0,     0,    10,    12,    15,     0,    62,     0,    44,     0,
      17,     0,    18,     0,     0,     0,    46,    36,     0,     0,
      16,     0,    23,     0,     0,    25,    45,    37,    22,     0,
      27,    24,     0,    21,    20
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     6,     7,    72,    73,    74,    75,   103,    76,
       9,    13,    14,    15,    10,    18,    19,    97,    77,    62,
      39,    40
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -23
static const yytype_int16 yypact[] =
{
     -23,    54,   -23,    49,     0,    21,   -23,   -23,   -23,   -23,
     -23,     7,    39,   -15,   -23,   -23,     8,   -23,    68,   -23,
     -23,    96,   205,     2,    90,   -23,    39,   205,     2,   -23,
       0,    44,    -1,   -23,    36,   205,   205,   205,   180,    62,
     -23,    67,    30,   -23,   -23,   180,   105,   -23,    48,   -23,
      44,   -23,   205,   199,   110,   110,   -23,   205,   205,   205,
     205,   205,   180,   -23,    61,    76,    76,    14,    81,    84,
     -23,   -23,   -23,    79,   -23,   -23,   -23,    66,    88,   -23,
     124,   110,   110,   129,   129,   129,   205,    82,    93,    -2,
     205,   205,   -23,   -23,   -23,   205,   -23,    40,   180,   205,
     -23,   109,   -23,   142,   172,   146,   180,   -23,   205,    53,
     -23,    72,   125,   205,    72,   -23,   180,   -23,   126,    72,
     199,   -23,    72,   -23,   -23
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -23,   -23,   -23,   -23,   -22,   -23,    65,    60,    56,   147,
     -23,   137,   133,    -3,   -23,   -23,   121,    63,   -23,   -20,
     -23,    -4
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      20,    17,    38,    42,    16,    33,    34,    45,    46,    49,
      51,    25,    26,   101,    50,    53,    54,    55,    35,    36,
      37,    22,    27,    48,   102,    21,    20,    17,    79,    88,
      89,    41,    80,    33,    34,    23,    28,    81,    82,    83,
      84,    85,    52,    11,    78,    56,    35,    57,    58,    59,
      60,    61,    67,    11,     2,     3,     4,    12,    68,    65,
      69,     3,     4,     5,    52,   107,    98,   108,    48,    78,
     104,   104,    48,    70,    71,   106,    67,    63,   117,    98,
     108,    64,    68,    67,    69,    86,     3,     4,   116,    68,
      87,    69,    94,   120,    29,    30,    48,    90,    71,    78,
      91,    78,    95,    48,    92,    71,    99,    78,    33,    34,
      78,    31,    32,    33,    34,    78,    43,    26,    78,   100,
      56,    35,    57,    58,    59,    60,    61,    33,    34,    59,
      60,    61,    33,    34,    66,   110,   119,   122,    93,    56,
      35,    57,    58,    59,    60,    61,    67,   105,     8,    24,
      67,    47,    68,    96,    69,     0,    68,   111,    69,    44,
       0,   114,   109,   112,     0,   115,    48,     0,    71,     0,
      48,   118,    71,     0,   121,    33,    34,     0,     0,   123,
       0,     0,   124,    33,    34,   113,     0,    56,    35,    57,
      58,    59,    60,    61,     0,    56,    35,    57,    58,    59,
      60,    61,    33,    34,     0,     0,     0,     0,    33,    34,
       0,     0,     0,     0,     0,    35,    57,    58,    59,    60,
      61,    35,    36,    37
};

static const yytype_int8 yycheck[] =
{
       4,     4,    22,    23,     4,     3,     4,    27,    28,    31,
      32,    26,    27,    15,    15,    35,    36,    37,    16,    17,
      18,    14,    14,    24,    26,     4,    30,    30,    50,    15,
      16,    29,    52,     3,     4,    28,    28,    57,    58,    59,
      60,    61,    28,     4,    48,    15,    16,    17,    18,    19,
      20,    21,     4,     4,     0,     7,     8,     8,    10,    29,
      12,     7,     8,     9,    28,    25,    86,    27,    24,    73,
      90,    91,    24,    25,    26,    95,     4,    15,    25,    99,
      27,    14,    10,     4,    12,    24,     7,     8,   108,    10,
      14,    12,    26,   113,    26,    27,    24,    16,    26,   103,
      16,   105,    14,    24,    25,    26,    24,   111,     3,     4,
     114,    15,    16,     3,     4,   119,    26,    27,   122,    26,
      15,    16,    17,    18,    19,    20,    21,     3,     4,    19,
      20,    21,     3,     4,    29,    26,    11,    11,    73,    15,
      16,    17,    18,    19,    20,    21,     4,    91,     1,    12,
       4,    30,    10,    29,    12,    -1,    10,    15,    12,    26,
      -1,    15,    99,   103,    -1,   105,    24,    -1,    26,    -1,
      24,   111,    26,    -1,   114,     3,     4,    -1,    -1,   119,
      -1,    -1,   122,     3,     4,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    -1,    15,    16,    17,    18,    19,
      20,    21,     3,     4,    -1,    -1,    -1,    -1,     3,     4,
      -1,    -1,    -1,    -1,    -1,    16,    17,    18,    19,    20,
      21,    16,    17,    18
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    31,     0,     7,     8,     9,    32,    33,    39,    40,
      44,     4,     8,    41,    42,    43,     4,    43,    45,    46,
      51,     4,    14,    28,    41,    26,    27,    14,    28,    26,
      27,    15,    16,     3,     4,    16,    17,    18,    49,    50,
      51,    29,    49,    26,    42,    49,    49,    46,    24,    34,
      15,    34,    28,    49,    49,    49,    15,    17,    18,    19,
      20,    21,    49,    15,    14,    29,    29,     4,    10,    12,
      25,    26,    34,    35,    36,    37,    39,    48,    51,    34,
      49,    49,    49,    49,    49,    49,    24,    14,    15,    16,
      16,    16,    25,    36,    26,    14,    29,    47,    49,    24,
      26,    15,    26,    38,    49,    38,    49,    25,    27,    47,
      26,    15,    37,    13,    15,    37,    49,    25,    37,    11,
      49,    37,    11,    37,    37
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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
		  Type, Value, Location); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
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
     `$$ = $1'.

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
        case 2:
#line 85 "config/parser.y"
    {   
                            error_flag = 0;
                            error_debug_flag = 0;                           
                            root = new InputNode ();
                            all_node.push_back((Node*)root);
                            line("Line:%-3d",1);
                            debug ("input ::= empty\n"); 
                        ;}
    break;

  case 3:
#line 93 "config/parser.y"
    {                             
                            if ((yyvsp[(2) - (2)].node)!=NULL)   // ignore empty line
                            {   
                                if(error_flag == 0)
                                    root->append ((CompUnitNode*)(yyvsp[(2) - (2)].node));
                            }
                            line("Line:%-3d",1);
                            debug ("input ::= CompUnit\n");
                        ;}
    break;

  case 4:
#line 104 "config/parser.y"
    {   line("Line:%-3d",(yylsp[(1) - (1)]).first_line);
                                    debug ("CompUnit ::= Decl\n");
                                    (yyval.node) = (yyvsp[(1) - (1)].node);
                                    //printf("%d %d \n", $$->loc->first_line,$$->loc->last_column);
                                ;}
    break;

  case 5:
#line 109 "config/parser.y"
    {   line("Line:%-3d",(yylsp[(1) - (1)]).first_line);
                                    debug("CompUnit ::= FuncDef\n");
                                    (yyval.node) = (yyvsp[(1) - (1)].node);
                                ;}
    break;

  case 6:
#line 114 "config/parser.y"
    {   line("Line:%-3d",(yylsp[(1) - (5)]).first_line);
                                                    debug("FuncDef ::= void ident() Block\n");
                                                    if(error_flag == 0)
                                                    {   
                                                        (yyval.node) = new FuncDefNode(new VarNode((yyvsp[(2) - (5)].var)),(BlockNode*)(yyvsp[(5) - (5)].node)); 
                                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                        all_node.push_back((Node*)(yyval.node));
                                                    }                                                   
                                                ;}
    break;

  case 7:
#line 124 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);debug("FuncDef ::= void ident'(') Block\n");
                                                    error("%s:%3d.(%2d) left paren missing, there should be '('\n",infile_name,(yyloc).first_line,(yylsp[(1) - (4)]).last_column+1);
                                                    show_line((yyloc).first_line,infile_name);
                                                    print_blank((yylsp[(1) - (4)]).last_column+1);
                                                    if(error_flag == 0)
                                                    {   
                                                        if(error_debug_flag == 0)
                                                        {
                                                            delete_all_node();
                                                            error_flag = 1;
                                                        }
                                                        else
                                                        {
                                                            (yyval.node) = new FuncDefNode(new VarNode((yyvsp[(2) - (4)].var)),(BlockNode*)(yyvsp[(4) - (4)].node)); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }
                                                    }
                                                ;}
    break;

  case 8:
#line 143 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);debug("FuncDef ::= void ident(')' Block\n");
                                                    error("%s:%3d.(%2d) right paren missing, there should be ')'\n",infile_name,(yyloc).first_line,(yylsp[(3) - (4)]).last_column+1);
                                                    show_line((yyloc).first_line,infile_name);
                                                    print_blank((yylsp[(3) - (4)]).last_column+1);
                                                    if(error_flag == 0)
                                                    {   
                                                        if(error_debug_flag == 0)
                                                        {
                                                            delete_all_node();
                                                            error_flag = 1;
                                                        }
                                                        else
                                                        {
                                                            (yyval.node) = new FuncDefNode(new VarNode((yyvsp[(2) - (4)].var)),(BlockNode*)(yyvsp[(4) - (4)].node)); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }
                                                    }
                                                ;}
    break;

  case 9:
#line 163 "config/parser.y"
    {   line("Line:%-3d",(yylsp[(1) - (2)]).first_line);
                                        debug("Block ::= {  }\n");
                                        if(error_flag == 0)
                                        {   
                                            (yyval.node) = new BlockNode(0);
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        } 

                                    ;}
    break;

  case 10:
#line 173 "config/parser.y"
    {   line("Line:%-3d",(yylsp[(1) - (3)]).first_line);
                                        debug("Block ::= { BlockItemH }\n");
                                        if((yyvsp[(2) - (3)].node)==0)
                                        {
                                            printf("paser.y:73 BlockItem = NULL!\n");
                                            (yyval.node) = NULL;
                                        }
                                        else
                                        {    
                                            if(error_flag == 0)
                                            {   
                                                (yyval.node) = new BlockNode((BlockItemHNode*)(yyvsp[(2) - (3)].node));
                                                (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                all_node.push_back((Node*)(yyval.node));
                                            } 

                                        }
                                    ;}
    break;

  case 11:
#line 192 "config/parser.y"
    {   line("Line:%-3d",(yylsp[(1) - (1)]).first_line);
                                        debug("BlockItemH ::= BlockItem\n");
                                        if(error_flag == 0)
                                        {   
                                            (yyval.node) = new BlockItemHNode();
                                            ((BlockItemHNode*)(yyval.node))->append((BlockItemNode*)(yyvsp[(1) - (1)].node));
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        } 

                                    ;}
    break;

  case 12:
#line 203 "config/parser.y"
    {   line("Line:%-3d",(yylsp[(1) - (2)]).first_line);
                                        debug("BlockItemH ::= BlockItemH BlockItem\n");
                                        if((yyvsp[(2) - (2)].node)!=NULL)
                                        { 
                                            if(error_flag == 0)
                                            {   
                                                ((BlockItemHNode*)(yyval.node))->append((BlockItemNode*)(yyvsp[(2) - (2)].node));
                                                (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            } 
                                        }

                                    ;}
    break;

  case 13:
#line 216 "config/parser.y"
    {   line("Line:%-3d",(yylsp[(1) - (1)]).first_line);
                                        debug("BlockItem ::= Decl\n");
                                        (yyval.node) = (yyvsp[(1) - (1)].node);
                                    ;}
    break;

  case 14:
#line 220 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);
                                        debug("BlockItem ::= Stmt\n");
                                        (yyval.node) = (yyvsp[(1) - (1)].node);
                                    ;}
    break;

  case 15:
#line 225 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);
                                        debug("Stmt ::= asgn;\n");
                                        (yyval.node) = (yyvsp[(1) - (2)].node);
                                    ;}
    break;

  case 16:
#line 229 "config/parser.y"
    {   
                                                line("Line:%-3d",(yyloc).first_line);
                                                debug("Stmt ::= ident();\n");
                                                if(error_flag == 0)
                                                {   
                                                    (yyval.node) = new FuncStmtNode(new VarNode((yyvsp[(1) - (4)].var)));
                                                    (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                    all_node.push_back((Node*)(yyval.node));
                                                } 
                                            ;}
    break;

  case 17:
#line 239 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);debug("Stmt ::= ident'(')\n");
                                                error("%s:%3d.(%2d) left paren missing, there should be '('\n",infile_name,(yyloc).first_line,(yylsp[(2) - (3)]).last_column-1);
                                                show_line((yyloc).first_line,infile_name);
                                                print_blank((yylsp[(2) - (3)]).last_column-1);
                                               
                                                if(error_flag == 0)
                                                {   
                                                    if(error_debug_flag == 0)
                                                    {
                                                        delete_all_node();
                                                        error_flag = 1;
                                                    }
                                                    else
                                                    {
                                                        (yyval.node) = new FuncStmtNode(new VarNode((yyvsp[(1) - (3)].var)));
                                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                        all_node.push_back((yyval.node));
                                                    }
                                                }
                                            ;}
    break;

  case 18:
#line 259 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);debug("Stmt ::= ident(')'\n");
                                                error("%s:%3d.(%2d) right paren missing, there should be ')'\n",infile_name,(yyloc).first_line,(yylsp[(2) - (3)]).last_column+1);
                                                show_line((yyloc).first_line,infile_name);
                                                print_blank((yylsp[(2) - (3)]).last_column+1);
                                                if(error_flag == 0)
                                                {   
                                                    if(error_debug_flag == 0)
                                                    {
                                                        delete_all_node();
                                                        error_flag = 1;
                                                    }
                                                    else
                                                    {
                                                        (yyval.node) = new FuncStmtNode(new VarNode((yyvsp[(1) - (3)].var)));
                                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                        all_node.push_back((yyval.node));
                                                    }
                                                }
                                            ;}
    break;

  case 19:
#line 278 "config/parser.y"
    {   
                                                line("Line:%-3d",(yyloc).first_line);
                                                debug("Stmt ::= Block\n");
                                                (yyval.node) = (yyvsp[(1) - (1)].node);
                                            ;}
    break;

  case 20:
#line 283 "config/parser.y"
    {   
                                                                    line("Line:%-3d",(yyloc).first_line);
                                                                    debug("Stmt ::= if(Cond)Stmt else Stmt\n");
                                                                    if(error_flag == 0)
                                                                    {   
                                                                        (yyval.node) = new IFELStmtNode((CondNode*)(yyvsp[(3) - (7)].node),(StmtNode*)(yyvsp[(5) - (7)].node),(StmtNode*)(yyvsp[(7) - (7)].node));
                                                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                                        all_node.push_back((Node*)(yyval.node));
                                                                    } 
                                                                ;}
    break;

  case 21:
#line 293 "config/parser.y"
    {   
                                                                    line("Line:%-3d",(yyloc).first_line);
                                                                    debug("Stmt ::= if(Cond ')' Stmt else Stmt\n");
                                                                    error("%s:%3d.(%2d) right paren missing, there should be ')'\n",infile_name,(yyloc).first_line,(yylsp[(3) - (6)]).last_column+1);
                                                                    show_line((yyloc).first_line,infile_name);
                                                                    print_blank((yylsp[(3) - (6)]).last_column+1);
                                                                    if(error_flag == 0)
                                                                    {   
                                                                        if(error_debug_flag == 0)
                                                                        {
                                                                            delete_all_node();
                                                                            error_flag = 1;
                                                                        }
                                                                        else
                                                                        {
                                                                            (yyval.node) = new IFELStmtNode((CondNode*)(yyvsp[(3) - (6)].node),(StmtNode*)(yyvsp[(4) - (6)].node),(StmtNode*)(yyvsp[(6) - (6)].node));
                                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                                            all_node.push_back((Node*)(yyval.node));
                                                                        }
                                                                    } 
                                                                ;}
    break;

  case 22:
#line 315 "config/parser.y"
    {   
                                                            line("Line:%-3d",(yyloc).first_line);
                                                            debug("Stmt ::= if(Cond)Stmt\n");
                                                            if(error_flag == 0)
                                                            {   
                                                                (yyval.node) = new IFStmtNode((CondNode*)(yyvsp[(3) - (5)].node),(StmtNode*)(yyvsp[(5) - (5)].node));
                                                                (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                                all_node.push_back((Node*)(yyval.node));
                                                            } 
                                                ;}
    break;

  case 23:
#line 325 "config/parser.y"
    {   
                                                            line("Line:%-3d",(yyloc).first_line);
                                                            debug("Stmt ::= if(Cond ')' Stmt\n");
                                                            error("%s:%3d.(%2d) right paren missing, there should be ')'\n",infile_name,(yyloc).first_line,(yylsp[(3) - (4)]).last_column+1);
                                                            show_line((yyloc).first_line,infile_name);
                                                            print_blank((yylsp[(3) - (4)]).last_column+1);
                                                            if(error_flag == 0)
                                                            {   
                                                                if(error_debug_flag == 0)
                                                                {
                                                                    delete_all_node();
                                                                    error_flag = 1;
                                                                }
                                                                else
                                                                {
                                                                    (yyval.node) = new IFStmtNode((CondNode*)(yyvsp[(3) - (4)].node),(StmtNode*)(yyvsp[(4) - (4)].node));
                                                                    (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                                    all_node.push_back((Node*)(yyval.node));
                                                                }
                                                            } 
                                                ;}
    break;

  case 24:
#line 347 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);
                                                debug("Stmt ::= While(Cond) Stmt\n");
                                                if(error_flag == 0)
                                                {   
                                                    (yyval.node) = new WhileStmtNode((CondNode*)(yyvsp[(3) - (5)].node),(StmtNode*)(yyvsp[(5) - (5)].node));
                                                    (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                    all_node.push_back((Node*)(yyval.node));
                                                } 
                                            ;}
    break;

  case 25:
#line 356 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);
                                                debug("Stmt ::= While(Cond ')'' Stmt\n");
                                                error("%s:%3d.(%2d) right paren missing, there should be ')'\n",infile_name,(yyloc).first_line,(yylsp[(3) - (4)]).last_column+1);
                                                show_line((yyloc).first_line,infile_name);
                                                print_blank((yylsp[(3) - (4)]).last_column+1);
                                                if(error_flag == 0)
                                                {   
                                                    if(error_debug_flag == 0)
                                                    {
                                                        delete_all_node();
                                                        error_flag = 1;
                                                    }
                                                    else
                                                    {
                                                        (yyval.node) = new WhileStmtNode((CondNode*)(yyvsp[(3) - (4)].node),(StmtNode*)(yyvsp[(4) - (4)].node));
                                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                        all_node.push_back((Node*)(yyval.node));
                                                    }
                                                }  
                                            ;}
    break;

  case 26:
#line 376 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);
                                                debug("Stmt ::= ;\n");
                                                if(error_flag == 0)
                                                {   
                                                    (yyval.node) = new VarNode(new std::string (";"));
                                                    (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                    all_node.push_back((Node*)(yyval.node));
                                                } 
                                            ;}
    break;

  case 27:
#line 386 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);
                                        debug("Cond ::= Exp %s Exp\n",(yyvsp[(2) - (3)].var)->c_str());
                                        if(error_flag == 0)
                                        {   
                                            (yyval.node) = new CondNode((ExpNode*)(yyvsp[(1) - (3)].node),new VarNode((yyvsp[(2) - (3)].var)),(ExpNode*)(yyvsp[(3) - (3)].node));
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        } 
                                    ;}
    break;

  case 28:
#line 399 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);
                                    debug ("Decl ::= ConstDecl\n");
                                    (yyval.node) = (yyvsp[(1) - (1)].node);; 
                                ;}
    break;

  case 29:
#line 403 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);
                                    debug ("Decl ::= VarDecl\n");
                                    (yyval.node) = (yyvsp[(1) - (1)].node);
                                ;}
    break;

  case 30:
#line 409 "config/parser.y"
    {       line("Line:%-3d",(yyloc).first_line);
                                                        debug("ConstDecl ::= const int ConstDefH;\n");
                                                        if(error_flag == 0)
                                                        {   
                                                            (yyval.node) = new ConstDeclNode( (ConstDefHNode*)(yyvsp[(3) - (4)].node));
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        } 
                                                ;}
    break;

  case 31:
#line 418 "config/parser.y"
    {       line("Line:%-3d",(yyloc).first_line);
                                                        debug("ConstDecl ::= const 'int' ConstDefH;\n");
                                                        warning("%s:%3d.(%2d) type specifier missing, defaults to 'int'\n",infile_name,(yyloc).first_line,(yylsp[(1) - (3)]).last_column+1);
                                                        show_line((yyloc).first_line,infile_name);
                                                        print_blank((yylsp[(1) - (3)]).last_column+1);
                                                        if(error_flag == 0)
                                                        {   
                                                            (yyval.node) = new ConstDeclNode( (ConstDefHNode*)(yyvsp[(2) - (3)].node));
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        } 
                                                ;}
    break;

  case 32:
#line 431 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);
                                            debug("ConstDefH ::= ConstDef\n");
                                            if(error_flag == 0)
                                            {   
                                                (yyval.node) = new ConstDefHNode();
                                                ((ConstDefHNode*)(yyval.node))->append((ConstDefNode*)(yyvsp[(1) - (1)].node));
                                                (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                all_node.push_back((Node*)(yyval.node));
                                            } 
                                        ;}
    break;

  case 33:
#line 441 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);
                                            debug("ConstDefH ::= ConstDefH,ConstDef\n");
                                            if((yyvsp[(3) - (3)].node)!=NULL)
                                            {
                                                if(error_flag == 0)
                                                {   
                                                    ((ConstDefHNode*)(yyval.node))->append((ConstDefNode*)(yyvsp[(3) - (3)].node));
                                                    (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                } 
                                            }
                                        ;}
    break;

  case 34:
#line 453 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);
                                    debug("ConstDef ::= ident = Exp\n");
                                    if(error_flag == 0)
                                    {   
                                        (yyval.node) = new AsgnNode((LValNode*)new VarNode((yyvsp[(1) - (3)].var)),(ExpNode*)(yyvsp[(3) - (3)].node));
                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                        all_node.push_back((Node*)(yyval.node));
                                    } 
                                ;}
    break;

  case 35:
#line 462 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);
                                    debug("ConstDef ::= ArrayDef\n");
                                    (yyval.node) = (yyvsp[(1) - (1)].node);
                                ;}
    break;

  case 36:
#line 467 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);
                                                    debug("ArrayDef ::= ident[]={ExpH}\n");
                                                    if(error_flag == 0)
                                                    {   
                                                        (yyval.node) = new ArrayDef_1_Node(new VarNode((yyvsp[(1) - (7)].var)),(ExpHNode*)(yyvsp[(6) - (7)].node));
                                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                        all_node.push_back((Node*)(yyval.node));
                                                    } 

                                                ;}
    break;

  case 37:
#line 477 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);
                                                        debug("ArrayDef ::= ident[Exp]={ExpH}\n");
                                                        if(error_flag == 0)
                                                        {   
                                                            (yyval.node) = new ArrayDef_2_Node(new VarNode((yyvsp[(1) - (8)].var)),(ExpNode*)(yyvsp[(3) - (8)].node),(ExpHNode*)(yyvsp[(7) - (8)].node));
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        } 

                                                    ;}
    break;

  case 38:
#line 489 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);
                                        debug("VarDecl ::= int VarDefH ;\n");
                                        if(error_flag == 0)
                                        {   
                                            (yyval.node) = new VarDeclNode( (VarDefHNode*)(yyvsp[(2) - (3)].node));
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        } 

                                    ;}
    break;

  case 39:
#line 500 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);
                                        debug("VarDefH ::= VarDef\n");
                                        if(error_flag == 0)
                                        {   
                                            (yyval.node) = new VarDefHNode();
                                            ((VarDefHNode*)(yyval.node))->append((VarDefNode*)(yyvsp[(1) - (1)].node));
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        } 
                                    ;}
    break;

  case 40:
#line 510 "config/parser.y"
    {   
                                        if((yyvsp[(3) - (3)].node)!=NULL)
                                        {   
                                            if(error_flag == 0)
                                            {   
                                                ((VarDefHNode*)(yyval.node))->append((VarDefNode*)(yyvsp[(3) - (3)].node));
                                                (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            } 
                                        }
                                        line("Line:%-3d",(yyloc).first_line);
                                        debug("VarDefH ::= VarDefH,VarDef\n");
                                    ;}
    break;

  case 41:
#line 523 "config/parser.y"
    {   (yyval.node) = (yyvsp[(1) - (1)].node);
                                        line("Line:%-3d",(yyloc).first_line);
                                        debug("Var ::= ident\n");
                                        
                                    ;}
    break;

  case 42:
#line 528 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);
                                        debug("VarDef ::= ident=Exp\n");
                                        if(error_flag == 0)
                                        {   
                                            (yyval.node) = new AsgnNode((LValNode*)new VarNode((yyvsp[(1) - (3)].var)),(ExpNode*)(yyvsp[(3) - (3)].node));
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        } 
                                    ;}
    break;

  case 43:
#line 537 "config/parser.y"
    {   line("Line:%-3d",(yylsp[(1) - (1)]).first_line);
                                        debug("VarDef ::= ArrayDef\n");
                                        (yyval.node) = (yyvsp[(1) - (1)].node);
                                    ;}
    break;

  case 44:
#line 543 "config/parser.y"
    {   line("Line:%-3d",(yylsp[(1) - (1)]).first_line);
                                debug("ExpH ::= exp\n");
                                if(error_flag == 0)
                                {   
                                    (yyval.node) = new ExpHNode();
                                    ((ExpHNode*)(yyval.node))->append((ExpNode*)(yyvsp[(1) - (1)].node));
                                    (yyval.node)->setLoc((Loc*)&((yyloc)));
                                    all_node.push_back((Node*)(yyval.node));
                                } 
                            ;}
    break;

  case 45:
#line 553 "config/parser.y"
    {   line("Line:%-3d",(yylsp[(1) - (3)]).first_line);
                                debug("ExpH ::= ExpH,Exp\n");
                                if((yyvsp[(3) - (3)].node)!=NULL)
                                {
                                    if(error_flag == 0)
                                    {   
                                        ((ExpHNode*)(yyval.node))->append((ExpNode*)(yyvsp[(3) - (3)].node));
                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                    } 
                                }
                            ;}
    break;

  case 46:
#line 566 "config/parser.y"
    {   line("Line:%-3d",(yylsp[(1) - (3)]).first_line);
                            debug ("asgn ::= LVal = exp\n");
                            if(error_flag == 0)
                            {   
                                (yyval.node) = new AsgnNode((LValNode*)(yyvsp[(1) - (3)].node),(ExpNode*)(yyvsp[(3) - (3)].node));
                                (yyval.node)->setLoc((Loc*)&((yyloc)));
                                all_node.push_back((Node*)(yyval.node));
                            } 
                        ;}
    break;

  case 47:
#line 577 "config/parser.y"
    {   line("Line:%-3d",(yylsp[(1) - (1)]).first_line);
                            debug ("exp ::= num\n");
                            if(error_flag == 0)
                            {   
                                (yyval.node) = new NumNode ((yyvsp[(1) - (1)].num));
                                (yyval.node)->setLoc((Loc*)&((yyloc)));
                                all_node.push_back((Node*)(yyval.node));
                            } 
                        ;}
    break;

  case 48:
#line 586 "config/parser.y"
    {   line("Line:%-3d",(yylsp[(1) - (3)]).first_line);    
                            debug ("exp ::= exp + exp\n");
                            
                            if(error_flag == 0)
                            {   
                                (yyval.node) = new BinaryExpNode ('+', (ExpNode*)(yyvsp[(1) - (3)].node), (ExpNode*)(yyvsp[(3) - (3)].node));
                                (yyval.node)->setLoc((Loc*)&((yyloc)));
                                all_node.push_back((Node*)(yyval.node));
                            } 
                        ;}
    break;

  case 49:
#line 596 "config/parser.y"
    {   line("Line:%-3d",(yylsp[(1) - (3)]).first_line);
                            debug ("exp ::= exp - exp\n");
                            
                            if(error_flag == 0)
                            {   
                                (yyval.node) = new BinaryExpNode ('-', (ExpNode*)(yyvsp[(1) - (3)].node), (ExpNode*)(yyvsp[(3) - (3)].node));
                                (yyval.node)->setLoc((Loc*)&((yyloc)));
                                all_node.push_back((Node*)(yyval.node));
                            } 
                        ;}
    break;

  case 50:
#line 606 "config/parser.y"
    {   line("Line:%-3d",(yylsp[(1) - (3)]).first_line);
                            debug ("exp ::= exp * exp\n");
                            
                            if(error_flag == 0)
                            {   
                                (yyval.node) = new BinaryExpNode ('*', (ExpNode*)(yyvsp[(1) - (3)].node), (ExpNode*)(yyvsp[(3) - (3)].node));
                                (yyval.node)->setLoc((Loc*)&((yyloc)));
                                all_node.push_back((Node*)(yyval.node));
                            } 
                        ;}
    break;

  case 51:
#line 616 "config/parser.y"
    {   line("Line:%-3d",(yylsp[(1) - (3)]).first_line);
                            debug ("exp ::= exp / exp\n");
                            
                            if(error_flag == 0)
                            {   
                                (yyval.node) = new BinaryExpNode ('/', (ExpNode*)(yyvsp[(1) - (3)].node), (ExpNode*)(yyvsp[(3) - (3)].node));
                                (yyval.node)->setLoc((Loc*)&((yyloc)));
                                all_node.push_back((Node*)(yyval.node));
                            } 
                        ;}
    break;

  case 52:
#line 626 "config/parser.y"
    {   line("Line:%-3d",(yylsp[(1) - (3)]).first_line);
                            debug ("exp ::= exp %% exp\n");
                            
                            if(error_flag == 0)
                            {   
                                (yyval.node) = new BinaryExpNode ('%', (ExpNode*)(yyvsp[(1) - (3)].node), (ExpNode*)(yyvsp[(3) - (3)].node));
                                (yyval.node)->setLoc((Loc*)&((yyloc)));
                                all_node.push_back((Node*)(yyval.node));
                            } 
                        ;}
    break;

  case 53:
#line 636 "config/parser.y"
    {   line("Line:%-3d",(yylsp[(1) - (2)]).first_line);
                            debug ("exp ::= - exp\n");
                            
                            if(error_flag == 0)
                            {   
                                (yyval.node) = new UnaryExpNode ('-', (ExpNode*)(yyvsp[(2) - (2)].node));
                                (yyval.node)->setLoc((Loc*)&((yyloc)));
                                all_node.push_back((Node*)(yyval.node));
                            } 
                        ;}
    break;

  case 54:
#line 646 "config/parser.y"
    {   line("Line:%-3d",(yylsp[(1) - (2)]).first_line);
                            debug ("exp ::= + exp\n");
                            
                            if(error_flag == 0)
                            {   
                                (yyval.node) = new UnaryExpNode ('+', (ExpNode*)(yyvsp[(2) - (2)].node));
                                (yyval.node)->setLoc((Loc*)&((yyloc)));
                                all_node.push_back((Node*)(yyval.node));
                            } 
                        ;}
    break;

  case 55:
#line 656 "config/parser.y"
    {   debug(")\n");
                            if(error_flag == 0)
                            {   
                                (yyval.node) = new ParenExpNode ( (ExpNode*)(yyvsp[(1) - (2)].node));
                                (yyval.node)->setLoc((Loc*)&((yyloc)));
                                all_node.push_back((Node*)(yyval.node));
                            } 
                        ;}
    break;

  case 56:
#line 664 "config/parser.y"
    {   debug("')'\n");
                            error("%s:%3d.(%2d) right paren missing, there should be ')'\n",infile_name,(yyloc).first_line,(yylsp[(1) - (1)]).last_column+1);
                            show_line((yyloc).first_line,infile_name);
                            print_blank((yylsp[(1) - (1)]).last_column+1);
                            if(error_flag == 0)
                            {   
                                if(error_debug_flag == 0)
                                {
                                    delete_all_node();
                                    error_flag = 1;
                                }
                                else
                                {
                                    (yyval.node) = new ParenExpNode ( (ExpNode*)(yyvsp[(1) - (1)].node));
                                    (yyval.node)->setLoc((Loc*)&((yyloc)));
                                    all_node.push_back((yyval.node));
                                }
                            }
                        ;}
    break;

  case 57:
#line 683 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);debug("exp ::= '('exp)\n");
                            error("%s:%3d.(%2d) left paren missing, there should be '('\n",infile_name,(yyloc).first_line,(yylsp[(1) - (2)]).first_column-1);
                            show_line((yyloc).first_line,infile_name);
                            print_blank((yylsp[(1) - (2)]).first_column-1);
                            if(error_flag == 0)
                            {   
                                if(error_debug_flag == 0)
                                {
                                    delete_all_node();
                                    error_flag = 1;
                                }
                                else
                                {
                                    (yyval.node) = new ParenExpNode ( (ExpNode*)(yyvsp[(1) - (2)].node));
                                    (yyval.node)->setLoc((Loc*)&((yyloc)));
                                    all_node.push_back((yyval.node));
                                }
                            }
                        ;}
    break;

  case 58:
#line 702 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);debug("exp ::= exp ?? exp\n");
                            error("%s:%3d.(%2d) operator missing, there should be '+'|'-'|'*'|'/'|'%%'\n",infile_name,(yyloc).first_line,(yylsp[(1) - (2)]).last_column+1);
                            show_line((yyloc).first_line,infile_name);
                            print_blank((yylsp[(1) - (2)]).last_column+1);
                            if(error_flag == 0)
                            {   
                                if(error_debug_flag == 0)
                                {
                                    delete_all_node();
                                    error_flag = 1;
                                }
                                else
                                {
                                    (yyval.node) = new BinaryExpNode ('?', (ExpNode*)(yyvsp[(1) - (2)].node), (ExpNode*)(yyvsp[(2) - (2)].node)); 
                                    (yyval.node)->setLoc((Loc*)&((yyloc)));
                                    all_node.push_back((yyval.node));
                                }
                            }
                        ;}
    break;

  case 59:
#line 721 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);
                            debug ("exp ::= LVal\n");
                            (yyval.node) = (yyvsp[(1) - (1)].node);
                        ;}
    break;

  case 60:
#line 727 "config/parser.y"
    {   line("Line:%-3d",(yyloc).first_line);
                        debug("exp ::= (exp"); 
                        (yyval.node) = (yyvsp[(2) - (2)].node);
                    ;}
    break;

  case 61:
#line 732 "config/parser.y"
    {
                                line("Line:%-3d",(yylsp[(1) - (1)]).first_line);
                                debug ("LVal ::= ident\n");
                                if(error_flag == 0)
                                {   
                                    (yyval.node) = new VarNode((yyvsp[(1) - (1)].var));
                                    (yyval.node)->setLoc((Loc*)&((yyloc)));
                                    all_node.push_back((Node*)(yyval.node));
                                } 
                            ;}
    break;

  case 62:
#line 742 "config/parser.y"
    {
                                    line("Line:%-3d",(yylsp[(1) - (4)]).first_line);
                                    debug ("LVal ::= ident[Exp]\n");
                                    if(error_flag == 0)
                                    {   
                                        (yyval.node) = new ArrayLValNode(new VarNode((yyvsp[(1) - (4)].var)),(ExpNode*)(yyvsp[(3) - (4)].node));
                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                        all_node.push_back((Node*)(yyval.node));
                                    } 
                                ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2431 "src/parser.cc"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
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

  yyerror_range[0] = yylsp[1-yylen];
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
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


#line 754 "config/parser.y"



void yyerror (const char *msg)
{
    error ("%s", msg);
}

