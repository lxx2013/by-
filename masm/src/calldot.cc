#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include "node.hh"
#include "calldot.hh"
//#define DEBUG
#include "util.hh"
extern GlobalNode* global;
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

int CallDOT::newNode(int num, ...) {
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

int CallDOT::newNode(std::vector<std::string> list) {
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

void CallDOT::drawLine(int nSrc, int pSrc, int nDst) {
    fprintf(fp, "    %d", nSrc);
    if (pSrc>=0)
        fprintf(fp, ":%d", pSrc);
    fprintf(fp, " -> %d;\n", nDst);
}

//===----------------------------------------------------------------------===//
// Dump AST to DOT
//===----------------------------------------------------------------------===//

// The following functions convert AST to DOT using CallDOT.
// Each CallDOT returns an integer, which is corresponding number in DOT file.
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

int NumNode::calldot(CallDOT *caller) {
    // std::ostringstream strs;
    // strs << val;
    // int nThis = caller->newNode(1, strs.str().c_str());
    // return nThis;
    return 0;
}
int VarNode::calldot(CallDOT *caller) {
    return 0;
}
int IntInsNode::calldot(CallDOT *caller) {
    std::ostringstream strs;
    strs << "int ";
    strs << val;
    int nThis = caller->newNode(1,strs.str().c_str());
    return nThis;
}
int MovInsNode::calldot(CallDOT *caller) {
    return 0;
}
int CmpInsNode::calldot(CallDOT *caller) {
    return 0;
}
int JmpInsNode::calldot(CallDOT *caller) {
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
    int nThis = caller->newNode(1,strs.str().c_str());
    return nThis;
}
int AddInsNode::calldot(CallDOT *caller) {
    return 0;
}
int SubInsNode::calldot(CallDOT *caller) {
    return 0;
}
int PushInsNode::calldot(CallDOT *caller) {
    return 0;
}
int PopInsNode::calldot(CallDOT *caller) {
    return 0;
}
int RetInsNode::calldot(CallDOT *caller) {
    std::ostringstream strs;
    strs << "ret ";
    int nThis = caller->newNode(1,strs.str().c_str());
    return nThis;
}

int MulInsNode::calldot(CallDOT *caller) {
    return 0;
}
int DivInsNode::calldot(CallDOT *caller) {
    return 0;
}
int CallInsNode::calldot(CallDOT *caller) {
    std::ostringstream strs;
    strs << "call ";
    strs << label->c_str();
    int nThis = caller->newNode(1,strs.str().c_str());
    return nThis;
}
int BlockNode::calldot(CallDOT *caller) {
    std::ostringstream strs;
    strs << label->c_str();
    strs << " : ";
    int nThis = caller->newNode(1,strs.str().c_str());
    calldot_first = nThis;
    int nUp,nDown;
    nUp = nThis;
    for (InstructionNode* line : block_root->lines) {
       if(line->type == BLK)
       {
            if(((BlockNode*)line)->calldot_first == -1){
                nDown = line->calldot(caller);
                caller->drawLine(nUp,0,nDown/10000);
                nUp = nDown%10000;
            }
       }
       else if(line->type == CALL_INS)
       {

            nDown = line->calldot(caller);
            caller->drawLine(nUp,0,nDown);
            BlockNode* blk =  global->GetLabelNode(((CallInsNode*)line)->label);
            if(blk->calldot_first > -1)
            {
                nUp = nDown;
                continue;
            }
            int nNext = blk->calldot(caller);
            caller->drawLine(nDown,0,nNext/10000);
            caller->drawLine(nNext%10000,0,nDown);
            nUp = nDown;
       }
       else if(line->type == INT_INS)
       {
            nDown = line->calldot(caller);
            caller->drawLine(nUp,0,nDown);
            nUp = nDown;
            if(global->ax->getvalue() == 19456)
               exit(0);
       }
       else if(line->type == RET_INS)
       {
            nDown = line->calldot(caller);
            caller->drawLine(nUp,0,nDown);
            nUp = nDown;
            break;
       }
    }
    return (nThis*10000+nUp);  // return /10000 = begin,return %10000 = end
}
int MacroNode::calldot(CallDOT *caller) {
    return 0;
}
int AssumeNode::calldot(CallDOT *caller) {
    return 0;
}
int AllocaSegmentNode::calldot(CallDOT *caller) {
    return 0;
}
int AllocaLineNode::calldot(CallDOT *caller) {
    return 0;
}
int ContentNode::calldot(CallDOT *caller) {
    int flag = 0;
    int nUp,nDown;
    for (BlockNode* line : block_root) {
        if(strcmp(line->label->c_str(),"start") == 0)
        {
            flag = 1;
            nUp = line->calldot(caller);
            continue;
        }
        if(flag == 0)
            continue;
        nDown = line->calldot(caller);
        caller->drawLine(nUp/100000, 0, nDown/10000);
        nUp = nDown;
    }
    return 0;
}


int InputNode::calldot(CallDOT *caller) {
    for (CompUnitNode* line : lines) {
        if(line->type == CONTENT)
        {
            line->calldot(caller);
        }
    }
    return 0;
}


