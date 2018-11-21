#include "node.hh"
#include "util.hh"
#include "global.hh"
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
#include <cctype>
#include <cstdio>
#include <map>
#include <string>
#include <vector>
#include "dumpdot.hh"
using namespace std;
void Node::setLoc(Loc* loc) {
    this->loc->first_line   = loc->first_line;
    this->loc->first_column = loc->first_column;
    this->loc->last_line    = loc->last_line;
    this->loc->last_column  = loc->last_column;
}

// add a new line
void InputNode::append(CompUnitNode *line) {
    lines.push_back(line);
}

void ConstDefHNode::append(ConstDefNode *line) {
    lines.push_back(line);
}

void VarDefHNode::append(VarDefNode *line) {
    lines.push_back(line);
}

void ExpHNode::append(ExpNode *line) {
    lines.push_back(line);
}

void BlockItemHNode::append(BlockItemNode *line) {
    lines.push_back(line);
}

//===----------------------------------------------------------------------===//
// Utilities in Code DOT
//===----------------------------------------------------------------------===//
int CodeDOT::getifendflag(){
    return ifendflag;
}
int CodeDOT::setifendflag(int x){
    ifendflag = x;
    return -1;
}
int CodeDOT::FindNum(string *var){
	// FILE *fp;
 //    int count;
 //    map<string,int>  NameTable; 
    if(strcmp(var->c_str(),";") == 0){
        return 0;
    }
    if(NameTable.count(*var) == 1){
    	return NameTable[*var];
    }
    else{
    	count++;
        //printf("count inc here: %d->%d,ifcount=%d,whilecount=%d\n",count-1,count,ifcount,whilecount);
    	NameTable[*var] = count;
    	return count;
    }
}
int CodeDOT::FindArray(string *var){
    if(ArrayTable.count(*var) == 1){
        return ArrayTable[*var];
    }
    else{
        printf("Find Array error!\n");
        return 0;
    }
}
int CodeDOT::FindGArray(string *var){
    if(GArrayTable.count(*var) == 1){
        return GArrayTable[*var];
    }
    else{
        return 0;
    }
}
int CodeDOT::NewG(string *var){
    GlobalTable[*var] = 0;
    return 0;
}
int CodeDOT::NewF(string *var){
    FuncTable[*var] = 0;
    return 0;
}
int CodeDOT::NewA(string *var,int x){
    ArrayTable[*var] = x;
    return 0;
}
int CodeDOT::NewGA(string *var,int x){
    GArrayTable[*var] = x;
    return 0;
}
// int CodeDOT::getscope(){
//     return scope;
// }
// int CodeDOT::setscope(int x){
//     scope = x;
//     return scope;
// }
int CodeDOT::is_exist(string *var){
    // FILE *fp;
 //    int count;
 //    map<string,int>  NameTable; 
    if(NameTable.count(*var) == 1){
        return 1;
    }
    else{
        return 0;
    }
}
int CodeDOT::is_existG(string *var){
    // FILE *fp;
 //    int count;
 //    map<string,int>  GlobalTable; 
    if(GlobalTable.count(*var) == 1){
        return 1;
    }
    else{
        return 0;
    }
}
int CodeDOT::is_existF(string *var){
    // FILE *fp;
 //    int count;
 //    map<string,int>  FuncTable; 
    if(FuncTable.count(*var) == 1){
        return 1;
    }
    else{
        return 0;
    }
}
int CodeDOT::IncCount(){
	count++;
    //printf("count inc here: %d->%d,ifcount=%d,whilecount=%d\n",count-1,count,ifcount,whilecount);

	return count;
}
int CodeDOT::ResetCount(){
    count = -1;
    NameTable.clear();
    return count;
}
int CodeDOT::incifcount(){
    ifcount++;
    return ifcount;
}
int CodeDOT::getifcount(){
    return ifcount;
}
int CodeDOT::incwhilecount(){
    whilecount++;
    return whilecount;
}
int CodeDOT::getwhilecount(){
    return whilecount;
}
FILE * CodeDOT::getfp(){
	return fp;
}

//===----------------------------------------------------------------------===//
// Utilities in Code DOT
//===----------------------------------------------------------------------===//
int NumNode::Codegen(CodeDOT *coder) {
// public:
//     int val;
//     NumNode(int val) : val(val) { type = EXP; };
//     int dumpdot(DumpDOT *dumper);
//     int  Codegen(CodeDOT *coder);
    int m = coder->IncCount();
    fprintf(coder->getfp(),"\t%%%d = add nsw i32 %d, 0\n",m,val);
    return m;
}

int VarNode::Codegen(CodeDOT *coder) {
    return coder->FindNum(name);
}
int VarDefHNode::Codegen(CodeDOT *coder){
	return -1;     //用不到此函数了
}

