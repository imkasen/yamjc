#ifndef COMPARE_EXPRESSION_H
#define COMPARE_EXPRESSION_H

#include "ast/node.h"

class CompareExpression : public Node {
public:
    CompareExpression();
    CompareExpression(std::string t, std::string v);
};

#endif
