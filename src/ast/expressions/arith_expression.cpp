#include "ast/expressions/arith_expression.h"
using std::string;

ArithExpression::ArithExpression() : Node() {}
ArithExpression::ArithExpression(string t, string v) : Node(std::move(t), std::move(v)) {}
