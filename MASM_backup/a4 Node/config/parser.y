%{
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
%}


%union
{
    int  num;
    std::string *var;
    Node *node;
    RegNode * regnode;
}

%token err_tok var_tok num_tok assume_tok segment_tok ends_tok macro_tok endm_tok end_tok 
%token cs_tok ss_tok sp_tok ds_tok db_tok dd_tok dw_tok string_tok dup_tok code_tok data_tok stack_tok
%token ax_tok ah_tok al_tok bx_tok bh_tok bl_tok cx_tok ch_tok cl_tok dx_tok dh_tok dl_tok si_tok di_tok
%token ret_tok int_tok mov_tok offset_tok byte_tok word_tok ptr_tok cmp_tok call_tok push_tok pop_tok
%token add_tok sub_tok inc_tok dec_tok mul_tok div_tok
%token jmp_tok jle_tok jl_tok jge_tok jg_tok je_tok jne_tok loop_tok

%type <num> num_tok AllocaExpH AllocaExp 
%type <var> string_tok var_tok data_tok stack_tok code_tok MemAddrExp_a 
%type <var> ax_tok ah_tok al_tok bx_tok bh_tok bl_tok cx_tok ch_tok cl_tok dx_tok dh_tok dl_tok
%type <node> input CompUnit  Segment Macro Block BlockItem Alloca AllocaLine Content Instruction
%type <node> Int_ins Mov_ins Add_ins Sub_ins Mul_ins Div_ins Ret_ins Push_ins Pop_ins Call_ins Cmp_ins Jmp_ins
%type <node> DoubleOE DoubleOS
%type <regnode> RegE RegS MemAddr
%locations

%%
input : /*empty*/       {   
                            error_flag = 0;
                            error_debug_flag = 0;                           
                            line("Line:%-4d",1);
                            debug ("input ::= empty\n"); 
                            root = new InputNode ();
                            global = new GlobalNode();
                            all_node.push_back((Node*)root);
                        }
      | input CompUnit  {
                            line("Line:%-4d",@2.first_line);
                            debug ("input ::= input CompUnit\n"); 
                            if ($2!=NULL)   // ignore empty line
                            {   
                                if(error_flag == 0)
                                    root->append ((CompUnitNode*)$2);
                            }
                        } 
      ;
CompUnit    :   Assume  {
                            line("Line:%-4d",@1.first_line);
                            debug ("Assume ::= assume cs:code,ds:data,ss:stack\n");
                            line("Line:%-4d",@1.first_line);
                            debug ("CompUnit ::= Assume\n");
                            if(error_flag == 0)
                            {   
                                $$ = new AssumeNode(); 
                                $$->setLoc((Loc*)&(@$));
                                all_node.push_back((Node*)$$);
                            }  
                        }
            |   Segment {
                            line("Line:%-4d",@1.first_line);
                            debug ("CompUnit ::= Segment\n");
                            $$ = $1; 
                        }
            |   end_tok var_tok     {
                                        line("Line:%-4d",@1.first_line);
                                        debug ("CompUnit ::= end %s\n",$2->c_str());
                                        $$ = NULL;
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
                                                                    $$ = $3;  
                                                                    global->SetMemLength($1,8);
                                                                }
            | stack_tok segment_tok Alloca stack_tok ends_tok   {
                                                                    line("Line:%-4d",@$.first_line);
                                                                    debug ("Segment ::= stack Segment\n"); 
                                                                    $$ = $3;   
                                                                    global->SetMemLength($1,8);
                                                                }
            | code_tok segment_tok Content code_tok ends_tok    {
                                                                    line("Line:%-4d",@$.first_line);
                                                                    debug ("Segment ::= code Segment\n");
                                                                    $$ = $3;
                                                                    global->SetMemLength($1,8);
                                                                }
            ;

Content     : Block                 {
                                        line("Line:%-4d",@$.first_line);
                                        debug ("Content ::= Block\n"); 
                                        if(error_flag == 0)
                                        {   
                                            $$ = new ContentNode(); 
                                            ((ContentNode*)$$)->appendB((BlockNode*)$1);
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        }       
                                    }
            | Macro                 {
                                        line("Line:%-4d",@$.first_line);
                                        debug ("Content ::= Macro\n");   
                                        if(error_flag == 0)
                                        {   
                                            $$ = new ContentNode(); 
                                            ((ContentNode*)$$)->appendM((MacroNode*)$1);
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        }   
                                    }
            | Content Block         {
                                        line("Line:%-4d",@$.first_line);
                                        debug ("Content ::= Content Block\n"); 
                                        if(error_flag == 0)
                                        {   
                                            ((ContentNode*)$$)->appendB((BlockNode*)$2);
                                            $$->setLoc((Loc*)&(@$));
                                        }    
                                    }
            | Content Macro         {
                                        line("Line:%-4d",@$.first_line);
                                        debug ("Content ::= Content Macro\n");  
                                        if(error_flag == 0)
                                        {   
                                            ((ContentNode*)$$)->appendM((MacroNode*)$2);
                                            $$->setLoc((Loc*)&(@$));
                                        }    
                                    }
            ;

