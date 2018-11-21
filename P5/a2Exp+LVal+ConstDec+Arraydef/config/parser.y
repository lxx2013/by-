%{
#include <stdio.h>
#include <string>
#define DEBUG
#include "node.hh"
#include "util.hh"
#include "global.hh"
extern int yylex ();
extern void yyerror (const char *msg);
InputNode *root;
ConstDefHNode *cst_root;
ExpHNode *ExpH_root;
%}

%union
{
    int  num;
    std::string *var;
    Node *node;
}

%token num_tok var_tok eol_tok err_tok const_tok int_tok

%left '-' '+'
%left '*' '/' '%'
%right '^'

%type <num> num_tok
%type <var> var_tok
%type <node> input CompUnit asgn exp LVal Decl ConstDecl ConstDefH ConstDef ArrayDef ExpH

%locations

%%
input : /* empty */     {   debug ("input ::= empty\n"); 
                            root = new InputNode ();
                        }
      | input CompUnit  {   debug ("input ::= CompUnit\n");
                            if ($2!=NULL)   // ignore empty line
                                root->append ((CompUnitNode*)$2);
                        }
      ;

CompUnit    : eol_tok           {   debug ("CompUnit ::= eol\n");
                                    $$ = NULL;
                                }
            | asgn ';'          {   debug ("CompUnit ::= asgn eol\n");
                                    $$ = new CompUnitNode ((AsgnNode*)$1);
                                    $$->setLoc((Loc*)&(@$));
                                }
            | Decl              {   debug ("CompUnit ::= Decl\n");
                                    $$ = $1;
                                }
            ;

Decl        : ConstDecl         {   debug ("Decl ::= ConstDecl\n");
                                    $$ = $1;; 
                                }
/*            | VarDecl           {   debug ("CompUnit ::= VarDecl\n");
                                    $$ = new CompUnitNode ((AsgnNode*)$1);
                                }
*/            ;

ConstDecl   : const_tok int_tok ConstDefH  ';'  {       //line("Line:%-3d",@$.first_line);
                                                        debug("ConstDecl ::= const int ConstDefH;\n");
                                                        $$ = new ConstDeclNode( (ConstDefHNode*)$3);
                                                }
ConstDefH   : ConstDef                  {   //line("Line:%-3d",@$.first_line);
                                            debug("ConstDefH ::= ConstDef\n");
                                            cst_root = new ConstDefHNode();
                                            cst_root->append((ConstDefNode*)$1);
                                            printf("%d\n",2);
                                            $$ = cst_root;
                                        }
            | ConstDefH ',' ConstDef    {   //line("Line:%-3d",@$.first_line);
                                            debug("ConstDefH ::= ConstDefH,ConstDef\n");
                                            if($3!=NULL)
                                                cst_root->append((ConstDefNode*)$3);
                                        }
            ;
ConstDef    : var_tok '='  exp  {   //line("Line:%-3d",@$.first_line);
                                    debug("ConstDef ::= ident = Exp\n");
                                    $$ = new AsgnNode((LValNode*)new VarNode($1),(ExpNode*)$3);
                                    $$->setLoc((Loc*)&(@$));
                                }
            | ArrayDef          {   //line("Line:%-3d",@$.first_line);
                                    debug("ConstDef ::= ArrayDef\n");
                                    $$ = $1;
                                }
            ;
ArrayDef    : var_tok '[' ']' '=' '{' ExpH '}'  {   //line("Line:%-3d",@$.first_line);
                                                    debug("ArrayDef ::= ident[]={ExpH}\n");
                                                    $$ = new ArrayDef_1_Node(new VarNode($1),(ExpHNode*)$6);
                                                    $$->setLoc((Loc*)&(@$));
                                                }
            | var_tok '[' exp ']' '=' '{' ExpH '}'  {   //line("Line:%-3d",@$.first_line);
                                                        debug("ArrayDef ::= ident[Exp]={ExpH}\n");
                                                        $$ = new ArrayDef_2_Node(new VarNode($1),(ExpNode*)$3,(ExpHNode*)$7);
                                                        $$->setLoc((Loc*)&(@$));
                                                    }
            ;
ExpH        : exp           {   //line("Line:%-3d",@$.first_line);
                                debug("ExpH ::= exp\n");
                                ExpH_root = new ExpHNode();
                                ExpH_root->append((ExpNode*)$1);
                                $$ = ExpH_root;
                            }
            | ExpH ',' exp  {   //line("Line:%-3d",@$.first_line);
                                debug("ExpH ::= ExpH,Exp\n");
                                if($3!=NULL)
                                    ExpH_root->append((ExpNode*)$3);
                            }
            ;

asgn : LVal '=' exp     {   debug ("asgn ::= LVal = exp\n");
                            $$ = new AsgnNode((LValNode*)$1,(ExpNode*)$3);
                            $$->setLoc((Loc*)&(@$));
                            /* Loc* loc = (Loc*)&(@$); */
                            /* printf("%d %d %d %d\n", loc->first_line, loc->first_column, loc->last_line, loc->last_column); */
                        }
     ;

exp : num_tok           {   debug ("exp ::= num\n");
                            $$ = new NumNode ($1);
                            $$->setLoc((Loc*)&(@$));
                        }
    | var_tok           {   debug ("exp ::= ident\n");
                            $$ = new VarNode ($1);
                            $$->setLoc((Loc*)&(@$));
                        }
    | exp '+' exp       {   debug ("exp ::= exp + exp\n");
                            $$ = new BinaryExpNode ('+', (ExpNode*)$1, (ExpNode*)$3);
                            $$->setLoc((Loc*)&(@$));
                        }
    | exp '-' exp       {   debug ("exp ::= exp - exp\n");
                            $$ = new BinaryExpNode ('-', (ExpNode*)$1, (ExpNode*)$3);
                            $$->setLoc((Loc*)&(@$));
                        }
    | exp '*' exp       {   debug ("exp ::= exp * exp\n");
                            $$ = new BinaryExpNode ('*', (ExpNode*)$1, (ExpNode*)$3);
                            $$->setLoc((Loc*)&(@$));
                        }
    | exp '/' exp       {   debug ("exp ::= exp / exp\n");
                            $$ = new BinaryExpNode ('/', (ExpNode*)$1, (ExpNode*)$3);
                            $$->setLoc((Loc*)&(@$));
                        }
    | exp '%' exp       {   debug ("exp ::= exp %% exp\n");
                            $$ = new BinaryExpNode ('%', (ExpNode*)$1, (ExpNode*)$3);
                            $$->setLoc((Loc*)&(@$));
                        }
    | '-' exp           {   debug ("exp ::= - exp\n");
                            $$ = new UnaryExpNode ('-', (ExpNode*)$2);
                            $$->setLoc((Loc*)&(@$));
                        }
    | '+' exp           {   debug ("exp ::= - exp\n");
                            $$ = new UnaryExpNode ('+', (ExpNode*)$2);
                            $$->setLoc((Loc*)&(@$));
                        }
    | '(' exp ')'       {   debug ("exp ::= ( exp )\n");
                            $$ = new ParenExpNode ( (ExpNode*)$2);
                            $$->setLoc((Loc*)&(@$));
                        }
    | LVal              {   debug ("exp ::= LVal\n");
                            $$ = $1;
                        }
    ;
LVal	: var_tok           {
                                debug ("LVal ::= ident\n");
                                $$ = new VarNode($1);
                                $$->setLoc((Loc*)&(@$));
                            }
        | var_tok '[' exp ']'   {
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
