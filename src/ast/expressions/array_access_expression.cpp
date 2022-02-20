#include "ast/expressions/array_access_expression.h"
using ast::ArrayAccessExpression;
using std::string;

/*
     "ArrayAccessExpression"
         /          \
    "Expression"  "Expression"
 */

ArrayAccessExpression::ArrayAccessExpression() : Expression() {}
ArrayAccessExpression::ArrayAccessExpression(string t, string v) : Expression(std::move(t), std::move(v)) {}

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
