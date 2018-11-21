#ifndef _DUMPDOT_HH_
#define _DUMPDOT_HH_

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>
#include "global.hh"
using namespace std;
class DumpDOT {
    FILE *fp;
    int count;
public:
    DumpDOT(FILE *fp) : fp(fp) {
        fprintf(fp, "digraph {\n");
        fprintf(fp, "    node [shape = record];\n");
        count = 0;
    }
    ~DumpDOT() { fprintf(fp, "}"); }
    int newNode(int num, ...);
    int newNode(std::vector<std::string> list);
    void drawLine(int nSrc, int fSrc, int nDst);
};
class CodeDOT {
    FILE *fp;
    int count;
    int ifcount;
    int whilecount;
    int ifendflag;
    //int scope;
    map<string,int>  NameTable; 
    map<string,int>  GlobalTable;
    map<string,int>  FuncTable;
    map<string,int>  ArrayTable;
    map<string,int> GArrayTable;
public:
    CodeDOT(FILE *fp) : fp(fp) {
        fprintf(fp,";ModuleID = '%s'\n",infile_name);
        fprintf(fp,"target datalayout =");
        fprintf(fp,"%se-m:o-i64:64-f80:128-n8:16:32:64-S128%s\ntarget triple = %sx86_64-apple-darwin14.4.0%s\n\n","\"","\"","\"","\"");
        //@Output = external global i32
        fprintf(fp,"@Output = external global i32\n");
        fprintf(fp,"@Input = external global i32\n");
        count = -1;
        ifcount = 0;
        whilecount = 0;
        ifendflag = 0;
        string *str= new std::string("Output");
        //printf("%s\n",str->c_str());
        NewG(str);
        str = new std::string("Input");
        //printf("%s\n",str->c_str());
        NewG(str);
    }
    ~CodeDOT() {
        fprintf(fp,"declare void @print(...)\n");
        fprintf(fp,"declare void @scan(...)\n");
        fprintf(fp,"\n\n\nattributes #0 = { nounwind \"less-precise-fpmad\"=\"false\""); 
        fprintf(fp,"\"no-frame-pointer-elim\"=\"false\""); 
        fprintf(fp,"\"no-infs-fp-math\"=\"false\""); 
        fprintf(fp,"\"no-nans-fp-math\"=\"false\" "); 
        fprintf(fp,"\"no-realign-stack\""); 
        fprintf(fp,"\"stack-protector-buffer-size\"=\"8\""); 
        fprintf(fp,"\"unsafe-fp-math\"=\"false\" "); 
        fprintf(fp,"\"use-soft-float\"=\"false\" }\n");
        fprintf(fp,"!llvm.ident = !{!0}\n");
        fprintf(fp,"!0 = !{!\"clang version 3.6.2 (branches/release_36 254714)\"}\n");

     }
    int FindNum(string *var);
    int FindArray(string *var);
    int FindGArray(string *var);
    int is_exist(string *var);
    int is_existG(string *var);
    int is_existF(string *var);
    int NewF(string *var);
    int NewG(string *var);
    int NewA(string *var,int x);
    int NewGA(string *var,int x);
    int IncCount();
    int ResetCount();
    int getifcount();
    int incifcount();
    int getifendflag();
    int setifendflag(int x);
    int getwhilecount();
    int incwhilecount();
    //int getscope();
    //int setscope(int x);
    FILE* getfp();
};

#endif
