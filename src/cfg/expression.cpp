#include "expression.h"
using cfg::Expression;
using std::string;

Expression::Expression() : Tac() {}
Expression::Expression(string op, string lhs, string rhs, string result)
    : Tac(std::move(op), std::move(lhs), std::move(rhs), std::move(result)) {}