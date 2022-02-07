#include "ast/primary_expressions/primary_expression.h"
using std::string;

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
 * @brief:
 *   1. "PrimaryExpression"  or  "PrimaryExpression"
 *              |                       |
 *         "Identifier"             "Expression"
 *   2. "int:xx", "boolean:xxx", "keyword:this"
 * @return: std::nullopt || string
 */
std::optional<string> PrimaryExpression::checkSemantics() {
    // 1.
    if (this->children.size() == 1) {
        return this->children.at(0)->checkSemantics();
    }
    // 2.
    else if (this->children.empty()) {
        return this->getType();
    }
    return std::nullopt;
}
