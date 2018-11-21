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
//show_line //
std::string line_str;
void show_line(int line,char* filename)
{
    line_str = "";
    line_str+="./bin/sed.sh '";
    char temp[10];
    sprintf(temp,"%d",line);
    line_str+=temp;
    line_str+="p' ";
    line_str+=filename;
    line_str+=".temp.c";
    system(line_str.c_str());
}
void print_blank(int column)
{
    int i=0;
    for(i=0;i<column-1;i++)
        line(" ");
    line("^\n");
};
//**********//
%}

%union
{
    int  num;
    std::string *var;
    Node *node;
}

%token num_tok var_tok eol_tok err_tok const_tok int_tok void_tok if_tok else_tok while_tok break_tok continue_tok RelOp 

%left '='
%left ')'
%right '('
%left RelOp
%left '-' '+'
%left '*' '/' '%'
%right '^'
%left zg



%type <num> num_tok
%type <var> var_tok  RelOp
%type <node> input CompUnit asgn exp LVal Decl ConstDecl ConstDefH ConstDef ArrayDef ExpH VarDecl VarDefH VarDef
%type <node> FuncDef BlockItemH BlockItem Stmt Block Cond ExpL
%locations

%%

input: /* empty */     {   
                            error_flag = 0;
                            error_debug_flag = 0;                           
                            root = new InputNode ();
                            all_node.push_back((Node*)root);
                            line("Line:%-3d",1);
                            debug("input ::= empty\n"); 
                        }
      | input CompUnit  {                             
                            if ($2!=NULL)   // ignore empty line
                            {   
                                if(error_flag == 0)
                                    root->append ((CompUnitNode*)$2);
                            }
                            line("Line:%-3d",1);
                            debug ("input ::= CompUnit\n");
                        }
      ;

CompUnit: Decl              {   line("Line:%-3d",@1.first_line);
                                    debug ("CompUnit ::= Decl\n");
                                    $$ = $1;
                                    $$->scope =1;
                                    //printf("%d %d \n", $$->loc->first_line,$$->loc->last_column);
                                }
            | FuncDef           {   line("Line:%-3d",@1.first_line);
                                    debug("CompUnit ::= FuncDef\n");
                                    $$ = $1;
                                    $$ -> scope =1;
                                }
            ;
FuncDef: void_tok var_tok '(' ')' Block    {   line("Line:%-3d",@1.first_line);
                                                    debug("FuncDef ::= void ident() Block\n");
                                                    if(error_flag == 0)
                                                    {   
                                                        $$ = new FuncDefNode(new VarNode($2),(BlockNode*)$5); 
                                                        $$->setLoc((Loc*)&(@$));
                                                        all_node.push_back((Node*)$$);
                                                    }                                                   
                                                }

            | void_tok var_tok   ')' Block      {   line("Line:%-3d",@$.first_line);debug("FuncDef ::= void ident'(') Block\n");
                                                    error("%s:%3d.(%2d) left paren missing, there should be '('\n",infile_name,@$.first_line,@1.last_column+1);
                                                    show_line(@$.first_line,infile_name);
                                                    print_blank(@1.last_column+1);
                                                    if(error_flag == 0)
                                                    {   
                                                        if(error_debug_flag == 0)
                                                        {
                                                            delete_all_node();
                                                            error_flag = 1;
                                                        }
                                                        else
                                                        {
                                                            $$ = new FuncDefNode(new VarNode($2),(BlockNode*)$4); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }
                                                    }
                                                }
            | void_tok var_tok '('   Block      {   line("Line:%-3d",@$.first_line);debug("FuncDef ::= void ident(')' Block\n");
                                                    error("%s:%3d.(%2d) right paren missing, there should be ')'\n",infile_name,@$.first_line,@3.last_column+1);
                                                    show_line(@$.first_line,infile_name);
                                                    print_blank(@3.last_column+1);
                                                    if(error_flag == 0)
                                                    {   
                                                        if(error_debug_flag == 0)
                                                        {
                                                            delete_all_node();
                                                            error_flag = 1;
                                                        }
                                                        else
                                                        {
                                                            $$ = new FuncDefNode(new VarNode($2),(BlockNode*)$4); 
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        }
                                                    }
                                                } 
            ;                                               
