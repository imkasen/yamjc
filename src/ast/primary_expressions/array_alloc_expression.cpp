#include "ast/primary_expressions/array_alloc_expression.h"
using std::string;

ArrayAllocExpression::ArrayAllocExpression() : PrimaryExpression() {}
ArrayAllocExpression::ArrayAllocExpression(string t, string v) : PrimaryExpression(std::move(t), std::move(v)) {}
