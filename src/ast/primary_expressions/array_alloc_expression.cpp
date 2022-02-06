#include "ast/primary_expressions/array_alloc_expression.h"
using std::string;

ArrayAllocExpression::ArrayAllocExpression() : PrimaryExpression() {}
ArrayAllocExpression::ArrayAllocExpression(string t, string v) : PrimaryExpression(std::move(t), std::move(v)) {}

/*
 * "ArrayAllocExpression"
 *          |
 *     "Expression"
 * @return: string
 */
std::optional<string> ArrayAllocExpression::checkSemantics() {
    string type = this->children.at(0)->checkSemantics().value_or("");
    if (type != "int") {
        string msg = R"([Semantic Analysis] - Error: Array size should be "int" in scope ")" +
                     ArrayAllocExpression::st.getScopeType() + "\"!";
        ArrayAllocExpression::printErrMsg(msg);
    }

    return "int[]";
}
