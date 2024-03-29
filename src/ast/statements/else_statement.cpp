#include "ast/statements/else_statement.h"
using ast::ElseStatement;
using std::string;

[[maybe_unused]] ElseStatement::ElseStatement(string t, string v) : Statement(std::move(t), std::move(v)) {}

/*
 * @brief: Create an Else condition "BasicBlock", add into instruction
 * @return: block_ptr
 */
IRReturnVal ElseStatement::generateIR() {
    std::shared_ptr<cfg::BasicBlock> false_bb = ElseStatement::createBB();
    ElseStatement::bb_list.push_back(false_bb);

    for (const auto &child : this->children) {
        const auto vrt = child->generateIR();
        // "... else if () {} ..."
        if (auto ptr = std::get_if<std::shared_ptr<cfg::BasicBlock>>(&vrt)) {
            false_bb->setTrueExit(*ptr);
        }
    }

    return false_bb;
}
