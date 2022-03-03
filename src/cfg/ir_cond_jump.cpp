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
 *   ifeq x goto L
 */
string IRCondJump::printBC() const {
    string context;
    context += "ifeq " + this->getLHS() + " goto " + this->getResult() + "\n";
    return context;
}
