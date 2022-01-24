#include "ast/expressions/compare_expression.h"
using std::string;

CompareExpression::CompareExpression() : Expression() {}
CompareExpression::CompareExpression(string t, string v) : Expression(std::move(t), std::move(v)) {}
