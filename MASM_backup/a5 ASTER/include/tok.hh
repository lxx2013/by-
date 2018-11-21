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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 39 "config/parser.y"
{
    int  num;
    std::string *var;
    Node *node;
    RegNode * regnode;
}
/* Line 1529 of yacc.c.  */
#line 180 "include/tok.hh"
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
