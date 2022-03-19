#ifndef AST_PRIMARY_EXPRESSIONS_UNARY_EXPRESSION_H
#define AST_PRIMARY_EXPRESSIONS_UNARY_EXPRESSION_H

#include "cfg/ir_unary_expression.h"
#include "primary_expression.h"

namespace ast {

class UnaryExpression : public PrimaryExpression {
public:
    UnaryExpression() = delete;
    [[maybe_unused]] UnaryExpression(std::string t, std::string v);
    ~UnaryExpression() override = default;

    std::optional<std::string> checkSemantics() final;
    std::optional<IRReturnVal> generateIR() final;
};

}  // namespace ast

#endif
