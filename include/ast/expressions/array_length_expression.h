#ifndef ARRAY_LENGTH_EXPRESSION_H
#define ARRAY_LENGTH_EXPRESSION_H

#include "expression.h"

class ArrayLengthExpression : public Expression {
public:
    ArrayLengthExpression();
    ArrayLengthExpression(std::string t, std::string v);
    ~ArrayLengthExpression() override = default;

    std::optional<std::string> checkSemantics() final;
};

#endif
