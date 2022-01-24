#ifndef ALLOC_EXPRESSION_H
#define ALLOC_EXPRESSION_H

#include "ast/node.h"

class AllocExpression : public Node {
public:
    AllocExpression();
    AllocExpression(std::string t, std::string v);
};

#endif
