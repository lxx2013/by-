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
%}

%union
{
    int  num;
    std::string *var;
    Node *node;
}

%token num_tok var_tok eol_tok err_tok const_tok int_tok void_tok if_tok else_tok while_tok RelOp 


%left '-' '+'
%left '*' '/' '%'
%right '^'
%left ')'           //加上错误处理时注意处理这里的优先级
%right '('


%type <num> num_tok
%type <var> var_tok  RelOp
%type <node> input CompUnit asgn exp LVal Decl ConstDecl ConstDefH ConstDef ArrayDef ExpH VarDecl VarDefH VarDef
%type <node> FuncDef BlockItemH BlockItem Stmt Block Cond 
%locations

%%
input : /* empty */     {                              
                            root = new InputNode ();
                            line("Line:%-3d",1);
                            debug ("input ::= empty\n"); 
                        }
      | input CompUnit  {                             
                            if ($2!=NULL)   // ignore empty line
                                root->append ((CompUnitNode*)$2);
                            line("Line:%-3d",1);
                            debug ("input ::= CompUnit\n");
                        }
      ;

CompUnit    : Decl              {   line("Line:%-3d",@1.first_line);
                                    debug ("CompUnit ::= Decl\n");
                                    $$ = $1;
                                    //printf("%d %d \n", $$->loc->first_line,$$->loc->last_column);
                                }
            | FuncDef           {   line("Line:%-3d",@1.first_line);
                                    debug("CompUnit ::= FuncDef\n");
                                    $$ = $1;
                                }
            ;
FuncDef     : void_tok var_tok '(' ')' Block    {   line("Line:%-3d",@1.first_line);
                                                    debug("FuncDef ::= void ident() Block\n");
                                                    $$ = new FuncDefNode(new VarNode($2),(BlockNode*)$5); 
                                                    $$->setLoc((Loc*)&(@$));                                                   
                                                }
Block       : '{'   '}'             {   line("Line:%-3d",@1.first_line);
                                        debug("Block ::= {  }\n");
                                        $$ = new BlockNode(0);
                                        $$->setLoc((Loc*)&(@$));
                                    }
            | '{' BlockItemH '}'    {   line("Line:%-3d",@1.first_line);
                                        debug("Block ::= { BlockItemH }\n");
                                        if($2==0)
                                        {
                                            printf("paser.y:73 BlockItem = NULL!\n");
                                            $$ = NULL;
                                        }
                                        else
                                        {    
                                            $$ = new BlockNode((BlockItemHNode*)$2);
                                            $$->setLoc((Loc*)&(@$));
                                        }
                                    }
            ;
BlockItemH  : BlockItem             {   line("Line:%-3d",@1.first_line);
                                        debug("BlockItemH ::= BlockItem\n");
                                        $$ = new BlockItemHNode();
                                        ((BlockItemHNode*)$$)->append((BlockItemNode*)$1);
                                        $$->setLoc((Loc*)&(@$));
                                    }
            | BlockItemH BlockItem  {   line("Line:%-3d",@1.first_line);
                                        debug("BlockItemH ::= BlockItemH BlockItem\n");
                                        if($2!=NULL)
                                        { 
                                            ((BlockItemHNode*)$$)->append((BlockItemNode*)$2);
                                            $$->setLoc((Loc*)&(@$));
                                        }

                                    }
            ;
BlockItem   : Decl                  {   line("Line:%-3d",@1.first_line);
                                        debug("BlockItem ::= Decl\n");
                                        $$ = $1;
                                    }
            | Stmt                  {   line("Line:%-3d",@$.first_line);
                                        debug("BlockItem ::= Stmt\n");
                                        $$ = $1;
                                    }
            ;
Stmt        : asgn ';'              {   line("Line:%-3d",@$.first_line);
                                        debug("Stmt ::= asgn;\n");
                                        $$ = $1;
                                    }
            | var_tok '(' ')' ';'           {   
                                                line("Line:%-3d",@$.first_line);
                                                debug("Stmt ::= ident();\n");
                                                $$ = new FuncStmtNode(new VarNode($1));
                                                $$->setLoc((Loc*)&(@$));
                                            }
            | Block                         {   
                                                line("Line:%-3d",@$.first_line);
                                                debug("Stmt ::= Block\n");
                                                $$ = $1;
                                            }
            | if_tok '(' Cond ')' Stmt else_tok Stmt    {   
                                                            line("Line:%-3d",@$.first_line);
                                                            debug("Stmt ::= if(Cond)Stmt else Stmt\n");
                                                            $$ = new IFELStmtNode((CondNode*)$3,(StmtNode*)$5,(StmtNode*)$7);
                                                            $$->setLoc((Loc*)&(@$));
                                                        }

            | if_tok '(' Cond ')' Stmt                  {   
                                                            line("Line:%-3d",@$.first_line);
                                                            debug("Stmt ::= if(Cond)Stmt\n");
                                                            $$ = new IFStmtNode((CondNode*)$3,(StmtNode*)$5);
                                                            $$->setLoc((Loc*)&(@$));
                                                        }

            | while_tok '(' Cond ')' Stmt   {   line("Line:%-3d",@$.first_line);
                                                debug("Stmt ::= While(Cond) Stmt\n");
                                                $$ = new WhileStmtNode((CondNode*)$3,(StmtNode*)$5);
                                                $$->setLoc((Loc*)&(@$));
                                            }
            | ';'                           {   line("Line:%-3d",@$.first_line);
                                                debug("Stmt ::= ;\n");
                                                $$ = new VarNode(new std::string (";"));
                                                $$->setLoc((Loc*)&(@$));
                                            }
            ;
