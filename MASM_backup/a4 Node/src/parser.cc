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
//#define DEBUG
#include "node.hh"
#include "util.hh"
#include "global.hh"
extern int yylex ();
extern void yyerror (const char *msg);
InputNode *root;
GlobalNode *global;
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
#line 39 "config/parser.y"
{
    int  num;
    std::string *var;
    Node *node;
    RegNode * regnode;
}
/* Line 193 of yacc.c.  */
#line 263 "src/parser.cc"
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
#line 288 "src/parser.cc"

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
#define YYLAST   449

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  140
/* YYNRULES -- Number of states.  */
#define YYNSTATES  232

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
      29,    35,    41,    47,    53,    59,    65,    67,    69,    72,
      75,    77,    80,    81,    86,    87,    92,    93,    98,   100,
     104,   106,   108,   114,   116,   118,   120,   122,   124,   126,
     128,   130,   132,   135,   137,   139,   141,   143,   145,   147,
     149,   151,   153,   155,   157,   159,   161,   165,   169,   175,
     180,   187,   189,   191,   193,   195,   197,   199,   203,   207,
     211,   215,   219,   223,   229,   235,   239,   243,   247,   251,
     257,   263,   265,   267,   269,   271,   273,   275,   277,   279,
     281,   283,   285,   287,   289,   292,   295,   298,   301,   304,
     307,   310,   313,   316,   319,   322,   325,   328,   331,   334,
     337,   340,   343,   346,   349,   352,   355,   358,   361,   364,
     367,   372,   377,   380,   383,   386,   391,   396,   399,   402,
     405,   408,   411,   413,   414,   419,   422,   424,   427,   433,
     435
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
       7,    75,    21,     8,    -1,   103,    -1,   106,    -1,    75,
     103,    -1,    75,   106,    -1,    77,    -1,    76,    77,    -1,
      -1,     4,    16,    78,    81,    -1,    -1,     4,    18,    79,
      81,    -1,    -1,     4,    17,    80,    81,    -1,    82,    -1,
      81,    64,    82,    -1,    19,    -1,     5,    -1,     5,    20,
      65,     5,    66,    -1,    24,    -1,    27,    -1,    30,    -1,
      33,    -1,    36,    -1,    37,    -1,    15,    -1,    13,    -1,
      14,    -1,    41,     4,    -1,    25,    -1,    26,    -1,    28,
      -1,    29,    -1,    31,    -1,    32,    -1,    34,    -1,    35,
      -1,     4,    -1,    22,    -1,    23,    -1,    21,    -1,    86,
      -1,    67,     5,    68,    -1,    67,    87,    68,    -1,    67,
      87,    69,    87,    68,    -1,    67,    87,     5,    68,    -1,
      67,    87,    69,    87,     5,    68,    -1,    24,    -1,    27,
      -1,    30,    -1,    33,    -1,    36,    -1,    37,    -1,    84,
      64,    84,    -1,    84,    64,     5,    -1,    84,    64,    85,
      -1,    85,    64,    84,    -1,    85,    64,     5,    -1,    85,
      64,    85,    -1,    42,    44,    85,    64,    85,    -1,    42,
      44,    85,    64,     5,    -1,    83,    64,    83,    -1,    83,
      64,     5,    -1,    83,    64,    85,    -1,    85,    64,    83,
      -1,    43,    44,    85,    64,    85,    -1,    43,    44,    85,
      64,     5,    -1,    91,    -1,    92,    -1,    93,    -1,    94,
      -1,    95,    -1,    96,    -1,    97,    -1,    98,    -1,    99,
      -1,   100,    -1,   101,    -1,   102,    -1,   103,    -1,    39,
       5,    -1,    40,    88,    -1,    40,    89,    -1,    45,    88,
      -1,    45,    89,    -1,    55,     4,    -1,    56,     4,    -1,
      57,     4,    -1,    58,     4,    -1,    59,     4,    -1,    60,
       4,    -1,    61,     4,    -1,    62,     4,    -1,    49,    88,
      -1,    49,    89,    -1,    51,    84,    -1,    51,    83,    -1,
      51,    85,    -1,    50,    88,    -1,    50,    89,    -1,    52,
      84,    -1,    52,    83,    -1,    52,    85,    -1,    53,    84,
      -1,    53,    83,    -1,    53,    85,    -1,    53,    43,    44,
      85,    -1,    53,    42,    44,    85,    -1,    54,    84,    -1,
      54,    83,    -1,    54,    85,    -1,    54,    43,    44,    85,
      -1,    54,    42,    44,    85,    -1,    46,     4,    -1,    47,
      84,    -1,    47,    83,    -1,    48,    84,    -1,    48,    83,
      -1,    38,    -1,    -1,     4,    63,   104,   105,    -1,     4,
      63,    -1,    90,    -1,   105,    90,    -1,     4,     9,   107,
     105,    10,    -1,     4,    -1,   107,    64,     4,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    63,    63,    72,    82,    94,    99,   106,   107,   108,
     109,   110,   111,   114,   120,   126,   134,   145,   156,   165,
     176,   187,   197,   197,   207,   207,   217,   217,   229,   230,
     233,   246,   264,   267,   270,   273,   276,   279,   282,   285,
     288,   291,   294,   299,   302,   305,   308,   311,   314,   317,
     320,   324,   334,   337,   340,   343,   348,   349,   375,   393,
     428,   448,   449,   450,   451,   452,   453,   458,   466,   486,
     494,   502,   514,   522,   529,   548,   556,   577,   585,   593,
     601,   614,   619,   624,   629,   634,   639,   644,   649,   654,
     659,   664,   669,   674,   681,   691,   699,   709,   717,   727,
     742,   757,   772,   787,   802,   817,   832,   849,   857,   865,
     878,   891,   905,   913,   921,   934,   947,   962,   970,   978,
     989,   997,  1007,  1015,  1023,  1034,  1042,  1052,  1069,  1077,
    1087,  1095,  1104,  1113,  1113,  1125,  1138,  1149,  1161,  1173,
    1174
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
  "AllocaLine", "@1", "@2", "@3", "AllocaExpH", "AllocaExp", "RegS",
  "RegE", "MemAddr", "MemAddrExp", "MemAddrExp_a", "DoubleOE", "DoubleOS",
  "Instruction", "Int_ins", "Mov_ins", "Cmp_ins", "Jmp_ins", "Add_ins",
  "Sub_ins", "Mul_ins", "Div_ins", "Call_ins", "Push_ins", "Pop_ins",
  "Ret_ins", "Block", "@4", "BlockItem", "Macro", "MacroExp", 0
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
      76,    76,    78,    77,    79,    77,    80,    77,    81,    81,
      82,    82,    82,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    84,    84,    84,    84,    84,    84,    84,
      84,    85,    85,    85,    85,    85,    86,    86,    86,    86,
      86,    87,    87,    87,    87,    87,    87,    88,    88,    88,
      88,    88,    88,    88,    88,    89,    89,    89,    89,    89,
      89,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    91,    92,    92,    93,    93,    94,
      94,    94,    94,    94,    94,    94,    94,    95,    95,    95,
      95,    95,    96,    96,    96,    96,    96,    97,    97,    97,
      97,    97,    98,    98,    98,    98,    98,    99,   100,   100,
     101,   101,   102,   104,   103,   103,   105,   105,   106,   107,
     107
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     2,     4,     4,     4,
       5,     5,     5,     5,     5,     5,     1,     1,     2,     2,
       1,     2,     0,     4,     0,     4,     0,     4,     1,     3,
       1,     1,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     5,     4,
       6,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     5,     5,     3,     3,     3,     3,     5,
       5,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       4,     4,     2,     2,     2,     4,     4,     2,     2,     2,
       2,     2,     1,     0,     4,     2,     1,     2,     5,     1,
       3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     3,     4,
       5,     0,     0,     0,     6,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    16,    17,     0,     0,    20,     0,
       0,     0,     0,     7,     9,     8,     0,   133,     0,    18,
      19,    22,    26,    24,     0,    21,     0,     0,     0,     0,
     139,     0,     0,    15,     0,     0,     0,    13,    14,    10,
      12,    11,     0,   132,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   136,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,     0,
     134,    31,    30,    23,    28,    27,    25,    94,    51,    40,
      41,    39,    54,    52,    53,    33,    43,    44,    34,    45,
      46,    35,    47,    48,    36,    49,    50,    37,    38,     0,
       0,     0,     0,     0,     0,     0,    55,    95,    96,    97,
      98,   127,   129,   128,   131,   130,   107,   108,   112,   113,
     110,   109,   111,   115,   114,   116,     0,     0,   118,   117,
     119,     0,     0,   123,   122,   124,    99,   100,   101,   102,
     103,   104,   105,   106,   140,   138,   137,     0,     0,    42,
       0,     0,     0,    61,    62,    63,    64,    65,    66,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    29,     0,
       0,    56,     0,    57,     0,    76,    75,    77,    68,    67,
      69,    71,    78,    70,    72,   121,   120,   126,   125,     0,
       0,     0,    59,     0,    32,    74,    73,    80,    79,     0,
      58,    60
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     8,     9,    10,    23,    27,    28,    54,    56,
      55,   103,   104,   133,   134,   135,   136,   189,   137,   138,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    52,    99,    25,    51
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -73
static const yytype_int16 yypact[] =
{
     -73,   218,   -73,    15,    72,    56,    89,    90,   -73,    42,
     -73,    47,    64,    69,   -73,   133,   136,   136,    92,   120,
     122,   124,    -2,    54,   -73,   -73,    98,    46,   -73,    51,
      84,   105,   106,   -73,   -73,   -73,   169,     5,   166,   -73,
     -73,   -73,   -73,   -73,   168,   -73,   170,   156,   159,   157,
     -73,   283,   344,   -73,    59,    59,    59,   -73,   -73,   -73,
     -73,   -73,   125,   -73,   178,    10,    10,   183,   408,   408,
      10,    10,   223,   223,    58,   129,   188,   189,   190,   191,
     210,   211,   212,   216,   217,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   314,
     344,   203,   -73,   162,   -73,   162,   162,   -73,   -73,   -73,
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   229,
     198,   221,   383,   171,   197,   202,   -73,   -73,   -73,   -73,
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,   -73,   -73,   -73,   -73,   224,   225,   -73,   -73,
     -73,   226,   230,   -73,   -73,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   213,    59,   -73,
     163,   163,   199,   -73,   -73,   -73,   -73,   -73,   -73,     1,
     258,   279,   176,   163,   163,   163,   163,   270,   -73,   222,
     228,   -73,   208,   -73,   195,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   227,
      44,   108,   -73,    49,   -73,   -73,   -73,   -73,   -73,   209,
     -73,   -73
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -73,   -73,   -73,   -73,   -73,   -73,   272,    -7,   -73,   -73,
     -73,     4,   118,   -64,   -56,   -72,   -73,    30,    32,    68,
     -43,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,   -73,     6,   -73,   245,   275,   -73
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -136
static const yytype_int16 yytable[] =
{
     152,   155,   160,   165,   142,   144,   202,    36,   150,   153,
     158,   163,   143,   145,   108,  -135,   151,   154,   159,   164,
      45,    24,    45,   109,   110,   111,  -135,    11,    12,    39,
      13,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   108,   225,
      26,   129,   130,   131,   229,    26,   176,   176,    22,   105,
     106,    37,   108,    15,   101,   112,   113,   114,    44,   203,
     204,   109,   110,   111,    46,    38,    14,   132,   102,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,    16,    17,   139,   129,
     156,   157,   146,   148,    30,    31,    18,    32,   199,   200,
      19,   132,   108,   227,    41,    42,    43,   230,   207,   210,
     214,   215,   216,   217,   218,   132,   206,    20,   212,   112,
     113,   114,    21,   108,   140,   209,   213,    22,   147,   149,
      26,    33,   109,   110,   111,    34,    35,    47,   226,   228,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   108,    48,    49,
     129,   161,   162,    50,    53,   132,    57,    59,    58,    61,
     108,   211,    60,   107,   112,   113,   114,   141,    37,   109,
     110,   111,   166,   167,   168,   169,   132,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   170,   171,   172,   129,     2,   183,
     173,   174,   184,   177,     3,   185,   178,   108,   186,     4,
     132,   187,   188,   179,   223,   190,   109,   110,   111,     5,
       6,     7,   180,   132,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   191,   108,   205,   129,   181,   192,   201,   193,   194,
     195,   109,   110,   111,   196,   219,   222,   231,   197,   112,
     113,   114,   115,   108,   208,   118,   220,    62,   121,    29,
     132,   124,   221,   224,   127,   128,   198,   100,    40,   129,
     112,   113,   114,     0,   116,   117,     0,   119,   120,     0,
     122,   123,     0,   125,   126,     0,     0,     0,    62,     0,
       0,    63,    64,    65,   175,   132,     0,     0,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,   132,    84,    62,     0,
       0,     0,    63,    64,    65,     0,     0,     0,     0,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,     0,     0,     0,
       0,     0,    63,    64,    65,     0,     0,     0,   182,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,   183,     0,     0,
     184,     0,     0,   185,     0,     0,   186,     0,     0,   187,
     188,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,     0,     0,     0,   129
};

static const yytype_int16 yycheck[] =
{
      72,    73,    74,    75,    68,    69,     5,     9,    72,    73,
      74,    75,    68,    69,     4,    10,    72,    73,    74,    75,
      27,    15,    29,    13,    14,    15,    21,    12,    13,    23,
      15,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,     4,     5,
       4,    41,    42,    43,     5,     4,    99,   100,     4,    55,
      56,    63,     4,     7,     5,    21,    22,    23,    22,    68,
      69,    13,    14,    15,    23,    21,     4,    67,    19,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,     7,     7,    66,    41,
      42,    43,    70,    71,    12,    13,    64,    15,   180,   181,
      63,    67,     4,     5,    16,    17,    18,    68,   190,   191,
     192,   193,   194,   195,   196,    67,   190,    63,   192,    21,
      22,    23,    63,     4,    66,   191,   192,     4,    70,    71,
       4,    21,    13,    14,    15,    23,    22,    63,   220,   221,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,     4,    63,    63,
      41,    42,    43,     4,     8,    67,     8,    21,     8,    22,
       4,     5,    23,     5,    21,    22,    23,     4,    63,    13,
      14,    15,     4,     4,     4,     4,    67,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,     4,     4,     4,    41,     0,    24,
       4,     4,    27,    20,     6,    30,    64,     4,    33,    11,
      67,    36,    37,     4,   204,    64,    13,    14,    15,    21,
      22,    23,    44,    67,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    64,     4,     5,    41,    44,    64,    68,    44,    44,
      44,    13,    14,    15,    44,     5,    68,    68,    65,    21,
      22,    23,    24,     4,     5,    27,    64,     4,    30,    17,
      67,    33,    64,    66,    36,    37,   178,    52,    23,    41,
      21,    22,    23,    -1,    25,    26,    -1,    28,    29,    -1,
      31,    32,    -1,    34,    35,    -1,    -1,    -1,     4,    -1,
      -1,    38,    39,    40,    10,    67,    -1,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    67,    64,     4,    -1,
      -1,    -1,    38,    39,    40,    -1,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    -1,    -1,    -1,
      -1,    -1,    38,    39,    40,    -1,    -1,    -1,     5,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    24,    -1,    -1,
      27,    -1,    -1,    30,    -1,    -1,    33,    -1,    -1,    36,
      37,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    -1,    -1,    41
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    71,     0,     6,    11,    21,    22,    23,    72,    73,
      74,    12,    13,    15,     4,     7,     7,     7,    64,    63,
      63,    63,     4,    75,   103,   106,     4,    76,    77,    76,
      12,    13,    15,    21,    23,    22,     9,    63,    21,   103,
     106,    16,    17,    18,    22,    77,    23,    63,    63,    63,
       4,   107,   104,     8,    78,    80,    79,     8,     8,    21,
      23,    22,     4,    38,    39,    40,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    64,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   105,
     105,     5,    19,    81,    82,    81,    81,     5,     4,    13,
      14,    15,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    41,
      42,    43,    67,    83,    84,    85,    86,    88,    89,    88,
      89,     4,    83,    84,    83,    84,    88,    89,    88,    89,
      83,    84,    85,    83,    84,    85,    42,    43,    83,    84,
      85,    42,    43,    83,    84,    85,     4,     4,     4,     4,
       4,     4,     4,     4,     4,    10,    90,    20,    64,     4,
      44,    44,     5,    24,    27,    30,    33,    36,    37,    87,
      64,    64,    64,    44,    44,    44,    44,    65,    82,    85,
      85,    68,     5,    68,    69,     5,    83,    85,     5,    84,
      85,     5,    83,    84,    85,    85,    85,    85,    85,     5,
      64,    64,    68,    87,    66,     5,    85,     5,    85,     5,
      68,    68
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
#line 63 "config/parser.y"
    {   
                            error_flag = 0;
                            error_debug_flag = 0;                           
                            line("Line:%-4d",1);
                            debug ("input ::= empty\n"); 
                            root = new InputNode ();
                            global = new GlobalNode();
                            all_node.push_back((Node*)root);
                        ;}
    break;

  case 3:
#line 72 "config/parser.y"
    {
                            line("Line:%-4d",(yylsp[(2) - (2)]).first_line);
                            debug ("input ::= input CompUnit\n"); 
                            if ((yyvsp[(2) - (2)].node)!=NULL)   // ignore empty line
                            {   
                                if(error_flag == 0)
                                    root->append ((CompUnitNode*)(yyvsp[(2) - (2)].node));
                            }
                        ;}
    break;

  case 4:
#line 82 "config/parser.y"
    {
                            line("Line:%-4d",(yylsp[(1) - (1)]).first_line);
                            debug ("Assume ::= assume cs:code,ds:data,ss:stack\n");
                            line("Line:%-4d",(yylsp[(1) - (1)]).first_line);
                            debug ("CompUnit ::= Assume\n");
                            if(error_flag == 0)
                            {   
                                (yyval.node) = new AssumeNode(); 
                                (yyval.node)->setLoc((Loc*)&((yyloc)));
                                all_node.push_back((Node*)(yyval.node));
                            }  
                        ;}
    break;

  case 5:
#line 94 "config/parser.y"
    {
                            line("Line:%-4d",(yylsp[(1) - (1)]).first_line);
                            debug ("CompUnit ::= Segment\n");
                            (yyval.node) = (yyvsp[(1) - (1)].node); 
                        ;}
    break;

  case 6:
#line 99 "config/parser.y"
    {
                                        line("Line:%-4d",(yylsp[(1) - (2)]).first_line);
                                        debug ("CompUnit ::= end %s\n",(yyvsp[(2) - (2)].var)->c_str());
                                        (yyval.node) = NULL;
                                    ;}
    break;

  case 13:
#line 114 "config/parser.y"
    {
                                                                    line("Line:%-4d",(yyloc).first_line);
                                                                    debug ("Segment ::= data Segment\n");  
                                                                    (yyval.node) = (yyvsp[(3) - (5)].node);  
                                                                    global->SetMemLength((yyvsp[(1) - (5)].var),8);
                                                                ;}
    break;

  case 14:
#line 120 "config/parser.y"
    {
                                                                    line("Line:%-4d",(yyloc).first_line);
                                                                    debug ("Segment ::= stack Segment\n"); 
                                                                    (yyval.node) = (yyvsp[(3) - (5)].node);   
                                                                    global->SetMemLength((yyvsp[(1) - (5)].var),8);
                                                                ;}
    break;

  case 15:
#line 126 "config/parser.y"
    {
                                                                    line("Line:%-4d",(yyloc).first_line);
                                                                    debug ("Segment ::= code Segment\n");
                                                                    (yyval.node) = (yyvsp[(3) - (5)].node);
                                                                    global->SetMemLength((yyvsp[(1) - (5)].var),8);
                                                                ;}
    break;

  case 16:
#line 134 "config/parser.y"
    {
                                        line("Line:%-4d",(yyloc).first_line);
                                        debug ("Content ::= Block\n"); 
                                        if(error_flag == 0)
                                        {   
                                            (yyval.node) = new ContentNode(); 
                                            ((ContentNode*)(yyval.node))->appendB((BlockNode*)(yyvsp[(1) - (1)].node));
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        }       
                                    ;}
    break;

  case 17:
#line 145 "config/parser.y"
    {
                                        line("Line:%-4d",(yyloc).first_line);
                                        debug ("Content ::= Macro\n");   
                                        if(error_flag == 0)
                                        {   
                                            (yyval.node) = new ContentNode(); 
                                            ((ContentNode*)(yyval.node))->appendM((MacroNode*)(yyvsp[(1) - (1)].node));
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        }   
                                    ;}
    break;

  case 18:
#line 156 "config/parser.y"
    {
                                        line("Line:%-4d",(yyloc).first_line);
                                        debug ("Content ::= Content Block\n"); 
                                        if(error_flag == 0)
                                        {   
                                            ((ContentNode*)(yyval.node))->appendB((BlockNode*)(yyvsp[(2) - (2)].node));
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                        }    
                                    ;}
    break;

  case 19:
#line 165 "config/parser.y"
    {
                                        line("Line:%-4d",(yyloc).first_line);
                                        debug ("Content ::= Content Macro\n");  
                                        if(error_flag == 0)
                                        {   
                                            ((ContentNode*)(yyval.node))->appendM((MacroNode*)(yyvsp[(2) - (2)].node));
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                        }    
                                    ;}
    break;

  case 20:
#line 176 "config/parser.y"
    {
                                                        if(error_flag == 0)
                                                        {   
                                                            (yyval.node) = new AllocaSegmentNode();
                                                            ((AllocaSegmentNode*)(yyval.node)) ->append((AllocaLineNode*)(yyvsp[(1) - (1)].node));
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }  
                                                        line("Line:%-4d",(yyloc).first_line);
                                                        debug ("Alloca ::= AllocaLine\n");   
                                                    ;}
    break;

  case 21:
#line 187 "config/parser.y"
    {
                                                        line("Line:%-4d",(yylsp[(2) - (2)]).first_line);
                                                        debug ("Alloca ::= Alloca AllocaLine\n"); 
                                                        if(error_flag == 0)
                                                        {   
                                                            ((AllocaSegmentNode*)(yyval.node))->append((AllocaLineNode*)(yyvsp[(2) - (2)].node));
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                        }    
                                                    ;}
    break;

  case 22:
#line 197 "config/parser.y"
    {global->now_length = 8;;}
    break;

  case 23:
#line 198 "config/parser.y"
    {
                                                        if(error_flag == 0)
                                                        {   
                                                            (yyval.node) = new AllocaLineNode((yyvsp[(1) - (4)].var),8); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        } 
                                                        global->SetMemLength((yyvsp[(1) - (4)].var),8);
                                                    ;}
    break;

  case 24:
#line 207 "config/parser.y"
    {global->now_length = 16;;}
    break;

  case 25:
#line 208 "config/parser.y"
    {
                                                        if(error_flag == 0)
                                                        {   
                                                            (yyval.node) = new AllocaLineNode((yyvsp[(1) - (4)].var),16); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }  
                                                        global->SetMemLength((yyvsp[(1) - (4)].var),16);
                                                    ;}
    break;

  case 26:
#line 217 "config/parser.y"
    {global->now_length = 32;;}
    break;

  case 27:
#line 218 "config/parser.y"
    {
                                                        if(error_flag == 0)
                                                        {   
                                                            (yyval.node) = new AllocaLineNode((yyvsp[(1) - (4)].var),32); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }  
                                                        global->SetMemLength((yyvsp[(1) - (4)].var),32);
                                                    ;}
    break;

  case 30:
#line 233 "config/parser.y"
    {
                                                if(global->now_length > 8)
                                                {
                                                    if(global->now_length == 16)
                                                        error("%s:%3d.(%2d) Wrong to store ASCII to [word]! please use [byte]\n",infile_name,(yyloc).first_line,(yylsp[(1) - (1)]).first_column+1);
                                                    else 
                                                        error("%s:%3d.(%2d) Wrong to store ASCII to [double word]! please use [byte]\n",infile_name,(yyloc).first_line,(yylsp[(1) - (1)]).first_column+1);
                                                    show_line((yyloc).first_line,infile_name);
                                                    print_blank((yylsp[(1) - (1)]).first_column+1);
                                                    root = NULL;
                                                    error_flag =1;
                                                }
                                            ;}
    break;

  case 31:
#line 246 "config/parser.y"
    {
                                                if(global->now_length == 8 && (yyvsp[(1) - (1)].num) > 256)
                                                {
                                                    error("%s:%3d.(%2d) Can't store Number over 256 to [byte]!\n",infile_name,(yyloc).first_line,(yylsp[(1) - (1)]).first_column);
                                                    show_line((yyloc).first_line,infile_name);
                                                    print_blank((yylsp[(1) - (1)]).first_column);
                                                    root = NULL;
                                                    error_flag =1;
                                                }
                                                if(global->now_length == 16 && (yyvsp[(1) - (1)].num) > 65536)
                                                {
                                                    error("%s:%3d.(%2d) Can't store Number over 65536 to [word]!\n",infile_name,(yyloc).first_line,(yylsp[(1) - (1)]).first_column);
                                                    show_line((yyloc).first_line,infile_name);
                                                    print_blank((yylsp[(1) - (1)]).first_column);
                                                    root = NULL;
                                                    error_flag =1;
                                                }
                                            ;}
    break;

  case 33:
#line 267 "config/parser.y"
    {
                                (yyval.regnode) = global->ax;   
                            ;}
    break;

  case 34:
#line 270 "config/parser.y"
    {
                                (yyval.regnode) = global->bx;   
                            ;}
    break;

  case 35:
#line 273 "config/parser.y"
    {
                                (yyval.regnode) = global->cx;   
                            ;}
    break;

  case 36:
#line 276 "config/parser.y"
    {
                                (yyval.regnode) = global->dx;   
                            ;}
    break;

  case 37:
#line 279 "config/parser.y"
    {
                                (yyval.regnode) = global->si;   
                            ;}
    break;

  case 38:
#line 282 "config/parser.y"
    {
                                (yyval.regnode) = global->di;   
                            ;}
    break;

  case 39:
#line 285 "config/parser.y"
    {
                                (yyval.regnode) = global->ds;   
                            ;}
    break;

  case 40:
#line 288 "config/parser.y"
    {
                                (yyval.regnode) = global->ss;   
                            ;}
    break;

  case 41:
#line 291 "config/parser.y"
    {
                                (yyval.regnode) = global->sp;   
                            ;}
    break;

  case 42:
#line 294 "config/parser.y"
    {
                                (yyval.regnode) = global->mem;   
                            ;}
    break;

  case 43:
#line 299 "config/parser.y"
    {
                                (yyval.regnode) = global->ax->h;   
                            ;}
    break;

  case 44:
#line 302 "config/parser.y"
    {
                                (yyval.regnode) = global->ax->l;   
                            ;}
    break;

  case 45:
#line 305 "config/parser.y"
    {
                                (yyval.regnode) = global->bx->h;   
                            ;}
    break;

  case 46:
#line 308 "config/parser.y"
    {
                                (yyval.regnode) = global->bx->l;   
                            ;}
    break;

  case 47:
#line 311 "config/parser.y"
    {
                                (yyval.regnode) = global->cx->h;   
                            ;}
    break;

  case 48:
#line 314 "config/parser.y"
    {
                                (yyval.regnode) = global->cx->l;   
                            ;}
    break;

  case 49:
#line 317 "config/parser.y"
    {
                                (yyval.regnode) = global->dx->h;   
                            ;}
    break;

  case 50:
#line 320 "config/parser.y"
    {
                                (yyval.regnode) = global->dx->l;   
                            ;}
    break;

  case 51:
#line 324 "config/parser.y"
    {
                                (yyval.regnode) = global->mem;   
                                if(global->GetMemLength((yyvsp[(1) - (1)].var)) == 0){
                                    error("%s:%3d.(%2d) The Memory address isn't defined : %s\n",infile_name,(yyloc).first_line,(yylsp[(1) - (1)]).first_column,(yyvsp[(1) - (1)].var)->c_str());
                                    show_line((yyloc).first_line,infile_name);
                                    print_blank((yylsp[(1) - (1)]).first_column);
                                    root = NULL;
                                    error_flag =1;
                                }
                            ;}
    break;

  case 52:
#line 334 "config/parser.y"
    {
                                (yyval.regnode) = global->mem;   
                            ;}
    break;

  case 53:
#line 337 "config/parser.y"
    {
                                (yyval.regnode) = global->mem;  
                            ;}
    break;

  case 54:
#line 340 "config/parser.y"
    {
                                (yyval.regnode) = global->mem;  
                            ;}
    break;

  case 55:
#line 343 "config/parser.y"
    {
                                line("Line:%-4d",(yyloc).first_line);
                                debug ("MemAddr ::= MemAddrExp\n"); 
                            ;}
    break;

  case 57:
#line 349 "config/parser.y"
    {
                                                        if(strcmp("cx",(yyvsp[(2) - (3)].var)->c_str()) == 0)
                                                        {
                                                            error("%s:%3d.(%2d) There can't be cx! please use bx|si|di|num\n",infile_name,(yyloc).first_line,(yylsp[(2) - (3)]).first_column);
                                                            show_line((yyloc).first_line,infile_name);
                                                            print_blank((yylsp[(2) - (3)]).first_column);
                                                            root = NULL;
                                                            error_flag =1;
                                                        }
                                                        if(strcmp("dx",(yyvsp[(2) - (3)].var)->c_str()) == 0)
                                                        {
                                                            error("%s:%3d.(%2d) There can't be dx! please use bx|si|di|num\n",infile_name,(yyloc).first_line,(yylsp[(2) - (3)]).first_column);
                                                            show_line((yyloc).first_line,infile_name);
                                                            print_blank((yylsp[(2) - (3)]).first_column);
                                                            root = NULL;
                                                            error_flag =1;
                                                        }
                                                        if(strcmp("ax",(yyvsp[(2) - (3)].var)->c_str()) == 0)
                                                        {
                                                            error("%s:%3d.(%2d) There can't be ax! please use bx|si|di|num\n",infile_name,(yyloc).first_line,(yylsp[(2) - (3)]).first_column);
                                                            show_line((yyloc).first_line,infile_name);
                                                            print_blank((yylsp[(2) - (3)]).first_column);
                                                            root = NULL;
                                                            error_flag =1;
                                                        }
                                                    ;}
    break;

  case 58:
#line 375 "config/parser.y"
    {
                                                        if(strcmp("bx",(yyvsp[(2) - (5)].var)->c_str()) != 0)
                                                        {
                                                            error("%s:%3d.(%2d) There can't be %s! please use bx\n",infile_name,(yyloc).first_line,(yylsp[(2) - (5)]).first_column,(yyvsp[(2) - (5)].var)->c_str());
                                                            show_line((yyloc).first_line,infile_name);
                                                            print_blank((yylsp[(2) - (5)]).first_column);
                                                            root = NULL;
                                                            error_flag =1;
                                                        }
                                                        if(strcmp("si",(yyvsp[(4) - (5)].var)->c_str()) != 0 && strcmp("di",(yyvsp[(4) - (5)].var)->c_str()) != 0)
                                                        {
                                                            error("%s:%3d.(%2d) There can't be %s! please use si|di|num\n",infile_name,(yyloc).first_line,(yylsp[(2) - (5)]).first_column,(yyvsp[(4) - (5)].var)->c_str());
                                                            show_line((yyloc).first_line,infile_name);
                                                            print_blank((yylsp[(2) - (5)]).first_column);
                                                            root = NULL;
                                                            error_flag =1;
                                                        }
                                                    ;}
    break;

  case 59:
#line 393 "config/parser.y"
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
                                                        if(strcmp("cx",(yyvsp[(2) - (4)].var)->c_str()) == 0)
                                                        {
                                                            error("%s:%3d.(%2d) There can't be cx! please use bx|si|di\n",infile_name,(yyloc).first_line,(yylsp[(2) - (4)]).first_column);
                                                            show_line((yyloc).first_line,infile_name);
                                                            print_blank((yylsp[(2) - (4)]).first_column);
                                                            root = NULL;
                                                            error_flag =1;
                                                        }
                                                        if(strcmp("dx",(yyvsp[(2) - (4)].var)->c_str()) == 0)
                                                        {
                                                            error("%s:%3d.(%2d) There can't be dx! please use bx|si|di\n",infile_name,(yyloc).first_line,(yylsp[(2) - (4)]).first_column);
                                                            show_line((yyloc).first_line,infile_name);
                                                            print_blank((yylsp[(2) - (4)]).first_column);
                                                            root = NULL;
                                                            error_flag =1;
                                                        }
                                                        if(strcmp("ax",(yyvsp[(2) - (4)].var)->c_str()) == 0)
                                                        {
                                                            error("%s:%3d.(%2d) There can't be ax! please use bx|si|di\n",infile_name,(yyloc).first_line,(yylsp[(2) - (4)]).first_column);
                                                            show_line((yyloc).first_line,infile_name);
                                                            print_blank((yylsp[(2) - (4)]).first_column);
                                                            root = NULL;
                                                            error_flag =1;
                                                        }
                                                    ;}
    break;

  case 60:
#line 429 "config/parser.y"
    {
                                                        if(strcmp("bx",(yyvsp[(2) - (6)].var)->c_str()) != 0)
                                                        {
                                                            error("%s:%3d.(%2d) There can't be %s! please use bx\n",infile_name,(yyloc).first_line,(yylsp[(2) - (6)]).first_column,(yyvsp[(2) - (6)].var)->c_str());
                                                            show_line((yyloc).first_line,infile_name);
                                                            print_blank((yylsp[(2) - (6)]).first_column);
                                                            root = NULL;
                                                            error_flag =1;
                                                        }
                                                        if(strcmp("si",(yyvsp[(4) - (6)].var)->c_str()) != 0 && strcmp("di",(yyvsp[(4) - (6)].var)->c_str()) != 0)
                                                        {
                                                            error("%s:%3d.(%2d) There can't be %s! please use si|di\n",infile_name,(yyloc).first_line,(yylsp[(2) - (6)]).first_column,(yyvsp[(4) - (6)].var)->c_str());
                                                            show_line((yyloc).first_line,infile_name);
                                                            print_blank((yylsp[(2) - (6)]).first_column);
                                                            root = NULL;
                                                            error_flag =1;
                                                        }
                                                    ;}
    break;

  case 67:
#line 458 "config/parser.y"
    {
                                                        if(error_flag == 0)
                                                        {   
                                                            (yyval.node) = new DoubleONode((RegNode*)(yyvsp[(1) - (3)].regnode),(RegNode*)(yyvsp[(3) - (3)].regnode)); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }  
                                                    ;}
    break;

  case 68:
#line 466 "config/parser.y"
    {
                                                        if(error_flag == 0)
                                                        {   
                                                            RegSNode * num = new RegSNode(); 
                                                            char str[10];
                                                            sprintf(str,"%d",(yyvsp[(3) - (3)].num));
                                                            num->name = new std::string (str);
                                                            (yyval.node) = new DoubleONode((RegNode*)(yyvsp[(1) - (3)].regnode),(RegNode*)num); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }  
                                                        if( (yyvsp[(3) - (3)].num) > 256)
                                                        {
                                                            error("%s:%3d.(%2d) Can't store Number over 256 to [byte]!\n",infile_name,(yyloc).first_line,(yylsp[(3) - (3)]).first_column);
                                                            show_line((yyloc).first_line,infile_name);
                                                            print_blank((yylsp[(3) - (3)]).first_column);
                                                            root = NULL;
                                                            error_flag =1;
                                                        }
                                                    ;}
    break;

  case 69:
#line 486 "config/parser.y"
    {
                                                        if(error_flag == 0)
                                                        {   
                                                            (yyval.node) = new DoubleONode((RegNode*)(yyvsp[(1) - (3)].regnode),(RegNode*)(yyvsp[(3) - (3)].regnode)); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }  
                                                    ;}
    break;

  case 70:
#line 494 "config/parser.y"
    {
                                                        if(error_flag == 0)
                                                        {   
                                                            (yyval.node) = new DoubleONode((RegNode*)(yyvsp[(1) - (3)].regnode),(RegNode*)(yyvsp[(3) - (3)].regnode)); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }  
                                                    ;}
    break;

  case 71:
#line 502 "config/parser.y"
    {
                                                        if(error_flag == 0)
                                                        {   
                                                            RegSNode * num = new RegSNode(); 
                                                            char str[10];
                                                            sprintf(str,"%d",(yyvsp[(3) - (3)].num));
                                                            num->name = new std::string (str);
                                                            (yyval.node) = new DoubleONode((RegNode*)(yyvsp[(1) - (3)].regnode),(RegNode*)num); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }  
                                                    ;}
    break;

  case 72:
#line 514 "config/parser.y"
    {
                                                        error("%s:%3d.(%2d)[Severe ERROR]:It's wrong to 'mov mem,mem'\n",infile_name,(yyloc).first_line,(yylsp[(3) - (3)]).first_column);
                                                        show_line((yyloc).first_line,infile_name);
                                                        print_blank((yylsp[(3) - (3)]).first_column);
                                                        root = NULL;
                                                        error_flag =1;
                                                        
                                                    ;}
    break;

  case 73:
#line 522 "config/parser.y"
    {
                                                        error("%s:%3d.(%2d)[Severe ERROR]:It's wrong to 'mov mem,mem'\n",infile_name,(yyloc).first_line,(yylsp[(3) - (5)]).first_column);
                                                        show_line((yyloc).first_line,infile_name);
                                                        print_blank((yylsp[(3) - (5)]).first_column);
                                                        root = NULL;
                                                        error_flag =1;
                                                    ;}
    break;

  case 74:
#line 529 "config/parser.y"
    {
                                                        if(error_flag == 0)
                                                        {   
                                                            RegSNode * num = new RegSNode(); 
                                                            char str[10];
                                                            sprintf(str,"%d",(yyvsp[(5) - (5)].num));
                                                            num->name = new std::string (str);
                                                            (yyval.node) = new DoubleONode((RegNode*)(yyvsp[(3) - (5)].regnode),(RegNode*)num); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }  
                                                        if( (yyvsp[(5) - (5)].num) > 256)
                                                        {
                                                            error("%s:%3d.(%2d) Can't store Number over 256 to [byte]!\n",infile_name,(yyloc).first_line,(yylsp[(5) - (5)]).first_column);
                                                            show_line((yyloc).first_line,infile_name);
                                                            print_blank((yylsp[(5) - (5)]).first_column);
                                                        }
                                                    ;}
    break;

  case 75:
#line 548 "config/parser.y"
    {
                                                        if(error_flag == 0)
                                                        {   
                                                            (yyval.node) = new DoubleONode((RegNode*)(yyvsp[(1) - (3)].regnode),(RegNode*)(yyvsp[(3) - (3)].regnode)); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }  
                                                    ;}
    break;

  case 76:
#line 556 "config/parser.y"
    {
                                                        if(error_flag == 0)
                                                        {   
                                                            RegSNode * num = new RegSNode(); 
                                                            char str[10];
                                                            sprintf(str,"%d",(yyvsp[(3) - (3)].num));
                                                            num->name = new std::string (str);
                                                            (yyval.node) = new DoubleONode((RegNode*)(yyvsp[(1) - (3)].regnode),(RegNode*)num); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                            
                                                        }  
                                                        if( (yyvsp[(3) - (3)].num) > 65536)
                                                            {
                                                                error("%s:%3d.(%2d) Can't store Number over 65536 to [word]!\n",infile_name,(yyloc).first_line,(yylsp[(3) - (3)]).first_column);
                                                                show_line((yyloc).first_line,infile_name);
                                                                print_blank((yylsp[(3) - (3)]).first_column);
                                                                root = NULL;
                                                                error_flag =1;
                                                            }
                                                    ;}
    break;

  case 77:
#line 577 "config/parser.y"
    {
                                                        if(error_flag == 0)
                                                        {   
                                                            (yyval.node) = new DoubleONode((RegNode*)(yyvsp[(1) - (3)].regnode),(RegNode*)(yyvsp[(3) - (3)].regnode)); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }  
                                                    ;}
    break;

  case 78:
#line 585 "config/parser.y"
    {
                                                        if(error_flag == 0)
                                                        {   
                                                            (yyval.node) = new DoubleONode((RegNode*)(yyvsp[(1) - (3)].regnode),(RegNode*)(yyvsp[(3) - (3)].regnode)); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }  
                                                    ;}
    break;

  case 79:
#line 593 "config/parser.y"
    {
                                                        error("%s:%3d.(%2d)[Severe ERROR]:It's wrong to 'mov mem,mem'\n",infile_name,(yyloc).first_line,(yylsp[(3) - (5)]).first_column);
                                                        show_line((yyloc).first_line,infile_name);
                                                        print_blank((yylsp[(3) - (5)]).first_column);
                                                        root = NULL;
                                                            error_flag =1;
                                                         
                                                    ;}
    break;

  case 80:
#line 601 "config/parser.y"
    {
                                                        if(error_flag == 0)
                                                        {   
                                                            RegSNode * num = new RegSNode(); 
                                                            char str[10];
                                                            sprintf(str,"%d",(yyvsp[(5) - (5)].num));
                                                            num->name = new std::string (str);
                                                            (yyval.node) = new DoubleONode((RegNode*)(yyvsp[(3) - (5)].regnode),(RegNode*)num); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }  
                                                    ;}
    break;

  case 81:
#line 614 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Int_ins\n");  
                                    (yyval.node) = (yyvsp[(1) - (1)].node);
                                ;}
    break;

  case 82:
