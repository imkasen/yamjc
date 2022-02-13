#include "ast/expressions/arith_expression.h"
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
