#include "ast/primary_expressions/array_alloc_expression.h"
using std::string;

ArrayAllocExpression::ArrayAllocExpression() : Node() {}
ArrayAllocExpression::ArrayAllocExpression(string t, string v) : Node(std::move(t), std::move(v)) {}
