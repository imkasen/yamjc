#include "basic_block.h"
using cfg::BasicBlock;
using std::string;

BasicBlock::BasicBlock() : tac_instructions(0), true_exit(nullptr), false_exit(nullptr) {
    this->name = "L" + std::to_string(BasicBlock::id++);
}

void BasicBlock::setTrueExit(const std::shared_ptr<BasicBlock> &basic_block) {
    this->true_exit = basic_block;
}

void BasicBlock::setFalseExit(const std::shared_ptr<BasicBlock> &basic_block) {
    this->false_exit = basic_block;
}

void BasicBlock::addInstruction(const std::shared_ptr<Tac> &instruction) {
    this->tac_instructions.push_back(instruction);
}

std::shared_ptr<BasicBlock> BasicBlock::getTrueExit() const {
    return this->true_exit;
}

std::shared_ptr<BasicBlock> BasicBlock::getFalseExit() const {
    return this->false_exit;
}

string BasicBlock::getName() const {
    return this->name;
}