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
    LINE,
    ASGN,
    EXP,
    BINARYEXP,
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

class UnaryExpNode : public ExpNode {
public:
    char op;
    ExpNode *operand;
    UnaryExpNode(char op, ExpNode *operand) : op(op), operand(operand) { type = UNARYEXP; };
    int dumpdot(DumpDOT *dumper);
};

class AsgnNode : public Node {
public:
    VarNode *var;
    ExpNode *exp;
    AsgnNode(VarNode *var, ExpNode *exp) : var(var), exp(exp) { type = ASGN; };
    int dumpdot(DumpDOT *dumper);
};

class LineNode : public Node {
public:
    AsgnNode *asgn;
    LineNode(AsgnNode *asgn) : asgn(asgn) { type = LINE; };
    int dumpdot(DumpDOT *dumper);
};

class InputNode : public Node {
public:
    vector<LineNode*> lines;
    InputNode() { type = INPUT; };
    int dumpdot(DumpDOT *dumper);
    void append(LineNode *line);
};

#endif
