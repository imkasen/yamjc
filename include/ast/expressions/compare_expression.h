#ifndef COMPARE_EXPRESSION_H
#define COMPARE_EXPRESSION_H

#include "expression.h"

class CompareExpression : public Expression {
public:
    CompareExpression();
    CompareExpression(std::string t, std::string v);
};

#endif
