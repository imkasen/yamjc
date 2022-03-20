#ifndef AST_EXPRESSIONS_ARITH_EXPRESSION_H
#define AST_EXPRESSIONS_ARITH_EXPRESSION_H

#include "cfg/ir_expression.h"
#include "expression.h"

namespace ast {

class ArithExpression : public Expression {
public:
    ArithExpression() = delete;
    [[maybe_unused]] ArithExpression(std::string t, std::string v);
    ~ArithExpression() override = default;

    std::optional<std::string> checkSemantics() final;
    IRReturnVal generateIR() final;
};

}  // namespace ast

#endif
