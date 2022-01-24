#include "ast/expressions/expression_list.h"
using std::string;

ExpressionList::ExpressionList() : Expression() {}
ExpressionList::ExpressionList(string t, string v) : Expression(std::move(t), std::move(v)) {}