Alloca      : AllocaLine                            {
                                                        if(error_flag == 0)
                                                        {   
                                                            $$ = new AllocaSegmentNode();
                                                            ((AllocaSegmentNode*)$$) ->append((AllocaLineNode*)$1);
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }  
                                                        line("Line:%-4d",@$.first_line);
                                                        debug ("Alloca ::= AllocaLine\n");   
                                                    }
            | Alloca AllocaLine                     {
                                                        line("Line:%-4d",@2.first_line);
                                                        debug ("Alloca ::= Alloca AllocaLine\n"); 
                                                        if(error_flag == 0)
                                                        {   
                                                            ((AllocaSegmentNode*)$$)->append((AllocaLineNode*)$2);
                                                            $$->setLoc((Loc*)&(@$));
                                                        }    
                                                    }
            ;
AllocaLine  : var_tok db_tok {global->now_length = 8;}
                AllocaExpH                          {
                                                        if(error_flag == 0)
                                                        {   
                                                            $$ = new AllocaLineNode($1,8); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        } 
                                                        global->SetMemLength($1,8);
                                                    } 
            | var_tok dw_tok {global->now_length = 16;}
                 AllocaExpH                         {
                                                        if(error_flag == 0)
                                                        {   
                                                            $$ = new AllocaLineNode($1,16); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }  
                                                        global->SetMemLength($1,16);
                                                    }
            | var_tok dd_tok {global->now_length = 32;}
                AllocaExpH                          {
                                                        if(error_flag == 0)
                                                        {   
                                                            $$ = new AllocaLineNode($1,32); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }  
                                                        global->SetMemLength($1,32);
                                                    }
            ;

AllocaExpH  : AllocaExp                     
            | AllocaExpH ',' AllocaExp      
            ;

AllocaExp   : string_tok                    {
                                                if(global->now_length > 8)
                                                {
                                                    if(global->now_length == 16)
                                                        error("%s:%3d.(%2d) Wrong to store ASCII to [word]! please use [byte]\n",infile_name,@$.first_line,@1.first_column+1);
                                                    else 
                                                        error("%s:%3d.(%2d) Wrong to store ASCII to [double word]! please use [byte]\n",infile_name,@$.first_line,@1.first_column+1);
                                                    show_line(@$.first_line,infile_name);
                                                    print_blank(@1.first_column+1);
                                                    root = NULL;
                                                    error_flag =1;
                                                }
                                            }
            | num_tok                       {
                                                if(global->now_length == 8 && $1 > 256)
                                                {
                                                    error("%s:%3d.(%2d) Can't store Number over 256 to [byte]!\n",infile_name,@$.first_line,@1.first_column);
                                                    show_line(@$.first_line,infile_name);
                                                    print_blank(@1.first_column);
                                                    root = NULL;
                                                    error_flag =1;
                                                }
                                                if(global->now_length == 16 && $1 > 65536)
                                                {
                                                    error("%s:%3d.(%2d) Can't store Number over 65536 to [word]!\n",infile_name,@$.first_line,@1.first_column);
                                                    show_line(@$.first_line,infile_name);
                                                    print_blank(@1.first_column);
                                                    root = NULL;
                                                    error_flag =1;
                                                }
                                            }
            | num_tok dup_tok '(' num_tok ')'
            ;

RegS        : ax_tok        {
                                $$ = global->ax;   
                            }
            | bx_tok        {
                                $$ = global->bx;   
                            }
            | cx_tok        {
                                $$ = global->cx;   
                            }
            | dx_tok        {
                                $$ = global->dx;   
                            }
            | si_tok        {
                                $$ = global->si;   
                            }
            | di_tok        {
                                $$ = global->di;   
                            }
            | ds_tok        {
                                $$ = global->ds;   
                            }
            | ss_tok        {
                                $$ = global->ss;   
                            }
            | sp_tok        {
                                $$ = global->sp;   
                            }
            | offset_tok var_tok        {
                                $$ = global->mem;   
                            }
            ;

RegE        : ah_tok        {
                                $$ = global->ax->h;   
                            }
            | al_tok        {
                                $$ = global->ax->l;   
                            }
            | bh_tok        {
                                $$ = global->bx->h;   
                            }
            | bl_tok        {
                                $$ = global->bx->l;   
                            }
            | ch_tok        {
                                $$ = global->cx->h;   
                            }
            | cl_tok        {
                                $$ = global->cx->l;   
                            }
            | dh_tok        {
                                $$ = global->dx->h;   
                            }
            | dl_tok        {
                                $$ = global->dx->l;   
                            }
            ;
