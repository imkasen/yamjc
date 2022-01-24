#ifndef ARRAY_LENGTH_EXPRESSION_H
#define ARRAY_LENGTH_EXPRESSION_H

#include "ast/node.h"

class ArrayLengthExpression : public Node {
public:
    ArrayLengthExpression();
    ArrayLengthExpression(std::string t, std::string v);
};

#endif
