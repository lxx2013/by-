%{
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
%}

%union
{
    int  num;
    std::string *var;
    Node *node;
}

%token err_tok var_tok num_tok assume_tok segment_tok ends_tok macro_tok 
%token cs_tok ss_tok ds_tok db_tok dd_tok dw_tok string_tok dup_tok
%token ret_tok

%type <num> num_tok
%type <var> string_tok
%type <node> input CompUnit Assume Segment Macro Block Function Alloca AllocaLine
%locations

%%
input : /*empty*/       {   
                            error_flag = 0;
                            error_debug_flag = 0;                           
                            line("Line:%-3d",1);
                            debug ("input ::= empty\n"); 
                        }
      | input CompUnit  {
                            line("Line:%-3d",@2.first_line);
                            debug ("input ::= CompUnit\n"); 
                        } 
      ;
CompUnit    :   Assume  {
                            line("Line:%-3d",@1.first_line);
                            debug ("CompUnit ::= Assume\n");
                            $$ = $1; 
                        }
            |   Segment {
                            line("Line:%-3d",@1.first_line);
                            debug ("CompUnit ::= Segment\n");
                            $$ = $1; 
                        }
            ;
Assume      :   assume_tok cs_tok ':' var_tok   {
                                                    line("Line:%-3d",@3.first_line);
                                                    debug ("Assume ::= assume cs:var\n");
                                                }
            |   assume_tok ds_tok ':' var_tok   {
                                                    line("Line:%-3d",@3.first_line);
                                                    debug ("Assume ::= assume ds:var\n");                
                                                }
            |   assume_tok ss_tok ':' var_tok   {
                                                    line("Line:%-3d",@3.first_line);
                                                    debug ("Assume ::= assume ss:var\n");                
                                                }                                    
            |   Assume ',' cs_tok ':' var_tok   {
                                                    line("Line:%-3d",@2.first_line);
                                                    debug ("Assume ::= Assume , cs:var\n");                
                                                }
            |   Assume ',' ds_tok ':' var_tok   {
                                                    line("Line:%-3d",@2.first_line);
                                                    debug ("Assume ::= Assume , ds:var\n");                
                                                }
            |   Assume ',' ss_tok ':' var_tok   {
                                                    line("Line:%-3d",@2.first_line);
                                                    debug ("Assume ::= Assume , ss:var\n");               
                                                }
            ;

Segment     : var_tok segment_tok Alloca var_tok ends_tok
            | var_tok segment_tok Content var_tok ends_tok
            ;

Content     : Block
            | Macro
            | Function
            | Content Block
            | Content Macro
            | Content Function
            ;

Alloca      : AllocaLine                            {
                                                        line("Line:%-3d",@$.first_line);
                                                        debug ("Alloca ::= AllocaString\n");   
                                                    }
            | Alloca AllocaLine                     {
                                                        line("Line:%-3d",@2.first_line);
                                                        debug ("Alloca ::= Alloca AllocaString\n");   
                                                    }
            ;
AllocaLine  : var_tok db_tok AllocaExpH
            | var_tok dw_tok AllocaExpH             
            | var_tok dd_tok AllocaExpH
            ;

AllocaExpH  : AllocaExp
            | AllocaExpH ',' AllocaExp
            ;

AllocaExp   : string_tok
            | num_tok
            | num_tok dup_tok '(' num_tok ')'
            ;

Block       : var_tok ':'
            ;
Macro       : macro_tok
            ;
Function    : ret_tok
            ;

%%


void yyerror (const char *msg)
{
    error ("%s\n", msg);
}