#line 619 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Mov_ins\n"); 
                                    (yyval.node) = (yyvsp[(1) - (1)].node);
                                ;}
    break;

  case 83:
#line 624 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Cmp_ins\n");   
                                    (yyval.node) = (yyvsp[(1) - (1)].node);
                                ;}
    break;

  case 84:
#line 629 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Jmp_ins\n");  
                                    (yyval.node) = (yyvsp[(1) - (1)].node); 
                                ;}
    break;

  case 85:
#line 634 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Add_ins\n"); 
                                    (yyval.node) = (yyvsp[(1) - (1)].node);  
                                ;}
    break;

  case 86:
#line 639 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Sub_ins\n");  
                                    (yyval.node) = (yyvsp[(1) - (1)].node); 
                                ;}
    break;

  case 87:
#line 644 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Mul_ins\n");  
                                    (yyval.node) = (yyvsp[(1) - (1)].node);  
                                ;}
    break;

  case 88:
#line 649 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Div_ins\n");  
                                    (yyval.node) = (yyvsp[(1) - (1)].node);  
                                ;}
    break;

  case 89:
#line 654 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Call_ins\n");   
                                    (yyval.node) = (yyvsp[(1) - (1)].node); 
                                ;}
    break;

  case 90:
#line 659 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Push_ins\n");  
                                    (yyval.node) = (yyvsp[(1) - (1)].node); 
                                ;}
    break;

  case 91:
