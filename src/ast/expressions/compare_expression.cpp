#include "ast/expressions/compare_expression.h"
using std::string;

CompareExpression::CompareExpression() : Expression() {}
CompareExpression::CompareExpression(string t, string v) : Expression(std::move(t), std::move(v)) {}

/*
 * @brief:
 *       "CompareExpression"
 *         /           \
 *   "Expression"  "Expression"
 * @return: std::nullopt
 */
std::optional<string> CompareExpression::checkSemantics() {
    string lhs = this->children.at(0)->checkSemantics().value_or("");
    string rhs = this->children.at(1)->checkSemantics().value_or("");
    if (!lhs.empty() && !rhs.empty() && lhs == rhs) {
        return "boolean";
    } else {
        string msg = "[Semantic Analysis] - Error: lhs (\"" + lhs + "\") and rhs (\"" + rhs +
                     "\") variable types are different in scope \"" + CompareExpression::st.getScopeTitle() + "\"!";
        CompareExpression::printErrMsg(msg);
    }

    return std::nullopt;
}
