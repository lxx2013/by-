#include "node.hh"
#include "util.hh"
#include "global.hh"
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

void BlockItemNode::append(InstructionNode *line) {
    lines.push_back(line);
}
void AllocaSegmentNode::append(AllocaLineNode *line) {
    lines.push_back(line);
}
void ContentNode::appendB(BlockNode* block){
    block_root.push_back(block);
}
void ContentNode::appendM(MacroNode* macro){
    macros.push_back(macro);
}
//===----------------------------------------------------------------------===//
// Utilities in Code DOT
//===----------------------------------------------------------------------===//