#line 664 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Pop_ins\n");  
                                    (yyval.node) = (yyvsp[(1) - (1)].node); 
                                ;}
    break;

  case 92:
#line 669 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Ret_ins\n"); 
                                    (yyval.node) = (yyvsp[(1) - (1)].node);  
                                ;}
    break;

  case 93:
#line 674 "config/parser.y"
    {
                                    line("Line:%-4d",(yyloc).first_line);
                                    debug ("Instruction ::= Block\n");   
                                    (yyval.node) = (yyvsp[(1) - (1)].node);
                                ;}
    break;

  case 94:
#line 681 "config/parser.y"
    {
                                    if(error_flag == 0)
                                    {   
                                        (yyval.node) = new IntInsNode((yyvsp[(2) - (2)].num)); 
                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                        all_node.push_back((Node*)(yyval.node));
                                    }  
                                ;}
    break;

  case 95:
#line 691 "config/parser.y"
    {
                                    if(error_flag == 0)
                                    {   
                                        (yyval.node) = new MovInsNode((DoubleONode*)(yyvsp[(2) - (2)].node)); 
                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                        all_node.push_back((Node*)(yyval.node));
                                    }  
                                ;}
    break;

  case 96:
#line 699 "config/parser.y"
    {
                                    if(error_flag == 0)
                                    {   
                                        (yyval.node) = new MovInsNode((DoubleONode*)(yyvsp[(2) - (2)].node)); 
                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                        all_node.push_back((Node*)(yyval.node));
                                    }  
                                ;}
    break;

  case 97:
