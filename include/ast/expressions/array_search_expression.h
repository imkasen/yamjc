#ifndef ARRAY_SEARCH_EXPRESSION_H
#define ARRAY_SEARCH_EXPRESSION_H

#include "expression.h"

class ArraySearchExpression : public Expression {
public:
    ArraySearchExpression();
    ArraySearchExpression(std::string t, std::string v);
    ~ArraySearchExpression() override = default;

    std::optional<std::string> checkSemantics() final;
};

#endif
