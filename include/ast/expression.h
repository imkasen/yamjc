#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "node.h"

class Expression : public Node
{
public:
    Expression();
    Expression(std::string t, std::string v);

    std::optional<std::string> checkSemantics() override;
};

#endif