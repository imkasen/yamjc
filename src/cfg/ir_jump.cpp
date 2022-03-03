#include "ir_jump.h"
using cfg::IRJump;
using std::string;

IRJump::IRJump() : Tac() {}
IRJump::IRJump(string label) : Tac("goto", "", "", std::move(label)) {}

string IRJump::printInfo() const {
    return this->getOP() + " " + this->getResult();
}

/*
 * TAC:
 *   goto L
 * ByteCode:
 *   goto L
 */
string IRJump::printBC() const {
    string context;
    context += "goto " + this->getResult() + "\n";
    return context;
}
