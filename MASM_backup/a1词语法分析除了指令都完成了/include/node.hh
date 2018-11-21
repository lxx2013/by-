#ifndef _NODE_HH_
#define _NODE_HH_

#include <stdio.h>
#include <string>
#include <vector>
#include "dumpdot.hh"
// #include "llvm/IR/IRBuilder.h"
// #include "llvm/Analysis/Passes.h"
// #include "llvm/ExecutionEngine/ExecutionEngine.h"
// #include "llvm/ExecutionEngine/MCJIT.h"
// #include "llvm/ExecutionEngine/SectionMemoryManager.h"
// #include "llvm/IR/DataLayout.h"
// #include "llvm/IR/DerivedTypes.h"
// //#include "llvm/IR/IRBuilder.h"
// #include "llvm/IR/LLVMContext.h"
// #include "llvm/IR/Module.h"
// #include "llvm/IR/Verifier.h"
// #include "llvm/PassManager.h"
// #include "llvm/Support/TargetSelect.h"
// #include "llvm/Transforms/Scalar.h"
#include <cctype>
#include <cstdio>
#include <map>
using namespace std;
//using namespace llvm;
typedef enum {
    NUM,
    VAR,
    INPUT,
    CSTDFH,
    CSTDF,
    CSTDC,
    VARDFH,
    VARDF,
    VARDC,
    FUNCDF,
    BLK,
    BLITH,
    BLIT,
    COND,
    STMT,
    IFSTMT,
    IFELSTMT,
    FUNCSTMT,
    WHISTMT,
    EXPH,
    ARRAYDEF1,
    ARRAYDEF2,
    LINE,
    ASGN,
    ARRAYLVAL,
    VARLVAL,
    LVAL,
    EXP,
    BINARYEXP,
    PARENEXP,
    UNARYEXP
} NodeType;

typedef struct {
    int first_line;
    int first_column;
    int last_line;
    int last_column;
} Loc;

class Node {
public:
    NodeType type;
    Loc* loc;
    int scope;
    int value;
    Node() {loc = (Loc*)malloc(sizeof(Loc)); scope =0;value = 0;}
    virtual ~Node() {delete loc;}
    void setLoc(Loc* loc);
    virtual int dumpdot(DumpDOT *dumper) = 0;
    virtual int Codegen(CodeDOT *coder)=0;;
};

class ExpNode : public Node {
public:
    virtual int dumpdot(DumpDOT *dumper) = 0;
    virtual int  Codegen(CodeDOT *coder) = 0;
};

class NumNode : public ExpNode {
public:
    int val;
    NumNode(int val) : val(val) { type = EXP; value = val;};
    int dumpdot(DumpDOT *dumper);
    int  Codegen(CodeDOT *coder);
};

class VarNode : public ExpNode {
public:
    std::string *name;
    VarNode(std::string* name) : name(name) { type = VAR; };
    int dumpdot(DumpDOT *dumper);
    int  Codegen(CodeDOT *coder);
};

class BinaryExpNode : public ExpNode {
public:
    char op;
    ExpNode *lhs, *rhs;
    BinaryExpNode(char op, ExpNode *lhs, ExpNode *rhs) : op(op), lhs(lhs), rhs(rhs) { type = BINARYEXP; 
                                                                                        if(op == '+')
                                                                                            value = lhs->value + rhs->value;
                                                                                        else if(op == '-')
                                                                                            value = lhs->value - rhs->value;
                                                                                        else if(op == '*')
                                                                                            value = lhs->value * rhs->value;
                                                                                        else if(op == '/')
                                                                                            value = lhs->value / rhs->value;
                                                                                        else if(op == '%')
                                                                                            value = lhs->value % rhs->value;
                                                                                      };
    int dumpdot(DumpDOT *dumper);
    int  Codegen(CodeDOT *coder);
};

class ParenExpNode : public ExpNode {
public:
    ExpNode *exp;
    ParenExpNode(ExpNode *exp) : exp(exp) { type = PARENEXP; value = exp->value;};
    int dumpdot(DumpDOT *dumper);
    int  Codegen(CodeDOT *coder);
};

