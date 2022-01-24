#include "ast/expressions/arith_expression.h"
using std::string;

ArithExpression::ArithExpression() : Expression() {}
ArithExpression::ArithExpression(string t, string v) : Expression(std::move(t), std::move(v)) {}
