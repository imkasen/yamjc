#include "ast/statements/else_statement.h"
using ast::ElseStatement;
using std::string;

ElseStatement::ElseStatement() : Node() {}
ElseStatement::ElseStatement(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * @brief:
 * @return: IRReturnVal
 */
std::optional<IRReturnVal> ElseStatement::generateIR() {
    std::shared_ptr<cfg::BasicBlock> false_bb = ElseStatement::createBB();
    ElseStatement::bb_list.push_back(false_bb);

    for (const auto &child : this->children) {
        child->generateIR();
    }

    return false_bb;
}
