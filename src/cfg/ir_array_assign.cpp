#include "ir_array_assign.h"
using cfg::IRArrayAssign;
using std::string;

IRArrayAssign::IRArrayAssign() : Tac() {}
IRArrayAssign::IRArrayAssign(string lhs, string rhs, string result)
    : Tac("", std::move(lhs), std::move(rhs), std::move(result)) {}

string IRArrayAssign::printInfo() const {
    return this->getLHS() + "[" + this->getRHS() + "] := " + this->getResult();
}
