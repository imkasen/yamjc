#include "ir_return.h"
using cfg::IRReturn;
using std::string;

IRReturn::IRReturn(string lhs, char t) : Tac("return", std::move(lhs), "", "") {
    this->para_type = t;
}

string IRReturn::printInfo() const {
    return this->getOP() + " " + this->getLHS();
}

/*
 * TAC:
 *   return y
 * ByteCode:
 *   "0":
 *     iconst y
 *     ireturn
 *   "_i" || "_b" || "num" || "boolean":
 *     iload y
 *     ireturn
 *   "_a" || "_r" || "array" || "class":
 *     aload y
 *     areturn
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
                   (this->getLHS().find("_b") != string::npos)) {
            context += "iload " + this->getLHS() + "\n";
            context += "ireturn\n";
        } else if ((this->getLHS().find("_a") != string::npos) ||
                   (this->getLHS().find("_r") != string::npos)) {
            context += "aload " + this->getLHS() + "\n";
            context += "areturn\n";
        } else {
            switch (this->para_type) {
                case 'i':
                case 'b':
                    context += "iload " + this->getLHS() + "\n";
                    context += "ireturn\n";
                    break;
                case 'a':
                case 'r':
                default:
                    context += "aload " + this->getLHS() + "\n";
                    context += "areturn\n";
                    break;
            }
        }
    } else {
        context += "return\n";
    }
    return context;
}
