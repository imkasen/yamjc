#ifndef STATEMENT_H
#define STATEMENT_H

#include "node.h"

class Statement : public Node
{
public:
    Statement();
    Statement(std::string t, std::string v);

    virtual std::optional<std::string> generateST() override;
};

#endif