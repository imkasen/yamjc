#include "ast/expressions/logic_expression.h"
using std::string;

/*
         "LogicExpression"
           /           \
     "Expression"  "Expression"
 */

LogicExpression::LogicExpression() : Expression() {}
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
