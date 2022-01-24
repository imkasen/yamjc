#include "ast/primary_expressions/unary_expression.h"
using std::string;

UnaryExpression::UnaryExpression() : Node() {}
UnaryExpression::UnaryExpression(string t, string v) : Node(std::move(t), std::move(v)) {}
