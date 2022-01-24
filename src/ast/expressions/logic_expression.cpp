#include "ast/expressions/logic_expression.h"
using std::string;

LogicExpression::LogicExpression() : Expression() {}
LogicExpression::LogicExpression(string t, string v) : Expression(std::move(t), std::move(v)) {}