Cond        : exp RelOp exp         {   line("Line:%-3d",@$.first_line);
                                        debug("Cond ::= Exp %s Exp\n",$2->c_str());
                                        $$ = new CondNode((ExpNode*)$1,new VarNode($2),(ExpNode*)$3);
                                        $$->setLoc((Loc*)&(@$));
                                    }                                 

            ;


Decl        : ConstDecl         {   line("Line:%-3d",@$.first_line);
                                    debug ("Decl ::= ConstDecl\n");
                                    $$ = $1;; 
                                }
            | VarDecl           {   line("Line:%-3d",@$.first_line);
                                    debug ("Decl ::= VarDecl\n");
                                    $$ = $1;
                                }
            ;

ConstDecl   : const_tok int_tok ConstDefH  ';'  {       line("Line:%-3d",@$.first_line);
                                                        debug("ConstDecl ::= const int ConstDefH;\n");
                                                        $$ = new ConstDeclNode( (ConstDefHNode*)$3);
                                                        $$->setLoc((Loc*)&(@$));
                                                }
ConstDefH   : ConstDef                  {   line("Line:%-3d",@$.first_line);
                                            debug("ConstDefH ::= ConstDef\n");
                                            $$ = new ConstDefHNode();
                                            ((ConstDefHNode*)$$)->append((ConstDefNode*)$1);
                                            $$->setLoc((Loc*)&(@$));
                                        }
            | ConstDefH ',' ConstDef    {   line("Line:%-3d",@$.first_line);
                                            debug("ConstDefH ::= ConstDefH,ConstDef\n");
                                            if($3!=NULL)
                                            {
                                                ((ConstDefHNode*)$$)->append((ConstDefNode*)$3);
                                                $$->setLoc((Loc*)&(@$));
                                            }
                                        }
            ;
ConstDef    : var_tok '='  exp  {   line("Line:%-3d",@$.first_line);
                                    debug("ConstDef ::= ident = Exp\n");
                                    $$ = new AsgnNode((LValNode*)new VarNode($1),(ExpNode*)$3);
                                    $$->setLoc((Loc*)&(@$));
                                }
            | ArrayDef          {   line("Line:%-3d",@$.first_line);
                                    debug("ConstDef ::= ArrayDef\n");
                                    $$ = $1;
                                }
            ;
ArrayDef    : var_tok '[' ']' '=' '{' ExpH '}'  {   line("Line:%-3d",@$.first_line);
                                                    debug("ArrayDef ::= ident[]={ExpH}\n");
                                                    $$ = new ArrayDef_1_Node(new VarNode($1),(ExpHNode*)$6);
                                                    $$->setLoc((Loc*)&(@$));
                                                }
            | var_tok '[' exp ']' '=' '{' ExpH '}'  {   line("Line:%-3d",@$.first_line);
                                                        debug("ArrayDef ::= ident[Exp]={ExpH}\n");
                                                        $$ = new ArrayDef_2_Node(new VarNode($1),(ExpNode*)$3,(ExpHNode*)$7);
                                                        $$->setLoc((Loc*)&(@$));
                                                    }
            ;

VarDecl     : int_tok  VarDefH ';'  {   line("Line:%-3d",@$.first_line);
                                        debug("VarDecl ::= int VarDefH ;\n");
                                        $$ = new VarDeclNode( (VarDefHNode*)$2);
                                        $$->setLoc((Loc*)&(@$));
                                    }
            ;
VarDefH     : VarDef                {   line("Line:%-3d",@$.first_line);
                                        debug("VarDefH ::= VarDef\n");
                                        $$ = new VarDefHNode();
                                        ((VarDefHNode*)$$)->append((VarDefNode*)$1);
                                        $$->setLoc((Loc*)&(@$));
                                    }
            | VarDefH ',' VarDef    {   
                                        if($3!=NULL)
                                        {   
                                             ((VarDefHNode*)$$)->append((VarDefNode*)$3);
                                             $$->setLoc((Loc*)&(@$));
                                        }
                                        line("Line:%-3d",@$.first_line);
                                        debug("VarDefH ::= VarDefH,VarDef\n");
                                    }
            ;
