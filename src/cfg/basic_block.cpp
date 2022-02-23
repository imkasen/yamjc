#include "basic_block.h"
using cfg::BasicBlock;
using std::string;

BasicBlock::BasicBlock() : tac_instructions(0), condition(nullptr), true_exit(nullptr), false_exit(nullptr) {
    this->name = "block_" + std::to_string(BasicBlock::id++);
}

string BasicBlock::getName() const {
    return this->name;
}
