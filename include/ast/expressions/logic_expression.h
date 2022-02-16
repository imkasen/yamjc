#ifndef AST_EXPRESSIONS_LOGIC_EXPRESSION_H
#define AST_EXPRESSIONS_LOGIC_EXPRESSION_H

#include "expression.h"

class LogicExpression : public Expression {
public:
    LogicExpression();
    LogicExpression(std::string t, std::string v);
    ~LogicExpression() override = default;

    std::optional<std::string> checkSemantics() final;
};

#endif
