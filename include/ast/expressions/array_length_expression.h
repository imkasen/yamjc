#ifndef AST_EXPRESSIONS_ARRAY_LENGTH_EXPRESSION_H
#define AST_EXPRESSIONS_ARRAY_LENGTH_EXPRESSION_H

#include "expression.h"

namespace ast {

class ArrayLengthExpression : public Expression {
public:
    ArrayLengthExpression();
    ArrayLengthExpression(std::string t, std::string v);
    ~ArrayLengthExpression() override = default;

    std::optional<std::string> checkSemantics() final;
};

}  // namespace ast

#endif
