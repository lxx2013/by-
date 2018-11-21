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
     err_tok = 258,
     var_tok = 259,
     num_tok = 260,
     assume_tok = 261,
     segment_tok = 262,
     ends_tok = 263,
     macro_tok = 264,
     endm_tok = 265,
     end_tok = 266,
     cs_tok = 267,
     ss_tok = 268,
     sp_tok = 269,
     ds_tok = 270,
     db_tok = 271,
     dd_tok = 272,
     dw_tok = 273,
     string_tok = 274,
     dup_tok = 275,
     code_tok = 276,
     data_tok = 277,
     stack_tok = 278,
     ax_tok = 279,
     ah_tok = 280,
     al_tok = 281,
     bx_tok = 282,
     bh_tok = 283,
     bl_tok = 284,
     cx_tok = 285,
     ch_tok = 286,
     cl_tok = 287,
     dx_tok = 288,
     dh_tok = 289,
     dl_tok = 290,
     si_tok = 291,
     di_tok = 292,
     ret_tok = 293,
     int_tok = 294,
     mov_tok = 295,
     offset_tok = 296,
     byte_tok = 297,
     word_tok = 298,
     ptr_tok = 299,
     cmp_tok = 300,
     call_tok = 301,
     push_tok = 302,
     pop_tok = 303,
     add_tok = 304,
     sub_tok = 305,
     inc_tok = 306,
     dec_tok = 307,
     mul_tok = 308,
     div_tok = 309,
     jmp_tok = 310,
     jle_tok = 311,
     jl_tok = 312,
     jge_tok = 313,
     jg_tok = 314,
     je_tok = 315,
     jne_tok = 316,
     loop_tok = 317
   };
