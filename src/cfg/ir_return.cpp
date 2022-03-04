#include "ir_return.h"
using cfg::IRReturn;
using std::string;

IRReturn::IRReturn() : Tac() {}
IRReturn::IRReturn(string lhs) : Tac("return", std::move(lhs), "", "") {}

string IRReturn::printInfo() const {
    return this->getOP() + " " + this->getLHS();
}

/*
 * TAC:
 *   return y
 * ByteCode:
 *   "y":
 *     iconst || iload y
 *     ireturn
 *   "":
 *     return
 */
string IRReturn::printBC() const {
    string context;
    if (!this->getLHS().empty()) {
        context += Tac::isNum(this->getLHS()) ? ("iconst " + this->getLHS()) : ("iload " + this->getLHS());
        context += "\n";
        context += "ireturn\n";
    } else {
        context += "return\n";
    }
    return context;
}
