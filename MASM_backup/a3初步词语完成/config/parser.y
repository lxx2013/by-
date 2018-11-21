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

%token err_tok var_tok num_tok assume_tok segment_tok ends_tok macro_tok endm_tok end_tok 
%token cs_tok ss_tok sp_tok ds_tok db_tok dd_tok dw_tok string_tok dup_tok code_tok data_tok stack_tok
%token ax_tok ah_tok al_tok bx_tok bh_tok bl_tok cx_tok ch_tok cl_tok dx_tok dh_tok dl_tok si_tok di_tok
%token ret_tok int_tok mov_tok offset_tok byte_tok word_tok ptr_tok cmp_tok call_tok push_tok pop_tok
%token add_tok sub_tok inc_tok dec_tok mul_tok div_tok
%token jmp_tok jle_tok jl_tok jge_tok jg_tok je_tok jne_tok loop_tok

%type <num> num_tok
%type <var> string_tok var_tok
%type <node> input CompUnit Assume Segment Macro Block Function Alloca AllocaLine
%locations

%%
input : /*empty*/       {   
                            error_flag = 0;
                            error_debug_flag = 0;                           
                            line("Line:%-4d",1);
                            debug ("input ::= empty\n"); 
                        }
      | input CompUnit  {
                            line("Line:%-4d",@2.first_line);
                            debug ("input ::= CompUnit\n"); 
                        } 
      ;
CompUnit    :   Assume  {
                            line("Line:%-4d",@1.first_line);
                            debug ("Assume ::= assume cs:code,ds:data,ss:stack\n");
                            line("Line:%-4d",@1.first_line);
                            debug ("CompUnit ::= Assume\n");
                            $$ = $1; 
                        }
            |   Segment {
                            line("Line:%-4d",@1.first_line);
                            debug ("CompUnit ::= Segment\n");
                            $$ = $1; 
                        }
            |   end_tok var_tok   {
                                        line("Line:%-4d",@1.first_line);
                                        debug ("CompUnit ::= end %s\n",$2->c_str());
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
                                                                    line("Line:%-4d",@$.first_line);
                                                                    debug ("Segment ::= data Segment\n");   
                                                                }
            | stack_tok segment_tok Alloca stack_tok ends_tok   {
                                                                    line("Line:%-4d",@$.first_line);
                                                                    debug ("Segment ::= stack Segment\n");   
                                                                }
            | code_tok segment_tok Content code_tok ends_tok    {
                                                                    line("Line:%-4d",@$.first_line);
                                                                    debug ("Segment ::= code Segment\n");   
                                                                }
            ;

Content     : Block                 {
                                        line("Line:%-4d",@$.first_line);
                                        debug ("Content ::= Block\n");   
                                    }
            | Macro                 {
                                        line("Line:%-4d",@$.first_line);
                                        debug ("Content ::= Macro\n");   
                                    }
            | Function              {
                                        line("Line:%-4d",@$.first_line);
                                        debug ("Content ::= Function\n");   
                                    }
            | Content Block         {
                                        line("Line:%-4d",@$.first_line);
                                        debug ("Content ::= Content Block\n");   
                                    }
            | Content Macro         {
                                        line("Line:%-4d",@$.first_line);
                                        debug ("Content ::= Content Macro\n");   
                                    }
            | Content Function      {
                                        line("Line:%-4d",@$.first_line);
                                        debug ("Content ::= Content Function\n");   
                                    }
            ;

