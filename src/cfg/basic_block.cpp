#include "basic_block.h"
using cfg::BasicBlock;
using std::string;

BasicBlock::BasicBlock() : tac_instructions(0), condition(nullptr), true_exit(nullptr), false_exit(nullptr) {}
