#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include "node.hh"
#include "dumpdot.hh"

//===----------------------------------------------------------------------===//
// Utilities in Dump DOT
//===----------------------------------------------------------------------===//

// There are two ways to create a dot node:
// 1. newNode(num, str1, str2, ...)
//    num corresponds to the number of strings
//    Each string will appear in the generated image as a port
//    All strings are char*
// 2. newNode(vec)
//    All elements of the vector are std::string
// newNode returns an integer, which is the number of the corresponding
// node in DOT file.

int DumpDOT::newNode(int num, ...) {
    va_list list;
    va_start(list, num);
    fprintf(fp, "    %d [label = \"", count);
    bool first = true;
    for (int i=0; i<num; i++) {
        char* st = va_arg(list, char*);
        if (!first)
            fprintf(fp, "|");
        first = false;
        if (st[0]=='<')
            fprintf(fp, "<%d> \\<", i);
        else
            fprintf(fp, "<%d> %s", i, st);
    }
    va_end(list);
    fprintf(fp, "\"];\n");
    return count++;
}

int DumpDOT::newNode(std::vector<std::string> list) {
    fprintf(fp, "    %d [label = \"", count);
    bool first = true;
    for (int i=0; i<list.size(); i++) {
        std::string st = list[i];
        if (!first)
            fprintf(fp, "|");
        first = false;
        fprintf(fp, "<%d> %s", i, st.c_str());
    }
    fprintf(fp, "\"];\n");
    return count++;
}

// Draw a line from nSrc node's pSrc port to nDst node.
// If you want it start from the whole node, let pSrc = -1

void DumpDOT::drawLine(int nSrc, int pSrc, int nDst) {
    fprintf(fp, "    %d", nSrc);
    if (pSrc>=0)
        fprintf(fp, ":%d", pSrc);
    fprintf(fp, " -> %d;\n", nDst);
}

//===----------------------------------------------------------------------===//
// Dump AST to DOT
//===----------------------------------------------------------------------===//

// The following functions convert AST to DOT using DumpDOT.
// Each dumpdot returns an integer, which is corresponding number in DOT file.
// 53+29*71 will become:
// digraph {
// node [shape = record];
//     0 [label = "<0> |<1> +|<2> "];
//     1 [label = "<0> 53"];
//     2 [label = "<0> |<1> *|<2> "];
//     3 [label = "<0> 29"];
//     4 [label = "<0> 71"];
//     0:0 -> 1;
//     0:2 -> 2;
//     2:0 -> 3;
//     2:2 -> 4;
// }

int NumNode::dumpdot(DumpDOT *dumper) {
    std::ostringstream strs;
    strs << val;
    int nThis = dumper->newNode(1, strs.str().c_str());
    return nThis;
}

int VarNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(1, name->c_str());
    return nThis;
}

int BinaryExpNode::dumpdot(DumpDOT *dumper) {
    char st[2] = " ";
    st[0] = op;
    int nThis = dumper->newNode(3, " ", st, " ");
    int nlhs = lhs->dumpdot(dumper);
    int nrhs = rhs->dumpdot(dumper);
    dumper->drawLine(nThis, 0, nlhs);
    dumper->drawLine(nThis, 2, nrhs);
    return nThis;
}

int ParenExpNode::dumpdot(DumpDOT *dumper){
    int nThis = dumper->newNode(3,"("," ",")");
    int nexp = exp->dumpdot(dumper);
    dumper->drawLine(nThis,1,nexp);
    return nThis;
}

int UnaryExpNode::dumpdot(DumpDOT *dumper) {
    char st[2] = " ";
    st[0] = op;
    int nThis = dumper->newNode(2, st, " ");
    int nOperand = operand->dumpdot(dumper);
    dumper->drawLine(nThis, 1, nOperand);
    return nThis;
}

int AsgnNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(3, " ", "="," ");
    int nLVal = lval->dumpdot(dumper);
    int nExp = exp->dumpdot(dumper);
    dumper->drawLine(nThis, 0, nLVal);
    dumper->drawLine(nThis, 2, nExp);
    return nThis;
}
int ArrayLValNode::dumpdot(DumpDOT *dumper){  
    int nThis = dumper->newNode(4,var->name->c_str(),"["," ","]");
    int nExp = exp->dumpdot(dumper);
    dumper->drawLine(nThis, 2, nExp);   
    return nThis;
}




int ConstDefHNode::dumpdot(DumpDOT *dumper){
// public:
//     std::vector<ConstDefNode*> lines;
//     ConstDefHNode() {type = CSTDFH;};
//     int dumpdot(DumpDOT *dumper);
//     void append(ConstDefNode *line);
    std::ostringstream strs;
    strs << lines.size() << " ConstDefs";
    int nThis = dumper->newNode(1, strs.str().c_str());
    for (ConstDefNode* line : lines) {
        int nLine = line->dumpdot(dumper);
        dumper->drawLine(nThis, 0, nLine);
    }
    return nThis;
}

