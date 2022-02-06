#include "ast/expressions/array_length_expression.h"
using std::string;

ArrayLengthExpression::ArrayLengthExpression() : Expression() {}
ArrayLengthExpression::ArrayLengthExpression(string t, string v) : Expression(std::move(t), std::move(v)) {}

/*
 * "ArrayLengthExpression"
 *          |
 *       "Expression"
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
