#include "ast/expressions/array_search_expression.h"
using std::string;

/*
     "ArraySearchExpression"
         /          \
    "Expression"  "Expression"
 */

ArraySearchExpression::ArraySearchExpression() : Expression() {}
ArraySearchExpression::ArraySearchExpression(string t, string v) : Expression(std::move(t), std::move(v)) {}

/*
 * @return: std::nullopt | string
 */
std::optional<string> ArraySearchExpression::checkSemantics() {
    string lhs = this->children.at(0)->checkSemantics().value_or("");
    string rhs = this->children.at(1)->checkSemantics().value_or("");
    if (lhs == "int[]" && rhs == "int") {
        return "int";
    } else if (lhs != "int[]") {
        string msg = R"([Semantic Analysis] - Error: Should be "int[]" rather than ")" + lhs + "\" in the scope \"" +
                     ArraySearchExpression::st.getScopeTitle() + "\"!";
        ArraySearchExpression::printErrMsg(msg);
    } else if (rhs != "int") {
        string msg = R"([Semantic Analysis] - Error: only "int" can be used to access array's position in scope ")" +
                     ArraySearchExpression::st.getScopeTitle() + "\"!";
        ArraySearchExpression::printErrMsg(msg);
    }

    return std::nullopt;
}
