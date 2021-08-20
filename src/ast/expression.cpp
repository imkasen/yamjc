#include "ast/expression.h"

#include <utility>

Expression::Expression() : Node() {}
Expression::Expression(std::string t, std::string v) : Node(std::move(t), std::move(v)) {}
