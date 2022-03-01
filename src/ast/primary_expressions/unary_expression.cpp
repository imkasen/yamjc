#include "ast/primary_expressions/unary_expression.h"
using ast::UnaryExpression;
using std::string;

/*
   "UnaryExpression"
         |
     "Expression"
 */

UnaryExpression::UnaryExpression() : PrimaryExpression() {}
UnaryExpression::UnaryExpression(string t, string v) : PrimaryExpression(std::move(t), std::move(v)) {}

/*
 * @return: string
 */
std::optional<string> UnaryExpression::checkSemantics() {
    string type = this->children.at(0)->checkSemantics().value_or("");
    if (type != "boolean") {
        string msg = R"([Semantic Analysis] - Error: Unary expression condition should be "boolean" in scope ")" +
                     UnaryExpression::st.getScopeTitle() + "\"!";
        UnaryExpression::printErrMsg(msg);
    }
    return type;
}

/*
 * @brief:
 *   1. Get current "BasicBlock"
 *   2. Create an instruction "IRUnaryExpression"
 * @return: IRReturnVal
 */
std::optional<IRReturnVal> UnaryExpression::generateIR() {
    // 1.
    std::shared_ptr<cfg::BasicBlock> cur_bb = UnaryExpression::bb_list.back();
    // 2.
    string tmp_name, lhs, op = this->getValue();
    const auto vrt = this->children.at(0)->generateIR().value_or(std::monostate{});
    if (auto s_ptr = std::get_if<string>(&vrt)) {
        lhs = *s_ptr;
    }
    tmp_name = cfg::Tac::generateTmpVarName();
    std::shared_ptr<cfg::Tac> instruction = std::make_shared<cfg::IRUnaryExpression>(op, lhs, tmp_name);
    cur_bb->addInstruction(instruction);

    return tmp_name;
}