Block: '{'   '}'             {   line("Line:%-3d",@1.first_line);
                                        debug("Block ::= {  }\n");
                                        if(error_flag == 0)
                                        {   
                                            $$ = new BlockNode(0);
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        } 

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
                                            if(error_flag == 0)
                                            {   
                                                $$ = new BlockNode((BlockItemHNode*)$2);
                                                $$->setLoc((Loc*)&(@$));
                                                all_node.push_back((Node*)$$);
                                            } 

                                        }
                                    }
            ;
BlockItemH: BlockItem             {   line("Line:%-3d",@1.first_line);
                                        debug("BlockItemH ::= BlockItem\n");
                                        if(error_flag == 0)
                                        {   
                                            $$ = new BlockItemHNode();
                                            ((BlockItemHNode*)$$)->append((BlockItemNode*)$1);
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        } 

                                    }
            | BlockItemH BlockItem  {   line("Line:%-3d",@1.first_line);
                                        debug("BlockItemH ::= BlockItemH BlockItem\n");
                                        if($2!=NULL)
                                        { 
                                            if(error_flag == 0)
                                            {   
                                                ((BlockItemHNode*)$$)->append((BlockItemNode*)$2);
                                                $$->setLoc((Loc*)&(@$));
                                            } 
                                        }

                                    }
            ;
BlockItem: Decl                  {   line("Line:%-3d",@1.first_line);
                                        debug("BlockItem ::= Decl\n");
                                        $$ = $1;
                                        $$->scope = 0;
                                    }
            | Stmt                  {   line("Line:%-3d",@$.first_line);
                                        debug("BlockItem ::= Stmt\n");
                                        $$ = $1;
                                    }
            ;
