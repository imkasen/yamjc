#include "unary_expression.h"
using cfg::UnaryExpression;
using std::string;

UnaryExpression::UnaryExpression() : Tac() {}
UnaryExpression::UnaryExpression(string op, string lhs, string result)
    : Tac(std::move(op), std::move(lhs), "", std::move(result)) {}
