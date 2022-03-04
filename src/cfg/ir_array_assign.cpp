#include "ir_array_assign.h"
using cfg::IRArrayAssign;
using std::string;

IRArrayAssign::IRArrayAssign() : Tac() {}
IRArrayAssign::IRArrayAssign(string lhs, string rhs, string result)
    : Tac("", std::move(lhs), std::move(rhs), std::move(result)) {}

string IRArrayAssign::printInfo() const {
    return this->getLHS() + "[" + this->getRHS() + "] := " + this->getResult();
}

/*
 * TAC:
 *   y[i] := x
 * ByteCode:
 *   iconst || iload x
 *   iconst || iload i
 *   iastore y
 */
string IRArrayAssign::printBC() const {
    string context;
    context += Tac::isNum(this->getResult()) ? ("iconst " + this->getResult()) : ("iload " + this->getResult());
    context += "\n";
    context += Tac::isNum(this->getRHS()) ? ("iconst " + this->getRHS()) : ("iload " + this->getRHS());
    context += "\n";
    context += "iastore " + this->getLHS() + "\n";
    return context;
}
