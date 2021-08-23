#include "ast/primary_expression.h"

PrimaryExpression::PrimaryExpression() : Node() {}
PrimaryExpression::PrimaryExpression(std::string t, std::string v) : Node(std::move(t), std::move(v)) {}
