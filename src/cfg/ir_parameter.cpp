#include "ir_parameter.h"

#include <utility>
using cfg::IRParameter;
using std::string;

IRParameter::IRParameter() : Tac() {
    this->para_type = 0;
}
IRParameter::IRParameter(string lhs, char t) : Tac("param", std::move(lhs), "", "") {
    this->para_type = t;
}

string IRParameter::printInfo() const {
    return this->getOP() + " " + this->getLHS();
}

/*
 * TAC:
 *   param y
 * ByteCode:
 *   "arg num" || "arg boolean":
 *     istore num
 *   "arg a[]" || "arg class":
 *     astore xxx
 */
string IRParameter::printBC() const {
    string context;
    switch (this->para_type) {
        case 'i':
        case 'b':
            context += "istore ";
            break;
        case 'a':
        case 'r':
        default:
            context += "astore ";
            break;
    }
    context += this->getLHS() + "\n";
    return context;
}