MemAddr     : var_tok       {
                                $$ = global->mem;   
                                if(global->GetMemLength($1) == 0){
                                    error("%s:%3d.(%2d) The Memory address isn't defined : %s\n",infile_name,@$.first_line,@1.first_column,$1->c_str());
                                    show_line(@$.first_line,infile_name);
                                    print_blank(@1.first_column);
                                    root = NULL;
                                    error_flag =1;
                                }
                            }
            | data_tok      {
                                $$ = global->mem;   
                            }
            | stack_tok     {
                                $$ = global->mem;  
                            }
            | code_tok      {
                                $$ = global->mem;  
                            }
            | MemAddrExp    {
                                line("Line:%-4d",@$.first_line);
                                debug ("MemAddr ::= MemAddrExp\n"); 
                            }
            ;
MemAddrExp  : '[' num_tok ']'
            | '[' MemAddrExp_a ']'                  {
                                                        if(strcmp("cx",$2->c_str()) == 0)
                                                        {
                                                            error("%s:%3d.(%2d) There can't be cx! please use bx|si|di|num\n",infile_name,@$.first_line,@2.first_column);
                                                            show_line(@$.first_line,infile_name);
                                                            print_blank(@2.first_column);
                                                            root = NULL;
                                                            error_flag =1;
                                                        }
                                                        if(strcmp("dx",$2->c_str()) == 0)
                                                        {
                                                            error("%s:%3d.(%2d) There can't be dx! please use bx|si|di|num\n",infile_name,@$.first_line,@2.first_column);
                                                            show_line(@$.first_line,infile_name);
                                                            print_blank(@2.first_column);
                                                            root = NULL;
                                                            error_flag =1;
                                                        }
                                                        if(strcmp("ax",$2->c_str()) == 0)
                                                        {
                                                            error("%s:%3d.(%2d) There can't be ax! please use bx|si|di|num\n",infile_name,@$.first_line,@2.first_column);
                                                            show_line(@$.first_line,infile_name);
                                                            print_blank(@2.first_column);
                                                            root = NULL;
                                                            error_flag =1;
                                                        }
                                                    }
            | '[' MemAddrExp_a '+' MemAddrExp_a ']' {
                                                        if(strcmp("bx",$2->c_str()) != 0)
                                                        {
                                                            error("%s:%3d.(%2d) There can't be %s! please use bx\n",infile_name,@$.first_line,@2.first_column,$2->c_str());
                                                            show_line(@$.first_line,infile_name);
                                                            print_blank(@2.first_column);
                                                            root = NULL;
                                                            error_flag =1;
                                                        }
                                                        if(strcmp("si",$4->c_str()) != 0 && strcmp("di",$4->c_str()) != 0)
                                                        {
                                                            error("%s:%3d.(%2d) There can't be %s! please use si|di|num\n",infile_name,@$.first_line,@2.first_column,$4->c_str());
                                                            show_line(@$.first_line,infile_name);
                                                            print_blank(@2.first_column);
                                                            root = NULL;
                                                            error_flag =1;
                                                        }
                                                    }
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
                                                        if(strcmp("cx",$2->c_str()) == 0)
                                                        {
                                                            error("%s:%3d.(%2d) There can't be cx! please use bx|si|di\n",infile_name,@$.first_line,@2.first_column);
                                                            show_line(@$.first_line,infile_name);
                                                            print_blank(@2.first_column);
                                                            root = NULL;
                                                            error_flag =1;
                                                        }
                                                        if(strcmp("dx",$2->c_str()) == 0)
                                                        {
                                                            error("%s:%3d.(%2d) There can't be dx! please use bx|si|di\n",infile_name,@$.first_line,@2.first_column);
                                                            show_line(@$.first_line,infile_name);
                                                            print_blank(@2.first_column);
                                                            root = NULL;
                                                            error_flag =1;
                                                        }
                                                        if(strcmp("ax",$2->c_str()) == 0)
                                                        {
                                                            error("%s:%3d.(%2d) There can't be ax! please use bx|si|di\n",infile_name,@$.first_line,@2.first_column);
                                                            show_line(@$.first_line,infile_name);
                                                            print_blank(@2.first_column);
                                                            root = NULL;
                                                            error_flag =1;
                                                        }
                                                    }
            | '[' MemAddrExp_a '+' MemAddrExp_a num_tok']'
                                                    {
                                                        if(strcmp("bx",$2->c_str()) != 0)
                                                        {
                                                            error("%s:%3d.(%2d) There can't be %s! please use bx\n",infile_name,@$.first_line,@2.first_column,$2->c_str());
                                                            show_line(@$.first_line,infile_name);
                                                            print_blank(@2.first_column);
                                                            root = NULL;
                                                            error_flag =1;
                                                        }
                                                        if(strcmp("si",$4->c_str()) != 0 && strcmp("di",$4->c_str()) != 0)
                                                        {
                                                            error("%s:%3d.(%2d) There can't be %s! please use si|di\n",infile_name,@$.first_line,@2.first_column,$4->c_str());
                                                            show_line(@$.first_line,infile_name);
                                                            print_blank(@2.first_column);
                                                            root = NULL;
                                                            error_flag =1;
                                                        }
                                                    }
            ;
