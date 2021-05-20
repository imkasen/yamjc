#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "node.h"

class Expression : public Node
{
    public:
        Expression();
        Expression(string t, string v);
};

#endif