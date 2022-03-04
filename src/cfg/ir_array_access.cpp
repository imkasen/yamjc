#include "ir_array_access.h"
using cfg::IRArrayAccess;
using std::string;

IRArrayAccess::IRArrayAccess() : Tac() {}
IRArrayAccess::IRArrayAccess(string lhs, string rhs, string result)
    : Tac("", std::move(lhs), std::move(rhs), std::move(result)) {}

string IRArrayAccess::printInfo() const {
    return this->getResult() + " := " + this->getLHS() + "[" + this->getRHS() + "]";
}

/*
 * TAC:
 *   x := y[i]
 * ByteCode:
 *   iconst || iload i
 *   iaload y
 *   istore x
 */
string IRArrayAccess::printBC() const {
    string context;
    context += Tac::isNum(this->getRHS()) ? ("iconst " + this->getRHS()) : ("iload " + this->getRHS());
    context += "\n";
    context += "iaload " + this->getLHS() + "\n";
    context += "istore " + this->getResult() + "\n";
    return context;
}
