#include "ast/primary_expressions/primary_expression.h"
using ast::PrimaryExpression;
using std::string;

/*
      "PrimaryExpression"  or  "PrimaryExpression"
              |                        |
          "Identifier"             "Expression"

      "int:xxx" or "boolean:xxx" or "keyword:this"
 */

PrimaryExpression::PrimaryExpression() : Node() {}
PrimaryExpression::PrimaryExpression(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * @brief: It will not be called at all, do nothing.
 * @return: std::nullopt
 */
std::optional<string> PrimaryExpression::generateST() {
    return std::nullopt;
}

/*
 * @brief: Execute when "this->type" is "PrimaryExpression"
 * @return: std::nullopt || string
 */
std::optional<string> PrimaryExpression::checkSemantics() {
    if (this->children.size() == 1) {
        return this->children.at(0)->checkSemantics();
    }

    return std::nullopt;
}
