#ifndef AST_EXPRESSIONS_LOGIC_EXPRESSION_H
#define AST_EXPRESSIONS_LOGIC_EXPRESSION_H

#include "cfg/ir_expression.h"
#include "expression.h"

namespace ast {

class LogicExpression : public Expression {
public:
    LogicExpression();
    LogicExpression(std::string t, std::string v);
    ~LogicExpression() override = default;

    std::optional<std::string> checkSemantics() final;
    std::optional<IRReturnVal> generateIR() final;
};

}  // namespace ast

#endif
