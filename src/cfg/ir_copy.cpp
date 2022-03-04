#include "ir_copy.h"
using cfg::IRCopy;
using std::string;

IRCopy::IRCopy() : Tac() {}
IRCopy::IRCopy(string lhs, string result) : Tac("", std::move(lhs), "", std::move(result)) {}

string IRCopy::printInfo() const {
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
 *   "x := _a0" || "x := _r0" || "x := Class":
 *     aload y
 *     astore x
 */
string IRCopy::printBC() const {
    string context;
    string lhs = this->getLHS();
    string rst = this->getResult();
    if (Tac::isNum(lhs)) {
        context += "iconst " + lhs + "\n";
        context += "istore " + rst + "\n";
    } else if (lhs.find("_i") != string::npos) {
        context += "iload " + lhs + "\n";
        context += "istore " + rst + "\n";
    } else {
        context += "aload " + lhs + "\n";
        context += "astore " + rst + "\n";
    }
    return context;
}
