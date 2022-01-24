#include "ast/expressions/array_length_expression.h"
using std::string;

ArrayLengthExpression::ArrayLengthExpression() : Expression() {}
ArrayLengthExpression::ArrayLengthExpression(string t, string v) : Expression(std::move(t), std::move(v)) {}