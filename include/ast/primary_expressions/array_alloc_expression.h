#ifndef ARRAY_ALLOC_EXPRESSION_H
#define ARRAY_ALLOC_EXPRESSION_H

#include "ast/node.h"

class ArrayAllocExpression : public Node {
public:
    ArrayAllocExpression();
    ArrayAllocExpression(std::string t, std::string v);
};

#endif
