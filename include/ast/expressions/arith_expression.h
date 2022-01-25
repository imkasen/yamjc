#ifndef ARITH_EXPRESSION_H
#define ARITH_EXPRESSION_H

#include "expression.h"

class ArithExpression : public Expression {
public:
    ArithExpression();
    ArithExpression(std::string t, std::string v);
    ~ArithExpression() override = default;
};

#endif