VarDef      : LVal                  {   $$ = $1;
                                        line("Line:%-3d",@$.first_line);
                                        debug("Var ::= ident\n");
                                        
                                    }
            | var_tok '=' exp       {   line("Line:%-3d",@$.first_line);
                                        debug("VarDef ::= ident=Exp\n");
                                        $$ = new AsgnNode((LValNode*)new VarNode($1),(ExpNode*)$3);
                                        $$->setLoc((Loc*)&(@$));
                                    }
            | ArrayDef              {   line("Line:%-3d",@1.first_line);
                                        debug("VarDef ::= ArrayDef\n");
                                        $$ = $1;
                                    }
            ;

ExpH        : exp           {   line("Line:%-3d",@1.first_line);
                                debug("ExpH ::= exp\n");
                                $$ = new ExpHNode();
                                ((ExpHNode*)$$)->append((ExpNode*)$1);
                                $$->setLoc((Loc*)&(@$));
                            }
            | ExpH ',' exp  {   line("Line:%-3d",@1.first_line);
                                debug("ExpH ::= ExpH,Exp\n");
                                if($3!=NULL)
                                {
                                    ((ExpHNode*)$$)->append((ExpNode*)$3);
                                    $$->setLoc((Loc*)&(@$));
                                }
                            }
            ;

asgn : LVal '=' exp     {   line("Line:%-3d",@1.first_line);
                            debug ("asgn ::= LVal = exp\n");
                            $$ = new AsgnNode((LValNode*)$1,(ExpNode*)$3);
                            $$->setLoc((Loc*)&(@$));
                        }
     ;

exp : num_tok           {   line("Line:%-3d",@1.first_line);
                            debug ("exp ::= num\n");
                            $$ = new NumNode ($1);
                            $$->setLoc((Loc*)&(@$));
                        }
    | exp '+' exp       {   line("Line:%-3d",@1.first_line);    
                            debug ("exp ::= exp + exp\n");
                            $$ = new BinaryExpNode ('+', (ExpNode*)$1, (ExpNode*)$3);
                            $$->setLoc((Loc*)&(@$));
                        }
    | exp '-' exp       {   line("Line:%-3d",@1.first_line);
                            debug ("exp ::= exp - exp\n");
                            $$ = new BinaryExpNode ('-', (ExpNode*)$1, (ExpNode*)$3);
                            $$->setLoc((Loc*)&(@$));
                        }
    | exp '*' exp       {   line("Line:%-3d",@1.first_line);
                            debug ("exp ::= exp * exp\n");
                            $$ = new BinaryExpNode ('*', (ExpNode*)$1, (ExpNode*)$3);
                            $$->setLoc((Loc*)&(@$));
                        }
    | exp '/' exp       {   line("Line:%-3d",@1.first_line);
                            debug ("exp ::= exp / exp\n");
                            $$ = new BinaryExpNode ('/', (ExpNode*)$1, (ExpNode*)$3);
                            $$->setLoc((Loc*)&(@$));
                        }
    | exp '%' exp       {   line("Line:%-3d",@1.first_line);
                            debug ("exp ::= exp %% exp\n");
                            $$ = new BinaryExpNode ('%', (ExpNode*)$1, (ExpNode*)$3);
                            $$->setLoc((Loc*)&(@$));
                        }
    | '-' exp           {   line("Line:%-3d",@1.first_line);
                            debug ("exp ::= - exp\n");
                            $$ = new UnaryExpNode ('-', (ExpNode*)$2);
                            $$->setLoc((Loc*)&(@$));
                        }
    | '+' exp           {   line("Line:%-3d",@1.first_line);
                            debug ("exp ::= + exp\n");
                            $$ = new UnaryExpNode ('+', (ExpNode*)$2);
                            $$->setLoc((Loc*)&(@$));
                        }
    | '(' exp ')'       {   
                            line("Line:%-3d",@1.first_line);
                            debug ("exp ::= ( exp )\n");
                            $$ = new ParenExpNode ( (ExpNode*)$2);
                            $$->setLoc((Loc*)&(@$));
                        }
    | LVal              {   line("Line:%-3d",@$.first_line);
                            debug ("exp ::= LVal\n");
                            $$ = $1;
                        }
    ;
LVal	: var_tok           {
                                line("Line:%-3d",@1.first_line);
                                debug ("LVal ::= ident\n");
                                $$ = new VarNode($1);
                                $$->setLoc((Loc*)&(@$));
                            }
        | var_tok '[' exp ']'   {
                                    line("Line:%-3d",@1.first_line);
                                    debug ("LVal ::= ident[Exp]\n");
                                    $$ = new ArrayLValNode(new VarNode($1),(ExpNode*)$3);
                                    $$->setLoc((Loc*)&(@$));
                                }
        ;

%%


void yyerror (const char *msg)
{
    error ("%s", msg);
}