#line 709 "config/parser.y"
    {
                                    if(error_flag == 0)
                                    {   
                                        (yyval.node) = new CmpInsNode((DoubleONode*)(yyvsp[(2) - (2)].node)); 
                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                        all_node.push_back((Node*)(yyval.node));
                                    }  
                                ;}
    break;

  case 98:
#line 717 "config/parser.y"
    {
                                    if(error_flag == 0)
                                    {   
                                        (yyval.node) = new CmpInsNode((DoubleONode*)(yyvsp[(2) - (2)].node)); 
                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                        all_node.push_back((Node*)(yyval.node));
                                    }  
                                ;}
    break;

  case 99:
#line 727 "config/parser.y"
    {
                                    if(error_flag == 0)
                                    {   
                                        (yyval.node) = new JmpInsNode(0,(yyvsp[(2) - (2)].var)); 
                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                        all_node.push_back((Node*)(yyval.node));
                                    }  
                                    if(global->GetLabelLine((yyvsp[(2) - (2)].var)) == 0){
                                            error("%s:%3d.(%2d)This label isn't defined : %s\n",infile_name,(yyloc).first_line,(yylsp[(2) - (2)]).first_column,(yyvsp[(2) - (2)].var)->c_str());
                                            show_line((yyloc).first_line,infile_name);
                                            print_blank((yylsp[(2) - (2)]).first_column);
                                            root = NULL;
                                            error_flag =1;
                                    }
                                ;}
    break;

  case 100:
