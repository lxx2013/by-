%{
#include <string>
#include "node.hh"
#include "string.h"
#include "tok.hh"
#define DEBUG
#include "util.hh"
int yycolumn = 1;
int ano_flag = 0;    // 0 : common state; 1: '/*' state; 2: '//' state 
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; \
    yylloc.last_column = yycolumn + yyleng - 1; \
    yycolumn += yyleng;
%}

D       [0-9]
DHX     [0-9a-f][0-9a-f]*(h)
L       [a-zA-Z_]
AnoBegin         \/\*
AnoEnd           \*\/
StringD   \x22[^\x22]*\x22              
StringS   \x27[^\x27]*\x27             
%option noyywrap
%option yylineno

%%


{StringD}           {
                        if(ano_flag == 0)
                        {
                            yylval.var = new std::string (yytext);
                            debug("%s\n",yylval.var->c_str());
                            return string_tok;
                        }
                    }
{StringS}           {
                        if(ano_flag == 0)
                        {
                            yylval.var = new std::string (yytext);
                            debug("%s\n",yylval.var->c_str());
                            return string_tok;
                        }
                    }                    
"#".*               // comment
{AnoBegin}          {
                        ano_flag=1;
                    }
{AnoEnd}            {
                        ano_flag=0;
                    }
{D}+                {  
                        if(ano_flag ==0)
                        {   
                            yylval.num = atoi (yytext);
                            debug("return num_tok:%d\n",yylval.num);
                            return num_tok;
                        }
                    }
{DHX}               {  
                        if(ano_flag ==0)
                        {   
                            yylval.num = strtol (yytext,NULL,16);
                            debug("return num_tok:%d\n",yylval.num);
                            if(yytext[0] > '9')   //不是以数字开头的话就要报错
                            {
                                warning("%s:%3d.(%2d) Hex Number should begin with num, instead of 'a-f'\n",infile_name,yylineno,yycolumn);
                                show_line(yylineno,infile_name);
                                print_blank(yycolumn-yyleng);
                            }
                            return num_tok;
                        }
                    }                  
{L}({L}|{D})*       {
                        if(ano_flag==0)
                        {   
                            yylval.var = new std::string (yytext);
                            debug("%s\n",yylval.var->c_str());
    						if(strcmp(yylval.var->c_str(),"assume")==0)
    							return assume_tok;
                            else if(strcmp(yylval.var->c_str(),"segment")==0)
                                return segment_tok;
                            else if(strcmp(yylval.var->c_str(),"ends")==0)
                                return ends_tok;
                            else if(strcmp(yylval.var->c_str(),"macro")==0)
                                return macro_tok;
                            else if(strcmp(yylval.var->c_str(),"cs")==0)
                                return cs_tok;
                            else if(strcmp(yylval.var->c_str(),"ds")==0)
                                return ds_tok;
                            else if(strcmp(yylval.var->c_str(),"ss")==0)
                                return ss_tok;
                            else if(strcmp(yylval.var->c_str(),"db")==0)
                                return db_tok;
                            else if(strcmp(yylval.var->c_str(),"dw")==0)
                                return dw_tok;
                            else if(strcmp(yylval.var->c_str(),"dd")==0)
                                return dd_tok;
                            else if(strcmp(yylval.var->c_str(),"dup")==0)
                                return dup_tok;
                            else if(strcmp(yylval.var->c_str(),"ret")==0)
                                return ret_tok;
    						else
                            	return var_tok;
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
"("                 {   if(ano_flag ==0)
                        {   
                            return '(';
                        }
                    }
")"                 {   if(ano_flag ==0)
                        {   
                            return ')';
                        }
                    }

";"                 {   
                        if(ano_flag==0)
                        {   ano_flag=2;
                        }
                    }
","                 {   if(ano_flag ==0)
                        {   
                            return ',';
                        }
                    }
":"                 {   if(ano_flag ==0)
                        {   
                            return ':';
                        }
                    }
"?"                 {   if(ano_flag ==0)
                        {   
                            yylval.num = 0;
                            debug("return num_tok:%d\n",yylval.num);
                            return num_tok;
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
