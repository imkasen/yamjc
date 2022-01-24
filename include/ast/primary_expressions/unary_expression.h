#ifndef UNARY_EXPRESSION_H
#define UNARY_EXPRESSION_H

#include "ast/node.h"

class UnaryExpression : public Node {
public:
    UnaryExpression();
    UnaryExpression(std::string t, std::string v);
};

#endif
