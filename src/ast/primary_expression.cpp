#include "ast/primary_expression.h"

PrimaryExpression::PrimaryExpression() : Node() {}
PrimaryExpression::PrimaryExpression(std::string t, std::string v) : Node(std::move(t), std::move(v)) {}

std::optional<std::string> PrimaryExpression::checkSemantics() {
    if (this->children.size() == 1) {
        return this->children.at(0)->checkSemantics();
    }

    return std::nullopt;
}
