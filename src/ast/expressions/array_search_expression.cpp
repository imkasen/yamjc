#include "ast/expressions/array_search_expression.h"
using std::string;

ArraySearchExpression::ArraySearchExpression() : Expression() {}
ArraySearchExpression::ArraySearchExpression(string t, string v) : Expression(std::move(t), std::move(v)) {}
