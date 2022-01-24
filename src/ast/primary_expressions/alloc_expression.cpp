#include "ast/primary_expressions/alloc_expression.h"
using std::string;

AllocExpression::AllocExpression() : PrimaryExpression() {}
AllocExpression::AllocExpression(string t, string v) : PrimaryExpression(std::move(t), std::move(v)) {}
