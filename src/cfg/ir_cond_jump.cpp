#include "ir_cond_jump.h"
using cfg::IRCondJump;
using std::string;

IRCondJump::IRCondJump() : Tac() {}
IRCondJump::IRCondJump(string lhs, string rhs)
    : Tac("goto", std::move(lhs), std::move(rhs), "") {}
