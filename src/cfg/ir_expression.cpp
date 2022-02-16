#include "ir_expression.h"
using std::string;

IRExpression::IRExpression() : Tac() {}
IRExpression::IRExpression(string op, string lhs, string rhs, string result)
    : Tac(std::move(op), std::move(lhs), std::move(rhs), std::move(result)) {}