int VarDefHNode::dumpdot(DumpDOT *dumper){
    std::ostringstream strs;
    strs << lines.size() << " VarDefs";
    int nThis = dumper->newNode(1, strs.str().c_str());
    for (VarDefNode* line : lines) {
        int nLine = line->dumpdot(dumper);
        dumper->drawLine(nThis, 0, nLine);
    }
    return nThis;
}

int ExpHNode::dumpdot(DumpDOT *dumper){
// public:
//     std::vector<CExpNode*> lines;
//     ExpHNode() {type = EXPH;};
//     int dumpdot(DumpDOT *dumper);
//     void append(ExpNode *line);
    std::ostringstream strs;
    strs << lines.size() << " Exps";
    int nThis = dumper->newNode(1, strs.str().c_str());
    for (ExpNode* line : lines) {
        int nLine = line->dumpdot(dumper);
        dumper->drawLine(nThis, 0, nLine);
    }
    return nThis;
}
int ArrayDef_1_Node::dumpdot(DumpDOT *dumper){
// public:
//     VarNode *var;
//     ExpHNode *ExpH_root;
//     ArrayDef_1_Node(VarNode *var,ExpHNode *ExpH_root):var(var),ExpH_root(ExpH_root) {type=ARRAYDEF1;};
//     int dumpdot(DumpDOT *dumper);
    std::ostringstream strs;
    strs << ExpH_root->lines.size() << " Exps";
    int nThis = dumper->newNode(7,var->name->c_str(),"[","]","=","\\{",strs.str().c_str(),"\\}");
    for (ExpNode* line : ExpH_root->lines) {
        int nLine = line->dumpdot(dumper);
        dumper->drawLine(nThis, 5, nLine);
    }
    return nThis;
}
int ArrayDef_2_Node::dumpdot(DumpDOT *dumper){
// public:
//     VarNode *var;
//     ExpNode *exp;
//     ExpHNode *ExpH_root;
//     ArrayDef_2_Node(VarNode *var,ExpNode *exp,ExpHNode *ExpH_root):var(var),exp(exp),ExpH_root(ExpH_root) {type=ARRAYDEF2;};
//     int dumpdot(DumpDOT *dumper);

    std::ostringstream strs;
    strs << ExpH_root->lines.size() << " Exps";
    int nThis = dumper->newNode(8,var->name->c_str(),"["," ","]","=","\\{",strs.str().c_str(),"\\}");
    int nExp = exp->dumpdot(dumper);
    dumper->drawLine(nThis,2,nExp);
    for (ExpNode* line : ExpH_root->lines) {
        int nLine = line->dumpdot(dumper);
        dumper->drawLine(nThis, 6, nLine);
    }
    return nThis;

    
}
int  ConstDeclNode::dumpdot(DumpDOT *dumper){
// public:
//     ConstDefHNode *cst_root;
//     ConstDeclNode(ConstDefHNode * cst_root) : cst_root(cst_root) {type = CSTDC;};
//     int dumpdot(DumpDOT *dumper);
    std::ostringstream strs;
    strs << cst_root->lines.size() << " ConstDefs"; 
    int nThis = dumper->newNode(3,"const","int",strs.str().c_str());
    for (ConstDefNode* line : cst_root->lines) {
        int nLine = line->dumpdot(dumper);
        dumper->drawLine(nThis, 2, nLine);
    }
    return nThis;
}

int  VarDeclNode::dumpdot(DumpDOT *dumper){
// public:
//     VarDefHNode *var_root;
//     VarDeclNode(VarDefHNode * var_root) : var_root(var_root) {type = VARDC;};
//     int dumpdot(DumpDOT *dumper);
    std::ostringstream strs;
    strs << var_root->lines.size() << " VarDefs"; 
    int nThis = dumper->newNode(2,"int",strs.str().c_str());
    for (VarDefNode* line : var_root->lines) {
        int nLine = line->dumpdot(dumper);
        dumper->drawLine(nThis, 1, nLine);
    }
    return nThis;
}

