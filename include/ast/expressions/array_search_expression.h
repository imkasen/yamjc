#ifndef ARRAY_SEARCH_EXPRESSION_H
#define ARRAY_SEARCH_EXPRESSION_H

#include "ast/node.h"

class ArraySearchExpression : public Node {
public:
    ArraySearchExpression();
    ArraySearchExpression(std::string t, std::string v);
};

#endif