MemAddrExp_a    : ax_tok
                | bx_tok
                | cx_tok
                | dx_tok
                | si_tok
                | di_tok
                ;



DoubleOE    : RegE ',' RegE                         {
                                                        if(error_flag == 0)
                                                        {   
                                                            $$ = new DoubleONode((RegNode*)$1,(RegNode*)$3); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }  
                                                    }
            | RegE ',' num_tok                      {
                                                        if(error_flag == 0)
                                                        {   
                                                            RegSNode * num = new RegSNode(); 
                                                            char str[10];
                                                            sprintf(str,"%d",$3);
                                                            num->name = new std::string (str);
                                                            $$ = new DoubleONode((RegNode*)$1,(RegNode*)num); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }  
                                                        if( $3 > 256)
                                                        {
                                                            error("%s:%3d.(%2d) Can't store Number over 256 to [byte]!\n",infile_name,@$.first_line,@3.first_column);
                                                            show_line(@$.first_line,infile_name);
                                                            print_blank(@3.first_column);
                                                            root = NULL;
                                                            error_flag =1;
                                                        }
                                                    }
            | RegE ',' MemAddr                      {
                                                        if(error_flag == 0)
                                                        {   
                                                            $$ = new DoubleONode((RegNode*)$1,(RegNode*)$3); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }  
                                                    }
            | MemAddr ',' RegE                      {
                                                        if(error_flag == 0)
                                                        {   
                                                            $$ = new DoubleONode((RegNode*)$1,(RegNode*)$3); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }  
                                                    }
            | MemAddr ',' num_tok                   {
                                                        if(error_flag == 0)
                                                        {   
                                                            RegSNode * num = new RegSNode(); 
                                                            char str[10];
                                                            sprintf(str,"%d",$3);
                                                            num->name = new std::string (str);
                                                            $$ = new DoubleONode((RegNode*)$1,(RegNode*)num); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }  
                                                    }
            | MemAddr ',' MemAddr                   {
                                                        error("%s:%3d.(%2d)[Severe ERROR]:It's wrong to 'mov mem,mem'\n",infile_name,@$.first_line,@3.first_column);
                                                        show_line(@$.first_line,infile_name);
                                                        print_blank(@3.first_column);
                                                        root = NULL;
                                                        error_flag =1;
                                                        
                                                    }
            | byte_tok ptr_tok MemAddr ',' MemAddr  {
                                                        error("%s:%3d.(%2d)[Severe ERROR]:It's wrong to 'mov mem,mem'\n",infile_name,@$.first_line,@3.first_column);
                                                        show_line(@$.first_line,infile_name);
                                                        print_blank(@3.first_column);
                                                        root = NULL;
                                                        error_flag =1;
                                                    }
            | byte_tok ptr_tok MemAddr ',' num_tok  {
                                                        if(error_flag == 0)
                                                        {   
                                                            RegSNode * num = new RegSNode(); 
                                                            char str[10];
                                                            sprintf(str,"%d",$5);
                                                            num->name = new std::string (str);
                                                            $$ = new DoubleONode((RegNode*)$3,(RegNode*)num); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }  
                                                        if( $5 > 256)
                                                        {
                                                            error("%s:%3d.(%2d) Can't store Number over 256 to [byte]!\n",infile_name,@$.first_line,@5.first_column);
                                                            show_line(@$.first_line,infile_name);
                                                            print_blank(@5.first_column);
                                                        }
                                                    }
            ;
