#include "ir_argument.h"
using cfg::IRArgument;
using std::string;

IRArgument::IRArgument() : Tac() {}
IRArgument::IRArgument(string lhs) : Tac("arg", std::move(lhs), "", "") {}

string IRArgument::printInfo() const {
    return this->getOP() + " " + this->getLHS();
}

/*
 * TAC:
 *   arg y
 * ByteCode:
 *   "arg 10" || "arg _i0":
 *     iconst || iload y
 *   "arg _r0" || "arg _a0" || "arg xxx":
 *     aload y
 */
string IRArgument::printBC() const {
    string context;
    if (Tac::isNum(this->getLHS())) {
        context += "iconst ";
    } else if ((this->getLHS().find("_i") != string::npos) ||
               (this->getLHS().find("_b") != string::npos)) {
        context += "iload ";
    } else {
        context += "aload ";
    }
    context += this->getLHS() + "\n";
    return context;
}
