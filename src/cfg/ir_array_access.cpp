#include "ir_array_access.h"
using cfg::IRArrayAccess;
using std::string;

IRArrayAccess::IRArrayAccess() : Tac() {}
IRArrayAccess::IRArrayAccess(string lhs, string rhs, string result)
    : Tac("", std::move(lhs), std::move(rhs), std::move(result)) {}

std::string IRArrayAccess::printInfo() const {
    return this->getResult() + " := " + this->getLHS() + "[" + this->getRHS() + "]";
}