Stmt: asgn ';'              {   line("Line:%-3d",@$.first_line);
                                        debug("Stmt ::= asgn;\n");
                                        $$ = $1;
                                    }
            | var_tok '(' ')' ';'           {   
                                                line("Line:%-3d",@$.first_line);
                                                debug("Stmt ::= ident();\n");
                                                if(error_flag == 0)
                                                {   
                                                    $$ = new FuncStmtNode(new VarNode($1));
                                                    $$->setLoc((Loc*)&(@$));
                                                    all_node.push_back((Node*)$$);
                                                } 
                                            }
            | var_tok   ')' ';'             {   line("Line:%-3d",@$.first_line);debug("Stmt ::= ident'(')\n");
                                                error("%s:%3d.(%2d) left paren missing, there should be '('\n",infile_name,@$.first_line,@2.last_column-1);
                                                show_line(@$.first_line,infile_name);
                                                print_blank(@2.last_column-1);
                                               
                                                if(error_flag == 0)
                                                {   
                                                    if(error_debug_flag == 0)
                                                    {
                                                        delete_all_node();
                                                        error_flag = 1;
                                                    }
                                                    else
                                                    {
                                                        $$ = new FuncStmtNode(new VarNode($1));
                                                        $$->setLoc((Loc*)&(@$));
                                                        all_node.push_back($$);
                                                    }
                                                }
                                            }
            | var_tok '('   ';'             {   line("Line:%-3d",@$.first_line);debug("Stmt ::= ident(')'\n");
                                                error("%s:%3d.(%2d) right paren missing, there should be ')'\n",infile_name,@$.first_line,@2.last_column+1);
                                                show_line(@$.first_line,infile_name);
                                                print_blank(@2.last_column+1);
                                                if(error_flag == 0)
                                                {   
                                                    if(error_debug_flag == 0)
                                                    {
                                                        delete_all_node();
                                                        error_flag = 1;
                                                    }
                                                    else
                                                    {
                                                        $$ = new FuncStmtNode(new VarNode($1));
                                                        $$->setLoc((Loc*)&(@$));
                                                        all_node.push_back($$);
                                                    }
                                                }
                                            }
            | Block                         {   
                                                line("Line:%-3d",@$.first_line);
                                                debug("Stmt ::= Block\n");
                                                $$ = $1;
                                            }
            | if_tok '(' Cond   ')'         Stmt else_tok Stmt  {   
                                                                    line("Line:%-3d",@$.first_line);
                                                                    debug("Stmt ::= if(Cond)Stmt else Stmt\n");
                                                                    if(error_flag == 0)
                                                                    {   
                                                                        $$ = new IFELStmtNode((CondNode*)$3,(StmtNode*)$5,(StmtNode*)$7);
                                                                        $$->setLoc((Loc*)&(@$));
                                                                        all_node.push_back((Node*)$$);
                                                                    } 
                                                                }
            | if_tok '(' Cond            Stmt else_tok Stmt     {   
                                                                    line("Line:%-3d",@$.first_line);
                                                                    debug("Stmt ::= if(Cond ')' Stmt else Stmt\n");
                                                                    error("%s:%3d.(%2d) right paren missing, there should be ')'\n",infile_name,@$.first_line,@3.last_column+1);
                                                                    show_line(@$.first_line,infile_name);
                                                                    print_blank(@3.last_column+1);
                                                                    if(error_flag == 0)
                                                                    {   
                                                                        if(error_debug_flag == 0)
                                                                        {
                                                                            delete_all_node();
                                                                            error_flag = 1;
                                                                        }
                                                                        else
                                                                        {
                                                                            $$ = new IFELStmtNode((CondNode*)$3,(StmtNode*)$4,(StmtNode*)$6);
                                                                            $$->setLoc((Loc*)&(@$));
                                                                            all_node.push_back((Node*)$$);
                                                                        }
                                                                    } 
                                                                }

            | if_tok '(' Cond ')' Stmt          {   
                                                            line("Line:%-3d",@$.first_line);
                                                            debug("Stmt ::= if(Cond)Stmt\n");
                                                            if(error_flag == 0)
                                                            {   
                                                                $$ = new IFStmtNode((CondNode*)$3,(StmtNode*)$5);
                                                                $$->setLoc((Loc*)&(@$));
                                                                all_node.push_back((Node*)$$);
                                                            } 
                                                }
            | if_tok '(' Cond     Stmt          {   
                                                            line("Line:%-3d",@$.first_line);
                                                            debug("Stmt ::= if(Cond ')' Stmt\n");
                                                            error("%s:%3d.(%2d) right paren missing, there should be ')'\n",infile_name,@$.first_line,@3.last_column+1);
                                                            show_line(@$.first_line,infile_name);
                                                            print_blank(@3.last_column+1);
                                                            if(error_flag == 0)
                                                            {   
                                                                if(error_debug_flag == 0)
                                                                {
                                                                    delete_all_node();
                                                                    error_flag = 1;
                                                                }
                                                                else
                                                                {
                                                                    $$ = new IFStmtNode((CondNode*)$3,(StmtNode*)$4);
                                                                    $$->setLoc((Loc*)&(@$));
                                                                    all_node.push_back((Node*)$$);
                                                                }
                                                            } 
                                                }

            | while_tok '(' Cond ')' Stmt   {   line("Line:%-3d",@$.first_line);
                                                debug("Stmt ::= While(Cond) Stmt\n");
                                                if(error_flag == 0)
                                                {   
                                                    $$ = new WhileStmtNode((CondNode*)$3,(StmtNode*)$5);
                                                    $$->setLoc((Loc*)&(@$));
                                                    all_node.push_back((Node*)$$);
                                                } 
                                            }
            | while_tok '(' Cond     Stmt   {   line("Line:%-3d",@$.first_line);
                                                debug("Stmt ::= While(Cond ')'' Stmt\n");
                                                error("%s:%3d.(%2d) right paren missing, there should be ')'\n",infile_name,@$.first_line,@3.last_column+1);
                                                show_line(@$.first_line,infile_name);
                                                print_blank(@3.last_column+1);
                                                if(error_flag == 0)
                                                {   
                                                    if(error_debug_flag == 0)
                                                    {
                                                        delete_all_node();
                                                        error_flag = 1;
                                                    }
                                                    else
                                                    {
                                                        $$ = new WhileStmtNode((CondNode*)$3,(StmtNode*)$4);
                                                        $$->setLoc((Loc*)&(@$));
                                                        all_node.push_back((Node*)$$);
                                                    }
                                                }  
                                            }
            | break_tok ';'                 {
                                                line("Line:%-3d",@$.first_line);
                                                debug("Stmt ::= break stmt\n");
                                                if(error_flag == 0)
                                                {   
                                                    $$ = new BreakStmtNode( );
                                                    $$->setLoc((Loc*)&(@$));
                                                    all_node.push_back((Node*)$$);
                                                } 
                                            }
            | continue_tok ';'                 {
                                                line("Line:%-3d",@$.first_line);
                                                debug("Stmt ::= break stmt\n");
                                                if(error_flag == 0)
                                                {   
                                                    $$ = new ContinueStmtNode( );
                                                    $$->setLoc((Loc*)&(@$));
                                                    all_node.push_back((Node*)$$);
                                                } 
                                            }
            | ';'                           {   line("Line:%-3d",@$.first_line);
                                                debug("Stmt ::= ;\n");
                                                if(error_flag == 0)
                                                {   
                                                    $$ = new VarNode(new std::string (";"));
                                                    $$->setLoc((Loc*)&(@$));
                                                    all_node.push_back((Node*)$$);
                                                } 
                                            }
            ;