int  FuncDefNode::dumpdot(DumpDOT *dumper){
// public:
//     VarNode   *var;
//     BlockNode* block;
//     FuncDefNode(BlockNode * block) : block(block) {type = FUNCDF;};
//     int dumpdot(DumpDOT *dumper);
    int nThis;
    if(block->block_root == NULL)
    {
        nThis = dumper->newNode(4,"void",var->name->c_str(),"( )","\\{ \\}");
    }
    else
    {
        std::ostringstream strs;
        strs << block->block_root->lines.size() << " BlockItems"; 
        nThis = dumper->newNode(6,"void",var->name->c_str(),"( )","\\{",strs.str().c_str(),"\\}");
        for (BlockItemNode* line : block->block_root->lines) {
            int nLine = line->dumpdot(dumper);
            dumper->drawLine(nThis, 4, nLine);
        }
    }
    return nThis;
}
int BlockNode::dumpdot(DumpDOT *dumper){
// public:
//     BlockItemHNode* block_root;
//     BlockNode(BlockItemHNode * block_root) : block_root(block_root) {type = BLK;};
//     int dumpdot(DumpDOT *dumper);
    int nThis;
    if(block_root == NULL)
    {
        nThis = dumper->newNode(1,"\\{ \\}");
    }
    else
    {
        std::ostringstream strs;
        strs << block_root->lines.size() << " BlockItems"; 
        nThis = dumper->newNode(3,"\\{",strs.str().c_str(),"\\}");
        for (BlockItemNode* line : block_root->lines) {
            int nLine = line->dumpdot(dumper);
            dumper->drawLine(nThis, 1, nLine);
        }
    }
    return nThis;
}
int BlockItemHNode::dumpdot(DumpDOT *dumper){
// public:
//     std::vector<BlockItemNode*> lines;
//     BlockItenHNode() {type = BLITH;};
//     int dumpdot(DumpDOT *dumper);
//     void append(BlockItemNode *line);
    std::ostringstream strs;
    strs << lines.size() << " BlockItems"; 
    int nThis = dumper->newNode(3,"\\{",strs.str().c_str(),"\\}");
    for (BlockItemNode* line : lines) {
        int nLine = line->dumpdot(dumper);
        dumper->drawLine(nThis, 1, nLine);
    }
    return nThis;
}
int FuncStmtNode::dumpdot(DumpDOT *dumper){
// class FuncStmtNode : public StmtNode{
// public:
//     VarNode *var;
//     FuncStmtNode(VarNode *var) : var(var) {type= FUNCSTMT};
//     int dumpdot(DumpDOT *dumper);
// };
    int nThis = dumper->newNode(2,var->name->c_str()," (  ) ;");
    return nThis;
}
int IFELStmtNode::dumpdot(DumpDOT *dumper){
// class IFELStmtNode : public StmtNode{
// public:
//     CondNode *cond;
//     StmtNode *stmt;
//     StmtNode *stmt2;
//     IFELStmtNode(CondNode *cond,StmtNode *stmt,StmtNode *stmt2):cond(cond),stmt(stmt),stmt2(stmt2) {type=IFELSTMT;};
//     int dumpdot(DumpDOT *dumper);
// };
    int nThis = dumper->newNode(6,"if ("," ",")"," ","else"," ");
    int nCond = cond->dumpdot(dumper);
    int nStmt = stmt->dumpdot(dumper);
    int nStmt2 = stmt2->dumpdot(dumper);
    dumper->drawLine(nThis,1,nCond);
    dumper->drawLine(nThis,3,nStmt);
    dumper->drawLine(nThis,5,nStmt2);
    return nThis;
}
int IFStmtNode::dumpdot(DumpDOT *dumper){
//class IFStmeNode : public StmtNode{
// public:
//     CondNode *cond;
//     StmtNode *stmt;
//     IFStmtNode(CondNode *cond,StmtNode *stmt):cond(cond),stmt(stmt) {type=IFELSTMT;};
//     int dumpdot(DumpDOT *dumper);
// };
    int nThis = dumper->newNode(4,"if ("," ",")"," ");
    int nCond = cond->dumpdot(dumper);
    int nStmt = stmt->dumpdot(dumper);
    dumper->drawLine(nThis,1,nCond);
    dumper->drawLine(nThis,3,nStmt);
    return nThis;
}

int CondNode::dumpdot(DumpDOT *dumper){
// class RelOpCondNode : public CondNode{
// public:
//     VarNode *var;
//     ExpNode *lhs, *rhs;
//     RelOpCondNode(VarNode *var, ExpNode *lhs, ExpNode *rhs) : var(var), lhs(lhs), rhs(rhs) { type = RELC; };
//     int dumpdot(DumpDOT *dumper);
// };
    int nThis = dumper->newNode(3," ",var->name->c_str()," ");
    int nLhs = lhs->dumpdot(dumper);
    int nRhs = rhs->dumpdot(dumper);
    dumper->drawLine(nThis,0,nLhs);
    dumper->drawLine(nThis,2,nRhs);
    return nThis;
}
int WhileStmtNode::dumpdot(DumpDOT *dumper){
// class WhileStmtNode : public Node{
// public:
//     CondNode * cond;
//     StmtNode * stmt;
//     WhileStmtNode(CondNode * cond,StmtNode * stmt) : cond(cond),stmt(stmt) { type = WHISTMT};
//     int dumpdot(DumpDOT *dumper);
// };
    int nThis = dumper->newNode(5,"while","("," ",")"," ");
    int nCond = cond->dumpdot(dumper);
    int nStmt = stmt->dumpdot(dumper);
    dumper->drawLine(nThis,2,nCond);
    dumper->drawLine(nThis,4,nStmt);
    return nThis;
}
int InputNode::dumpdot(DumpDOT *dumper) {
    std::ostringstream strs;
    strs << lines.size() << " CompUnits";
    int nThis = dumper->newNode(1, strs.str().c_str());
    for (CompUnitNode* line : lines) {
        int nLine = line->dumpdot(dumper);
        dumper->drawLine(nThis, 0, nLine);
    }
    return nThis;
}
