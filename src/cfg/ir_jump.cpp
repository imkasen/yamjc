#include "ir_jump.h"
using cfg::IRJump;
using std::string;

IRJump::IRJump() : Tac() {}
IRJump::IRJump(string label) : Tac("goto", "", "", std::move(label)) {}
