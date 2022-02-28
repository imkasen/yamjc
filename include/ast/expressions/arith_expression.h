#ifndef AST_EXPRESSIONS_ARITH_EXPRESSION_H
#define AST_EXPRESSIONS_ARITH_EXPRESSION_H

#include "cfg/ir_expression.h"
#include "expression.h"

namespace ast {

class ArithExpression : public Expression {
public:
    ArithExpression();
    ArithExpression(std::string t, std::string v);
    ~ArithExpression() override = default;

    std::optional<std::string> checkSemantics() final;
    std::optional<IRReturnVal> generateIR() final;
};

}  // namespace ast

#endif
