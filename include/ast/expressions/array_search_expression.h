#ifndef AST_EXPRESSIONS_ARRAY_SEARCH_EXPRESSION_H
#define AST_EXPRESSIONS_ARRAY_SEARCH_EXPRESSION_H

#include "expression.h"

class ArraySearchExpression : public Expression {
public:
    ArraySearchExpression();
    ArraySearchExpression(std::string t, std::string v);
    ~ArraySearchExpression() override = default;

    std::optional<std::string> checkSemantics() final;
};

#endif
