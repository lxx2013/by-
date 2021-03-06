#ifndef _NODE_HH_
#define _NODE_HH_

#include <stdio.h>
#include <string>
#include <vector>
#include "dumpdot.hh"
using namespace std;

typedef enum {
    NUM,
    VAR,
    INPUT,
    CSTDFH,
    CSTDF,
    CSTDC,
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
    Node() {loc = (Loc*)malloc(sizeof(Loc));}
    void setLoc(Loc* loc);
    virtual int dumpdot(DumpDOT *dumper) = 0;
};

class ExpNode : public Node {
public:
    virtual int dumpdot(DumpDOT *dumper) = 0;
};

class NumNode : public ExpNode {
public:
    int val;
    NumNode(int val) : val(val) { type = EXP; };
    int dumpdot(DumpDOT *dumper);
};

class VarNode : public ExpNode {
public:
    std::string *name;
    VarNode(std::string* name) : name(name) { type = VAR; };
    int dumpdot(DumpDOT *dumper);
};

class BinaryExpNode : public ExpNode {
public:
    char op;
    ExpNode *lhs, *rhs;
    BinaryExpNode(char op, ExpNode *lhs, ExpNode *rhs) : op(op), lhs(lhs), rhs(rhs) { type = BINARYEXP; };
    int dumpdot(DumpDOT *dumper);
};

class ParenExpNode : public ExpNode {
public:
    ExpNode *exp;
    ParenExpNode(ExpNode *exp) : exp(exp) { type = PARENEXP; };
    int dumpdot(DumpDOT *dumper);
};

class UnaryExpNode : public ExpNode {
public:
    char op;
    ExpNode *operand;
    UnaryExpNode(char op, ExpNode *operand) : op(op), operand(operand) { type = UNARYEXP; };
    int dumpdot(DumpDOT *dumper);
};

class LValNode : public Node{
public:
    virtual int dumpdot(DumpDOT *dumper) = 0;
};


class ArrayLValNode : public LValNode{
public:
    VarNode *var;
    ExpNode *exp;
    ArrayLValNode(VarNode *var, ExpNode *exp) : var(var), exp(exp) { type = ARRAYLVAL; };
    int dumpdot(DumpDOT *dumper);
};
class AsgnNode : public Node {
public:
    LValNode *lval;
    ExpNode *exp;
    AsgnNode(LValNode *lval, ExpNode *exp) : lval(lval), exp(exp) { type = ASGN; };
    int dumpdot(DumpDOT *dumper);
};



class CompUnitNode : public Node {
public:
    AsgnNode *asgn;
    CompUnitNode(AsgnNode *asgn) : asgn(asgn) { type = LINE; };
    int dumpdot(DumpDOT *dumper);
};

class ConstDefNode : public Node{
public:
     virtual int dumpdot(DumpDOT *dumper) = 0;
};

class ConstDefHNode : public Node{
public:
    std::vector<ConstDefNode*> lines;
    ConstDefHNode() {type = CSTDFH;};
    int dumpdot(DumpDOT *dumper);
    void append(ConstDefNode *line);
};

class ConstDeclNode : public Node{
public:
    ConstDefHNode *cst_root;
    ConstDeclNode(ConstDefHNode * cst_root) : cst_root(cst_root) {type = CSTDC;};
    int dumpdot(DumpDOT *dumper);
};
class ExpHNode : public Node{
public:
    std::vector<ExpNode*> lines;
    ExpHNode() {type = EXPH;};
    int dumpdot(DumpDOT *dumper);
    void append(ExpNode *line);
};
class ArrayDef_1_Node : public Node{
public:
    VarNode *var;
    ExpHNode *ExpH_root;
    ArrayDef_1_Node(VarNode *var,ExpHNode *ExpH_root):var(var),ExpH_root(ExpH_root) {type=ARRAYDEF1;};
    int dumpdot(DumpDOT *dumper);
};
class ArrayDef_2_Node : public Node{
public:
    VarNode *var;
    ExpNode *exp;
    ExpHNode *ExpH_root;
    ArrayDef_2_Node(VarNode *var,ExpNode *exp,ExpHNode *ExpH_root):var(var),exp(exp),ExpH_root(ExpH_root) {type=ARRAYDEF2;};
    int dumpdot(DumpDOT *dumper);
};


class InputNode : public Node {
public:
    vector<CompUnitNode*> lines;
    InputNode() { type = INPUT; };
    int dumpdot(DumpDOT *dumper);
    void append(CompUnitNode *line);
};

#endif
