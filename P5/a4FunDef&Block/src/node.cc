#include "node.hh"
#include "util.hh"

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




