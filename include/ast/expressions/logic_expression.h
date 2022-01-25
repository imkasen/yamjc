#ifndef LOGIC_EXPRESSION_H
#define LOGIC_EXPRESSION_H

#include "expression.h"

class LogicExpression : public Expression {
public:
    LogicExpression();
    LogicExpression(std::string t, std::string v);
    ~LogicExpression() override = default;
};

#endif
