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
 *   iconst || iload y
 */
string IRParameter::printBC() const {
    string context;
    context += isNum(this->getLHS()) ? ("iconst " + this->getLHS()) : ("iload " + this->getLHS());
    context += "\n";
    return context;
}
