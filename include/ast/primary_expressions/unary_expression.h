#ifndef AST_PRIMARY_EXPRESSIONS_UNARY_EXPRESSION_H
#define AST_PRIMARY_EXPRESSIONS_UNARY_EXPRESSION_H

#include "primary_expression.h"

namespace ast {

class UnaryExpression : public PrimaryExpression {
public:
    UnaryExpression();
    UnaryExpression(std::string t, std::string v);
    ~UnaryExpression() override = default;

    std::optional<std::string> checkSemantics() final;
};

}  // namespace ast

#endif