DoubleOS    : RegS ',' RegS                         {
                                                        if(error_flag == 0)
                                                        {   
                                                            $$ = new DoubleONode((RegNode*)$1,(RegNode*)$3); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }  
                                                    }
            | RegS ',' num_tok                      {
                                                        if(error_flag == 0)
                                                        {   
                                                            RegSNode * num = new RegSNode(); 
                                                            char str[10];
                                                            sprintf(str,"%d",$3);
                                                            num->name = new std::string (str);
                                                            $$ = new DoubleONode((RegNode*)$1,(RegNode*)num); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                            
                                                        }  
                                                        if( $3 > 65536)
                                                            {
                                                                error("%s:%3d.(%2d) Can't store Number over 65536 to [word]!\n",infile_name,@$.first_line,@3.first_column);
                                                                show_line(@$.first_line,infile_name);
                                                                print_blank(@3.first_column);
                                                                root = NULL;
                                                                error_flag =1;
                                                            }
                                                    }
            | RegS ',' MemAddr                      {
                                                        if(error_flag == 0)
                                                        {   
                                                            $$ = new DoubleONode((RegNode*)$1,(RegNode*)$3); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }  
                                                    }
            | MemAddr ',' RegS                      {
                                                        if(error_flag == 0)
                                                        {   
                                                            $$ = new DoubleONode((RegNode*)$1,(RegNode*)$3); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }  
                                                    }
            | word_tok ptr_tok MemAddr ',' MemAddr  {
                                                        error("%s:%3d.(%2d)[Severe ERROR]:It's wrong to 'mov mem,mem'\n",infile_name,@$.first_line,@3.first_column);
                                                        show_line(@$.first_line,infile_name);
                                                        print_blank(@3.first_column);
                                                        root = NULL;
                                                            error_flag =1;
                                                         
                                                    }
            | word_tok ptr_tok MemAddr ',' num_tok  {
                                                        if(error_flag == 0)
                                                        {   
                                                            RegSNode * num = new RegSNode(); 
                                                            char str[10];
                                                            sprintf(str,"%d",$5);
                                                            num->name = new std::string (str);
                                                            $$ = new DoubleONode((RegNode*)$3,(RegNode*)num); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }  
                                                    }
            ;
Instruction : Int_ins           {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Int_ins\n");  
                                    $$ = $1;
                                }
            | Mov_ins           {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Mov_ins\n"); 
                                    $$ = $1;
                                }
            | Cmp_ins           {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Cmp_ins\n");   
                                    $$ = $1;
                                }
            | Jmp_ins           {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Jmp_ins\n");  
                                    $$ = $1; 
                                }
            | Add_ins           {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Add_ins\n"); 
                                    $$ = $1;  
                                }
            | Sub_ins           {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Sub_ins\n");  
                                    $$ = $1; 
                                }
            | Mul_ins           {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Mul_ins\n");  
                                    $$ = $1;  
                                }
            | Div_ins           {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Div_ins\n");  
                                    $$ = $1;  
                                }
            | Call_ins          {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Call_ins\n");   
                                    $$ = $1; 
                                }
            | Push_ins          {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Push_ins\n");  
                                    $$ = $1; 
                                }
            | Pop_ins           {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Pop_ins\n");  
                                    $$ = $1; 
                                }
            | Ret_ins           {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Ret_ins\n"); 
                                    $$ = $1;  
                                }
            | Block             {
                                    line("Line:%-4d",@$.first_line);
                                    debug ("Instruction ::= Block\n");   
                                    $$ = $1;
                                }
            ;

Int_ins     : int_tok num_tok   {
                                    if(error_flag == 0)
                                    {   
                                        $$ = new IntInsNode($2); 
                                        $$->setLoc((Loc*)&(@$));
                                        all_node.push_back((Node*)$$);
                                    }  
                                }
            ;

Mov_ins     : mov_tok DoubleOE  {
                                    if(error_flag == 0)
                                    {   
                                        $$ = new MovInsNode((DoubleONode*)$2); 
                                        $$->setLoc((Loc*)&(@$));
                                        all_node.push_back((Node*)$$);
                                    }  
                                }
            | mov_tok DoubleOS  {
                                    if(error_flag == 0)
                                    {   
                                        $$ = new MovInsNode((DoubleONode*)$2); 
                                        $$->setLoc((Loc*)&(@$));
                                        all_node.push_back((Node*)$$);
                                    }  
                                }
            ;

Cmp_ins     : cmp_tok DoubleOE  {
                                    if(error_flag == 0)
                                    {   
                                        $$ = new CmpInsNode((DoubleONode*)$2); 
                                        $$->setLoc((Loc*)&(@$));
                                        all_node.push_back((Node*)$$);
                                    }  
                                }
            | cmp_tok DoubleOS  {
                                    if(error_flag == 0)
                                    {   
                                        $$ = new CmpInsNode((DoubleONode*)$2); 
                                        $$->setLoc((Loc*)&(@$));
                                        all_node.push_back((Node*)$$);
                                    }  
                                }
            ;

