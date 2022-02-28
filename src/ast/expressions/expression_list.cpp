#include "ast/expressions/expression_list.h"
using ast::ExpressionList;
using std::string;

ExpressionList::ExpressionList() : Node() {}
ExpressionList::ExpressionList(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * @return: string
 */
std::optional<string> ExpressionList::checkSemantics() {
    string parameter_type_list;

    // Splice formal parameter types, "xxx xxx ..."
    for (const auto &child : this->children) {
        parameter_type_list += child->checkSemantics().value_or("") + " ";
    }

    return parameter_type_list;
}

/*
 * @brief:
 *   1. Obtain the current "BasicBlock".
 *   2. Get the return value, add an instruction "IRParameter"
 *   3. return the size of "Expression"
 * @return: string
 */
std::optional<IRReturnVal> ExpressionList::generateIR() {
    // 1.
    std::shared_ptr<cfg::BasicBlock> cur_bb = ExpressionList::bb_list.back();
    // 2.
    for (const auto &child : this->children) {
        string lhs;
        const auto lhs_vrt = child->generateIR().value_or(std::monostate{});
        if (auto s_vrt = std::get_if<string>(&lhs_vrt)) {
            lhs = *s_vrt;
        }
        std::shared_ptr<cfg::Tac> instruction = std::make_shared<cfg::IRParameter>(lhs);
        cur_bb->addInstruction(instruction);
    }
    // 3.
    return std::to_string(this->children.size());
}
