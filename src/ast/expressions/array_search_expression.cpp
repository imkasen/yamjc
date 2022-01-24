#include "ast/expressions/array_search_expression.h"
using std::string;

ArraySearchExpression::ArraySearchExpression() : Node() {}
ArraySearchExpression::ArraySearchExpression(string t, string v) : Node(std::move(t), std::move(v)) {}
