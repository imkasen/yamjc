#ifndef LOGIC_EXPRESSION_H
#define LOGIC_EXPRESSION_H

#include "ast/node.h"

class LogicExpression : public Node {
public:
    LogicExpression();
    LogicExpression(std::string t, std::string v);
};

#endif
