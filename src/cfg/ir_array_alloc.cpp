#include "ir_array_alloc.h"
using cfg::IRArrayAlloc;
using std::string;

IRArrayAlloc::IRArrayAlloc() : Tac() {}
IRArrayAlloc::IRArrayAlloc(string lhs, string rhs, string result)
    : Tac("new", std::move(lhs), std::move(rhs), std::move(result)) {}

std::string IRArrayAlloc::printInfo() const {
    return this->result + " := " + this->op + " " + this->lhs + ", " + this->rhs;
}
