#include "ast/expressions/array_length_expression.h"
using std::string;

ArrayLengthExpression::ArrayLengthExpression() : Node() {}
ArrayLengthExpression::ArrayLengthExpression(string t, string v) : Node(std::move(t), std::move(v)) {}