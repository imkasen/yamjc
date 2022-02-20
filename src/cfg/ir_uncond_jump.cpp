#include "ir_uncond_jump.h"
using cfg::IRUncondJump;
using std::string;

IRUncondJump::IRUncondJump() : Tac() {}
IRUncondJump::IRUncondJump(string lhs) : Tac("goto", std::move(lhs), "", "") {}
