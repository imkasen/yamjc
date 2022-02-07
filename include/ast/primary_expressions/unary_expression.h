#ifndef UNARY_EXPRESSION_H
#define UNARY_EXPRESSION_H

#include "primary_expression.h"

class UnaryExpression : public PrimaryExpression {
public:
    UnaryExpression();
    UnaryExpression(std::string t, std::string v);
    ~UnaryExpression() override = default;

    std::optional<std::string> checkSemantics() final;
};

#endif
