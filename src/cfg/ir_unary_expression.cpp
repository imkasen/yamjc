#include "ir_unary_expression.h"
using cfg::IRUnaryExpression;
using std::string;

IRUnaryExpression::IRUnaryExpression() : Tac() {}
IRUnaryExpression::IRUnaryExpression(string op, string lhs, string result)
    : Tac(std::move(op), std::move(lhs), "", std::move(result)) {}