#endif
/* Tokens.  */
#define err_tok 258
#define var_tok 259
#define num_tok 260
#define assume_tok 261
#define segment_tok 262
#define ends_tok 263
#define macro_tok 264
#define endm_tok 265
#define end_tok 266
#define cs_tok 267
#define ss_tok 268
#define sp_tok 269
#define ds_tok 270
#define db_tok 271
#define dd_tok 272
#define dw_tok 273
#define string_tok 274
#define dup_tok 275
#define code_tok 276
#define data_tok 277
#define stack_tok 278
#define ax_tok 279
#define ah_tok 280
#define al_tok 281
#define bx_tok 282
#define bh_tok 283
#define bl_tok 284
#define cx_tok 285
#define ch_tok 286
#define cl_tok 287
#define dx_tok 288
#define dh_tok 289
#define dl_tok 290
#define si_tok 291
#define di_tok 292
#define ret_tok 293
#define int_tok 294
#define mov_tok 295
#define offset_tok 296
#define byte_tok 297
#define word_tok 298
#define ptr_tok 299
#define cmp_tok 300
#define call_tok 301
#define push_tok 302
#define pop_tok 303
#define add_tok 304
#define sub_tok 305
#define inc_tok 306
#define dec_tok 307
#define mul_tok 308
#define div_tok 309
#define jmp_tok 310
#define jle_tok 311
#define jl_tok 312
#define jge_tok 313
#define jg_tok 314
#define je_tok 315
#define jne_tok 316
#define loop_tok 317




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
#line 38 "config/parser.y"
{
    int  num;
    std::string *var;
    Node *node;
}
/* Line 193 of yacc.c.  */
#line 261 "src/parser.cc"
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
#line 286 "src/parser.cc"

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
#define YYLAST   452

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  130
/* YYNRULES -- Number of states.  */
#define YYNSTATES  223

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   317

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      65,    66,     2,    69,    64,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    63,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    67,     2,    68,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,     9,    11,    14,    19,    24,
      29,    35,    41,    47,    53,    59,    65,    67,    69,    71,
      74,    77,    80,    82,    85,    89,    93,    97,    99,   103,
     105,   107,   113,   115,   117,   119,   121,   123,   125,   127,
     129,   131,   134,   136,   138,   140,   142,   144,   146,   148,
     150,   152,   154,   156,   158,   160,   164,   170,   175,   182,
     184,   186,   188,   190,   194,   198,   202,   206,   210,   216,
     220,   224,   228,   232,   238,   240,   242,   244,   246,   248,
     250,   252,   254,   256,   258,   260,   262,   265,   268,   271,
     276,   279,   282,   285,   288,   291,   294,   297,   300,   303,
     306,   309,   312,   315,   318,   321,   324,   327,   330,   333,
     336,   339,   342,   347,   352,   355,   358,   363,   368,   371,
     374,   377,   380,   383,   387,   390,   392,   395,   401,   403,
     407
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      71,     0,    -1,    -1,    71,    72,    -1,    73,    -1,    74,
      -1,    11,     4,    -1,     6,    12,    63,    21,    -1,     6,
      15,    63,    22,    -1,     6,    13,    63,    23,    -1,    73,
      64,    12,    63,    21,    -1,    73,    64,    15,    63,    22,
      -1,    73,    64,    13,    63,    23,    -1,    22,     7,    76,
      22,     8,    -1,    23,     7,    76,    23,     8,    -1,    21,
       7,    75,    21,     8,    -1,    99,    -1,   101,    -1,   103,
      -1,    75,    99,    -1,    75,   101,    -1,    75,   103,    -1,
      77,    -1,    76,    77,    -1,     4,    16,    78,    -1,     4,
      18,    78,    -1,     4,    17,    78,    -1,    79,    -1,    78,
      64,    79,    -1,    19,    -1,     5,    -1,     5,    20,    65,
       5,    66,    -1,    24,    -1,    27,    -1,    30,    -1,    33,
      -1,    36,    -1,    37,    -1,    15,    -1,    13,    -1,    14,
      -1,    41,     4,    -1,    25,    -1,    26,    -1,    28,    -1,
      29,    -1,    31,    -1,    32,    -1,    34,    -1,    35,    -1,
       4,    -1,    22,    -1,    23,    -1,    21,    -1,    83,    -1,
      67,    84,    68,    -1,    67,    84,    69,    84,    68,    -1,
      67,    84,     5,    68,    -1,    67,    84,    69,    84,     5,
      68,    -1,    24,    -1,    27,    -1,    36,    -1,    37,    -1,
      81,    64,    81,    -1,    81,    64,     5,    -1,    81,    64,
      82,    -1,    82,    64,    81,    -1,    82,    64,     5,    -1,
      42,    44,    82,    64,    82,    -1,    80,    64,    80,    -1,
      80,    64,     5,    -1,    80,    64,    82,    -1,    82,    64,
      80,    -1,    43,    44,    82,    64,    82,    -1,    88,    -1,
      89,    -1,    90,    -1,    91,    -1,    92,    -1,    93,    -1,
      94,    -1,    95,    -1,    96,    -1,    97,    -1,    98,    -1,
      99,    -1,    39,     5,    -1,    40,    85,    -1,    40,    86,
      -1,    40,    82,    64,    82,    -1,    45,    85,    -1,    45,
      86,    -1,    55,     4,    -1,    56,     4,    -1,    57,     4,
      -1,    58,     4,    -1,    59,     4,    -1,    60,     4,    -1,
      61,     4,    -1,    62,     4,    -1,    49,    85,    -1,    49,
      86,    -1,    51,    81,    -1,    51,    80,    -1,    51,    82,
      -1,    50,    85,    -1,    50,    86,    -1,    52,    81,    -1,
      52,    80,    -1,    52,    82,    -1,    53,    81,    -1,    53,
      80,    -1,    53,    43,    44,    82,    -1,    53,    42,    44,
      82,    -1,    54,    81,    -1,    54,    80,    -1,    54,    43,
      44,    82,    -1,    54,    42,    44,    82,    -1,    46,     4,
      -1,    47,    81,    -1,    47,    80,    -1,    48,    81,    -1,
      48,    80,    -1,     4,    63,   100,    -1,     4,    63,    -1,
      87,    -1,   100,    87,    -1,     4,     9,   102,   100,    10,
      -1,     4,    -1,   102,    64,     4,    -1,    38,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    57,    57,    63,    68,    75,    80,    86,    87,    88,
      89,    90,    91,    94,    98,   102,   108,   112,   116,   120,
     124,   128,   134,   138,   143,   144,   145,   148,   149,   152,
     153,   154,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   169,   170,   171,   172,   173,   174,   175,   176,
     178,   179,   180,   181,   182,   187,   188,   189,   200,   202,
     203,   204,   205,   210,   211,   212,   213,   214,   215,   217,
     218,   219,   220,   221,   223,   227,   231,   235,   239,   243,
     247,   251,   255,   259,   263,   267,   273,   276,   277,   278,
     281,   282,   285,   286,   287,   288,   289,   290,   291,   292,
     295,   296,   297,   298,   299,   301,   302,   303,   304,   305,
     308,   309,   310,   311,   314,   315,   316,   317,   320,   323,
     324,   327,   328,   331,   335,   341,   345,   351,   357,   358,
     361
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "err_tok", "var_tok", "num_tok",
  "assume_tok", "segment_tok", "ends_tok", "macro_tok", "endm_tok",
  "end_tok", "cs_tok", "ss_tok", "sp_tok", "ds_tok", "db_tok", "dd_tok",
  "dw_tok", "string_tok", "dup_tok", "code_tok", "data_tok", "stack_tok",
  "ax_tok", "ah_tok", "al_tok", "bx_tok", "bh_tok", "bl_tok", "cx_tok",
  "ch_tok", "cl_tok", "dx_tok", "dh_tok", "dl_tok", "si_tok", "di_tok",
  "ret_tok", "int_tok", "mov_tok", "offset_tok", "byte_tok", "word_tok",
  "ptr_tok", "cmp_tok", "call_tok", "push_tok", "pop_tok", "add_tok",
  "sub_tok", "inc_tok", "dec_tok", "mul_tok", "div_tok", "jmp_tok",
  "jle_tok", "jl_tok", "jge_tok", "jg_tok", "je_tok", "jne_tok",
  "loop_tok", "':'", "','", "'('", "')'", "'['", "']'", "'+'", "$accept",
  "input", "CompUnit", "Assume", "Segment", "Content", "Alloca",
  "AllocaLine", "AllocaExpH", "AllocaExp", "RegS", "RegE", "MemAddr",
  "MemAddrExp", "MemAddrExp_a", "DoubleOE", "DoubleOS", "Instruction",
  "Int_ins", "Mov_ins", "Cmp_ins", "Jmp_ins", "Add_ins", "Sub_ins",
  "Mul_ins", "Div_ins", "Call_ins", "Push_ins", "Pop_ins", "Block",
  "BlockItem", "Macro", "MacroExp", "Function", 0
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,    58,    44,    40,    41,    91,    93,    43
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    70,    71,    71,    72,    72,    72,    73,    73,    73,
      73,    73,    73,    74,    74,    74,    75,    75,    75,    75,
      75,    75,    76,    76,    77,    77,    77,    78,    78,    79,
      79,    79,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    81,    81,    81,    81,    81,    81,    81,    81,
      82,    82,    82,    82,    82,    83,    83,    83,    83,    84,
      84,    84,    84,    85,    85,    85,    85,    85,    85,    86,
      86,    86,    86,    86,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    88,    89,    89,    89,
      90,    90,    91,    91,    91,    91,    91,    91,    91,    91,
      92,    92,    92,    92,    92,    93,    93,    93,    93,    93,
      94,    94,    94,    94,    95,    95,    95,    95,    96,    97,
      97,    98,    98,    99,    99,   100,   100,   101,   102,   102,
     103
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     2,     4,     4,     4,
       5,     5,     5,     5,     5,     5,     1,     1,     1,     2,
       2,     2,     1,     2,     3,     3,     3,     1,     3,     1,
       1,     5,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     5,     4,     6,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     5,     3,
       3,     3,     3,     5,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     4,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     4,     4,     2,     2,     4,     4,     2,     2,
       2,     2,     2,     3,     2,     1,     2,     5,     1,     3,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     3,     4,
       5,     0,     0,     0,     6,     0,     0,     0,     0,     0,
       0,     0,     0,   130,     0,    16,    17,    18,     0,     0,
      22,     0,     0,     0,     0,     7,     9,     8,     0,   124,
       0,    19,    20,    21,     0,     0,     0,     0,    23,     0,
       0,     0,     0,   128,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   125,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,   123,
      15,    30,    29,    24,    27,    26,    25,    13,    14,    10,
      12,    11,     0,     0,    86,    50,    39,    40,    38,    53,
      51,    52,    32,    42,    43,    33,    44,    45,    34,    46,
      47,    35,    48,    49,    36,    37,     0,     0,     0,     0,
       0,     0,     0,    54,    87,    88,     0,    90,    91,   118,
     120,   119,   122,   121,   100,   101,   105,   106,   103,   102,
     104,   108,   107,   109,     0,     0,   111,   110,     0,     0,
     115,   114,    92,    93,    94,    95,    96,    97,    98,    99,
     126,     0,     0,   129,   127,    41,     0,     0,    59,    60,
      61,    62,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    28,     0,     0,     0,    55,     0,    70,    69,
      71,    64,    63,    65,    67,    72,    66,    89,   113,   112,
     117,   116,     0,     0,     0,    57,     0,    31,    68,    73,
       0,    56,    58
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     8,     9,    10,    24,    29,    30,    93,    94,
     130,   131,   136,   133,   182,   134,   135,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    26,    54,    27
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -58
static const yytype_int16 yypact[] =
{
     -58,   429,   -58,    21,     2,    28,    30,    63,   -58,   -55,
     -58,    -6,    22,    25,   -58,    24,   107,   107,    95,    97,
      93,   103,    -7,   -58,   102,   -58,   -58,   -58,    96,     0,
     -58,     6,    66,    75,    79,   -58,   -58,   -58,   135,   258,
     138,   -58,   -58,   -58,     8,     8,     8,   139,   -58,   140,
     128,   130,   132,   -58,   197,    92,   170,    17,    17,   175,
     391,   391,    17,    17,   137,   137,   341,   366,   176,   177,
     178,   179,   180,   184,   185,   186,   -58,   -58,   -58,   -58,
     -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   258,
     -58,   171,   -58,   136,   -58,   136,   136,   -58,   -58,   -58,
     -58,   -58,   188,   225,   -58,   -58,   -58,   -58,   -58,   -58,
     -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,
     -58,   -58,   -58,   -58,   -58,   -58,   199,   162,   163,    50,
     146,   147,   148,   -58,   -58,   -58,   153,   -58,   -58,   -58,
     -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,
     -58,   -58,   -58,   -58,   182,   187,   -58,   -58,   189,   190,
     -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,
     -58,   155,     8,   -58,   -58,   -58,    57,    57,   -58,   -58,
     -58,   -58,    -4,   172,   193,    68,   316,    57,    57,    57,
      57,   218,   -58,   166,   168,   173,   -58,    50,   -58,   -58,
     -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,
     -58,   -58,   174,    57,    57,   -58,    -2,   -58,   -58,   -58,
     195,   -58,   -58
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -58,   -58,   -58,   -58,   -58,   -58,   221,    86,    76,    94,
     -49,   -41,   -57,   -58,    70,     5,    13,   -34,   -58,   -58,
     -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -10,
     214,   245,   -58,   264
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
     132,   195,    38,   220,    28,    25,    14,   150,   153,    18,
      28,   140,   142,    91,    41,   148,   151,   156,   160,   141,
     143,   105,    47,   149,   152,   157,   161,    92,    22,    49,
     106,   107,   108,    11,    12,    15,    13,    16,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   170,    39,    19,   126,   127,
     128,   105,    23,   137,   196,   197,   221,   144,   146,   170,
      17,   138,   105,   204,   178,   145,   147,   179,   109,   110,
     111,   106,   107,   108,   129,    20,   180,   181,    21,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,    22,    32,    33,   126,
      34,    28,    44,    45,    46,    48,    36,    48,    35,   193,
     194,    95,    96,    40,   129,    37,   200,   203,   207,    50,
     208,   209,   210,   211,   199,   129,   205,   205,    51,    53,
      23,   105,    52,   202,   206,   206,    90,    97,    98,    99,
     106,   107,   108,   100,   101,    39,   218,   219,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   104,   105,   198,   126,   139,
     162,   163,   164,   165,   166,   106,   107,   108,   167,   168,
     169,   171,   173,   109,   110,   111,   112,   105,   201,   115,
     172,    55,   118,   175,   129,   121,   176,   177,   124,   125,
     183,   184,   185,   126,   109,   110,   111,   186,   113,   114,
     191,   116,   117,   212,   119,   120,   187,   122,   123,    55,
     213,   188,   214,   189,   190,   174,    56,    57,    31,   129,
     217,   215,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
     129,   102,    55,   222,    56,    57,   192,   216,   103,    42,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    43,     0,
       0,     0,     0,     0,     0,     0,     0,    56,    57,     0,
       0,     0,     0,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,   204,     0,     0,     0,     0,     0,     0,     0,   106,
     107,   108,     0,     0,     0,     0,     0,     0,     0,     0,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   106,   107,   108,   126,     0,     0,
       0,     0,     0,     0,     0,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   106,
     107,   108,   126,   154,   155,     0,     0,     0,     0,     0,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   106,   107,   108,   126,   158,   159,
       0,     0,     0,     0,     0,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,     2,
       0,     0,   126,     0,     0,     3,     0,     0,     0,     0,
       4,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       5,     6,     7
};

