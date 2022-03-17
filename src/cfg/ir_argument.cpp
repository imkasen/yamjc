#include "ir_argument.h"
using cfg::IRArgument;
using std::string;

IRArgument::IRArgument(string lhs, char t) : Tac("arg", std::move(lhs), "", "") {
    this->para_type = t;
}

string IRArgument::printInfo() const {
    return this->getOP() + " " + this->getLHS();
}

/*
 * TAC:
 *   arg y
 * ByteCode:
 *   "arg 10":
 *     iconst y
 *   "arg _i0" || "arg _b0" || "arg num" || "arg boolean":
 *     iload y
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
    } else if ((this->getLHS().find("_a") != string::npos) ||
               (this->getLHS().find("_r") != string::npos)) {
        context += "aload ";
    } else {
        switch (this->para_type) {
            case 'i':
            case 'b':
                context += "iload ";
                break;
            case 'a':
            case 'r':
            default:
                context += "aload ";
                break;
        }
    }
    context += this->getLHS() + "\n";
    return context;
}