class UnaryExpNode : public ExpNode {
public:
    char op;
    ExpNode *operand;
    UnaryExpNode(char op, ExpNode *operand) : op(op), operand(operand) { type = UNARYEXP;
                                                                            if(op == '+')
                                                                                value = operand->value;
                                                                            else if(op == '-')
                                                                                value = -operand->value; };
    int dumpdot(DumpDOT *dumper);
    int  Codegen(CodeDOT *coder);
};

class LValNode : public Node{
public:
    virtual int dumpdot(DumpDOT *dumper) = 0;
    virtual int  Codegen(CodeDOT *coder) = 0;
};

class LoadExpNode : public ExpNode {
public:
    LValNode *lval;
    LoadExpNode(LValNode *lval) : lval(lval) { type = UNARYEXP; };
    int dumpdot(DumpDOT *dumper);
    int  Codegen(CodeDOT *coder);
};
class ArrayLValNode : public LValNode{
public:
    VarNode *var;
    ExpNode *exp;
    ArrayLValNode(VarNode *var, ExpNode *exp) : var(var), exp(exp) { type = ARRAYLVAL; };
    int dumpdot(DumpDOT *dumper);
    int  Codegen(CodeDOT *coder);
};
class AsgnNode : public Node {
public:
    LValNode *lval;
    ExpNode *exp;
    AsgnNode(LValNode *lval, ExpNode *exp) : lval(lval), exp(exp) { type = ASGN; };
    int dumpdot(DumpDOT *dumper);
    int Codegen(CodeDOT *coder);
};



class CompUnitNode : public Node {
public:
     virtual int dumpdot(DumpDOT *dumper) = 0;
     virtual int  Codegen(CodeDOT *coder) = 0;
};

class ConstDefNode : public Node{
public:
     virtual int dumpdot(DumpDOT *dumper) = 0;
     virtual int Codegen(CodeDOT *coder) = 0;
};

class ConstDefHNode : public Node{
public:
    std::vector<ConstDefNode*> lines;
    ConstDefHNode() {type = CSTDFH;};
    int dumpdot(DumpDOT *dumper);
    void append(ConstDefNode *line);
    int  Codegen(CodeDOT *coder);
};

class ConstDeclNode : public Node{
public:
    ConstDefHNode *cst_root;
    ConstDeclNode(ConstDefHNode * cst_root) : cst_root(cst_root) {type = CSTDC;};
    int dumpdot(DumpDOT *dumper);
    int  Codegen(CodeDOT *coder);
};

class StmtNode      : public Node{
public:
    virtual int dumpdot(DumpDOT *dumper) = 0;
    virtual int  Codegen(CodeDOT *coder) = 0;
};

class BlockItemNode : public Node{
public:
     virtual int dumpdot(DumpDOT *dumper) = 0;
     virtual int  Codegen(CodeDOT *coder) = 0;
};

class BlockItemHNode : public Node{
public:
    std::vector<BlockItemNode*> lines;
    BlockItemHNode() {type = BLITH;};
    int dumpdot(DumpDOT *dumper);
    void append(BlockItemNode *line);
    int  Codegen(CodeDOT *coder);
};

class BlockNode : public Node{
public:
    BlockItemHNode* block_root;
    BlockNode(BlockItemHNode * block_root) : block_root(block_root) {type = BLK;};
    int dumpdot(DumpDOT *dumper);
    int  Codegen(CodeDOT *coder);
};

class FuncDefNode : public Node{
public:
    VarNode   *var;
    BlockNode* block;
    FuncDefNode(VarNode   *var,BlockNode * block) : var(var),block(block) {type = FUNCDF;};
    int dumpdot(DumpDOT *dumper);
    int  Codegen(CodeDOT *coder);
};

class VarDefNode : public Node{
public:
     virtual int dumpdot(DumpDOT *dumper) = 0;
     virtual int  Codegen(CodeDOT *coder) = 0;
};