Cond: exp RelOp exp         {   line("Line:%-3d",@$.first_line);
                                        debug("Cond ::= Exp %s Exp\n",$2->c_str());
                                        if(error_flag == 0)
                                        {   
                                            $$ = new CondNode((ExpNode*)$1,new VarNode($2),(ExpNode*)$3);
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        } 
                                    }                                 

            ;


Decl: ConstDecl         {   line("Line:%-3d",@$.first_line);
                                    debug ("Decl ::= ConstDecl\n");
                                    $$ = $1;
                                }
            | VarDecl           {   line("Line:%-3d",@$.first_line);
                                    debug ("Decl ::= VarDecl\n");
                                    $$ = $1;
                                }
            ;

ConstDecl: const_tok int_tok ConstDefH  ';'  {       line("Line:%-3d",@$.first_line);
                                                        debug("ConstDecl ::= const int ConstDefH;\n");
                                                        if(error_flag == 0)
                                                        {   
                                                            $$ = new ConstDeclNode( (ConstDefHNode*)$3);
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        } 
                                                }
            | const_tok  ConstDefH  ';'         {       line("Line:%-3d",@$.first_line);
                                                        debug("ConstDecl ::= const 'int' ConstDefH;\n");
                                                        warning("%s:%3d.(%2d) type specifier missing, defaults to 'int'\n",infile_name,@$.first_line,@1.last_column+1);
                                                        show_line(@$.first_line,infile_name);
                                                        print_blank(@1.last_column+1);
                                                        if(error_flag == 0)
                                                        {   
                                                            $$ = new ConstDeclNode( (ConstDefHNode*)$2);
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        } 
                                                }
            ;                                                                      
ConstDefH: ConstDef                  {   line("Line:%-3d",@$.first_line);
                                            debug("ConstDefH ::= ConstDef\n");
                                            if(error_flag == 0)
                                            {   
                                                $$ = new ConstDefHNode();
                                                ((ConstDefHNode*)$$)->append((ConstDefNode*)$1);
                                                $$->setLoc((Loc*)&(@$));
                                                all_node.push_back((Node*)$$);
                                            } 
                                        }
            | ConstDefH ',' ConstDef    {   line("Line:%-3d",@$.first_line);
                                            debug("ConstDefH ::= ConstDefH,ConstDef\n");
                                            if($3!=NULL)
                                            {
                                                if(error_flag == 0)
                                                {   
                                                    ((ConstDefHNode*)$$)->append((ConstDefNode*)$3);
                                                    $$->setLoc((Loc*)&(@$));
                                                } 
                                            }
                                        }
            ;