#line 742 "config/parser.y"
    {
                                    if(error_flag == 0)
                                    {   
                                        (yyval.node) = new JmpInsNode(2,(yyvsp[(2) - (2)].var)); 
                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                        all_node.push_back((Node*)(yyval.node));
                                    }  
                                    if(global->GetLabelLine((yyvsp[(2) - (2)].var)) == 0){
                                            error("%s:%3d.(%2d)This label isn't defined : %s\n",infile_name,(yyloc).first_line,(yylsp[(2) - (2)]).first_column,(yyvsp[(2) - (2)].var)->c_str());
                                            show_line((yyloc).first_line,infile_name);
                                            print_blank((yylsp[(2) - (2)]).first_column);
                                            root = NULL;
                                            error_flag =1;
                                    }
                                ;}
    break;

  case 101:
#line 757 "config/parser.y"
    {
                                    if(error_flag == 0)
                                    {   
                                        (yyval.node) = new JmpInsNode(1,(yyvsp[(2) - (2)].var)); 
                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                        all_node.push_back((Node*)(yyval.node));
                                    }  
                                    if(global->GetLabelLine((yyvsp[(2) - (2)].var)) == 0){
                                            error("%s:%3d.(%2d)This label isn't defined : %s\n",infile_name,(yyloc).first_line,(yylsp[(2) - (2)]).first_column,(yyvsp[(2) - (2)].var)->c_str());
                                            show_line((yyloc).first_line,infile_name);
                                            print_blank((yylsp[(2) - (2)]).first_column);
                                            root = NULL;
                                            error_flag =1;
                                    }
                                ;}
    break;

  case 102:
#line 772 "config/parser.y"
    {
                                    if(error_flag == 0)
                                    {   
                                        (yyval.node) = new JmpInsNode(4,(yyvsp[(2) - (2)].var)); 
                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                        all_node.push_back((Node*)(yyval.node));
                                    } 
                                    if(global->GetLabelLine((yyvsp[(2) - (2)].var)) == 0){
                                            error("%s:%3d.(%2d)This label isn't defined : %s\n",infile_name,(yyloc).first_line,(yylsp[(2) - (2)]).first_column,(yyvsp[(2) - (2)].var)->c_str());
                                            show_line((yyloc).first_line,infile_name);
                                            print_blank((yylsp[(2) - (2)]).first_column);
                                            root = NULL;
                                            error_flag =1;
                                    } 
                                ;}
    break;

  case 103:
#line 787 "config/parser.y"
    {
                                    if(error_flag == 0)
                                    {   
                                        (yyval.node) = new JmpInsNode(5,(yyvsp[(2) - (2)].var)); 
                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                        all_node.push_back((Node*)(yyval.node));
                                    }  
                                    if(global->GetLabelLine((yyvsp[(2) - (2)].var)) == 0){
                                            error("%s:%3d.(%2d)This label isn't defined : %s\n",infile_name,(yyloc).first_line,(yylsp[(2) - (2)]).first_column,(yyvsp[(2) - (2)].var)->c_str());
                                            show_line((yyloc).first_line,infile_name);
                                            print_blank((yylsp[(2) - (2)]).first_column);
                                            root = NULL;
                                            error_flag =1;
                                    }
                                ;}
    break;

  case 104:
#line 802 "config/parser.y"
    {
                                    if(error_flag == 0)
                                    {   
                                        (yyval.node) = new JmpInsNode(3,(yyvsp[(2) - (2)].var)); 
                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                        all_node.push_back((Node*)(yyval.node));
                                    } 
                                    if(global->GetLabelLine((yyvsp[(2) - (2)].var)) == 0){
                                            error("%s:%3d.(%2d)This label isn't defined : %s\n",infile_name,(yyloc).first_line,(yylsp[(2) - (2)]).first_column,(yyvsp[(2) - (2)].var)->c_str());
                                            show_line((yyloc).first_line,infile_name);
                                            print_blank((yylsp[(2) - (2)]).first_column);
                                            root = NULL;
                                            error_flag =1;
                                    } 
                                ;}
    break;

  case 105:
#line 817 "config/parser.y"
    {
                                    if(error_flag == 0)
                                    {   
                                        (yyval.node) = new JmpInsNode(6,(yyvsp[(2) - (2)].var)); 
                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                        all_node.push_back((Node*)(yyval.node));
                                    }
                                    if(global->GetLabelLine((yyvsp[(2) - (2)].var)) == 0){
                                            error("%s:%3d.(%2d)This label isn't defined : %s\n",infile_name,(yyloc).first_line,(yylsp[(2) - (2)]).first_column,(yyvsp[(2) - (2)].var)->c_str());
                                            show_line((yyloc).first_line,infile_name);
                                            print_blank((yylsp[(2) - (2)]).first_column);
                                            root = NULL;
                                            error_flag =1;
                                    }  
                                ;}
    break;

  case 106:
#line 832 "config/parser.y"
    {
                                    if(error_flag == 0)
                                    {   
                                        (yyval.node) = new JmpInsNode(7,(yyvsp[(2) - (2)].var)); 
                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                        all_node.push_back((Node*)(yyval.node));
                                    }  
                                    if(global->GetLabelLine((yyvsp[(2) - (2)].var)) == 0){
                                            error("%s:%3d.(%2d)This label isn't defined : %s\n",infile_name,(yyloc).first_line,(yylsp[(2) - (2)]).first_column,(yyvsp[(2) - (2)].var)->c_str());
                                            show_line((yyloc).first_line,infile_name);
                                            print_blank((yylsp[(2) - (2)]).first_column);
                                            root = NULL;
                                            error_flag =1;
                                    }
                                ;}
    break;

  case 107:
#line 849 "config/parser.y"
    {
                                        if(error_flag == 0)
                                        {   
                                            (yyval.node) = new AddInsNode((DoubleONode*)(yyvsp[(2) - (2)].node)); 
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        }  
                                    ;}
    break;

  case 108:
#line 857 "config/parser.y"
    {
                                        if(error_flag == 0)
                                        {   
                                            (yyval.node) = new AddInsNode((DoubleONode*)(yyvsp[(2) - (2)].node)); 
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        }  
                                    ;}
    break;

  case 109:
#line 865 "config/parser.y"
    {
                                        if(error_flag == 0)
                                        {   
                                            RegSNode * num = new RegSNode(); 
                                            char str[10];
                                            sprintf(str,"%d",1);
                                            num->name = new std::string (str);
                                            DoubleONode *operand = new DoubleONode((RegNode*)(yyvsp[(2) - (2)].regnode),(RegNode*)num); 
                                            (yyval.node) = new AddInsNode((DoubleONode*)operand); 
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        }  
                                    ;}
    break;

  case 110:
#line 878 "config/parser.y"
    {
                                        if(error_flag == 0)
                                        {   
                                            RegSNode * num = new RegSNode(); 
                                            char str[10];
                                            sprintf(str,"%d",1);
                                            num->name = new std::string (str);
                                            DoubleONode *operand = new DoubleONode((RegNode*)(yyvsp[(2) - (2)].regnode),(RegNode*)num); 
                                            (yyval.node) = new AddInsNode((DoubleONode*)operand); 
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        }  
                                    ;}
    break;

  case 111:
#line 891 "config/parser.y"
    {
                                        if(error_flag == 0)
                                        {   
                                            RegSNode * num = new RegSNode(); 
                                            char str[10];
                                            sprintf(str,"%d",1);
                                            num->name = new std::string (str);
                                            DoubleONode *operand = new DoubleONode((RegNode*)(yyvsp[(2) - (2)].regnode),(RegNode*)num); 
                                            (yyval.node) = new AddInsNode((DoubleONode*)operand); 
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        }  
                                    ;}
    break;

  case 112:
#line 905 "config/parser.y"
    {
                                        if(error_flag == 0)
                                        {   
                                            (yyval.node) = new SubInsNode((DoubleONode*)(yyvsp[(2) - (2)].node)); 
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        }  
                                    ;}
    break;

  case 113:
#line 913 "config/parser.y"
    {
                                        if(error_flag == 0)
                                        {   
                                            (yyval.node) = new SubInsNode((DoubleONode*)(yyvsp[(2) - (2)].node)); 
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        }  
                                    ;}
    break;

  case 114:
#line 921 "config/parser.y"
    {
                                        if(error_flag == 0)
                                        {   
                                            RegSNode * num = new RegSNode(); 
                                            char str[10];
                                            sprintf(str,"%d",1);
                                            num->name = new std::string (str);
                                            DoubleONode *operand = new DoubleONode((RegNode*)(yyvsp[(2) - (2)].regnode),(RegNode*)num); 
                                            (yyval.node) = new SubInsNode((DoubleONode*)operand); 
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        }  
                                    ;}
    break;

  case 115:
#line 934 "config/parser.y"
    {
                                        if(error_flag == 0)
                                        {   
                                            RegSNode * num = new RegSNode(); 
                                            char str[10];
                                            sprintf(str,"%d",1);
                                            num->name = new std::string (str);
                                            DoubleONode *operand = new DoubleONode((RegNode*)(yyvsp[(2) - (2)].regnode),(RegNode*)num); 
                                            (yyval.node) = new SubInsNode((DoubleONode*)operand); 
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        }  
                                    ;}
    break;

  case 116:
#line 947 "config/parser.y"
    {
                                        if(error_flag == 0)
                                        {   
                                            RegSNode * num = new RegSNode(); 
                                            char str[10];
                                            sprintf(str,"%d",1);
                                            num->name = new std::string (str);
                                            DoubleONode *operand = new DoubleONode((RegNode*)(yyvsp[(2) - (2)].regnode),(RegNode*)num); 
                                            (yyval.node) = new SubInsNode((DoubleONode*)operand); 
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        }  
                                    ;}
    break;

  case 117:
#line 962 "config/parser.y"
    {
                                                        if(error_flag == 0)
                                                        {   
                                                            (yyval.node) = new MulInsNode(global->ax->h,global->ax->l,global->ax->l,(yyvsp[(2) - (2)].regnode)); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }  
                                                    ;}
    break;

  case 118:
#line 970 "config/parser.y"
    {
                                                        if(error_flag == 0)
                                                        {   
                                                            (yyval.node) = new MulInsNode(global->dx,global->ax,global->ax,(yyvsp[(2) - (2)].regnode)); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }  
                                                    ;}
    break;

  case 119:
#line 978 "config/parser.y"
    {
                                                        warning("%s:%3d.(%2d) Mem length missing,do you mean 'word ptr' or 'byte ptr'?\n",infile_name,(yyloc).first_line,(yylsp[(1) - (2)]).last_column+1);
                                                        show_line((yyloc).first_line,infile_name);
                                                        print_blank((yylsp[(1) - (2)]).last_column+1);
                                                        if(error_flag == 0)
                                                        {   
                                                            (yyval.node) = new MulInsNode(global->ax->h,global->ax->l,global->ax->l,(yyvsp[(2) - (2)].regnode)); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }  
                                                    ;}
    break;

  case 120:
#line 989 "config/parser.y"
    {
                                                        if(error_flag == 0)
                                                        {   
                                                            (yyval.node) = new MulInsNode(global->dx,global->ax,global->ax,(yyvsp[(4) - (4)].regnode)); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }  
                                                    ;}
    break;

  case 121:
#line 997 "config/parser.y"
    {
                                                        if(error_flag == 0)
                                                        {   
                                                            (yyval.node) = new MulInsNode(global->ax->h,global->ax->l,global->ax->l,(yyvsp[(4) - (4)].regnode)); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }  
                                                    ;}
    break;

  case 122:
#line 1007 "config/parser.y"
    {
                                                        if(error_flag == 0)
                                                        {   
                                                            (yyval.node) = new DivInsNode(global->ax->h,global->ax->l,global->ax->h,global->ax->l,(yyvsp[(2) - (2)].regnode)); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }  
                                                    ;}
    break;

  case 123:
#line 1015 "config/parser.y"
    {
                                                        if(error_flag == 0)
                                                        {   
                                                            (yyval.node) = new DivInsNode(global->dx,global->ax,global->dx,global->ax,(yyvsp[(2) - (2)].regnode)); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }  
                                                    ;}
    break;

  case 124:
#line 1023 "config/parser.y"
    {
                                                        warning("%s:%3d.(%2d) Mem length missing,do you mean 'word ptr' or 'byte ptr'?\n",infile_name,(yyloc).first_line,(yylsp[(1) - (2)]).last_column+1);
                                                        show_line((yyloc).first_line,infile_name);
                                                        print_blank((yylsp[(1) - (2)]).last_column+1);
                                                        if(error_flag == 0)
                                                        {   
                                                            (yyval.node) = new DivInsNode(global->ax->h,global->ax->l,global->ax->h,global->ax->l,(yyvsp[(2) - (2)].regnode)); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }  
                                                    ;}
    break;

  case 125:
#line 1034 "config/parser.y"
    {
                                                        if(error_flag == 0)
                                                        {   
                                                            (yyval.node) = new DivInsNode(global->dx,global->ax,global->dx,global->ax,(yyvsp[(4) - (4)].regnode)); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }  
                                                    ;}
    break;

  case 126:
#line 1042 "config/parser.y"
    {
                                                        if(error_flag == 0)
                                                        {   
                                                            (yyval.node) = new DivInsNode(global->ax->h,global->ax->l,global->ax->h,global->ax->l,(yyvsp[(4) - (4)].regnode)); 
                                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                            all_node.push_back((Node*)(yyval.node));
                                                        }  
                                                    ;}
    break;

  case 127:
#line 1052 "config/parser.y"
    {
                                        if(error_flag == 0)
                                        {   
                                            (yyval.node) = new CallInsNode((yyvsp[(2) - (2)].var)); 
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        }   
                                        if(global->GetLabelLine((yyvsp[(2) - (2)].var)) == 0){
                                            error("%s:%3d.(%2d)This label isn't defined : %s\n",infile_name,(yyloc).first_line,(yylsp[(2) - (2)]).first_column,(yyvsp[(2) - (2)].var)->c_str());
                                            show_line((yyloc).first_line,infile_name);
                                            print_blank((yylsp[(2) - (2)]).first_column);
                                            root = NULL;
                                            error_flag =1;
                                        }
                                    ;}
    break;

  case 128:
#line 1069 "config/parser.y"
    {
                                        if(error_flag == 0)
                                        {   
                                            (yyval.node) = new PushInsNode((yyvsp[(2) - (2)].regnode)); 
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        }  
                                    ;}
    break;

  case 129:
#line 1077 "config/parser.y"
    {
                                        if(error_flag == 0)
                                        {   
                                            (yyval.node) = new PushInsNode((yyvsp[(2) - (2)].regnode));
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        }  
                                    ;}
    break;

  case 130:
#line 1087 "config/parser.y"
    {
                                        if(error_flag == 0)
                                        {   
                                            (yyval.node) = new PopInsNode((yyvsp[(2) - (2)].regnode)); 
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        }  
                                    ;}
    break;

  case 131:
#line 1095 "config/parser.y"
    {
                                        if(error_flag == 0)
                                        {   
                                            (yyval.node) = new PopInsNode((yyvsp[(2) - (2)].regnode)); 
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        }  
                                    ;}
    break;

  case 132:
#line 1104 "config/parser.y"
    {
                                        if(error_flag == 0)
                                        {   
                                            (yyval.node) = new RetInsNode();
                                            (yyval.node)->setLoc((Loc*)&((yyloc)));
                                            all_node.push_back((Node*)(yyval.node));
                                        }  
                                    ;}
    break;

  case 133:
#line 1113 "config/parser.y"
    { global->SetLabelLine((yyvsp[(1) - (2)].var),(yylsp[(1) - (2)]).first_line);;}
    break;

  case 134:
#line 1114 "config/parser.y"
    {
                                            line("Line:%-4d",(yyloc).first_line);
                                            debug ("Block ::= %s : BlockItem\n",(yyvsp[(1) - (4)].var)->c_str());
                                            if(error_flag == 0)
                                            {   
                                                (yyval.node) = new BlockNode((yyvsp[(1) - (4)].var),(BlockItemNode *)(yyvsp[(4) - (4)].node)); 
                                                (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                all_node.push_back((Node*)(yyval.node));
                                            }      
                                            
                                        ;}
    break;

  case 135:
#line 1125 "config/parser.y"
    {
                                            line("Line:%-4d",(yyloc).first_line);
                                            debug ("Block ::= %s : \n",(yyvsp[(1) - (2)].var)->c_str()); 
                                            if(error_flag == 0)
                                            {   
                                                (yyval.node) = new BlockNode((yyvsp[(1) - (2)].var),NULL); 
                                                (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                all_node.push_back((Node*)(yyval.node));
                                            }     
                                            global->SetLabelLine((yyvsp[(1) - (2)].var),(yylsp[(1) - (2)]).first_line);
                                        ;}
    break;

  case 136:
#line 1138 "config/parser.y"
    {
                                                                    line("Line:%-4d",(yyloc).first_line);
                                                                    debug ("BlockItem ::= Instruction\n");   
                                                                    if(error_flag == 0)
                                                                    {   
                                                                        (yyval.node) = new BlockItemNode(); 
                                                                        ((BlockItemNode*)(yyval.node))->append((InstructionNode*)(yyvsp[(1) - (1)].node));
                                                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                                        all_node.push_back((Node*)(yyval.node));
                                                                    }   
                                                                ;}
    break;

  case 137:
#line 1149 "config/parser.y"
    {
                                                                    line("Line:%-4d",(yyloc).first_line);
                                                                    debug ("BlockItem ::= BlockItem Instruction\n");  
                                                                    if(error_flag == 0)
                                                                    {   
                                                                        ((BlockItemNode*)(yyval.node))->append((InstructionNode*)(yyvsp[(2) - (2)].node));
                                                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                                        all_node.push_back((Node*)(yyval.node));
                                                                    }  
                                                                ;}
    break;

  case 138:
#line 1161 "config/parser.y"
    {
                                                                    line("Line:%-4d",(yyloc).first_line);
                                                                    debug ("Macro ::= var macro exp \n\t\t  BlockItem \n \t\t  endm\n");  
                                                                    if(error_flag == 0)
                                                                    {   
                                                                        (yyval.node) = new MacroNode((yyvsp[(1) - (5)].var),(BlockItemNode*)(yyvsp[(4) - (5)].node)); 
                                                                        (yyval.node)->setLoc((Loc*)&((yyloc)));
                                                                        all_node.push_back((Node*)(yyval.node));
                                                                    }   
                                                                ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3301 "src/parser.cc"
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


#line 1179 "config/parser.y"



void yyerror (const char *msg)
{
    error ("%s\n", msg);
}