static const yytype_int16 yycheck[] =
{
      57,     5,     9,     5,     4,    15,     4,    64,    65,    64,
       4,    60,    61,     5,    24,    64,    65,    66,    67,    60,
      61,     4,    22,    64,    65,    66,    67,    19,     4,    23,
      13,    14,    15,    12,    13,     7,    15,     7,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    89,    63,    63,    41,    42,
      43,     4,    38,    58,    68,    69,    68,    62,    63,   103,
       7,    58,     4,     5,    24,    62,    63,    27,    21,    22,
      23,    13,    14,    15,    67,    63,    36,    37,    63,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,     4,    12,    13,    41,
      15,     4,    16,    17,    18,    29,    23,    31,    21,   176,
     177,    45,    46,    21,    67,    22,   183,   184,   185,    63,
     187,   188,   189,   190,   183,    67,   185,   186,    63,     4,
      38,     4,    63,   184,   185,   186,     8,     8,     8,    21,
      13,    14,    15,    23,    22,    63,   213,   214,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,     5,     4,     5,    41,     4,
       4,     4,     4,     4,     4,    13,    14,    15,     4,     4,
       4,    20,     4,    21,    22,    23,    24,     4,     5,    27,
      64,     4,    30,     4,    67,    33,    44,    44,    36,    37,
      64,    64,    64,    41,    21,    22,    23,    64,    25,    26,
      65,    28,    29,     5,    31,    32,    44,    34,    35,     4,
      64,    44,    64,    44,    44,    10,    39,    40,    17,    67,
      66,    68,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      67,    64,     4,    68,    39,    40,   172,   197,    54,    24,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    -1,
      -1,    -1,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,     5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    13,    14,    15,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    13,
      14,    15,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    13,    14,    15,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,     0,
      -1,    -1,    41,    -1,    -1,     6,    -1,    -1,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    22,    23
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    71,     0,     6,    11,    21,    22,    23,    72,    73,
      74,    12,    13,    15,     4,     7,     7,     7,    64,    63,
      63,    63,     4,    38,    75,    99,   101,   103,     4,    76,
      77,    76,    12,    13,    15,    21,    23,    22,     9,    63,
      21,    99,   101,   103,    16,    17,    18,    22,    77,    23,
      63,    63,    63,     4,   102,     4,    39,    40,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
       8,     5,    19,    78,    79,    78,    78,     8,     8,    21,
      23,    22,    64,   100,     5,     4,    13,    14,    15,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    41,    42,    43,    67,
      80,    81,    82,    83,    85,    86,    82,    85,    86,     4,
      80,    81,    80,    81,    85,    86,    85,    86,    80,    81,
      82,    80,    81,    82,    42,    43,    80,    81,    42,    43,
      80,    81,     4,     4,     4,     4,     4,     4,     4,     4,
      87,    20,    64,     4,    10,     4,    44,    44,    24,    27,
      36,    37,    84,    64,    64,    64,    64,    44,    44,    44,
      44,    65,    79,    82,    82,     5,    68,    69,     5,    80,
      82,     5,    81,    82,     5,    80,    81,    82,    82,    82,
      82,    82,     5,    64,    64,    68,    84,    66,    82,    82,
       5,    68,    68
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
#line 57 "config/parser.y"
    {   
                            error_flag = 0;
                            error_debug_flag = 0;                           
                            line("Line:%-4d",1);
                            debug ("input ::= empty\n"); 
                        ;}
    break;

  case 3:
#line 63 "config/parser.y"
    {
                            line("Line:%-4d",(yylsp[(2) - (2)]).first_line);
                            debug ("input ::= CompUnit\n"); 
                        ;}
    break;

  case 4:
#line 68 "config/parser.y"
    {
                            line("Line:%-4d",(yylsp[(1) - (1)]).first_line);
                            debug ("Assume ::= assume cs:code,ds:data,ss:stack\n");
                            line("Line:%-4d",(yylsp[(1) - (1)]).first_line);
                            debug ("CompUnit ::= Assume\n");
                            (yyval.node) = (yyvsp[(1) - (1)].node); 
                        ;}
    break;

  case 5:
#line 75 "config/parser.y"
    {
                            line("Line:%-4d",(yylsp[(1) - (1)]).first_line);
                            debug ("CompUnit ::= Segment\n");
                            (yyval.node) = (yyvsp[(1) - (1)].node); 
                        ;}
    break;

  case 6:
#line 80 "config/parser.y"
    {
                                        line("Line:%-4d",(yylsp[(1) - (2)]).first_line);
                                        debug ("CompUnit ::= end %s\n",(yyvsp[(2) - (2)].var)->c_str());
                                    ;}
    break;

  case 13:
#line 94 "config/parser.y"
    {
                                                                    line("Line:%-4d",(yyloc).first_line);
                                                                    debug ("Segment ::= data Segment\n");   
                                                                ;}
    break;

  case 14:
#line 98 "config/parser.y"
    {
                                                                    line("Line:%-4d",(yyloc).first_line);
                                                                    debug ("Segment ::= stack Segment\n");   
                                                                ;}
    break;

  case 15:
#line 102 "config/parser.y"
    {
                                                                    line("Line:%-4d",(yyloc).first_line);
                                                                    debug ("Segment ::= code Segment\n");   
                                                                ;}
    break;

  case 16:
#line 108 "config/parser.y"
    {
                                        line("Line:%-4d",(yyloc).first_line);
                                        debug ("Content ::= Block\n");   
                                    ;}
    break;

  case 17:
#line 112 "config/parser.y"
    {
                                        line("Line:%-4d",(yyloc).first_line);
                                        debug ("Content ::= Macro\n");   
                                    ;}
    break;

  case 18:
#line 116 "config/parser.y"
    {
                                        line("Line:%-4d",(yyloc).first_line);
                                        debug ("Content ::= Function\n");   
                                    ;}
    break;

  case 19:
#line 120 "config/parser.y"
    {
                                        line("Line:%-4d",(yyloc).first_line);
                                        debug ("Content ::= Content Block\n");   
                                    ;}
    break;

  case 20:
#line 124 "config/parser.y"
    {
                                        line("Line:%-4d",(yyloc).first_line);
                                        debug ("Content ::= Content Macro\n");   
                                    ;}
    break;

  case 21:
#line 128 "config/parser.y"
    {
                                        line("Line:%-4d",(yyloc).first_line);
                                        debug ("Content ::= Content Function\n");   
                                    ;}
    break;

  case 22:
#line 134 "config/parser.y"
    {
                                                        line("Line:%-4d",(yyloc).first_line);
                                                        debug ("Alloca ::= AllocaLine\n");   
                                                    ;}
    break;

  case 23:
#line 138 "config/parser.y"
    {
                                                        line("Line:%-4d",(yylsp[(2) - (2)]).first_line);
                                                        debug ("Alloca ::= Alloca AllocaLine\n");   
                                                    ;}
    break;

  case 54:
#line 182 "config/parser.y"
    {
                                line("Line:%-4d",(yyloc).first_line);
                                debug ("MemAddr ::= MemAddrExp\n");   
                            ;}
    break;

  case 57:
#line 189 "config/parser.y"
    {
                                                        line("Line:%-4d",(yyloc).first_line);
                                                        if((yyvsp[(3) - (4)].num) >= 0)
                                                        {
                                                            debug ("MemAddrExp ::= '[' MemAddrExp_a + num_tok ']'\n");
                                                        }
                                                        else
                                                        {
                                                            debug ("MemAddrExp ::= '[' MemAddrExp_a - num_tok ']'\n");
                                                        }   
                                                    ;}
    break;

  case 74:
#line 223 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Int_ins\n");   
                                ;}
    break;

  case 75:
