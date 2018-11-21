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

%token err_tok var_tok num_tok assume_tok segment_tok ends_tok macro_tok endm_tok
%token cs_tok ss_tok sp_tok ds_tok db_tok dd_tok dw_tok string_tok dup_tok code_tok data_tok stack_tok
%token ax_tok ah_tok al_tok bx_tok bh_tok bl_tok cx_tok ch_tok cl_tok dx_tok dh_tok dl_tok si_tok di_tok
%token ret_tok int_tok mov_tok

%type <num> num_tok
%type <var> string_tok var_tok
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
                            debug ("Assume ::= assume cs:code,ds:data,ss:stack\n");
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

Assume      :   assume_tok cs_tok ':' code_tok  
            |   assume_tok ds_tok ':' data_tok   
            |   assume_tok ss_tok ':' stack_tok                                    
            |   Assume ',' cs_tok ':' code_tok  
            |   Assume ',' ds_tok ':' data_tok   
            |   Assume ',' ss_tok ':' stack_tok   
            ;

Segment     : data_tok segment_tok Alloca data_tok ends_tok     {
                                                                    line("Line:%-3d",@$.first_line);
                                                                    debug ("Segment ::= data Segment\n");   
                                                                }
            | stack_tok segment_tok Alloca stack_tok ends_tok   {
                                                                    line("Line:%-3d",@$.first_line);
                                                                    debug ("Segment ::= stack Segment\n");   
                                                                }
            | code_tok segment_tok Content code_tok ends_tok    {
                                                                    line("Line:%-3d",@$.first_line);
                                                                    debug ("Segment ::= code Segment\n");   
                                                                }
            ;

Content     : Block                 {
                                        line("Line:%-3d",@$.first_line);
                                        debug ("Content ::= Block\n");   
                                    }
            | Macro                 {
                                        line("Line:%-3d",@$.first_line);
                                        debug ("Content ::= Macro\n");   
                                    }
            | Function              {
                                        line("Line:%-3d",@$.first_line);
                                        debug ("Content ::= Function\n");   
                                    }
            | Content Block         {
                                        line("Line:%-3d",@$.first_line);
                                        debug ("Content ::= Content Block\n");   
                                    }
            | Content Macro         {
                                        line("Line:%-3d",@$.first_line);
                                        debug ("Content ::= Content Macro\n");   
                                    }
            | Content Function      {
                                        line("Line:%-3d",@$.first_line);
                                        debug ("Content ::= Content Function\n");   
                                    }
            ;

Alloca      : AllocaLine                            {
                                                        line("Line:%-3d",@$.first_line);
                                                        debug ("Alloca ::= AllocaLine\n");   
                                                    }
            | Alloca AllocaLine                     {
                                                        line("Line:%-3d",@2.first_line);
                                                        debug ("Alloca ::= Alloca AllocaLine\n");   
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

RegS        : ax_tok
            | bx_tok
            | cx_tok
            | dx_tok
            | si_tok
            | di_tok
            | ds_tok
            | ss_tok
            | sp_tok
            ;

RegE        : ah_tok
            | al_tok
            | bh_tok
            | bl_tok
            | ch_tok
            | cl_tok
            | dh_tok
            | dl_tok
            ;

Instruction : Int_ins           {
                                    line("Line:%-3d",@$.first_line);
                                    debug ("Instruction ::= Int_ins\n");   
                                }
            | Mov_ins           {
                                    line("Line:%-3d",@$.first_line);
                                    debug ("Instruction ::= Mov_ins\n");   
                                }
            | Block             {
                                    line("Line:%-3d",@$.first_line);
                                    debug ("Instruction ::= Block\n");   
                                }
            ;

Int_ins     : int_tok num_tok
            ;

Mov_ins     : mov_tok RegE ',' RegE
            | mov_tok RegS ',' RegS
            | mov_tok RegE ',' num_tok
            | mov_tok RegS ',' num_tok
            | mov_tok RegE ',' var_tok
            | mov_tok RegS ',' var_tok
            | mov_tok var_tok ',' var_tok
            ;

Block       : var_tok ':' BlockItem     {
                                            line("Line:%-3d",@$.first_line);
                                            debug ("Block ::= %s : BlockItem\n",$1->c_str());   
                                        }
            | var_tok ':'               {
                                            line("Line:%-3d",@$.first_line);
                                            debug ("Block ::= %s : \n",$1->c_str());   
                                        }
            ;

BlockItem   : Instruction                                       {
                                                                    line("Line:%-3d",@$.first_line);
                                                                    debug ("BlockItem ::= Instruction\n");   
                                                                }
            | BlockItem Instruction                             {
                                                                    line("Line:%-3d",@$.first_line);
                                                                    debug ("BlockItem ::= BlockItem Instruction\n");   
                                                                }
            ;

Macro       : var_tok macro_tok  MacroExp BlockItem endm_tok    {
                                                                    line("Line:%-3d",@$.first_line);
                                                                    debug ("Macro ::= var macro exp \n\t\t  BlockItem \n \t\t  endm\n");   
                                                                }
            ;

MacroExp    : var_tok
            | MacroExp ',' var_tok
            ;

Function    : ret_tok
            ;

%%


void yyerror (const char *msg)
{
    error ("%s\n", msg);
}