Jmp_ins     : jmp_tok var_tok   {
                                    if(error_flag == 0)
                                    {   
                                        $$ = new JmpInsNode(0,$2); 
                                        $$->setLoc((Loc*)&(@$));
                                        all_node.push_back((Node*)$$);
                                    }  
                                    if(global->GetLabelLine($2) == 0){
                                            error("%s:%3d.(%2d)This label isn't defined : %s\n",infile_name,@$.first_line,@2.first_column,$2->c_str());
                                            show_line(@$.first_line,infile_name);
                                            print_blank(@2.first_column);
                                            root = NULL;
                                            error_flag =1;
                                    }
                                }
            | jle_tok var_tok   {
                                    if(error_flag == 0)
                                    {   
                                        $$ = new JmpInsNode(2,$2); 
                                        $$->setLoc((Loc*)&(@$));
                                        all_node.push_back((Node*)$$);
                                    }  
                                    if(global->GetLabelLine($2) == 0){
                                            error("%s:%3d.(%2d)This label isn't defined : %s\n",infile_name,@$.first_line,@2.first_column,$2->c_str());
                                            show_line(@$.first_line,infile_name);
                                            print_blank(@2.first_column);
                                            root = NULL;
                                            error_flag =1;
                                    }
                                }
            | jl_tok var_tok    {
                                    if(error_flag == 0)
                                    {   
                                        $$ = new JmpInsNode(1,$2); 
                                        $$->setLoc((Loc*)&(@$));
                                        all_node.push_back((Node*)$$);
                                    }  
                                    if(global->GetLabelLine($2) == 0){
                                            error("%s:%3d.(%2d)This label isn't defined : %s\n",infile_name,@$.first_line,@2.first_column,$2->c_str());
                                            show_line(@$.first_line,infile_name);
                                            print_blank(@2.first_column);
                                            root = NULL;
                                            error_flag =1;
                                    }
                                }
            | jge_tok var_tok   {
                                    if(error_flag == 0)
                                    {   
                                        $$ = new JmpInsNode(4,$2); 
                                        $$->setLoc((Loc*)&(@$));
                                        all_node.push_back((Node*)$$);
                                    } 
                                    if(global->GetLabelLine($2) == 0){
                                            error("%s:%3d.(%2d)This label isn't defined : %s\n",infile_name,@$.first_line,@2.first_column,$2->c_str());
                                            show_line(@$.first_line,infile_name);
                                            print_blank(@2.first_column);
                                            root = NULL;
                                            error_flag =1;
                                    } 
                                }
            | jg_tok var_tok    {
                                    if(error_flag == 0)
                                    {   
                                        $$ = new JmpInsNode(5,$2); 
                                        $$->setLoc((Loc*)&(@$));
                                        all_node.push_back((Node*)$$);
                                    }  
                                    if(global->GetLabelLine($2) == 0){
                                            error("%s:%3d.(%2d)This label isn't defined : %s\n",infile_name,@$.first_line,@2.first_column,$2->c_str());
                                            show_line(@$.first_line,infile_name);
                                            print_blank(@2.first_column);
                                            root = NULL;
                                            error_flag =1;
                                    }
                                }
            | je_tok  var_tok   {
                                    if(error_flag == 0)
                                    {   
                                        $$ = new JmpInsNode(3,$2); 
                                        $$->setLoc((Loc*)&(@$));
                                        all_node.push_back((Node*)$$);
                                    } 
                                    if(global->GetLabelLine($2) == 0){
                                            error("%s:%3d.(%2d)This label isn't defined : %s\n",infile_name,@$.first_line,@2.first_column,$2->c_str());
                                            show_line(@$.first_line,infile_name);
                                            print_blank(@2.first_column);
                                            root = NULL;
                                            error_flag =1;
                                    } 
                                }
            | jne_tok var_tok   {
                                    if(error_flag == 0)
                                    {   
                                        $$ = new JmpInsNode(6,$2); 
                                        $$->setLoc((Loc*)&(@$));
                                        all_node.push_back((Node*)$$);
                                    }
                                    if(global->GetLabelLine($2) == 0){
                                            error("%s:%3d.(%2d)This label isn't defined : %s\n",infile_name,@$.first_line,@2.first_column,$2->c_str());
                                            show_line(@$.first_line,infile_name);
                                            print_blank(@2.first_column);
                                            root = NULL;
                                            error_flag =1;
                                    }  
                                }
            | loop_tok var_tok  {
                                    if(error_flag == 0)
                                    {   
                                        $$ = new JmpInsNode(7,$2); 
                                        $$->setLoc((Loc*)&(@$));
                                        all_node.push_back((Node*)$$);
                                    }  
                                    if(global->GetLabelLine($2) == 0){
                                            error("%s:%3d.(%2d)This label isn't defined : %s\n",infile_name,@$.first_line,@2.first_column,$2->c_str());
                                            show_line(@$.first_line,infile_name);
                                            print_blank(@2.first_column);
                                            root = NULL;
                                            error_flag =1;
                                    }
                                }
            ;

