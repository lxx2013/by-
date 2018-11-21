%{
#include <string>
#include "node.hh"
#include "string.h"
#include "tok.hh"
int yycolumn = 1;
int ano_flag = 0;    // 0 : common state; 1: '/*' state; 2: '//' state 
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; \
    yylloc.last_column = yycolumn + yyleng - 1; \
    yycolumn += yyleng;
%}

D       [0-9]
L       [a-zA-Z_]
RelOp           (<|>|<=|>=|==|!=)
Annotation       \/\/
AnoBegin         \/\*
AnoEnd           \*\/
%option noyywrap
%option yylineno

%%

"#".*               // comment
{AnoBegin}          {
                        ano_flag=1;
                    }
{AnoEnd}            {
                        ano_flag=0;
                    }
{Annotation}        {   if(ano_flag==0)
                        {   ano_flag=2;
                        }
                    }
{D}+                {  
                        if(ano_flag ==0)
                        {   
                            yylval.num = atoi (yytext);
                            return num_tok;
                        }
                    }
                    
{L}({L}|{D})*       {
                        if(ano_flag==0)
                        {   
                            yylval.var = new std::string (yytext);
    						if(strcmp(yylval.var->c_str(),"int")==0)
    							return int_tok;
    						else if(strcmp(yylval.var->c_str(),"const")==0)
    							return const_tok;
                            else if(strcmp(yylval.var->c_str(),"void")==0)
                                return void_tok;
                            else if(strcmp(yylval.var->c_str(),"if")==0)
                                return if_tok;
                            else if(strcmp(yylval.var->c_str(),"else")==0)
                                return else_tok;
                            else if(strcmp(yylval.var->c_str(),"while")==0)
                                return while_tok;
    						else
                            	return var_tok;
                        }
                    }

{RelOp}             {
                        if(ano_flag==0)
                        {
                            yylval.var = new std::string (yytext);
                            return RelOp;
                        }
                    }
"="                 {   if(ano_flag ==0)
                        {   
                            return '=';
                        }
                    }
"+"                 {   if(ano_flag ==0)
                        {   
                            return '+';
                        }
                    }
"-"                 {   if(ano_flag ==0)
                        {   
                            return '-';
                        }
                    }
"*"                 {   if(ano_flag ==0)
                        {   
                            return '*';
                        }
                    }
"%"					{   if(ano_flag ==0)
                        {   
                            return '%';
                        }
                    }
"/"                 {   if(ano_flag ==0)
                        {   
                            return '/';
                        }
                    }

"("                 {   if(ano_flag ==0)
                        {   
                            return '(';
                        }
                    }
"["                 {   if(ano_flag ==0)
                        {   
                            return '[';
                        }
                    }
"]"                 {   if(ano_flag ==0)
                        {   
                            return ']';
                        }
                    }
"{"                 {   if(ano_flag ==0)
                        {   
                            return '{';
                        }
                    }
"}"                 {   if(ano_flag ==0)
                        {   
                            return '}';
                        }
                    }
")"                 {   if(ano_flag ==0)
                        {   
                            return ')';
                        }
                    }
";"                 {   if(ano_flag ==0)
                        {   
                            return ';';
                        }
                    }
","                 {   if(ano_flag ==0)
                        {   
                            return ',';
                        }
                    }
\n                  {   if(ano_flag == 2)
                        {   yycolumn=1;
                            ano_flag=0;}
                        else 
                            yycolumn=1;
                    }
\t                  {yycolumn+=3;}
[ ]
.                   {if(ano_flag == 0)
                        return err_tok;}


%%
