#include <stdio.h>
#include <string>
#include "node.hh"
#include "tok.hh"
// #include "llvm/Analysis/Passes.h"
// #include "llvm/ExecutionEngine/ExecutionEngine.h"
// #include "llvm/ExecutionEngine/MCJIT.h"
// #include "llvm/ExecutionEngine/SectionMemoryManager.h"
// #include "llvm/IR/DataLayout.h"
// #include "llvm/IR/DerivedTypes.h"
// #include "llvm/IR/IRBuilder.h"
// #include "llvm/IR/LLVMContext.h"
// #include "llvm/IR/Module.h"
// #include "llvm/IR/Verifier.h"
// #include "llvm/PassManager.h"
// #include "llvm/Support/TargetSelect.h"
// #include "llvm/Transforms/Scalar.h"
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
    if (dumpfp != NULL && root !=NULL) {
        DumpDOT *dumper = new DumpDOT(dumpfp);
        root->dumpdot(dumper);
        delete dumper;
        fclose(dumpfp);
    }
    /////////
//===----------------------------------------------------------------------===//
// Code Generation
//===----------------------------------------------------------------------===//

    if(dumpfp != NULL && root != NULL){
        CodeDOT *coder = new CodeDOT(codefp);
        root->Codegen(coder);
        delete coder;
        fclose(codefp);
    }
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
