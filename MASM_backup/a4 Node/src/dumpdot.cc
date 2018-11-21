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
    // std::ostringstream strs;
    // strs << val;
    // int nThis = dumper->newNode(1, strs.str().c_str());
    // return nThis;
    return 0;
}
int VarNode::dumpdot(DumpDOT *dumper) {
    return 0;
}
int IntInsNode::dumpdot(DumpDOT *dumper) {
    std::ostringstream strs;
    strs << "int ";
    strs << val;
    int nThis = dumper->newNode(1,strs.str().c_str());
    return nThis;
}
int MovInsNode::dumpdot(DumpDOT *dumper) {
    std::ostringstream strs;
    strs << "Mov ";
    strs << *(operand->lhs->getname());
    strs << " , ";
    strs << *(operand->rhs->getname());
    int nThis = dumper->newNode(1,strs.str().c_str());
    return nThis;
}
int CmpInsNode::dumpdot(DumpDOT *dumper) {
    std::ostringstream strs;
    strs << "Cmp ";
    strs << *(operand->lhs->getname());
    strs << " , ";
    strs << *(operand->rhs->getname());
    int nThis = dumper->newNode(1,strs.str().c_str());
    return nThis;
}
int JmpInsNode::dumpdot(DumpDOT *dumper) {
    std::ostringstream strs;
    if(cmp_trend == 0)
        strs << "jmp";
    else if(cmp_trend == 1)
        strs << "jl";
    else if(cmp_trend == 2)
        strs << "jle";
    else if(cmp_trend == 3)
        strs << "je";
    else if(cmp_trend == 4)
        strs << "jge";
    else if(cmp_trend == 5)
        strs << "jg";
    else if(cmp_trend == 6)
        strs << "jne";
    else if(cmp_trend == 7)
        strs << "loop";
    strs << " "; 
    strs << label->c_str();  
    int nThis = dumper->newNode(1,strs.str().c_str());
    return nThis;
}
int AddInsNode::dumpdot(DumpDOT *dumper) {
    std::ostringstream strs;
    strs << "add ";
    strs << *(operand->lhs->getname());
    strs << " , ";
    strs << *(operand->rhs->getname());
    int nThis = dumper->newNode(1,strs.str().c_str());
    return nThis;
}
int SubInsNode::dumpdot(DumpDOT *dumper) {
    std::ostringstream strs;
    strs << "sub ";
    strs << *(operand->lhs->getname());
    strs << " , ";
    strs << *(operand->rhs->getname());
    int nThis = dumper->newNode(1,strs.str().c_str());
    return nThis;
}
int PushInsNode::dumpdot(DumpDOT *dumper) {
    std::ostringstream strs;
    strs << "push ";
    strs << *(operand->getname());
    int nThis = dumper->newNode(1,strs.str().c_str());
    return nThis;
}
int PopInsNode::dumpdot(DumpDOT *dumper) {
    std::ostringstream strs;
    strs << "push ";
    strs << *(operand->getname());
    int nThis = dumper->newNode(1,strs.str().c_str());
    return nThis;
}
int RetInsNode::dumpdot(DumpDOT *dumper) {
    std::ostringstream strs;
    strs << "ret ";
    int nThis = dumper->newNode(1,strs.str().c_str());
    return nThis;
}

int MulInsNode::dumpdot(DumpDOT *dumper) {
    std::ostringstream strs;
    strs << "mul ";
    strs << *(lh->getname());
    strs << " , ";
    strs << *(ll->getname());
    strs << " , ";
    strs << *(rh->getname());
    strs << " , ";
    strs << *(rl->getname());
    int nThis = dumper->newNode(1,strs.str().c_str());
    return nThis;
}
int DivInsNode::dumpdot(DumpDOT *dumper) {
    std::ostringstream strs;
    strs << "div ";
    strs << *(lh->getname());
    strs << " , ";
    strs << *(ll->getname());
    strs << " , ";
    strs << *(rh->getname());
    strs << " , ";
    strs << *(rl->getname());
    strs << " , ";
    strs << *(rf->getname());
    int nThis = dumper->newNode(1,strs.str().c_str());
    return nThis;
}
int CallInsNode::dumpdot(DumpDOT *dumper) {
    std::ostringstream strs;
    strs << "call ";
    strs << label->c_str();
    int nThis = dumper->newNode(1,strs.str().c_str());
    return nThis;
}
int BlockNode::dumpdot(DumpDOT *dumper) {
    std::ostringstream strs;
    strs << label->c_str();
    strs << " : ";
    int nThis = dumper->newNode(1,strs.str().c_str());
    int nUp,nDown;
    nUp = nThis;
    for (InstructionNode* line : block_root->lines) {
        nDown = line->dumpdot(dumper);
        dumper->drawLine(nUp, 0, nDown);
        nUp = nDown;
    }
    return nThis;
}
int MacroNode::dumpdot(DumpDOT *dumper) {
    std::ostringstream strs;
    strs << name->c_str();
    int nThis = dumper->newNode(2,strs.str().c_str(),"MACRO");
    int nUp,nDown;
    nUp = nThis;
    for (InstructionNode* line : blockitem->lines) {
        nDown = line->dumpdot(dumper);
        dumper->drawLine(nUp, 0, nDown);
        nUp = nDown;
    }
    return nThis;
}
int AssumeNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(1,"Assume");
    int n1 = dumper->newNode(2,"ds:","data");
    int n2 = dumper->newNode(2,"ss:","stack");
    int n3 = dumper->newNode(2,"cs:","code");
    dumper->drawLine(nThis, 0, n1);
    dumper->drawLine(nThis, 0, n2);
    dumper->drawLine(nThis, 0, n3);
    return nThis;
}
int AllocaSegmentNode::dumpdot(DumpDOT *dumper) {
    std::ostringstream strs;
    strs << lines.size() << " Allocas";
    int nThis = dumper->newNode(1, strs.str().c_str());
    int nUp = nThis,nDown;
    for (AllocaLineNode* line : lines) {
        int nDown = line->dumpdot(dumper);
        dumper->drawLine(nUp, 0, nDown);
        nUp = nDown;
    }
    return nThis;
}
int AllocaLineNode::dumpdot(DumpDOT *dumper) {
    std::ostringstream strs;
    strs << label->c_str();
    if(length == 8)
        strs << " db 8";
    else if (length == 16)
        strs << " dw 16";
    else if (length == 32)
        strs << " dd 32";
    int nThis = dumper->newNode(1, strs.str().c_str());
    return nThis;
}
int ContentNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(1,"Content");
    int nLine;
    for (MacroNode* line : macros) {
        nLine = line->dumpdot(dumper);
        dumper->drawLine(nThis, 0, nLine);
    }
    for (BlockNode* line : block_root) {
        nLine = line->dumpdot(dumper);
        dumper->drawLine(nThis, 0, nLine);
    }
    return nThis;
}


int InputNode::dumpdot(DumpDOT *dumper) {
    std::ostringstream strs;
    strs << lines.size() << " CompUnits";
    int nThis = dumper->newNode(1, strs.str().c_str());
    for (CompUnitNode* line : lines) {
        printf("%s\n",typeid(*line).name());
        int nLine = line->dumpdot(dumper);
        dumper->drawLine(nThis, 0, nLine);
    }
    return nThis;
}


