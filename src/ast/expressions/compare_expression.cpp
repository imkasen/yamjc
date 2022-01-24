#include "ast/expressions/compare_expression.h"
using std::string;

CompareExpression::CompareExpression() : Node() {}
CompareExpression::CompareExpression(string t, string v) : Node(std::move(t), std::move(v)) {}
