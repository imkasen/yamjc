#include "ast/statements/else_statement.h"
using ast::ElseStatement;
using std::string;

ElseStatement::ElseStatement(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * @brief:
 * @return: IRReturnVal
 */
std::optional<IRReturnVal> ElseStatement::generateIR() {
    std::shared_ptr<cfg::BasicBlock> false_bb = ElseStatement::createBB();
    ElseStatement::bb_list.push_back(false_bb);

    for (const auto &child : this->children) {
        const auto vrt = child->generateIR().value_or(std::monostate{});
        // "... else if () {} ..."
        if (auto ptr = std::get_if<std::shared_ptr<cfg::BasicBlock>>(&vrt)) {
            false_bb->setTrueExit(*ptr);
        }
    }

    return false_bb;
}
