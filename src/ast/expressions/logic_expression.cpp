#include "ast/expressions/logic_expression.h"
using ast::LogicExpression;
using std::string;

/*
         "LogicExpression"
           /           \
     "Expression"  "Expression"
 */

LogicExpression::LogicExpression(string t, string v) : Expression(std::move(t), std::move(v)) {}

/*
 * @brief: Compare lhs and rhs
 * @return: std::nullopt
 */
std::optional<string> LogicExpression::checkSemantics() {
    string lhs = this->children.at(0)->checkSemantics().value_or("");
    string rhs = this->children.at(1)->checkSemantics().value_or("");
    if (!lhs.empty() && !rhs.empty() && lhs == rhs) {
        return "boolean";
    } else {
        string msg = "[Semantic Analysis] - Error: lhs (\"" + lhs + "\") and rhs (\"" + rhs +
                     "\") variable types are different in scope \"" + LogicExpression::st.getScopeTitle() + "\"!";
        LogicExpression::printErrMsg(msg);
    }

    return std::nullopt;
}

/*
 * @brief:
 *   1. Obtain current "BasicBlock"
 *   2. Create an instruction "IRExpression"
 * @return: string
 */
std::optional<IRReturnVal> LogicExpression::generateIR() {
    // 1.
    std::shared_ptr<cfg::BasicBlock> cur_bb = LogicExpression::bb_list.back();
    // 2.
    std::string op = this->getValue();
    std::string lhs, rhs;
    const auto lhs_vrt = this->children.at(0)->generateIR().value_or(std::monostate{});
    if (auto s_ptr = std::get_if<string>(&lhs_vrt)) {
        lhs = *s_ptr;
    }
    const auto rhs_vrt = this->children.at(1)->generateIR().value_or(std::monostate{});
    if (auto s_ptr = std::get_if<string>(&rhs_vrt)) {
        rhs = *s_ptr;
    }
    std::string tmp_name = cfg::Tac::generateTmpVarName('b');
    std::shared_ptr<cfg::Tac> exp_ins = std::make_shared<cfg::IRExpression>(op, lhs, rhs, tmp_name);
    cur_bb->addInstruction(exp_ins);

    return tmp_name;
}
