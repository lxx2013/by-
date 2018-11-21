#include <stdio.h>
#include <string>
#include "node.hh"
#include "tok.hh"
// comment the next line to hide debug info
#define DEBUG
#include "util.hh"
#include "global.hh"

extern FILE *yyin;      // flex uses yyin as input file's pointer
extern int yylex();     // lexer.cc provides yylex()
extern int yyparse();   // parser.cc provides yyparse()
extern InputNode *root; // AST's root, shared with yyparse()

int main(int argc, char** argv)
{
    if (handle_opt(argc, argv) == false)
        return 0;
    yyin = infp;        // infp is initialized in handle_opt()
    yyparse();
    if (dumpfp != NULL) {
        DumpDOT *dumper = new DumpDOT(dumpfp);
        root->dumpdot(dumper);
        delete dumper;
        fclose(dumpfp);
    }
    char temp_file_name[100];
    strcpy(temp_file_name,infile_name);
    strcat(temp_file_name,".temp.c");
    if(remove(temp_file_name))
    {
        printf("%s\n","Can't delete temp file!");
        exit(0);
    }
    return 0;
}