ConstDef: var_tok '='  exp  {   line("Line:%-3d",@$.first_line);
                                    debug("ConstDef ::= ident = Exp\n");
                                    if(error_flag == 0)
                                    {   
                                        $$ = new AsgnNode((LValNode*)new VarNode($1),(ExpNode*)$3);
                                        $$->setLoc((Loc*)&(@$));
                                        all_node.push_back((Node*)$$);
                                    } 
                                }
            | ArrayDef          {   line("Line:%-3d",@$.first_line);
                                    debug("ConstDef ::= ArrayDef\n");
                                    $$ = $1;
                                }
            ;
ArrayDef: var_tok '[' ']' '=' '{' ExpH '}'  {   line("Line:%-3d",@$.first_line);
                                                    debug("ArrayDef ::= ident[]={ExpH}\n");
                                                    if(error_flag == 0)
                                                    {   
                                                        $$ = new ArrayDef_1_Node(new VarNode($1),(ExpHNode*)$6);
                                                        $$->setLoc((Loc*)&(@$));
                                                        all_node.push_back((Node*)$$);
                                                    } 

                                                }
            | var_tok '[' exp ']' '=' '{' ExpH '}'  {   line("Line:%-3d",@$.first_line);
                                                        debug("ArrayDef ::= ident[Exp]={ExpH}\n");
                                                        if(error_flag == 0)
                                                        {   
                                                            $$ = new ArrayDef_2_Node(new VarNode($1),(ExpNode*)$3,(ExpHNode*)$7);
                                                            $$->setLoc((Loc*)&(@$));
                                                            all_node.push_back((Node*)$$);
                                                        } 

                                                    }
            ;

VarDecl: int_tok  VarDefH ';'  {   line("Line:%-3d",@$.first_line);
                                        debug("VarDecl ::= int VarDefH ;\n");
                                        if(error_flag == 0)
                                        {   
                                            $$ = new VarDeclNode( (VarDefHNode*)$2);
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        } 

                                    }
            ;
VarDefH: VarDef                {   line("Line:%-3d",@$.first_line);
                                        debug("VarDefH ::= VarDef\n");
                                        if(error_flag == 0)
                                        {   
                                            $$ = new VarDefHNode();
                                            ((VarDefHNode*)$$)->append((VarDefNode*)$1);
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        } 
                                    }
            | VarDefH ',' VarDef    {   
                                        if($3!=NULL)
                                        {   
                                            if(error_flag == 0)
                                            {   
                                                ((VarDefHNode*)$$)->append((VarDefNode*)$3);
                                                $$->setLoc((Loc*)&(@$));
                                            } 
                                        }
                                        line("Line:%-3d",@$.first_line);
                                        debug("VarDefH ::= VarDefH,VarDef\n");
                                    }
            ;
VarDef: LVal                  {   $$ = $1;
                                        line("Line:%-3d",@$.first_line);
                                        debug("Var ::= ident\n");
                                        
                                    }
            | var_tok '=' exp       {   line("Line:%-3d",@$.first_line);
                                        debug("VarDef ::= ident=Exp\n");
                                        if(error_flag == 0)
                                        {   
                                            $$ = new AsgnNode((LValNode*)new VarNode($1),(ExpNode*)$3);
                                            $$->setLoc((Loc*)&(@$));
                                            all_node.push_back((Node*)$$);
                                        } 
                                    }
            | ArrayDef              {   line("Line:%-3d",@1.first_line);
                                        debug("VarDef ::= ArrayDef\n");
                                        $$ = $1;
                                    }
            ;

