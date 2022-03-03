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
 *   iconst || iload y
 *   istore x
 */
string IRCopy::printBC() const {
    string context;
    context += isNum(this->getLHS()) ? ("iconst " + this->getLHS()) : ("iload " + this->getLHS());
    context += "\n";
    context += "istore " + this->getResult() + "\n";
    return context;
}
