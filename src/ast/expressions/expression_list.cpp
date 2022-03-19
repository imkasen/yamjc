#include "ast/expressions/expression_list.h"
using ast::ExpressionList;
using std::string;

[[maybe_unused]] ExpressionList::ExpressionList(string t, string v) : Node(std::move(t), std::move(v)) {}

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
 *   2. Get the return value, add an instruction "IRArgument"
 *   3. return the size of "Expression"
 * @return: string
 */
std::optional<IRReturnVal> ExpressionList::generateIR() {
    // 1.
    std::shared_ptr<cfg::BasicBlock> cur_bb = ExpressionList::bb_list.back();
    // 2.
    for (int i = static_cast<int>(this->children.size()) - 1; i >= 0; --i) {  // using a reverse loop to match stack popping in the next few parts
        const auto &child = this->children.at(i);
        string lhs;
        char type = 0;
        const auto lhs_vrt = child->generateIR().value_or(std::monostate{});
        if (auto s_vrt = std::get_if<string>(&lhs_vrt)) {
            lhs = *s_vrt;
        }
        const auto &record_ptr = ExpressionList::st.lookupRecord(lhs).value_or(nullptr);
        if (record_ptr && record_ptr->getType() == "int") {
            type = 'i';
        } else if (record_ptr && record_ptr->getType() == "boolean") {
            type = 'b';
        } else if (record_ptr && record_ptr->getType() == "int[]") {
            type = 'a';
        } else if (record_ptr) {
            type = 'r';
        }
        std::shared_ptr<cfg::Tac> instruction = std::make_shared<cfg::IRArgument>(lhs, type);
        cur_bb->addInstruction(instruction);
    }
    // 3.
    return std::to_string(this->children.size());
}
