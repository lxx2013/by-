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
%}

%union
{
    int  num;
    std::string *var;
    Node *node;
}

%token num_tok var_tok eol_tok err_tok

%left '-' '+'
%left '*' '/'
%right '^'

%type <num> num_tok
%type <var> var_tok
%type <node> input line asgn exp

%locations

%%
input : /* empty */     {   debug ("input ::= empty\n"); 
                            root = new InputNode ();
                        }
      | input line      {   debug ("input ::= input line\n"); 
                            if ($2!=NULL)   // ignore empty line
                                root->append ((LineNode*)$2);
                        }
      ;

line : eol_tok          {   debug ("line ::= eol\n");
                            $$ = NULL;
                        }
     | asgn ';' eol_tok {   debug ("line ::= asgn eol\n");
                            $$ = new LineNode ((AsgnNode*)$1);
                        }
     ;

asgn : var_tok '=' exp  {   debug ("asgn ::= var = exp\n");
                            $$ = new AsgnNode (new VarNode($1), (ExpNode*)$3);
                            $$->setLoc((Loc*)&(@$));
                            /* Loc* loc = (Loc*)&(@$); */
                            /* printf("%d %d %d %d\n", loc->first_line, loc->first_column, loc->last_line, loc->last_column); */
                        }
     ;

exp : num_tok           {   debug ("exp ::= num\n");
                            $$ = new NumNode ($1);
                            $$->setLoc((Loc*)&(@$));
                        }
    | var_tok           {   debug ("exp ::= var\n");
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
    | exp '^' exp       {   debug ("exp ::= exp ^ exp\n");
                            $$ = new BinaryExpNode ('^', (ExpNode*)$1, (ExpNode*)$3);
                            $$->setLoc((Loc*)&(@$));
                        }
    | '-' exp %prec '-' {   debug ("exp ::= - exp\n");
                            $$ = new UnaryExpNode ('-', (ExpNode*)$2);
                            $$->setLoc((Loc*)&(@$));
                        }
    | '(' exp ')'       {   debug ("exp ::= ( exp )\n");
                            $$ = $2;
                            $$->setLoc((Loc*)&(@$));
                        }
    ;

%%

void yyerror (const char *msg)
{
    error ("%s", msg);
}
