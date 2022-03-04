#include "ast/expressions/arith_expression.h"
using ast::ArithExpression;
using std::string;

/*
        "ArithExpression"
          /           \
     "Expression"  "Expression"
 */

ArithExpression::ArithExpression() : Expression() {}
ArithExpression::ArithExpression(string t, string v) : Expression(std::move(t), std::move(v)) {}

/*
 * @brief: Compare lhs and rhs
 * @return: std::nullopt
 */
std::optional<std::string> ArithExpression::checkSemantics() {
    string lhs = this->children.at(0)->checkSemantics().value_or("");
    string rhs = this->children.at(1)->checkSemantics().value_or("");
    if (!lhs.empty() && !rhs.empty() && lhs == rhs) {
        return lhs;
    } else {
        string msg = "[Semantic Analysis] - Error: lhs (\"" + lhs + "\") and rhs (\"" + rhs +
                     "\") variable types are different in scope \"" + ArithExpression::st.getScopeTitle() + "\"!";
        ArithExpression::printErrMsg(msg);
    }

    return std::nullopt;
}

/*
 * @brief:
 *   1. Obtain current "BasicBlock".
 *   2. Get the return value of lhs, rhs.
 *      Add an instruction "IRExpression"
 * @return: string
 */
std::optional<IRReturnVal> ArithExpression::generateIR() {
    // 1.
    std::shared_ptr<cfg::BasicBlock> cur_bb = ArithExpression::bb_list.back();
    // 2.
    string lhs_name, rhs_name, tmp_name;
    string op = this->getValue();
    const auto lhs_vrt = this->children.at(0)->generateIR().value_or(std::monostate {});
    if (auto s_ptr = std::get_if<string>(&lhs_vrt)) {
        lhs_name = *s_ptr;
    }
    const auto rhs_vrt = this->children.at(1)->generateIR().value_or(std::monostate {});
    if (auto s_ptr = std::get_if<string>(&rhs_vrt)) {
        rhs_name = *s_ptr;
    }
    tmp_name = cfg::Tac::generateTmpVarName('i');
    std::shared_ptr<cfg::Tac> instruction =
        std::make_shared<cfg::IRExpression>(op, lhs_name, rhs_name, tmp_name);
    cur_bb->addInstruction(instruction);

    return tmp_name;
}
