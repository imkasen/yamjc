#include "ir_assign.h"
using cfg::IRAssign;
using std::string;

IRAssign::IRAssign(string lhs, string result, char t) : Tac("", std::move(lhs), "", std::move(result)) {
    this->para_type = t;
}

string IRAssign::printInfo() const {
    return this->getResult() + " := " + this->getLHS();
}

/*
 * TAC:
 *   x := y
 * ByteCode:
 *   "_i0 := 1" || "_b0 := 1":
 *     iconst y
 *     istore x
 *   "x := _i0" || "x := _b0" || "x = num" || "x = boolean":
 *     iload y
 *     istore x
 *   "x := _a0" || "x := _r0" || "x := null" || "x := xxx":
 *     aload y
 *     astore x
 */
string IRAssign::printBC() const {
    string context;
    string lhs = this->getLHS();
    string rst = this->getResult();
    if (Tac::isNum(lhs)) {
        context += "iconst " + lhs + "\n";
        context += "istore " + rst + "\n";
    } else if ((lhs.find("_i") != string::npos) ||
               (lhs.find("_b") != string::npos)) {
        context += "iload " + lhs + "\n";
        context += "istore " + rst + "\n";
    } else if ((lhs.find("_a") != string::npos) ||
               (lhs.find("_r") != string::npos)) {
        context += "aload " + lhs + "\n";
        context += "astore " + rst + "\n";
    } else {
        switch (this->para_type) {
            case 'i':
            case 'b':
                context += "iload " + lhs + "\n";
                context += "istore " + rst + "\n";
                break;
            case 'a':
            case 'r':
            default:
                context += "aload " + lhs + "\n";
                context += "astore " + rst + "\n";
                break;
        }
    }
    return context;
}
