#include "ast/expressions/array_length_expression.h"
using ast::ArrayLengthExpression;
using std::string;

/*
   "ArrayLengthExpression"
             |
        "Expression"
 */

[[maybe_unused]] ArrayLengthExpression::ArrayLengthExpression(string t, string v) : Expression(std::move(t), std::move(v)) {}

/*
 * @return: std::nullopt | string
 */
std::optional<string> ArrayLengthExpression::checkSemantics() {
    string type = this->children.at(0)->checkSemantics().value_or("");
    if (type == "int[]") {
        return "int";
    } else {
        string msg = R"([Semantic Analysis] - Error: ".length" can only be applied to "int[]" in scope ")" +
                     ArrayLengthExpression::st.getScopeTitle() + "\"!";
        ArrayLengthExpression::printErrMsg(msg);
    }

    return std::nullopt;
}

/*
 * @brief:
 *   1. Get current "BasicBlock"
 *   2. Create an instruction "IRArrayLength"
 * @return: string
 */
IRReturnVal ArrayLengthExpression::generateIR() {
    // 1.
    std::shared_ptr<cfg::BasicBlock> cur_bb = ArrayLengthExpression::bb_list.back();
    // 2.
    string lhs, tmp_name;
    const auto vrt = this->children.at(0)->generateIR();
    if (auto s_ptr = std::get_if<string>(&vrt)) {
        lhs = *s_ptr;
    }
    tmp_name = cfg::Tac::generateTmpVarName('i');
    std::shared_ptr<cfg::Tac> instruction = std::make_shared<cfg::IRArrayLength>(lhs, tmp_name);
    cur_bb->addInstruction(instruction);

    return tmp_name;
}
