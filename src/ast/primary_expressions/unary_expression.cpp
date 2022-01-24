#include "ast/primary_expressions/unary_expression.h"
using std::string;

UnaryExpression::UnaryExpression() : PrimaryExpression() {}
UnaryExpression::UnaryExpression(string t, string v) : PrimaryExpression(std::move(t), std::move(v)) {}
