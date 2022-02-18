#include "ast/primary_expressions/array_alloc_expression.h"
using ast::ArrayAllocExpression;
using std::string;

/*
   "ArrayAllocExpression"
          |
      "Expression"
 */

ArrayAllocExpression::ArrayAllocExpression() : PrimaryExpression() {}
ArrayAllocExpression::ArrayAllocExpression(string t, string v) : PrimaryExpression(std::move(t), std::move(v)) {}

/*
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
