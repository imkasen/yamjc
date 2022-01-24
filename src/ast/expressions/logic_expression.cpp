#include "ast/expressions/logic_expression.h"
using std::string;

LogicExpression::LogicExpression() : Node() {}
LogicExpression::LogicExpression(string t, string v) : Node(std::move(t), std::move(v)) {}
