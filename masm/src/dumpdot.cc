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
//#define DEBUG
#include "util.hh"
extern GlobalNode * global;
extern InputNode * root;
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
    if(val == 33)
    {
        if(global->ax->h->getvalue() == 2)
        {
            int num = global->dx->l->getvalue();
            if((num >=  0 && num <=31 && num != 10) || num == 127)
            {
                warning("%s:%3d.(%2d) 这里将会输出一个不可见字符\n",infile_name,loc->first_line,loc->first_column);
                show_line(global->dx->l->getlcl(),infile_name);
                print_blank(loc->first_column+8);
            }
        }
    }
    std::ostringstream strs;
    strs << "int ";
    strs << val;
    int nThis = dumper->newNode(1,strs.str().c_str());
    return nThis;
}
int MovInsNode::dumpdot(DumpDOT *dumper) {
    //***** value calculate ****//
            RegNode *l,*r;
            l = operand->lhs;
            r = operand->rhs;
            line("%s:%d,%s:%d\n",l->getname()->c_str(),l->getvalue(),r->getname()->c_str(),r->getvalue());
            l->setvalue(r->getvalue());
            l->setlcl(loc->first_line);
            l->settrend(r->getvalue());
    //***** value calculate ****//
    std::ostringstream strs;
    strs << "Mov ";
    strs << *(operand->lhs->getname());
    strs << " , ";
    strs << *(operand->rhs->getname());
    int nThis = dumper->newNode(1,strs.str().c_str());
    return nThis;
}
int CmpInsNode::dumpdot(DumpDOT *dumper) {
     //***** value calculate ****//
            RegNode *l,*r;
            l = operand->lhs;
            r = operand->rhs;
            line("CMP : %s:%d,%s:%d\n",l->getname()->c_str(),l->getvalue(),r->getname()->c_str(),r->getvalue());
            int a,b,c,d,e,f;
            a = l->getvalue();
            b = r->getvalue();
            c = l->gettrend();
            d = r->gettrend();
            e = l->getlcl();
            f = r->getlcl();
            if(a < b)
            {
                global->now_cmp = -1;
            }
            else if(a == b)
            {
                global->now_cmp = 0;
            }
            else if(a > b)
            {
                global->now_cmp = 1;
            }
            global->now_trend = c - d;
            global->now_lcl = e>f ? e:f ;
    //***** value calculate ****//
    std::ostringstream strs;
    strs << "Cmp ";
    strs << *(operand->lhs->getname());
    strs << " , ";
    strs << *(operand->rhs->getname());
    int nThis = dumper->newNode(1,strs.str().c_str());
    return nThis;
}
void JmpInsNode::diedcircle(){
    warning("%s:%3d.(%2d) There is a died circle! Please fix it!\n",infile_name,loc->first_line,loc->last_column);
    show_line(loc->first_line,infile_name);
    print_blank(loc->first_column+4);
}
int JmpInsNode::dumpdot(DumpDOT *dumper) {
    if(global->GetLabelLine(label) == 0)
    {
        error("%s:%3d.(%2d)This label isn't defined : %s\n",infile_name,loc->first_line,loc->first_column,label->c_str());
        show_line(loc->first_line,infile_name);
        print_blank(loc->first_column + 4);
        root = NULL;
    }
    int line = global->GetLabelLine(label);
    std::ostringstream strs;
    BlockNode * blk = global->GetLabelNode(label);
    int cmp = global->now_cmp;
    int trend = global->now_trend;
    int lcl = global->now_lcl;
    if(cmp_trend == 0)
    {    
        strs << "jmp";
    }
    else if(cmp_trend == 1)
    {    
        strs << "jl";
        if(cmp == -1)
        {
            if(lcl < line)
            {
                diedcircle();
            }
            else {
                if(trend <= 0)
                {
                    line("cmp:%d,trend:%d\n",cmp,trend);
                    diedcircle();
                }
            }
        }
    }    
    else if(cmp_trend == 2)
    {
        strs << "jle";
        if(cmp == -1 || cmp == 0)
        {
            if(lcl < line)
            {
                diedcircle();
            }
            else {
                if(trend <= 0)
                {
                    line("cmp:%d,trend:%d\n",cmp,trend);
                    diedcircle();
                }
            }
        }
    }    
    else if(cmp_trend == 3)
    {
        strs << "je";
        if(cmp == 0)
        {
            if(lcl < line)
            {
                diedcircle();
            }
            else {
                if(trend == 0)
                {
                    line("cmp:%d,trend:%d\n",cmp,trend);
                    diedcircle();
                }
            }
        }
    }    
    else if(cmp_trend == 4)
    {
        strs << "jge";
        if(cmp == 1 || cmp == 0)
        {
            if(lcl < line)
            {
                diedcircle();
            }
            else {
                if(trend >= 0)
                {
                    line("cmp:%d,trend:%d\n",cmp,trend);
                    diedcircle();
                }
            }
        }
    }    
    else if(cmp_trend == 5)
    {
        strs << "jg";
        if(cmp == 1)
        {
            if(lcl < line)
            {
                diedcircle();
            }
            else {
                if(trend >= 0)
                {
                    line("cmp:%d,trend:%d\n",cmp,trend);
                    diedcircle();
                }
            }
        }
    }    
    else if(cmp_trend == 6)
    {
        strs << "jne";
        if(cmp == -1)
        {
            if(lcl < line)
            {
                diedcircle();
            }
            else {
                if(trend <= 0)
                {
                    line("cmp:%d,trend:%d\n",cmp,trend);
                    diedcircle();
                }
            }
        }
        if(cmp == 1)
        {
            if(lcl < line)
            {
                diedcircle();
            }
            else {
                if(trend >= 0)
                {
                    line("cmp:%d,trend:%d\n",cmp,trend);
                    diedcircle();
                }
            }
        }
    }    
    else if(cmp_trend == 7)
    {
        strs << "loop";
        RegSNode * cx = global->cx;
        int a = cx->getvalue();
        cx->setvalue(a-1);
        cx->setlcl(line);
        int b = cx->gettrend();
        cx->settrend(b-1);
        trend = b-1;
        lcl = line;
        int v = a - 1;
        if(v > 0 )
            cmp = 1;
        else if(v == 0)
            cmp = 0;
        else
            cmp = -1;
        if(cmp == 1 || cmp == 0)
        {
            if(lcl < line)
            {
                diedcircle();
            }
            else {
                if(trend >= 0)
                {
                    line("cmp:%d,trend:%d\n",cmp,trend);
                    diedcircle();
                }
            }
        }
    }    
    strs << " "; 
    strs << label->c_str();  
    int nThis = dumper->newNode(1,strs.str().c_str());
    return nThis;
}
int AddInsNode::dumpdot(DumpDOT *dumper) {
    //***** value calculate ****//
            RegNode *l,*r;
            l = operand->lhs;
            r = operand->rhs;
            line("%s:%d,%s:%d\n",l->getname()->c_str(),l->getvalue(),r->getname()->c_str(),r->getvalue());
            int a,b,c;
            a = l->getvalue();
            b = r->getvalue();
            c = l->gettrend();
            l->setvalue(a+b);
            l->setlcl(loc->first_line);
            l->settrend(c+b);
    //***** value calculate ****//
    std::ostringstream strs;
    strs << "add ";
    strs << *(operand->lhs->getname());
    strs << " , ";
    strs << *(operand->rhs->getname());
    int nThis = dumper->newNode(1,strs.str().c_str());
    return nThis;
}
int SubInsNode::dumpdot(DumpDOT *dumper) {
    //***** value calculate ****//
            RegNode *l,*r;
            l = operand->lhs;
            r = operand->rhs;
            line("%s:%d,%s:%d\n",l->getname()->c_str(),l->getvalue(),r->getname()->c_str(),r->getvalue());
            int a,b,c;
            a = l->getvalue();
            b = r->getvalue();
            c = l->gettrend();
            l->setvalue(a-b);
            l->setlcl(loc->first_line);
            l->settrend(c-b);
    //***** value calculate ****//
    std::ostringstream strs;
    strs << "sub ";
    strs << *(operand->lhs->getname());
    strs << " , ";
    strs << *(operand->rhs->getname());
    int nThis = dumper->newNode(1,strs.str().c_str());
    return nThis;
}
int PushInsNode::dumpdot(DumpDOT *dumper) {
    //***** value calculate ****//
            global->push(operand->getvalue());
    //***** value calculate ****//
    std::ostringstream strs;
    strs << "push ";
    strs << *(operand->getname());
    int nThis = dumper->newNode(1,strs.str().c_str());
    return nThis;
}
int PopInsNode::dumpdot(DumpDOT *dumper) {
    //***** value calculate ****//
            RegNode *l;
            l = operand;
            l->setlcl(loc->first_line);
            l->setvalue(global->pop());
            l->settrend(0);
            line("%s:%d\n",l->getname()->c_str(),l->getvalue());
    //***** value calculate ****//
    std::ostringstream strs;
    strs << "pop ";
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
    //***** value calculate ****// // 只做8位的情况，暂不考虑16位
            int a,b,c;
            RegSNode * ax = global->ax;
            ax->h->setvalue(0);
            a = ax->l->getvalue();
            b = (rl->getvalue() -1) * a;
            c = ax->gettrend();
            ax->setvalue(a+b);
            ax->setlcl(loc->first_line);
            ax->settrend(c+b);
            line("%s:%d\n",ax->getname()->c_str(),ax->getvalue());
    //***** value calculate ****//
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
    //***** value calculate ****// // 只做8位的情况，暂不考虑16位
            int a,b,c;
            RegSNode * ax = global->ax;
            int m;

            m = ax->h->getvalue();
            line("1\n");
            a = ax->l->getvalue();
            if(rf->getvalue() == 0)
            {
                warning("%s:%3d.(%2d) 除数不能为0 !\n",infile_name,loc->first_line,loc->last_column);
                show_line(loc->first_line,infile_name);
                print_blank(loc->first_column+4);
            }
            else{
                line("2.rf->value:%d\n",rf->getvalue());
                b = a / rf->getvalue();
                line("3\n");
                c = a % rf->getvalue();
                line("4\n");

                ax->h->setvalue(c);
                ax->l->setvalue(b);
                ax->setlcl(loc->first_line);
                ax->h->settrend(c-m);
                ax->l->settrend(b-a);
                line("%s:%d\n",ax->getname()->c_str(),ax->getvalue());
            }
    //***** value calculate ****//
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
    if(global->GetLabelLine(label) == 0)
    {
        error("%s:%3d.(%2d)This label isn't defined : %s\n",infile_name,loc->first_line,loc->first_column,label->c_str());
        show_line(loc->first_line,infile_name);
        print_blank(loc->first_column + 5);
        root = NULL;
    }
    std::ostringstream strs;
    strs << "call ";
    strs << label->c_str();
    int nThis = dumper->newNode(1,strs.str().c_str());
    return nThis;
}
int BlockNode::dumpdot(DumpDOT *dumper) {
     //***** value calculate ****//
            global->ax->settrend(0);
            global->bx->settrend(0);
            global->cx->settrend(0);
            global->dx->settrend(0);
            global->si->settrend(0);
            global->di->settrend(0);
    //***** value calculate ****//
    std::ostringstream strs;
    strs << label->c_str();
    strs << " : ";
    int nThis = dumper->newNode(1,strs.str().c_str());
    int nUp,nDown;
    nUp = nThis;
    int i = 0;
    for (InstructionNode* line : block_root->lines) {
        line("%d %s\n",i++,typeid(*line).name());
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
    int i = 0;
    for (MacroNode* line : macros) {
        line("%d %s\n",i++,typeid(*line).name());
        nLine = line->dumpdot(dumper);
        dumper->drawLine(nThis, 0, nLine);
    }
    for (BlockNode* line : block_root) {
        line("%d %s\n",i++,typeid(*line).name());
        nLine = line->dumpdot(dumper);
        dumper->drawLine(nThis, 0, nLine);
    }
    return nThis;
}


int InputNode::dumpdot(DumpDOT *dumper) {
    std::ostringstream strs;
    strs << lines.size() << " CompUnits";
    int nThis = dumper->newNode(1, strs.str().c_str());
    int i = 0;
    for (CompUnitNode* line : lines) {
        line("%d %s\n",i++,typeid(*line).name());
        int nLine = line->dumpdot(dumper);
        dumper->drawLine(nThis, 0, nLine);
    }
    return nThis;
}