Add_ins     : add_tok DoubleOE      {
                                        if(error_flag == 0)
                                        {   
                                            $$ = new AddInsNode((DoubleONode*)$2); 
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        }  
                                    }
            | add_tok DoubleOS      {
                                        if(error_flag == 0)
                                        {   
                                            $$ = new AddInsNode((DoubleONode*)$2); 
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        }  
                                    }
            | inc_tok RegE          {
                                        if(error_flag == 0)
                                        {   
                                            RegSNode * num = new RegSNode(); 
                                            char str[10];
                                            sprintf(str,"%d",1);
                                            num->name = new std::string (str);
                                            DoubleONode *operand = new DoubleONode((RegNode*)$2,(RegNode*)num); 
                                            $$ = new AddInsNode((DoubleONode*)operand); 
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        }  
                                    }
            | inc_tok RegS          {
                                        if(error_flag == 0)
                                        {   
                                            RegSNode * num = new RegSNode(); 
                                            char str[10];
                                            sprintf(str,"%d",1);
                                            num->name = new std::string (str);
                                            DoubleONode *operand = new DoubleONode((RegNode*)$2,(RegNode*)num); 
                                            $$ = new AddInsNode((DoubleONode*)operand); 
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        }  
                                    }
            | inc_tok MemAddr       {
                                        if(error_flag == 0)
                                        {   
                                            RegSNode * num = new RegSNode(); 
                                            char str[10];
                                            sprintf(str,"%d",1);
                                            num->name = new std::string (str);
                                            DoubleONode *operand = new DoubleONode((RegNode*)$2,(RegNode*)num); 
                                            $$ = new AddInsNode((DoubleONode*)operand); 
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        }  
                                    }
            ;
Sub_ins     : sub_tok DoubleOE      {
                                        if(error_flag == 0)
                                        {   
                                            $$ = new SubInsNode((DoubleONode*)$2); 
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        }  
                                    }
            | sub_tok DoubleOS      {
                                        if(error_flag == 0)
                                        {   
                                            $$ = new SubInsNode((DoubleONode*)$2); 
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        }  
                                    }
            | dec_tok RegE          {
                                        if(error_flag == 0)
                                        {   
                                            RegSNode * num = new RegSNode(); 
                                            char str[10];
                                            sprintf(str,"%d",1);
                                            num->name = new std::string (str);
                                            DoubleONode *operand = new DoubleONode((RegNode*)$2,(RegNode*)num); 
                                            $$ = new SubInsNode((DoubleONode*)operand); 
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        }  
                                    }
            | dec_tok RegS          {
                                        if(error_flag == 0)
                                        {   
                                            RegSNode * num = new RegSNode(); 
                                            char str[10];
                                            sprintf(str,"%d",1);
                                            num->name = new std::string (str);
                                            DoubleONode *operand = new DoubleONode((RegNode*)$2,(RegNode*)num); 
                                            $$ = new SubInsNode((DoubleONode*)operand); 
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        }  
                                    }
            | dec_tok MemAddr       {
                                        if(error_flag == 0)
                                        {   
                                            RegSNode * num = new RegSNode(); 
                                            char str[10];
                                            sprintf(str,"%d",1);
                                            num->name = new std::string (str);
                                            DoubleONode *operand = new DoubleONode((RegNode*)$2,(RegNode*)num); 
                                            $$ = new SubInsNode((DoubleONode*)operand); 
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        }  
                                    }
            ;

Mul_ins     : mul_tok RegE                          {
                                                        if(error_flag == 0)
                                                        {   
                                                            $$ = new MulInsNode(global->ax->h,global->ax->l,global->ax->l,$2); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }  
                                                    }
            | mul_tok RegS                          {
                                                        if(error_flag == 0)
                                                        {   
                                                            $$ = new MulInsNode(global->dx,global->ax,global->ax,$2); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }  
                                                    }
            | mul_tok MemAddr                       {
                                                        warning("%s:%3d.(%2d) Mem length missing,do you mean 'word ptr' or 'byte ptr'?\n",infile_name,@$.first_line,@1.last_column+1);
                                                        show_line(@$.first_line,infile_name);
                                                        print_blank(@1.last_column+1);
                                                        if(error_flag == 0)
                                                        {   
                                                            $$ = new MulInsNode(global->ax->h,global->ax->l,global->ax->l,$2); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }  
                                                    }
            | mul_tok word_tok ptr_tok MemAddr      {
                                                        if(error_flag == 0)
                                                        {   
                                                            $$ = new MulInsNode(global->dx,global->ax,global->ax,$4); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }  
                                                    }
            | mul_tok byte_tok ptr_tok MemAddr      {
                                                        if(error_flag == 0)
                                                        {   
                                                            $$ = new MulInsNode(global->ax->h,global->ax->l,global->ax->l,$4); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }  
                                                    }
            ;

