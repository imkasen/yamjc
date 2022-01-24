#include "ast/primary_expressions/alloc_expression.h"
using std::string;

AllocExpression::AllocExpression() : Node() {}
AllocExpression::AllocExpression(string t, string v) : Node(std::move(t), std::move(v)) {}
