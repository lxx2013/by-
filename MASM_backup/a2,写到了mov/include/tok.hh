/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
     cs_tok = 266,
     ss_tok = 267,
     sp_tok = 268,
     ds_tok = 269,
     db_tok = 270,
     dd_tok = 271,
     dw_tok = 272,
     string_tok = 273,
     dup_tok = 274,
     code_tok = 275,
     data_tok = 276,
     stack_tok = 277,
     ax_tok = 278,
     ah_tok = 279,
     al_tok = 280,
     bx_tok = 281,
     bh_tok = 282,
     bl_tok = 283,
     cx_tok = 284,
     ch_tok = 285,
     cl_tok = 286,
     dx_tok = 287,
     dh_tok = 288,
     dl_tok = 289,
     si_tok = 290,
     di_tok = 291,
     ret_tok = 292,
     int_tok = 293,
     mov_tok = 294
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
#define cs_tok 266
#define ss_tok 267
#define sp_tok 268
#define ds_tok 269
#define db_tok 270
#define dd_tok 271
#define dw_tok 272
#define string_tok 273
#define dup_tok 274
#define code_tok 275
#define data_tok 276
#define stack_tok 277
#define ax_tok 278
#define ah_tok 279
#define al_tok 280
#define bx_tok 281
#define bh_tok 282
#define bl_tok 283
#define cx_tok 284
#define ch_tok 285
#define cl_tok 286
#define dx_tok 287
#define dh_tok 288
#define dl_tok 289
#define si_tok 290
#define di_tok 291
#define ret_tok 292
#define int_tok 293
#define mov_tok 294




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 38 "config/parser.y"
{
    int  num;
    std::string *var;
    Node *node;
}
/* Line 1529 of yacc.c.  */
#line 133 "include/tok.hh"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

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

extern YYLTYPE yylloc;
