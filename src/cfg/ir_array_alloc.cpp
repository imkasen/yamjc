#include "ir_array_alloc.h"
using cfg::IRArrayAlloc;
using std::string;

IRArrayAlloc::IRArrayAlloc() : Tac() {}
IRArrayAlloc::IRArrayAlloc(string rhs, string result)
    : Tac("new", "int[]", std::move(rhs), std::move(result)) {}

std::string IRArrayAlloc::printInfo() const {
    return this->getResult() + " := " + this->getOP() + " " + this->getLHS() + ", " + this->getRHS();
}
