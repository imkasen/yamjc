#include "ir_alloc.h"
using cfg::IRAlloc;
using std::string;

IRAlloc::IRAlloc() : Tac() {}
IRAlloc::IRAlloc(string lhs, string result) : Tac("new", std::move(lhs), "", std::move(result)) {}

std::string IRAlloc::printInfo() const {
    return this->result + " := " + this->op + " " + this->lhs;
}