int BinaryExpNode::Codegen(CodeDOT *coder) {
// public:
//     char op;
//     ExpNode *lhs, *rhs;
    int nlhs = lhs->Codegen(coder);
    int nrhs = rhs->Codegen(coder);
    int nThis = coder->IncCount();
    switch(op){
        case '+':
            fprintf(coder->getfp(),"\t%%%d = add nsw i32 %%%d, %%%d\n",nThis,nlhs,nrhs);
            break;
        case '-':
            fprintf(coder->getfp(),"\t%%%d = sub nsw i32 %%%d, %%%d\n",nThis,nlhs,nrhs);
            break;
        case '*':
            fprintf(coder->getfp(),"\t%%%d = mul nsw i32 %%%d, %%%d\n",nThis,nlhs,nrhs);
            break;
        case '/':
            fprintf(coder->getfp(),"\t%%%d = sdiv i32 %%%d, %%%d\n",nThis,nlhs,nrhs);
            break;
        case '%':
            fprintf(coder->getfp(),"\t%%%d = srem i32 %%%d, %%%d\n",nThis,nlhs,nrhs);
            break;
        default:
            printf("%s\n","Binary op error!");
            exit(0);
            break;
    }
    return nThis;
}

int ParenExpNode::Codegen(CodeDOT *coder){
// public:
//     ExpNode *exp;
    int nThis = exp->Codegen(coder);
    return nThis;
}

int UnaryExpNode::Codegen(CodeDOT *coder) {
// public:
//     char op;
//     ExpNode *operand;
   // %8 = load i32* %i, align 4
  //  %sub2 = sub nsw i32 0, %8
    int nThis;
    if(op == '+'){
        nThis = operand->Codegen(coder);
    }
    else{
        nThis = operand->Codegen(coder);
        int m = coder->IncCount();
        fprintf(coder->getfp(), "\t%%%d = sub nsw i32 0, %%%d\n",m,nThis);
        nThis = m;
    }
    return nThis;
}
int LoadExpNode::Codegen(CodeDOT *coder) {
    int nLval,nThis;
    //printf("%s\n",typeid(*lval).name());
    if(strcmp(typeid(*lval).name(),"7VarNode") == 0){
        if(coder->is_existG(((VarNode*)lval)->name) ==1)
        {
            nThis = coder->IncCount();
            fprintf(coder->getfp(), "\t%%%d = load i32* @%s, align 4\n",nThis,((VarNode*)lval)->name->c_str());
        }
        else{
            nLval = ((VarNode*)lval)->Codegen(coder);
            nThis = coder->IncCount();
            fprintf(coder->getfp(), "\t%%%d = load i32* %%%d, align 4\n",nThis,nLval);
        }     
    }
    else{
        //printf("[lineno:263] %s\n",typeid(*lval).name());
        ArrayLValNode *p = (ArrayLValNode*)lval;
        if(coder->FindGArray(p->var->name) > 0)
        {
            // %0 = load i32* getelementptr inbounds ([10 x i32]* @ara, i32 0, i64 2), align 4
            // store i32 %0, i32* %c, align 4
            int size = coder->FindGArray(p->var->name);
            int address_in_array = p->exp->Codegen(coder);
            int count = coder->IncCount();
          // %idxprom = sext i32 %add to i64
          // %arrayidx = getelementptr inbounds [10 x i32]* @ara, i32 0, i64 %idxprom
          // %1 = load i32* %arrayidx, align 4
            fprintf(coder->getfp(),"\t%%%d = sext i32 %%%d to i64\n",count,address_in_array);
            int address = coder->IncCount();
            fprintf(coder->getfp(),"\t%%%d = getelementptr inbounds [%d x i32]* @%s, i32 0, i64 %%%d\n",
                                    address,size,p->var->name->c_str(),count);
            nThis = coder->IncCount();
            fprintf(coder->getfp(),"\t%%%d = load i32* %%%d, align 4\n",
                                    nThis,address);
        }
        else{
            // %0 = load i32* getelementptr inbounds ([10 x i32]* @ara, i32 0, i64 2), align 4
            // store i32 %0, i32* %c, align 4
            int size = coder->FindArray(p->var->name);
            int address_in_array = p->exp->Codegen(coder);
            int count = coder->IncCount();
          // %idxprom = sext i32 %add to i64
          // %arrayidx = getelementptr inbounds [10 x i32]* @ara, i32 0, i64 %idxprom
          // %1 = load i32* %arrayidx, align 4
            fprintf(coder->getfp(),"\t%%%d = sext i32 %%%d to i64\n",count,address_in_array);
            int address = coder->IncCount();
            fprintf(coder->getfp(),"\t%%%d = getelementptr inbounds [%d x i32]* %%%s, i32 0, i64 %%%d\n",
                                    address,size,p->var->name->c_str(),count);
            nThis = coder->IncCount();
            fprintf(coder->getfp(),"\t%%%d = load i32* %%%d, align 4\n",
                                    nThis,address);
        }
    }
    
    return nThis;
}

