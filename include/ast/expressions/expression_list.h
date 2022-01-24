#ifndef EXPRESSION_LIST_H
#define EXPRESSION_LIST_H

#include "expression.h"

class ExpressionList : public Expression {
public:
    ExpressionList();
    ExpressionList(std::string t, std::string v);
};

#endif
