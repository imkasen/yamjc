#ifndef ARITH_EXPRESSION_H
#define ARITH_EXPRESSION_H

#include "ast/node.h"

class ArithExpression : public Node {
public:
    ArithExpression();
    ArithExpression(std::string t, std::string v);
};

#endif