int AsgnNode::Codegen(CodeDOT *coder) {
	// public:
 //    LValNode *lval;
 //    ExpNode *exp;
 //    AsgnNode(LValNode *lval, ExpNode *exp) : lval(lval), exp(exp) { type = ASGN; };
 //    int dumpdot(DumpDOT *dumper);
 //    virtual int  Codegen(CodeDOT *coder);
	int nExp  = exp->Codegen(coder);
	int nLval;
    //printf("%s\n",typeid(*lval).name());
    if(strcmp(typeid(*lval).name(),"7VarNode") == 0){
        if(coder->is_existG(((VarNode*)lval)->name) ==1)
        {
            fprintf(coder->getfp(),"\tstore i32 %%%d, i32* @%s, align 4\n",nExp,((VarNode*)lval)->name->c_str());
        }
        else{
            nLval = ((VarNode*)lval)->Codegen(coder);
            fprintf(coder->getfp(),"\tstore i32 %%%d, i32* %%%d, align 4\n",nExp,nLval);
        }
    }
    else{
        //printf("[lineno:293] %s\n",typeid(*lval).name());
        ArrayLValNode *p = (ArrayLValNode*)lval;
//class ArrayLValNode : public LValNode{
// public:
//     VarNode *var;
//     ExpNode *exp;
        if(coder->FindGArray(p->var->name) > 0)
        {
            int size = coder->FindGArray(p->var->name);
            int address_in_array = p->exp->Codegen(coder);
            int count = coder->IncCount();
            // %idxprom = sext i32 %1 to i64
            //store i32 30, i32* getelementptr inbounds ([10 x i32]* @ara, i32 0, i64 1), align 4
            fprintf(coder->getfp(),"\t%%%d = sext i32 %%%d to i64\n",count,address_in_array);
            int address = coder->IncCount();
            //%arrayidx4 = getelementptr inbounds [10 x i32]* @ara, i32 0, i64 %idxprom
            fprintf(coder->getfp(),"\t%%%d = getelementptr inbounds [%d x i32]* @%s, i32 0, i64 %%%d\n",
                                    address,size,p->var->name->c_str(),count);
            fprintf(coder->getfp(),"\tstore i32 %%%d,i32* %%%d, align 4\n",
                                    nExp,address);
        }
        else{
            int size = coder->FindArray(p->var->name);
            int address_in_array = p->exp->Codegen(coder);
            int count = coder->IncCount();
            // %idxprom = sext i32 %1 to i64
            //store i32 30, i32* getelementptr inbounds ([10 x i32]* @ara, i32 0, i64 1), align 4
            fprintf(coder->getfp(),"\t%%%d = sext i32 %%%d to i64\n",count,address_in_array);
            int address = coder->IncCount();
            //%arrayidx4 = getelementptr inbounds [10 x i32]* @ara, i32 0, i64 %idxprom
            fprintf(coder->getfp(),"\t%%%d = getelementptr inbounds [%d x i32]* %%%s, i32 0, i64 %%%d\n",
                                    address,size,p->var->name->c_str(),count);
            fprintf(coder->getfp(),"\tstore i32 %%%d,i32* %%%d, align 4\n",
                                    nExp,address);
        }
    }
	
    return -1;
}
int ArrayLValNode::Codegen(CodeDOT *coder){  
    //这个函数仅仅是用来处理 int a[10];这种情况
// class ArrayLValNode : public LValNode{
// public:
//     VarNode *var;
//     ExpNode *exp;
    //printf("scope is here:%d\n",scope);
    if(scope ==1){
                int size = exp->value;
                //@ara = global [10 x i32] [i32 6, i32 7, i32 8, i32 9, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0], align 16
                fprintf(coder->getfp(), "@%s = global [%d x i32] [",var->name->c_str(),size);
                int i = 0;
                for(; i <size ;)
                {
                    i++;
                    fprintf(coder->getfp(), "i32 0");
                    if(i<size)
                    {
                        fprintf(coder->getfp(), ", ");
                    }
                }
                fprintf(coder->getfp(), "], align 16\n");
                coder->NewGA(var->name,size);
    }
    else
    {
                int size = exp->value;
                //%brb = alloca [10 x i32], align 16
                fprintf(coder->getfp(), "\t%%%s = alloca [%d x i32], align 16\n",var->name->c_str(),size);
                coder->NewA(var->name,size);
    }
    return -1;
}

