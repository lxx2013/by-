%{
#include <string>
#include "node.hh"
#include "string.h"
#include "tok.hh"
int yycolumn = 1;
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; \
    yylloc.last_column = yycolumn + yyleng - 1; \
    yycolumn += yyleng;
%}

D       [0-9]
L       [a-zA-Z_]

%option noyywrap
%option yylineno

%%

"#".*               // comment
{D}+                {   yylval.num = atoi (yytext);
                        return num_tok;
                    }
{L}({L}|{D})*       {   yylval.var = new std::string (yytext);
						if(strcmp(yylval.var->c_str(),"int")==0)
							return int_tok;
						else if(strcmp(yylval.var->c_str(),"const")==0)
							return const_tok;
						else
                        	return var_tok;
                    }
"="                 return '=';
"+"                 return '+';
"-"                 return '-';
"*"                 return '*';
"%"					return '%';
"/"                 return '/';
"^"                 return '^';
"("                 return '(';
"["                 return '[';
"]"                 return ']';
"{"                 return '{';
"}"                 return '}';
")"                 return ')';
";"                 return ';';
","                 return ',';
\n                  {   yycolumn = 1;
                        return eol_tok;
                    }
[\t ]*
.                   return err_tok;

%%