class VarDefHNode : public Node{
public:
    std::vector<VarDefNode*> lines;
    VarDefHNode() {type = VARDFH;};
    int dumpdot(DumpDOT *dumper);
    void append(VarDefNode *line);
    int  Codegen(CodeDOT *coder);
};

class VarDeclNode : public Node{
public:
    VarDefHNode *var_root;
    VarDeclNode(VarDefHNode * var_root) : var_root(var_root) {type = VARDC;};
    int dumpdot(DumpDOT *dumper);
    int  Codegen(CodeDOT *coder);
};

class ExpHNode : public Node{
public:
    std::vector<ExpNode*> lines;
    ExpHNode() {type = EXPH;};
    int dumpdot(DumpDOT *dumper);
    void append(ExpNode *line);
    int  Codegen(CodeDOT *coder);
};

class ArrayDef_1_Node : public Node{
public:
    VarNode *var;
    ExpHNode *ExpH_root;
    ArrayDef_1_Node(VarNode *var,ExpHNode *ExpH_root):var(var),ExpH_root(ExpH_root) {type=ARRAYDEF1;};
    int dumpdot(DumpDOT *dumper);
    int  Codegen(CodeDOT *coder);
};
class ArrayDef_2_Node : public Node{
public:
    VarNode *var;
    ExpNode *exp;
    ExpHNode *ExpH_root;
    ArrayDef_2_Node(VarNode *var,ExpNode *exp,ExpHNode *ExpH_root):var(var),exp(exp),ExpH_root(ExpH_root) {type=ARRAYDEF2;};
    int dumpdot(DumpDOT *dumper);
    int  Codegen(CodeDOT *coder);
};




class CondNode : public Node{
public:
    VarNode *var;
    ExpNode *lhs, *rhs;
    CondNode(ExpNode *lhs, VarNode *var, ExpNode *rhs) :  lhs(lhs), var(var),rhs(rhs) { type = COND; };
    int dumpdot(DumpDOT *dumper);
    int  Codegen(CodeDOT *coder);
};
class FuncStmtNode : public StmtNode{
public:
    VarNode *var;
    FuncStmtNode(VarNode *var) : var(var) {type= FUNCSTMT;};
    int dumpdot(DumpDOT *dumper);
    int  Codegen(CodeDOT *coder);
};

class IFELStmtNode : public StmtNode{
public:
    CondNode *cond;
    StmtNode *stmt;
    StmtNode *stmt2;
    IFELStmtNode(CondNode *cond,StmtNode *stmt,StmtNode *stmt2):cond(cond),stmt(stmt),stmt2(stmt2) {type=IFELSTMT;};
    int dumpdot(DumpDOT *dumper);
    int  Codegen(CodeDOT *coder);
};

class IFStmtNode : public StmtNode{
public:
    CondNode *cond;
    StmtNode *stmt;
    IFStmtNode(CondNode *cond,StmtNode *stmt):cond(cond),stmt(stmt) {type=IFSTMT;};
    int dumpdot(DumpDOT *dumper);
    int  Codegen(CodeDOT *coder);
};

class WhileStmtNode : public Node{
public:
    CondNode * cond;
    StmtNode * stmt;
    WhileStmtNode(CondNode * cond,StmtNode * stmt) : cond(cond),stmt(stmt) { type = WHISTMT;};
    int dumpdot(DumpDOT *dumper);
    int  Codegen(CodeDOT *coder);
};
class BreakStmtNode : public Node{
public:
    BreakStmtNode( ) { type = WHISTMT;};
    int dumpdot(DumpDOT *dumper);
    int Codegen(CodeDOT *coder);
};
class ContinueStmtNode : public Node{
public:
    ContinueStmtNode( ) { type = WHISTMT;};
    int dumpdot(DumpDOT *dumper);
    int Codegen(CodeDOT *coder);
};

class InputNode : public Node {
public:
    vector<CompUnitNode*> lines;
    InputNode() { type = INPUT; };
    int dumpdot(DumpDOT *dumper);
    void append(CompUnitNode *line);
    int  Codegen(CodeDOT *coder);
};

#endif
