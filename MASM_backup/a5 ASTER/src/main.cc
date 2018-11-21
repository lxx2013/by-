#include <stdio.h>
#include <string>
#include "node.hh"
#include "tok.hh"
#define DEBUG
#include "util.hh"
#include "global.hh"

extern FILE *yyin;      // flex uses yyin as input file's pointer
extern int yylex();     // lexer.cc provides yylex()
extern int yyparse();   // parser.cc provides yyparse()
extern InputNode *root; // AST's root, shared with yyparse()
extern GlobalNode *global; // AST's root, shared with yyparse()
int main(int argc, char** argv)
{
    if (handle_opt(argc, argv) == false)
        return 0;
    yyin = infp;        // infp is initialized in handle_opt()
    yyparse();
    if (dumpfp != NULL && root !=NULL) {
        DumpDOT *dumper = new DumpDOT(dumpfp);
        root->dumpdot(dumper);
        delete dumper;
        fclose(dumpfp);
    }
    if (callfp != NULL && root !=NULL) {
        CallDOT *caller = new CallDOT(callfp);
        root->calldot(caller);
        delete caller;
        fclose(callfp);
    }
    /////////
//===----------------------------------------------------------------------===//
// Code Generation
//===----------------------------------------------------------------------===//


//===----------------------------------------------------------------------===//
// Code Generation End
//===----------------------------------------------------------------------===//
    char temp_file_name[100];
    strcpy(temp_file_name,infile_name);
    strcat(temp_file_name,".temp.asm");
    if(remove(temp_file_name))
    {
        printf("%s\n","Can't delete temp file!");
        exit(0);
    }
    return 0;
}
