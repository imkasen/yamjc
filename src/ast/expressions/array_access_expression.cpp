#include "ast/expressions/array_access_expression.h"
using ast::ArrayAccessExpression;
using std::string;

/*
     "ArrayAccessExpression"
         /          \
    "Expression"  "Expression"
 */

[[maybe_unused]] ArrayAccessExpression::ArrayAccessExpression(string t, string v) : Expression(std::move(t), std::move(v)) {}

/*
 * @return: std::nullopt | string
 */
std::optional<string> ArrayAccessExpression::checkSemantics() {
    string lhs = this->children.at(0)->checkSemantics().value_or("");
    string rhs = this->children.at(1)->checkSemantics().value_or("");
    if (lhs == "int[]" && rhs == "int") {
        return "int";
    } else if (lhs != "int[]") {
        string msg = R"([Semantic Analysis] - Error: Should be "int[]" rather than ")" + lhs + "\" in the scope \"" +
                     ArrayAccessExpression::st.getScopeTitle() + "\"!";
        ArrayAccessExpression::printErrMsg(msg);
    } else if (rhs != "int") {
        string msg = R"([Semantic Analysis] - Error: only "int" can be used to access array's position in scope ")" +
                     ArrayAccessExpression::st.getScopeTitle() + "\"!";
        ArrayAccessExpression::printErrMsg(msg);
    }

    return std::nullopt;
}

/*
 * @brief:
 *   1. Get current "BasicBlock"
 *   2. Create an instruction "IRArrayAccess"
 * @return: IRReturnVal
 */
std::optional<IRReturnVal> ArrayAccessExpression::generateIR() {
    // 1.
    std::shared_ptr<cfg::BasicBlock> cur_bb = ArrayAccessExpression::bb_list.back();
    // 2.
    string arr_name, idx, tmp_name;
    const auto arr_vrt = this->children.at(0)->generateIR().value_or(std::monostate{});
    if (auto s_ptr = std::get_if<string>(&arr_vrt)) {
        arr_name = *s_ptr;
    }
    const auto idx_vrt = this->children.at(1)->generateIR().value_or(std::monostate{});
    if (auto s_ptr = std::get_if<string>(&idx_vrt)) {
        idx = *s_ptr;
    }
    tmp_name = cfg::Tac::generateTmpVarName('i');
    std::shared_ptr<cfg::Tac> instruction = std::make_shared<cfg::IRArrayAccess>(arr_name, idx, tmp_name);
    cur_bb->addInstruction(instruction);

    return tmp_name;
}
