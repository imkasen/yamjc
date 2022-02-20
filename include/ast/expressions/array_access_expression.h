#ifndef AST_EXPRESSIONS_ARRAY_ACCESS_EXPRESSION_H
#define AST_EXPRESSIONS_ARRAY_ACCESS_EXPRESSION_H

#include "expression.h"

namespace ast {

class ArrayAccessExpression : public Expression {
public:
    ArrayAccessExpression();
    ArrayAccessExpression(std::string t, std::string v);
    ~ArrayAccessExpression() override = default;

    std::optional<std::string> checkSemantics() final;
};

}  // namespace ast

#endif