#line 227 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Mov_ins\n");   
                                ;}
    break;

  case 76:
#line 231 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Cmp_ins\n");   
                                ;}
    break;

  case 77:
#line 235 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Jmp_ins\n");   
                                ;}
    break;

  case 78:
#line 239 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Add_ins\n");   
                                ;}
    break;

  case 79:
#line 243 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Sub_ins\n");   
                                ;}
    break;

  case 80:
#line 247 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Mul_ins\n");   
                                ;}
    break;

  case 81:
#line 251 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Div_ins\n");   
                                ;}
    break;

  case 82:
#line 255 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Call_ins\n");   
                                ;}
    break;

  case 83:
#line 259 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Push_ins\n");   
                                ;}
    break;

  case 84:
#line 263 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Pop_ins\n");   
                                ;}
    break;

  case 85:
#line 267 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Block\n");   
                                ;}
    break;

  case 123:
#line 331 "config/parser.y"
    {
                                            line("Line:%-4d",(yyloc).first_line);
                                            debug ("Block ::= %s : BlockItem\n",(yyvsp[(1) - (3)].var)->c_str());   
                                        ;}
    break;

  case 124:
#line 335 "config/parser.y"
    {
                                            line("Line:%-4d",(yyloc).first_line);
                                            debug ("Block ::= %s : \n",(yyvsp[(1) - (2)].var)->c_str());   
                                        ;}
    break;

  case 125:
#line 341 "config/parser.y"
    {
                                                                    line("Line:%-4d",(yyloc).first_line);
                                                                    debug ("BlockItem ::= Instruction\n");   
                                                                ;}
    break;

  case 126:
#line 345 "config/parser.y"
    {
                                                                    line("Line:%-4d",(yyloc).first_line);
                                                                    debug ("BlockItem ::= BlockItem Instruction\n");   
                                                                ;}
    break;

  case 127:
#line 351 "config/parser.y"
    {
                                                                    line("Line:%-4d",(yyloc).first_line);
                                                                    debug ("Macro ::= var macro exp \n\t\t  BlockItem \n \t\t  endm\n");   
                                                                ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2063 "src/parser.cc"
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


#line 364 "config/parser.y"



void yyerror (const char *msg)
{
    error ("%s\n", msg);
}

