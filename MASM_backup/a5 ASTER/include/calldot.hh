#ifndef _CALLDOT_HH_
#define _CALLDOT_HH_

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>
#include "global.hh"
using namespace std;
class CallDOT {
    FILE *fp;
    int count;
public:
    CallDOT(FILE *fp) : fp(fp) {
        fprintf(fp, "digraph {\n");
        fprintf(fp, "    node [shape = record];\n");
        count = 0;
    }
    ~CallDOT() { fprintf(fp, "}"); }
    int newNode(int num, ...);
    int newNode(std::vector<std::string> list);
    void drawLine(int nSrc, int fSrc, int nDst);
};


#endif
