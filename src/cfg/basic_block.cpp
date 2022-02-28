#include "basic_block.h"
using cfg::BasicBlock;
using cfg::Tac;
using std::string;

BasicBlock::BasicBlock() : tac_instructions(0), false_exit(nullptr) {
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

string BasicBlock::getName() const {
    return this->name;
}

std::shared_ptr<BasicBlock> BasicBlock::getTrueExit() const {
    return this->true_exit.lock();
}

std::shared_ptr<BasicBlock> BasicBlock::getFalseExit() const {
    return this->false_exit;
}

std::list<std::shared_ptr<Tac>> BasicBlock::getInstructions() const {
    return this->tac_instructions;
}

std::string BasicBlock::printInfo() const {
    // Draw instructions
    string ins_content;
    for (const auto &tac_ptr : this->getInstructions()) {
        ins_content += tac_ptr->printInfo() + "\n";
    }

    // Draw block
    string block_content;
    string cur_block_name = this->getName();
    block_content += cur_block_name + " [label=\"" + cur_block_name + "\n" + ins_content + "\"];\n";

    if (this->getTrueExit()) {  // Draw true pointer
        string next_block_name = this->getTrueExit()->getName();
        block_content += cur_block_name + " -> " + next_block_name + " [xlabel=\"true\"];\n";
    }
    if (this->getFalseExit()) {  // Draw false pointer
        string next_block_name = this->getFalseExit()->getName();
        block_content += cur_block_name + " -> " + next_block_name + " [xlabel=\"false\"];\n";
    }

    return block_content;
}