int ExpHNode::Codegen(CodeDOT *coder){
// public:
//     std::vector<CExpNode*> lines;
//     ExpHNode() {type = EXPH;};
//     int Codegen(CodeDOT *coder);
//     void append(ExpNode *line);
    printf("真的调用到ExpHNode::Codegen这个函数了吗？那一定是调用错了！\n");
    return -1;
}
int ArrayDef_1_Node::Codegen(CodeDOT *coder){
// public:
//     VarNode *var;
//     ExpHNode *ExpH_root;
//     ArrayDef_1_Node(VarNode *var,ExpHNode *ExpH_root):var(var),ExpH_root(ExpH_root) {type=ARRAYDEF1;};
//     int Codegen(CodeDOT *coder);
    int size = ExpH_root->lines.size();
    //%brb = alloca [10 x i32], align 16
    fprintf(coder->getfp(), "\t%%%s = alloca [%d x i32], align 16\n",var->name->c_str(),size);
    //%arrayidx1 = getelementptr inbounds [5 x i32]* %brb, i32 0, i64 1
    //store i32 2, i32* %arrayidx1, align 4
    int count;
    int i=0;
    for(ExpNode * line : ExpH_root->lines){
        count = coder->IncCount();
        fprintf(coder->getfp(), "\t%%%d = getelementptr inbounds [%d x i32]* %%%s, i32 0, i64 %d\n",count,size,var->name->c_str(),i);
        fprintf(coder->getfp(), "\tstore i32 %d, i32* %%%d, align 4\n",line->value,count);
        i++;
    }
    coder->NewA(var->name,size);

    return -1;
}
int ArrayDef_2_Node::Codegen(CodeDOT *coder){
// public:
//     VarNode *var;
//     ExpNode *exp;
//     ExpHNode *ExpH_root;
//     ArrayDef_2_Node(VarNode *var,ExpNode *exp,ExpHNode *ExpH_root):var(var),exp(exp),ExpH_root(ExpH_root) {type=ARRAYDEF2;};
//     int Codegen(CodeDOT *coder);
    int size = exp->value;
    //%brb = alloca [10 x i32], align 16
    fprintf(coder->getfp(), "\t%%%s = alloca [%d x i32], align 16\n",var->name->c_str(),size);
    //%arrayidx1 = getelementptr inbounds [5 x i32]* %brb, i32 0, i64 1
    //store i32 2, i32* %arrayidx1, align 4
    int count;
    int i=0;
    for(ExpNode * line : ExpH_root->lines){
        count = coder->IncCount();
        fprintf(coder->getfp(), "\t%%%d = getelementptr inbounds [%d x i32]* %%%s, i32 0, i64 %d\n",count,size,var->name->c_str(),i);
        fprintf(coder->getfp(), "\tstore i32 %d, i32* %%%d, align 4\n",line->value,count);
        i++;
    }
    coder->NewA(var->name,size);

    return -1;
}
int  ConstDeclNode::Codegen(CodeDOT *coder){
// public:
//     ConstDefHNode *cst_root;
//     ConstDeclNode(ConstDefHNode * cst_root) : cst_root(cst_root) {type = CSTDC;};
//     int Codegen(CodeDOT *coder);
//   %a = alloca i32, align 4
    // if(scope == 1)
    // {  
    //      //coder->setscope(1);
    //      for (ConstDefNode* line : cst_root->lines) {
    //         if(coder->is_existG(((VarNode*)((AsgnNode*)line)->lval)->name))
    //         {
    //             printf("redefination of %s in GlobalTable\n", (((VarNode*)((AsgnNode*)line)->lval)->name)->c_str());
    //             exit(0);
    //         }
    //         coder->NewG(((VarNode*)((AsgnNode*)line)->lval)->name);
    //         //@i = global i32 0, align 4
    //         // int num = 0;
    //         // printf("%s\n", typeid(*((AsgnNode*)line)->exp).name());
    //         // if(strcmp(typeid(*((AsgnNode*)line)->exp).name(),"7NumNode")==0)
    //         // {
    //         //     num = ((NumNode*)((AsgnNode*)line)->exp)->val;
    //         // }
    //         int num = ((AsgnNode*)line)->exp->value;
    //         fprintf(coder->getfp(), "@%s = global i32 %d, align 4\n",((VarNode*)((AsgnNode*)line)->lval)->name->c_str(),num);
    //         //((VarNode*)((AsgnNode*)line)->lval)->scope = 1;
    //     }
    //      //coder->setscope(0);
    // }
    // else{
    // 	for (ConstDefNode* line : cst_root->lines) {
    //         if(coder->is_exist(((VarNode*)((AsgnNode*)line)->lval)->name))
    //         {
    //             printf("redefination of %s int NameTable\n", (((VarNode*)((AsgnNode*)line)->lval)->name)->c_str());
    //             exit(0);
    //         }
    // 		int m = coder->FindNum(((VarNode*)((AsgnNode*)line)->lval)->name);
    //         fprintf(coder->getfp(), "\t%%%d = alloca i32, align 4\n",m);
    //         line->Codegen(coder);
    //     }
    // }
    if(scope == 1)
    {  
         //coder->setscope(1);
         for (ConstDefNode* line : cst_root->lines) {
            //printf("[lineno:422] %s\n", typeid(*line).name());
            if(strcmp(typeid(*line).name(),"8AsgnNode")==0)
            {
                if(coder->is_existG(((VarNode*)((AsgnNode*)line)->lval)->name))
                {
                    printf("redefination of %%%s in GlobalTable\n", (((VarNode*)((AsgnNode*)line)->lval)->name)->c_str());
                    exit(0);
                }
                coder->NewG(((VarNode*)((AsgnNode*)line)->lval)->name);
                //@i = global i32 0, align 4
                //int num = 0;
                // printf("%s\n", typeid(*((AsgnNode*)line)->exp).name());
                // if(strcmp(typeid(*((AsgnNode*)line)->exp).name(),"7NumNode")==0)
                // {
                //     num = ((NumNode*)((AsgnNode*)line)->exp)->val;
                // }
                int num = ((AsgnNode*)line)->exp->value;
                fprintf(coder->getfp(), "@%s = global i32 %d, align 4\n",((VarNode*)((AsgnNode*)line)->lval)->name->c_str(),num);
                //((VarNode*)((AsgnNode*)line)->lval)->scope = 1;
            }
            else if(strcmp(typeid(*line).name(),"15ArrayDef_1_Node")==0)
            {
                ArrayDef_1_Node * p = (ArrayDef_1_Node*)line;
                int size = p->ExpH_root->lines.size();
                //@ara = global [10 x i32] [i32 6, i32 7, i32 8, i32 9, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0], align 16
                fprintf(coder->getfp(), "@%s = global [%d x i32] [",p->var->name->c_str(),size);
                int i = 0;
                for(ExpNode * line2 : p->ExpH_root->lines){
                    i++;
                    fprintf(coder->getfp(), "i32 %d",line2->value);
                    if(i<size){
                        fprintf(coder->getfp(), ", ");
                    }
                }
                fprintf(coder->getfp(), "], align 16\n");
                coder->NewGA(p->var->name,size);
            }
            else if(strcmp(typeid(*line).name(),"15ArrayDef_2_Node")==0)
            {
                ArrayDef_2_Node * p = (ArrayDef_2_Node*)line;
                int size = p->exp->value;
                //@ara = global [10 x i32] [i32 6, i32 7, i32 8, i32 9, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0], align 16
                fprintf(coder->getfp(), "@%s = global [%d x i32] [",p->var->name->c_str(),size);
                int i = 0;
                for(ExpNode * line2 : p->ExpH_root->lines){
                    i++;
                    fprintf(coder->getfp(), "i32 %d",line2->value);
                    if(i>size){
                        printf("给数组赋值溢出啦！\n");
                        exit(0);
                    }
                    if(i<size)
                    {
                        fprintf(coder->getfp(), ", ");
                    }
                }
                for(; i <size ;)
                {
                    i++;
                    fprintf(coder->getfp(), "i32 0");
                    if(i<size)
                    {
                        fprintf(coder->getfp(), ", ");
                    }
                }
                fprintf(coder->getfp(), "], align 16\n");
                coder->NewGA(p->var->name,size);
            }
            
        }
    }
    else{
        for (ConstDefNode* line : cst_root->lines) {
            //printf("[lineno:457] %s\n", typeid(*line).name());
            if(strcmp(typeid(*line).name(),"8AsgnNode")==0)
            {
                if(coder->is_exist(((VarNode*)((AsgnNode*)line)->lval)->name))
                {
                    printf("redefination of %%%s in NameTable\n", (((VarNode*)((AsgnNode*)line)->lval)->name)->c_str());
                    exit(0);
                }
                int m = coder->FindNum(((VarNode*)((AsgnNode*)line)->lval)->name);
                fprintf(coder->getfp(), "\t%%%d = alloca i32, align 4\n",m);
                line->Codegen(coder);
            }
            else if(strcmp(typeid(*line).name(),"15ArrayDef_1_Node")==0)
            {
                line->Codegen(coder);
            }
            else if(strcmp(typeid(*line).name(),"15ArrayDef_2_Node")==0)
            {
                line->Codegen(coder);
            }
        }
    }
    return 0;
}
int ConstDefHNode::Codegen(CodeDOT *coder){
// public:
//     std::vector<ConstDefNode*> lines;
//     ConstDefHNode() {type = CSTDFH;};
//     int dumpdot(DumpDOT *dumper);
//     void append(ConstDefNode *line);
    for (ConstDefNode* line : lines) {
       line->Codegen(coder);
    }
    return -1;
    //用不到这个函数了
}
int  VarDeclNode::Codegen(CodeDOT *coder){
// public:
//     VarDefHNode *var_root;
//     VarDeclNode(VarDefHNode * var_root) : var_root(var_root) {type = VARDC;};
//     int Codegen(CodeDOT *coder);
    if(scope == 1)
    {  
         //coder->setscope(1);
         for (VarDefNode* line : var_root->lines) {
            //printf("[lineno:422] %s\n", typeid(*line).name());
            if(strcmp(typeid(*line).name(),"8AsgnNode")==0)
            {
                if(coder->is_existG(((VarNode*)((AsgnNode*)line)->lval)->name))
                {
                    printf("redefination of %%%s in GlobalTable\n", (((VarNode*)((AsgnNode*)line)->lval)->name)->c_str());
                    exit(0);
                }
                coder->NewG(((VarNode*)((AsgnNode*)line)->lval)->name);
                //@i = global i32 0, align 4
                //int num = 0;
                // printf("%s\n", typeid(*((AsgnNode*)line)->exp).name());
                // if(strcmp(typeid(*((AsgnNode*)line)->exp).name(),"7NumNode")==0)
                // {
                //     num = ((NumNode*)((AsgnNode*)line)->exp)->val;
                // }
                int num = ((AsgnNode*)line)->exp->value;
                fprintf(coder->getfp(), "@%s = global i32 %d, align 4\n",((VarNode*)((AsgnNode*)line)->lval)->name->c_str(),num);
                //((VarNode*)((AsgnNode*)line)->lval)->scope = 1;
            }
            else if(strcmp(typeid(*line).name(),"15ArrayDef_1_Node")==0)
            {
                ArrayDef_1_Node * p = (ArrayDef_1_Node*)line;
                int size = p->ExpH_root->lines.size();
                //@ara = global [10 x i32] [i32 6, i32 7, i32 8, i32 9, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0], align 16
                fprintf(coder->getfp(), "@%s = global [%d x i32] [",p->var->name->c_str(),size);
                int i = 0;
                for(ExpNode * line2 : p->ExpH_root->lines){
                    i++;
                    fprintf(coder->getfp(), "i32 %d",line2->value);
                    if(i<size){
                        fprintf(coder->getfp(), ", ");
                    }
                }
                fprintf(coder->getfp(), "], align 16\n");
                coder->NewGA(p->var->name,size);
            }
            else if(strcmp(typeid(*line).name(),"15ArrayDef_2_Node")==0)
            {
                ArrayDef_2_Node * p = (ArrayDef_2_Node*)line;
                int size = p->exp->value;
                //@ara = global [10 x i32] [i32 6, i32 7, i32 8, i32 9, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0], align 16
                fprintf(coder->getfp(), "@%s = global [%d x i32] [",p->var->name->c_str(),size);
                int i = 0;
                for(ExpNode * line2 : p->ExpH_root->lines){
                    i++;
                    fprintf(coder->getfp(), "i32 %d",line2->value);
                    if(i>size){
                        printf("给数组赋值溢出啦！\n");
                        exit(0);
                    }
                    if(i<size)
                    {
                        fprintf(coder->getfp(), ", ");
                    }
                }
                for(; i <size ;)
                {
                    i++;
                    fprintf(coder->getfp(), "i32 0");
                    if(i<size)
                    {
                        fprintf(coder->getfp(), ", ");
                    }
                }
                fprintf(coder->getfp(), "], align 16\n");
                coder->NewGA(p->var->name,size);
            }
            else if(strcmp(typeid(*line).name(),"7VarNode")==0){
                VarNode* p = (VarNode*)line;
                coder->NewG(p->name);
                fprintf(coder->getfp(), "\t@%s = alloca i32, align 4\n",p->name->c_str());
            }
            else if(strcmp(typeid(*line).name(),"13ArrayLValNode")==0){
                ArrayLValNode* p = (ArrayLValNode*)line;
                p->scope = 1;
                p->Codegen(coder);
            }
            else
            {
                printf("这个声明很奇怪，不属于已知类型\n");
            }
        }

        //coder->setscope(0);
    }
    else{
        for (VarDefNode* line : var_root->lines) {
            //printf("[lineno:457] %s\n", typeid(*line).name());
            if(strcmp(typeid(*line).name(),"8AsgnNode")==0)
            {
                if(coder->is_exist(((VarNode*)((AsgnNode*)line)->lval)->name))
                {
                    printf("redefination of %%%s in NameTable\n", (((VarNode*)((AsgnNode*)line)->lval)->name)->c_str());
                    exit(0);
                }
                int m = coder->FindNum(((VarNode*)((AsgnNode*)line)->lval)->name);
                fprintf(coder->getfp(), "\t%%%d = alloca i32, align 4\n",m);
                line->Codegen(coder);
            }
            else if(strcmp(typeid(*line).name(),"15ArrayDef_1_Node")==0)
            {
                line->Codegen(coder);
            }
            else if(strcmp(typeid(*line).name(),"15ArrayDef_2_Node")==0)
            {
                line->Codegen(coder);
            }
            else if(strcmp(typeid(*line).name(),"7VarNode")==0){
                VarNode* p = (VarNode*)line;
                int m = coder->FindNum(p->name);
                fprintf(coder->getfp(), "\t%%%d = alloca i32, align 4\n",m);
            }
            else if(strcmp(typeid(*line).name(),"13ArrayLValNode")==0){
                ArrayLValNode* p = (ArrayLValNode*)line;
                p->scope = 0;
                p->Codegen(coder);
            }
            else
            {
                printf("这个声明很奇怪，不属于已知类型\n");
            }
        }
    }
    
    return 0;
}