Alloca      : AllocaLine                            {
                                                        line("Line:%-4d",@$.first_line);
                                                        debug ("Alloca ::= AllocaLine\n");   
                                                    }
            | Alloca AllocaLine                     {
                                                        line("Line:%-4d",@2.first_line);
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
            | offset_tok var_tok
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
MemAddr     : var_tok
            | data_tok
            | stack_tok
            | code_tok
            | MemAddrExp    {
                                line("Line:%-4d",@$.first_line);
                                debug ("MemAddr ::= MemAddrExp\n");   
                            }
            ;
MemAddrExp  : '[' MemAddrExp_a ']'
            | '[' MemAddrExp_a '+' MemAddrExp_a ']'
            | '[' MemAddrExp_a num_tok ']'          {
                                                        line("Line:%-4d",@$.first_line);
                                                        if($3 >= 0)
                                                        {
                                                            debug ("MemAddrExp ::= '[' MemAddrExp_a + num_tok ']'\n");
                                                        }
                                                        else
                                                        {
                                                            debug ("MemAddrExp ::= '[' MemAddrExp_a - num_tok ']'\n");
                                                        }   
                                                    }
            | '[' MemAddrExp_a '+' MemAddrExp_a num_tok']'
            ;
MemAddrExp_a    : ax_tok
                | bx_tok
                | si_tok
                | di_tok
                ;



DoubleOE    : RegE ',' RegE
            | RegE ',' num_tok
            | RegE ',' MemAddr
            | MemAddr ',' RegE
            | MemAddr ',' num_tok
            | byte_tok ptr_tok MemAddr ',' MemAddr
            ;
DoubleOS    : RegS ',' RegS
            | RegS ',' num_tok
            | RegS ',' MemAddr
            | MemAddr ',' RegS
            | word_tok ptr_tok MemAddr ',' MemAddr
            ;
Instruction : Int_ins           {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Int_ins\n");   
                                }
            | Mov_ins           {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Mov_ins\n");   
                                }
            | Cmp_ins           {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Cmp_ins\n");   
                                }
            | Jmp_ins           {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Jmp_ins\n");   
                                }
            | Add_ins           {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Add_ins\n");   
                                }
            | Sub_ins           {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Sub_ins\n");   
                                }
            | Mul_ins           {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Mul_ins\n");   
                                }
            | Div_ins           {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Div_ins\n");   
                                }
            | Call_ins          {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Call_ins\n");   
                                }
            | Push_ins          {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Push_ins\n");   
                                }
            | Pop_ins          {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Pop_ins\n");   
                                }
            | Block             {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Block\n");   
                                }
            ;

Int_ins     : int_tok num_tok
            ;

Mov_ins     : mov_tok DoubleOE
            | mov_tok DoubleOS
            | mov_tok MemAddr ',' MemAddr
            ;

Cmp_ins     : cmp_tok DoubleOE
            | cmp_tok DoubleOS
            ;

Jmp_ins     : jmp_tok var_tok
            | jle_tok var_tok
            | jl_tok var_tok
            | jge_tok var_tok
            | jg_tok var_tok
            | je_tok  var_tok
            | jne_tok var_tok
            | loop_tok var_tok
            ;

Add_ins     : add_tok DoubleOE
            | add_tok DoubleOS
            | inc_tok RegE
            | inc_tok RegS
            | inc_tok MemAddr
            ;
Sub_ins     : sub_tok DoubleOE
            | sub_tok DoubleOS
            | dec_tok RegE
            | dec_tok RegS
            | dec_tok MemAddr
            ;

Mul_ins     : mul_tok RegE
            | mul_tok RegS
            | mul_tok word_tok ptr_tok MemAddr
            | mul_tok byte_tok ptr_tok MemAddr
            ;

Div_ins     : div_tok RegE
            | div_tok RegS
            | div_tok word_tok ptr_tok MemAddr
            | div_tok byte_tok ptr_tok MemAddr
            ;

Call_ins    : call_tok var_tok
            ;

Push_ins    : push_tok RegE
            | push_tok RegS
            ;

Pop_ins     : pop_tok RegE
            | pop_tok RegS
            ;

Block       : var_tok ':' BlockItem     {
                                            line("Line:%-4d",@$.first_line);
                                            debug ("Block ::= %s : BlockItem\n",$1->c_str());   
                                        }
            | var_tok ':'               {
                                            line("Line:%-4d",@$.first_line);
                                            debug ("Block ::= %s : \n",$1->c_str());   
                                        }
            ;

BlockItem   : Instruction                                       {
                                                                    line("Line:%-4d",@$.first_line);
                                                                    debug ("BlockItem ::= Instruction\n");   
                                                                }
            | BlockItem Instruction                             {
                                                                    line("Line:%-4d",@$.first_line);
                                                                    debug ("BlockItem ::= BlockItem Instruction\n");   
                                                                }
            ;

Macro       : var_tok macro_tok  MacroExp BlockItem endm_tok    {
                                                                    line("Line:%-4d",@$.first_line);
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
