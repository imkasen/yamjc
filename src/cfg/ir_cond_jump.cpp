#include "ir_cond_jump.h"
using cfg::IRCondJump;
using std::string;

IRCondJump::IRCondJump() : Tac() {}
IRCondJump::IRCondJump(string lhs, string label)
    : Tac("goto", std::move(lhs), "", std::move(label)) {}

string IRCondJump::printInfo() const {
    return "if false " + this->getLHS() + ", " + this->getOP() + " " + this->getResult();
}

/*
 * TAC:
 *   if false x goto L
 * ByteCode:
 *   iconst || iload x
 *   ifeq
 *   goto L
 */
string IRCondJump::printBC() const {
    string context;
    context += Tac::isNum(this->getLHS()) ? ("iconst " + this->getLHS()) : ("iload " + this->getLHS());
    context += "\n";
    context += "ifeq\n";
    context += "goto " + this->getResult() + "\n";
    return context;
}
