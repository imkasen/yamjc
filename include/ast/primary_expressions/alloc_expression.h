#ifndef ALLOC_EXPRESSION_H
#define ALLOC_EXPRESSION_H

#include "primary_expression.h"

class AllocExpression : public PrimaryExpression {
public:
    AllocExpression();
    AllocExpression(std::string t, std::string v);
    ~AllocExpression() override = default;
};

#endif