ExpH: exp           {   line("Line:%-3d",@1.first_line);
                                debug("ExpH ::= exp\n");
                                if(error_flag == 0)
                                {   
                                    $$ = new ExpHNode();
                                    ((ExpHNode*)$$)->append((ExpNode*)$1);
                                    $$->setLoc((Loc*)&(@$));
                                    all_node.push_back((Node*)$$);
                                } 
                            }
            | ExpH ',' exp  {   line("Line:%-3d",@1.first_line);
                                debug("ExpH ::= ExpH,Exp\n");
                                if($3!=NULL)
                                {
                                    if(error_flag == 0)
                                    {   
                                        ((ExpHNode*)$$)->append((ExpNode*)$3);
                                        $$->setLoc((Loc*)&(@$));
                                    } 
                                }
                            }
            ;

asgn: LVal '=' exp     {   line("Line:%-3d",@1.first_line);
                            debug ("asgn ::= LVal = exp\n");
                            if(error_flag == 0)
                            {   
                                $$ = new AsgnNode((LValNode*)$1,(ExpNode*)$3);
                                $$->setLoc((Loc*)&(@$));
                                all_node.push_back((Node*)$$);
                            } 
                        }
     ;

exp: num_tok           {   line("Line:%-3d",@1.first_line);
                            debug ("exp ::= num\n");
                            if(error_flag == 0)
                            {   
                                $$ = new NumNode ($1);
                                $$->setLoc((Loc*)&(@$));
                                all_node.push_back((Node*)$$);
                            } 
                        }
    | exp '+' exp       {   line("Line:%-3d",@1.first_line);    
                            debug ("exp ::= exp + exp\n");
                            
                            if(error_flag == 0)
                            {   
                                $$ = new BinaryExpNode ('+', (ExpNode*)$1, (ExpNode*)$3);
                                $$->setLoc((Loc*)&(@$));
                                all_node.push_back((Node*)$$);
                            } 
                        }
    | exp '-' exp       {   line("Line:%-3d",@1.first_line);
                            debug ("exp ::= exp - exp\n");
                            
                            if(error_flag == 0)
                            {   
                                $$ = new BinaryExpNode ('-', (ExpNode*)$1, (ExpNode*)$3);
                                $$->setLoc((Loc*)&(@$));
                                all_node.push_back((Node*)$$);
                            } 
                        }
    | exp '*' exp       {   line("Line:%-3d",@1.first_line);
                            debug ("exp ::= exp * exp\n");
                            
                            if(error_flag == 0)
                            {   
                                $$ = new BinaryExpNode ('*', (ExpNode*)$1, (ExpNode*)$3);
                                $$->setLoc((Loc*)&(@$));
                                all_node.push_back((Node*)$$);
                            } 
                        }
    | exp '/' exp       {   line("Line:%-3d",@1.first_line);
                            debug ("exp ::= exp / exp\n");
                            
                            if(error_flag == 0)
                            {   
                                $$ = new BinaryExpNode ('/', (ExpNode*)$1, (ExpNode*)$3);
                                $$->setLoc((Loc*)&(@$));
                                all_node.push_back((Node*)$$);
                            } 
                        }
    | exp '%' exp       {   line("Line:%-3d",@1.first_line);
                            debug ("exp ::= exp %% exp\n");
                            
                            if(error_flag == 0)
                            {   
                                $$ = new BinaryExpNode ('%', (ExpNode*)$1, (ExpNode*)$3);
                                $$->setLoc((Loc*)&(@$));
                                all_node.push_back((Node*)$$);
                            } 
                        }
    | '-' exp           {   line("Line:%-3d",@1.first_line);
                            debug ("exp ::= - exp\n");
                            
                            if(error_flag == 0)
                            {   
                                $$ = new UnaryExpNode ('-', (ExpNode*)$2);
                                $$->setLoc((Loc*)&(@$));
                                all_node.push_back((Node*)$$);
                            } 
                        }
    | '+' exp           {   line("Line:%-3d",@1.first_line);
                            debug ("exp ::= + exp\n");
                            
                            if(error_flag == 0)
                            {   
                                $$ = new UnaryExpNode ('+', (ExpNode*)$2);
                                $$->setLoc((Loc*)&(@$));
                                all_node.push_back((Node*)$$);
                            } 
                        }
    |     ExpL ')'      {   debug(")\n");
                            if(error_flag == 0)
                            {   
                                $$ = new ParenExpNode ( (ExpNode*)$1);
                                $$->setLoc((Loc*)&(@$));
                                all_node.push_back((Node*)$$);
                            } 
                        }
    |     ExpL          {   debug("')'\n");
                            error("%s:%3d.(%2d) right paren missing, there should be ')'\n",infile_name,@$.first_line,@1.last_column+1);
                            show_line(@$.first_line,infile_name);
                            print_blank(@1.last_column+1);
                            if(error_flag == 0)
                            {   
                                if(error_debug_flag == 0)
                                {
                                    delete_all_node();
                                    error_flag = 1;
                                }
                                else
                                {
                                    $$ = new ParenExpNode ( (ExpNode*)$1);
                                    $$->setLoc((Loc*)&(@$));
                                    all_node.push_back($$);
                                }
                            }
                        }
    |     exp  ')'      {   line("Line:%-3d",@$.first_line);debug("exp ::= '('exp)\n");
                            error("%s:%3d.(%2d) left paren missing, there should be '('\n",infile_name,@$.first_line,@1.first_column-1);
                            show_line(@$.first_line,infile_name);
                            print_blank(@1.first_column-1);
                            if(error_flag == 0)
                            {   
                                if(error_debug_flag == 0)
                                {
                                    delete_all_node();
                                    error_flag = 1;
                                }
                                else
                                {
                                    $$ = new ParenExpNode ( (ExpNode*)$1);
                                    $$->setLoc((Loc*)&(@$));
                                    all_node.push_back($$);
                                }
                            }
                        }
    |     exp exp       {   line("Line:%-3d",@$.first_line);debug("exp ::= exp ?? exp\n");
                            error("%s:%3d.(%2d) operator missing, there should be '+'|'-'|'*'|'/'|'%%'\n",infile_name,@$.first_line,@1.last_column+1);
                            show_line(@$.first_line,infile_name);
                            print_blank(@1.last_column+1);
                            if(error_flag == 0)
                            {   
                                if(error_debug_flag == 0)
                                {
                                    delete_all_node();
                                    error_flag = 1;
                                }
                                else
                                {
                                    $$ = new BinaryExpNode ('?', (ExpNode*)$1, (ExpNode*)$2); 
                                    $$->setLoc((Loc*)&(@$));
                                    all_node.push_back($$);
                                }
                            }
                        }
    | LVal              {   line("Line:%-3d",@$.first_line);
                            debug ("exp ::= LVal\n");
                            $$ = new LoadExpNode((LValNode*)$1);
                            all_node.push_back($$);
                        }
    ;

ExpL: '(' exp      {   line("Line:%-3d",@$.first_line);
                        debug("exp ::= (exp"); 
                        $$ = $2;
                    }
     ;
LVal: var_tok           {
                                line("Line:%-3d",@1.first_line);
                                debug ("LVal ::= ident\n");
                                if(error_flag == 0)
                                {   
                                    $$ = new VarNode($1);
                                    $$->setLoc((Loc*)&(@$));
                                    all_node.push_back((Node*)$$);
                                } 
                            }
        | var_tok '[' exp ']'   {
                                    line("Line:%-3d",@1.first_line);
                                    debug ("LVal ::= ident[Exp]\n");
                                    if(error_flag == 0)
                                    {   
                                        $$ = new ArrayLValNode(new VarNode($1),(ExpNode*)$3);
                                        $$->setLoc((Loc*)&(@$));
                                        all_node.push_back((Node*)$$);
                                    } 
                                }
        ;

%%


void yyerror (const char *msg)
{
    error ("%s", msg);
}
