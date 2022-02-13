#include "ast/primary_expressions/unary_expression.h"
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
