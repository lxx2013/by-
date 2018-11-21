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

D       [\+\-]?[0-9]+
DHX     [\+\-]?[0-9a-f][0-9a-f]*(h)
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
{D}                 {  
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
                            yylval.var = new std::string (yytext);
                            if(strcmp(yylval.var->c_str(),"ah")==0)
                                return ah_tok;
                            else if(strcmp(yylval.var->c_str(),"bh")==0)
                                return bh_tok;
                            else if(strcmp(yylval.var->c_str(),"ch")==0)
                                return ch_tok;
                            else if(strcmp(yylval.var->c_str(),"dh")==0)
                                return dh_tok;
                            yylval.num = strtol (yytext,NULL,16);
                            debug("return num_tok:%d\n",yylval.num);
                            if(yytext[0] == '+' || yytext[0] == '-')
                            {
                                if(yytext[1] > '9')   //不是以数字开头的话就要报错
                                {
                                    warning("%s:%3d.(%2d) Hex Number should begin with '0-9', instead of 'a-f'\n",infile_name,yylineno,yycolumn);
                                    show_line(yylineno,infile_name);
                                    print_blank(yycolumn-yyleng+1);
                                }
                            }
                            else{
                                if(yytext[0] > '9')   //不是以数字开头的话就要报错
                                {
                                    warning("%s:%3d.(%2d) Hex Number should begin with '0-9', instead of 'a-f'\n",infile_name,yylineno,yycolumn);
                                    show_line(yylineno,infile_name);
                                    print_blank(yycolumn-yyleng);
                                }
                            }
                            return num_tok;
                        }
                    }                  
{L}({L}|[0-9])*       {
                        if(ano_flag==0)
                        {   
                            yylval.var = new std::string (yytext);
                            debug("%s\n",yylval.var->c_str());
                            if(strcmp(yylval.var->c_str(),"assume")==0)
                                return assume_tok;
                            else if(strcmp(yylval.var->c_str(),"segment")==0)
                                return segment_tok;
                            else if(strcmp(yylval.var->c_str(),"code")==0)
                                return code_tok;
                            else if(strcmp(yylval.var->c_str(),"data")==0)
                                return data_tok;
                            else if(strcmp(yylval.var->c_str(),"stack")==0)
                                return stack_tok;
                            else if(strcmp(yylval.var->c_str(),"ends")==0)
                                return ends_tok;
                            else if(strcmp(yylval.var->c_str(),"macro")==0)
                                return macro_tok;
                            else if(strcmp(yylval.var->c_str(),"endm")==0)
                                return endm_tok;
                            else if(strcmp(yylval.var->c_str(),"end")==0)
                                return end_tok;
                            else if(strcmp(yylval.var->c_str(),"ax")==0)
                                return ax_tok;
                            else if(strcmp(yylval.var->c_str(),"ah")==0)
                                return ah_tok;
                            else if(strcmp(yylval.var->c_str(),"al")==0)
                                return al_tok;
                            else if(strcmp(yylval.var->c_str(),"bx")==0)
                                return bx_tok;
                            else if(strcmp(yylval.var->c_str(),"bh")==0)
                                return bh_tok;
                            else if(strcmp(yylval.var->c_str(),"bl")==0)
                                return bl_tok;
                            else if(strcmp(yylval.var->c_str(),"cx")==0)
                                return cx_tok;
                            else if(strcmp(yylval.var->c_str(),"ch")==0)
                                return ch_tok;
                            else if(strcmp(yylval.var->c_str(),"cl")==0)
                                return cl_tok;
                            else if(strcmp(yylval.var->c_str(),"dx")==0)
                                return dx_tok;
                            else if(strcmp(yylval.var->c_str(),"dh")==0)
                                return dh_tok;
                            else if(strcmp(yylval.var->c_str(),"dl")==0)
                                return dl_tok;
                            else if(strcmp(yylval.var->c_str(),"si")==0)
                                return si_tok;
                            else if(strcmp(yylval.var->c_str(),"di")==0)
                                return di_tok;
                            else if(strcmp(yylval.var->c_str(),"cs")==0)
                                return cs_tok;
                            else if(strcmp(yylval.var->c_str(),"ds")==0)
                                return ds_tok;
                            else if(strcmp(yylval.var->c_str(),"ss")==0)
                                return ss_tok;
                            else if(strcmp(yylval.var->c_str(),"sp")==0)
                                return sp_tok;
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
                            else if(strcmp(yylval.var->c_str(),"int")==0)
                                return int_tok;
                            else if(strcmp(yylval.var->c_str(),"mov")==0)
                                return mov_tok;
                            else if(strcmp(yylval.var->c_str(),"offset")==0)
                                return offset_tok;
                            else if(strcmp(yylval.var->c_str(),"ptr")==0)
                                return ptr_tok;
                            else if(strcmp(yylval.var->c_str(),"word")==0)
                                return word_tok;
                            else if(strcmp(yylval.var->c_str(),"byte")==0)
                                return byte_tok;
                            else if(strcmp(yylval.var->c_str(),"cmp")==0)
                                return cmp_tok;
                            else if(strcmp(yylval.var->c_str(),"jmp")==0)
                                return jmp_tok;
                            else if(strcmp(yylval.var->c_str(),"loop")==0)
                                return loop_tok;
                            else if(strcmp(yylval.var->c_str(),"jl")==0)
                                return jl_tok;
                            else if(strcmp(yylval.var->c_str(),"jle")==0)
                                return jle_tok;
                            else if(strcmp(yylval.var->c_str(),"jg")==0)
                                return jg_tok;
                            else if(strcmp(yylval.var->c_str(),"jge")==0)
                                return jge_tok;
                            else if(strcmp(yylval.var->c_str(),"je")==0)
                                return je_tok;
                            else if(strcmp(yylval.var->c_str(),"jne")==0)
                                return jne_tok;
                            else if(strcmp(yylval.var->c_str(),"add")==0)
                                return add_tok;
                            else if(strcmp(yylval.var->c_str(),"sub")==0)
                                return sub_tok;
                            else if(strcmp(yylval.var->c_str(),"inc")==0)
                                return inc_tok;
                            else if(strcmp(yylval.var->c_str(),"dec")==0)
                                return dec_tok;
                            else if(strcmp(yylval.var->c_str(),"mul")==0)
                                return mul_tok;
                            else if(strcmp(yylval.var->c_str(),"div")==0)
                                return div_tok;
                            else if(strcmp(yylval.var->c_str(),"call")==0)
                                return call_tok;
                            else if(strcmp(yylval.var->c_str(),"push")==0)
                                return push_tok;
                            else if(strcmp(yylval.var->c_str(),"pop")==0)
                                return pop_tok;
                            
                            else
                                return var_tok;
                        }
                    }


"+"                 {   if(ano_flag ==0)
                        {   
                            debug("+");
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
                            debug("[");
                            return '[';
                        }
                    }
"]"                 {   if(ano_flag ==0)
                        {   
                            debug("]\n");
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
