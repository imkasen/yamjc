#include "ir_parameter.h"
using cfg::IRParameter;
using std::string;

IRParameter::IRParameter() : Tac() {}
IRParameter::IRParameter(string lhs) : Tac("param", std::move(lhs), "", "") {}

string IRParameter::printInfo() const {
    return this->getOP() + " " + this->getLHS();
}

/*
 * TAC:
 *   param y
 * ByteCode:
 *   "param 10" || "param _i0":
 *     iconst || iload y
 *   "param _r0":
 *     aload y
 */
string IRParameter::printBC() const {
    string context;
    if (Tac::isNum(this->getLHS())) {
        context += "iconst ";
    } else if (this->getLHS().find("_i") != string::npos) {
        context += "iload ";
    } else {
        context += "aload ";
    }
    context += this->getLHS() + "\n";
    return context;
}