int  FuncDefNode::Codegen(CodeDOT *coder){
// public:
//     VarNode   *var;
//     BlockNode* block;
//     FuncDefNode(BlockNode * block) : block(block) {type = FUNCDF;};
//     int Codegen(CodeDOT *coder);
    fprintf(coder->getfp(),"\n; Function Attrs: nounwind\n");
    fprintf(coder->getfp(),"define void @%s () #0 {\nentry:\n",var->name->c_str());
    coder->NewF(var->name);
    block->Codegen(coder);
    fprintf(coder->getfp(),"\tret void\n");
    fprintf(coder->getfp(),"}\n");
    coder->ResetCount();
    return 0;
}
int BlockNode::Codegen(CodeDOT *coder){
// public:
//     BlockItemHNode* block_root;
//     BlockNode(BlockItemHNode * block_root) : block_root(block_root) {type = BLK;};
//     int Codegen(CodeDOT *coder);
    for (BlockItemNode* line : block_root->lines) {
            line->Codegen(coder);
        }
    return 0;
}
int BlockItemHNode::Codegen(CodeDOT *coder){
// public:
//     std::vector<BlockItemNode*> lines;
//     BlockItenHNode() {type = BLITH;};
//     int Codegen(CodeDOT *coder);
//     void append(BlockItemNode *line);
    for (BlockItemNode* line : lines) {
        line->Codegen(coder);
    }
    return 0;
}
int FuncStmtNode::Codegen(CodeDOT *coder){
// class FuncStmtNode : public StmtNode{
// public:
//     VarNode *var;
//     FuncStmtNode(VarNode *var) : var(var) {type= FUNCSTMT};
//     int Codegen(CodeDOT *coder);
// };
    //call void @fib()
    if(coder->is_existF(var->name) == 0){
        fprintf(coder->getfp(), "\tcall void (...)* @%s()\n",var->name->c_str());
    }
    else{
        fprintf(coder->getfp(), "\tcall void @%s()\n",var->name->c_str());
    }
    return -1;
}
int IFELStmtNode::Codegen(CodeDOT *coder){
// class IFELStmtNode : public StmtNode{
// public:
//     CondNode *cond;
//     StmtNode *stmt;
//     StmtNode *stmt2;
//     IFELStmtNode(CondNode *cond,StmtNode *stmt,StmtNode *stmt2):cond(cond),stmt(stmt),stmt2(stmt2) {type=IFELSTMT;};
//     int Codegen(CodeDOT *coder);
// };
    int count = coder->incifcount();
    int m = cond->Codegen(coder);
    fprintf(coder->getfp(), "\tbr i1 %%%d, label %%if.then%d, label %%if.else%d\n",m,count,count);
    fprintf(coder->getfp(), "\nif.then%d: \n",count);
    stmt->Codegen(coder);
    if(coder->getifendflag() == 0)
        fprintf(coder->getfp(), "\tbr label %%if.end%d \n",count);
    fprintf(coder->getfp(), "\nif.else%d: \n",count);
    coder->setifendflag(0);
    stmt2->Codegen(coder);
    if(coder->getifendflag() == 0)
        fprintf(coder->getfp(), "\tbr label %%if.end%d \n",count);
    fprintf(coder->getfp(), "\nif.end%d: \n",count);
    coder->setifendflag(0);
    return -1;
}
int IFStmtNode::Codegen(CodeDOT *coder){
//class IFStmeNode : public StmtNode{
// public:
//     CondNode *cond;
//     StmtNode *stmt;
//     IFStmtNode(CondNode *cond,StmtNode *stmt):cond(cond),stmt(stmt) {type=IFELSTMT;};
//     int Codegen(CodeDOT *coder);
// };
    int count = coder->incifcount();
    int m = cond->Codegen(coder);
    fprintf(coder->getfp(), "\tbr i1 %%%d, label %%if.then%d, label %%if.end%d\n",m,count,count);
    fprintf(coder->getfp(), "\nif.then%d: \n",count);
    stmt->Codegen(coder);
    int flag = coder->getifendflag();
    if(flag == 0)
    {
     fprintf(coder->getfp(), "\tbr label %%if.end%d \n",count);
    }
    fprintf(coder->getfp(), "\nif.end%d: \n",count);
    coder->setifendflag(0);
    return -1;
}

