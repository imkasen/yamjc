#include "ir_cond_jump.h"
using cfg::IRCondJump;
using std::string;

IRCondJump::IRCondJump() : Tac() {}
IRCondJump::IRCondJump(string lhs, string label)
    : Tac("goto", std::move(lhs), "", std::move(label)) {}

std::string IRCondJump::printInfo() const {
    return "if false " + this->getLHS() + ", " + this->getOP() + " " + this->getResult();
}