Div_ins     : div_tok RegE                          {
                                                        if(error_flag == 0)
                                                        {   
                                                            $$ = new DivInsNode(global->ax->h,global->ax->l,global->ax->h,global->ax->l,$2); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }  
                                                    }
            | div_tok RegS                          {
                                                        if(error_flag == 0)
                                                        {   
                                                            $$ = new DivInsNode(global->dx,global->ax,global->dx,global->ax,$2); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }  
                                                    }
            | div_tok MemAddr                       {
                                                        warning("%s:%3d.(%2d) Mem length missing,do you mean 'word ptr' or 'byte ptr'?\n",infile_name,@$.first_line,@1.last_column+1);
                                                        show_line(@$.first_line,infile_name);
                                                        print_blank(@1.last_column+1);
                                                        if(error_flag == 0)
                                                        {   
                                                            $$ = new DivInsNode(global->ax->h,global->ax->l,global->ax->h,global->ax->l,$2); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }  
                                                    }
            | div_tok word_tok ptr_tok MemAddr      {
                                                        if(error_flag == 0)
                                                        {   
                                                            $$ = new DivInsNode(global->dx,global->ax,global->dx,global->ax,$4); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }  
                                                    }
            | div_tok byte_tok ptr_tok MemAddr      {
                                                        if(error_flag == 0)
                                                        {   
                                                            $$ = new DivInsNode(global->ax->h,global->ax->l,global->ax->h,global->ax->l,$4); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }  
                                                    }
            ;

Call_ins    : call_tok var_tok      {
                                        if(error_flag == 0)
                                        {   
                                            $$ = new CallInsNode($2); 
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        }   
                                        if(global->GetLabelLine($2) == 0){
                                            error("%s:%3d.(%2d)This label isn't defined : %s\n",infile_name,@$.first_line,@2.first_column,$2->c_str());
                                            show_line(@$.first_line,infile_name);
                                            print_blank(@2.first_column);
                                            root = NULL;
                                            error_flag =1;
                                        }
                                    }
            ;

Push_ins    : push_tok RegE         {
                                        if(error_flag == 0)
                                        {   
                                            $$ = new PushInsNode($2); 
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        }  
                                    }
            | push_tok RegS         {
                                        if(error_flag == 0)
                                        {   
                                            $$ = new PushInsNode($2);
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        }  
                                    }
            ;

Pop_ins     : pop_tok RegE          {
                                        if(error_flag == 0)
                                        {   
                                            $$ = new PopInsNode($2); 
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        }  
                                    }
            | pop_tok RegS          {
                                        if(error_flag == 0)
                                        {   
                                            $$ = new PopInsNode($2); 
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        }  
                                    }
            ;
Ret_ins     : ret_tok               {
                                        if(error_flag == 0)
                                        {   
                                            $$ = new RetInsNode();
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        }  
                                    }
            ;
Block       : var_tok ':' { global->SetLabelLine($1,@1.first_line);}
                BlockItem             {
                                            line("Line:%-4d",@$.first_line);
                                            debug ("Block ::= %s : BlockItem\n",$1->c_str());
                                            if(error_flag == 0)
                                            {   
                                                $$ = new BlockNode($1,(BlockItemNode *)$4); 
                                                $$->setLoc((Loc*)&(@$));
                                                all_node.push_back((Node*)$$);
                                            }      
                                            
                                        }
            | var_tok ':'               {
                                            line("Line:%-4d",@$.first_line);
                                            debug ("Block ::= %s : \n",$1->c_str()); 
                                            if(error_flag == 0)
                                            {   
                                                $$ = new BlockNode($1,NULL); 
                                                $$->setLoc((Loc*)&(@$));
                                                all_node.push_back((Node*)$$);
                                            }     
                                            global->SetLabelLine($1,@1.first_line);
                                        }
            ;

BlockItem   : Instruction                                       {
                                                                    line("Line:%-4d",@$.first_line);
                                                                    debug ("BlockItem ::= Instruction\n");   
                                                                    if(error_flag == 0)
                                                                    {   
                                                                        $$ = new BlockItemNode(); 
                                                                        ((BlockItemNode*)$$)->append((InstructionNode*)$1);
                                                                        $$->setLoc((Loc*)&(@$));
                                                                        all_node.push_back((Node*)$$);
                                                                    }   
                                                                }
            | BlockItem Instruction                             {
                                                                    line("Line:%-4d",@$.first_line);
                                                                    debug ("BlockItem ::= BlockItem Instruction\n");  
                                                                    if(error_flag == 0)
                                                                    {   
                                                                        ((BlockItemNode*)$$)->append((InstructionNode*)$2);
                                                                        $$->setLoc((Loc*)&(@$));
                                                                        all_node.push_back((Node*)$$);
                                                                    }  
                                                                }
            ;

Macro       : var_tok macro_tok  MacroExp BlockItem endm_tok    {
                                                                    line("Line:%-4d",@$.first_line);
                                                                    debug ("Macro ::= var macro exp \n\t\t  BlockItem \n \t\t  endm\n");  
                                                                    if(error_flag == 0)
                                                                    {   
                                                                        $$ = new MacroNode($1,(BlockItemNode*)$4); 
                                                                        $$->setLoc((Loc*)&(@$));
                                                                        all_node.push_back((Node*)$$);
                                                                    }   
                                                                }
            ;

MacroExp    : var_tok
            | MacroExp ',' var_tok
            ;



%%


void yyerror (const char *msg)
{
    error ("%s\n", msg);
}