int CondNode::Codegen(CodeDOT *coder){
// class RelOpCondNode : public CondNode{
// public:
//     VarNode *var;
//     ExpNode *lhs, *rhs;
//     RelOpCondNode(VarNode *var, ExpNode *lhs, ExpNode *rhs) : var(var), lhs(lhs), rhs(rhs) { type = RELC; };
//     int Codegen(CodeDOT *coder);
// };
    int nlhs = lhs->Codegen(coder);
    int nrhs = rhs->Codegen(coder);
    //%cmp = icmp slt i32 %2, 0
    int m = coder->IncCount();
    if(strcmp("<",var->name->c_str()) == 0)
        fprintf(coder->getfp(), "\t%%%d = icmp slt i32 %%%d, %%%d\n",m,nlhs,nrhs);
    else if(strcmp(">",var->name->c_str()) == 0){
        fprintf(coder->getfp(), "\t%%%d = icmp sgt i32 %%%d, %%%d\n",m,nlhs,nrhs);
    }
    else if(strcmp("<=",var->name->c_str()) == 0){
        fprintf(coder->getfp(), "\t%%%d = icmp sle i32 %%%d, %%%d\n",m,nlhs,nrhs);
    }
    else if(strcmp(">=",var->name->c_str()) == 0){
        fprintf(coder->getfp(), "\t%%%d = icmp sge i32 %%%d, %%%d\n",m,nlhs,nrhs);
    }
    else if(strcmp("==",var->name->c_str()) == 0){
        fprintf(coder->getfp(), "\t%%%d = icmp eq i32 %%%d, %%%d\n",m,nlhs,nrhs);
    }
    else if(strcmp("!=",var->name->c_str()) == 0){
        fprintf(coder->getfp(), "\t%%%d = icmp ne i32 %%%d, %%%d\n",m,nlhs,nrhs);
    }
    else{
        printf("RelOp error! at coder->ifcount:%d or whilecount:%d\n",coder->getifcount(),coder->getwhilecount());
    }
    return m;
}
int WhileStmtNode::Codegen(CodeDOT *coder){
// class WhileStmtNode : public Node{
// public:
//     CondNode * cond;
//     StmtNode * stmt;
//     WhileStmtNode(CondNode * cond,StmtNode * stmt) : cond(cond),stmt(stmt) { type = WHISTMT};
//     int Codegen(CodeDOT *coder);
// };
    int count = coder->incwhilecount();
    fprintf(coder->getfp(), "\tbr label %%while.cond%d \n",count);
    fprintf(coder->getfp(), "\nwhile.cond%d: \n",count);
    int m = cond->Codegen(coder);
    fprintf(coder->getfp(), "\tbr i1 %%%d, label %%while.body%d, label %%while.end%d\n",m,count,count);
    fprintf(coder->getfp(), "\nwhile.body%d: \n",count);
    stmt->Codegen(coder);
    fprintf(coder->getfp(), "\tbr label %%while.cond%d \n",count);
    fprintf(coder->getfp(), "\nwhile.end%d: \n",count);
    if(coder->getifendflag() == 1)
        coder->setifendflag(0);
    return -1;
}
int BreakStmtNode::Codegen(CodeDOT *coder){
// class WhileStmtNode : public Node{
// public:
//     CondNode * cond;
//     StmtNode * stmt;
//     WhileStmtNode(CondNode * cond,StmtNode * stmt) : cond(cond),stmt(stmt) { type = WHISTMT};
//     int Codegen(CodeDOT *coder);
// };
    int count = coder->getwhilecount();
    fprintf(coder->getfp(), "\tbr label %%while.end%d \n",count);
    coder->setifendflag(1);
    return -1;
}
int ContinueStmtNode::Codegen(CodeDOT *coder){
// class WhileStmtNode : public Node{
// public:
//     CondNode * cond;
//     StmtNode * stmt;
//     WhileStmtNode(CondNode * cond,StmtNode * stmt) : cond(cond),stmt(stmt) { type = WHISTMT};
//     int Codegen(CodeDOT *coder);
// };
    int count = coder->getwhilecount();
    fprintf(coder->getfp(), "\tbr label %%while.cond%d \n",count);
    coder->setifendflag(1);
    return -1;
}
int InputNode::Codegen(CodeDOT *coder) {
	
    for (CompUnitNode* line : lines) {
        line->Codegen(coder);
    }
	return -1;
}



