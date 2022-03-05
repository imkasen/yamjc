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
        if (Tac::isNum(this->getLHS())) {
            context += "iconst " + this->getLHS() + "\n";
            context += "ireturn\n";
        } else if ((this->getLHS().find("_i") != string::npos) ||
                   (this->getLHS().find("_r") != string::npos)) {
            context += "iload " + this->getLHS() + "\n";
            context += "ireturn\n";
        } else {
            context += "aload " + this->getLHS() + "\n";
            context += "areturn\n";
        }
    } else {
        context += "return\n";
    }
    return context;
}
