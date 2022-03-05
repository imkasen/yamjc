#include "ir_assign.h"
using cfg::IRAssign;
using std::string;

IRAssign::IRAssign() : Tac() {}
IRAssign::IRAssign(string lhs, string result) : Tac("", std::move(lhs), "", std::move(result)) {}

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
 *   "x := _i0" || "x := _b0":
 *     iload y
 *     istore x
 *   "x := _a0" || "x := _r0" || "x := null":
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
    } else {
        context += "aload " + lhs + "\n";
        context += "astore " + rst + "\n";
    }
    return context;
}
